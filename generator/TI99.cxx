/**
 *  Java Grinder
 *  Author: Michael Kohn
 *   Email: mike@mikekohn.net
 *     Web: http://www.mikekohn.net/
 * License: GPLv3
 *
 * Copyright 2014-2019 by Michael Kohn
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "generator/TI99.h"

// http://www.nouspikel.com/ti99/titechpages.htm

TI99::TI99() :
  need_vdp_command(false),
  need_print_string(false),
  need_clear_screen(false),
  need_plot(false),
  need_set_colors(false),
  need_set_sound_freq(false),
  need_set_sound_volume(false),
  need_set_sprite_visible(false),
  need_set_sprite_image(false),
  need_set_sprite_pos(false),
  need_set_sprite_color(false)
{
}

TI99::~TI99()
{
}

int TI99::open(const char *filename)
{
  if (TMS9900::open(filename) != 0) { return -1; }

  fprintf(out, ".include \"ti99.inc\"\n\n");
  fprintf(out, "ram_start equ RAM\n");
  fprintf(out, "heap_ptr equ ram_start\n");

  strncpy(app_name, filename, 16);
  app_name[15] = 0;

  int n;
  for (n = 0; n < 16; n++)
  {
    if (app_name[n] == '_') { app_name[n] = ' '; }
    else if (app_name[n] >= 'a' && app_name[n] <= 'z') { app_name[n] &= 0xdf; }
    else if (app_name[n] == 0) { break; }
  }

  return 0;
}

int TI99::finish()
{
  if (need_vdp_command) { insert_vdp_command(); }
  if (need_print_string) { insert_print_string(); }
  if (need_clear_screen) { insert_clear_screen(); }
  if (need_plot) { insert_plot(); }
  if (need_set_colors) { insert_set_colors(); }
  if (need_set_sound_freq) { insert_set_sound_freq(); }
  if (need_set_sound_volume) { insert_set_sound_volume(); }
  if (need_set_sprite_visible) { insert_set_sprite_visible(); }
  if (need_set_sprite_image) { insert_set_sprite_image(); }
  if (need_set_sprite_pos) { insert_set_sprite_pos(); }
  if (need_set_sprite_color) { insert_set_sprite_color(); }

  return 0;
}

int TI99::start_init()
{
  fprintf(out, "\n");
  fprintf(out, ".org 0x6000\n");

  fprintf(out, "  .db 0xaa, 0x01, 0x01, 0x00\n");
  fprintf(out, "  .dw 0x0000\n");
  fprintf(out, "  .dw _prog\n");
  fprintf(out, "  .dw 0x0000\n");
  fprintf(out, "  .dw 0x0000\n");
  fprintf(out, "  .dw 0x0000\n");
  fprintf(out, "  .dw 0x0000\n");
  fprintf(out, "_prog:\n");
  fprintf(out, "  .dw 0x0000\n");
  fprintf(out, "  .dw start\n");
  fprintf(out, "  .db %d, \"%s\"\n", (int)strlen(app_name), app_name);

  fprintf(out, ".align 16\n\n");

  // Add any set up items (stack, registers, etc).
  fprintf(out, "start:\n");

  // Sprite pattern table should start at 0x1600
  fprintf(out, "  li r0, 0x0386\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");

  return 0;
}

int TI99::ti99_print_X()
{
  need_print_string = true;

  fprintf(out, "  mov r%d, r1\n", REG_STACK(reg-1));
  fprintf(out, "  mov r11, *r10+\n");
  fprintf(out, "  bl @_print_string\n");
  fprintf(out, "  ai r10, -2\n");
  fprintf(out, "  mov *r10, r11\n");
  reg--;

  return 0;
}

int TI99::ti99_printChar_C()
{
  fprintf(out, "  swpb r%d\n", REG_STACK(reg-1));
  fprintf(out, "  movb r%d, @VDP_WRITE\n", REG_STACK(reg-1));
  reg--;

  return 0;
}

int TI99::ti99_printChar_C(int c)
{
  fprintf(out, "  li r0, 0x%02x\n", c << 8);
  fprintf(out, "  movb r0, @VDP_WRITE\n");

  return 0;
}

int TI99::ti99_setCursor_II()
{
  //mov @-24(r10), r3  ; push local_11
  //mov @-24(r10), r4  ; push local_11
  //mpy r4, r3
  //mov r4, r3

  // (REG-1 * 32) + REG-2

  // FIXME - Is this better as a function?
  fprintf(out, "  li r0, 32\n");
  fprintf(out, "  mpy r%d, r0\n", REG_STACK(reg-1));
  fprintf(out, "  a r%d, r1\n", REG_STACK(reg-2));
  fprintf(out, "  mov r1, r0\n");
  fprintf(out, "  ai r0, 0x4000\n");
  fprintf(out, "  bl @_vdp_command\n");

  reg -= 2;

  return 0;
}

int TI99::ti99_setCursor_II(int x, int y)
{
  need_vdp_command = true;
  int offset = (y * 32) + x;
  int address = offset + 0x4000;

  fprintf(out, "  li r0, 0x%02x%02x ; set write byte to %d\n",
    address & 0xff, address >> 8, offset);
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  //fprintf(out, "  bl @_vdp_command\n");

  return 0;
}

int TI99::ti99_setGraphicsMode_I()
{
  return -1;
}

int TI99::ti99_setGraphicsMode_I(int mode)
{
  need_vdp_command = true;

  // firstbyte: reg content, second byte 0x8000 | reg num

  switch(mode)
  {
    case 0:
      fprintf(out, "  li r0, 0x8000\n");
      fprintf(out, "  bl @_vdp_command\n");
      fprintf(out, "  li r0, 0x8100|0x040\n");
      fprintf(out, "  bl @_vdp_command\n");
      break;
    case 1:
      fprintf(out, "  li r0, 0x8000\n");
      fprintf(out, "  bl @_vdp_command\n");
      fprintf(out, "  li r0, 0x8110|0x40\n");
      fprintf(out, "  bl @_vdp_command\n");
      break;
    case 2:
      fprintf(out, "  li r0, 0x8000\n");
      fprintf(out, "  bl @_vdp_command\n");
      fprintf(out, "  li r0, 0x8108|0x040\n");
      fprintf(out, "  bl @_vdp_command\n");
      break;
    case 3:
      fprintf(out, "  li r0, 0x8002\n");
      fprintf(out, "  bl @_vdp_command\n");
      fprintf(out, "  li r0, 0x8100|0x040\n");
      fprintf(out, "  bl @_vdp_command\n");
      break;
    default:
      printf("Illegal graphics mode %d\n", mode);
      return -1;
  }

  return 0;
}

int TI99::ti99_clearScreen()
{
  need_clear_screen = true;

  fprintf(out, "  mov r11, *r10+\n");
  fprintf(out, "  bl @_clear_screen\n");
  fprintf(out, "  ai r10, -2\n");
  fprintf(out, "  mov *r10, r11\n");

  return 0;
}

int TI99::ti99_plot_III()
{
  need_plot = true;

  fprintf(out, "  mov r%d, r0\n", REG_STACK(reg-3));
  fprintf(out, "  mov r%d, r1\n", REG_STACK(reg-2));
  fprintf(out, "  mov r%d, r9\n", REG_STACK(reg-1));
  fprintf(out, "  mov r11, *r10+\n");
  fprintf(out, "  bl @_plot\n");
  fprintf(out, "  ai r10, -2\n");
  fprintf(out, "  mov *r10, r11\n");

  reg -= 3;

  return 0;
}

int TI99::ti99_setColors()
{
  need_set_colors = true;

  fprintf(out, "  mov r11, *r10+\n");
  fprintf(out, "  bl @_set_colors\n");
  fprintf(out, "  ai r10, -2\n");
  fprintf(out, "  mov *r10, r11\n");

  return 0;
}

int TI99::ti99_setSoundFreq_II()
{
  need_set_sound_freq = true;

  fprintf(out, "  mov r%d, r0\n", REG_STACK(reg-2));
  fprintf(out, "  mov r%d, r1\n", REG_STACK(reg-1));
  fprintf(out, "  mov r11, *r10+\n");
  fprintf(out, "  bl @_set_sound_freq\n");
  fprintf(out, "  ai r10, -2\n");
  fprintf(out, "  mov *r10, r11\n");

  reg -= 2;

  return 0;
}

int TI99::ti99_setSoundVolume_II()
{
  need_set_sound_volume = true;

  fprintf(out, "  mov r%d, r0\n", REG_STACK(reg-2));
  fprintf(out, "  mov r%d, r1\n", REG_STACK(reg-1));
  fprintf(out, "  mov r11, *r10+\n");
  fprintf(out, "  bl @_set_sound_volume\n");
  fprintf(out, "  ai r10, -2\n");
  fprintf(out, "  mov *r10, r11\n");

  reg -= 2;

  return 0;
}

int TI99::ti99_setSpriteVisible_IZ()
{
  need_set_sprite_visible = true;

  fprintf(out, "  mov r%d, r0\n", REG_STACK(reg-2));
  fprintf(out, "  mov r%d, r1\n", REG_STACK(reg-1));
  fprintf(out, "  mov r11, *r10+\n");
  fprintf(out, "  bl @_set_sprite_visible\n");
  fprintf(out, "  ai r10, -2\n");
  fprintf(out, "  mov *r10, r11\n");

  reg -= 2;

  return 0;
}

int TI99::ti99_setSpriteImage_IaB()
{
  need_set_sprite_image = true;

  if (reg < 2)
  {
    printf("Internal Error: Empty stack?\n");
    return -1;
  }

  fprintf(out, "  mov r%d, r0\n", REG_STACK(reg-2));
  fprintf(out, "  mov r%d, r1\n", REG_STACK(reg-1));
  fprintf(out, "  mov r11, *r10+\n");
  fprintf(out, "  bl @_set_sprite_image\n");
  fprintf(out, "  ai r10, -2\n");
  fprintf(out, "  mov *r10, r11\n");

  reg -= 2;

  return 0;
}

int TI99::ti99_setSpritePos_III()
{
  need_set_sprite_pos = true;

  fprintf(out, "  mov r%d, r0\n", REG_STACK(reg-3));
  fprintf(out, "  mov r%d, r1\n", REG_STACK(reg-2));
  fprintf(out, "  mov r%d, r9\n", REG_STACK(reg-1));
  fprintf(out, "  mov r11, *r10+\n");
  fprintf(out, "  bl @_set_sprite_pos\n");
  fprintf(out, "  ai r10, -2\n");
  fprintf(out, "  mov *r10, r11\n");

  reg -= 3;

  return 0;
}

int TI99::ti99_setSpriteColor_II()
{
  need_set_sprite_color = true;

  fprintf(out, "  mov r%d, r0\n", REG_STACK(reg-2));
  fprintf(out, "  mov r%d, r1\n", REG_STACK(reg-1));
  fprintf(out, "  mov r11, *r10+\n");
  fprintf(out, "  bl @_set_sprite_color\n");
  fprintf(out, "  ai r10, -2\n");
  fprintf(out, "  mov *r10, r11\n");

  reg -= 2;

  return 0;
}

int TI99::ti99_setSpriteSize_I()
{
  fprintf(out, "  sla r%d, 8\n", REG_STACK(reg-1));
  fprintf(out, "  ori r%d, 0xe081\n", REG_STACK(reg-1));
  fprintf(out, "  movb r%d, @VDP_COMMAND\n", REG_STACK(reg-1));
  fprintf(out, "  swpb r%d\n", REG_STACK(reg-1));
  fprintf(out, "  movb r%d, @VDP_COMMAND\n", REG_STACK(reg-1));

  reg -= 1;

  return 0;
}

void TI99::insert_print_string()
{
  fprintf(out, "_print_string:\n");
  fprintf(out, "  mov @-2(r1), r0\n");
  fprintf(out, "_print_string_loop:\n");
  fprintf(out, "  movb *r1+, @VDP_WRITE\n");
  fprintf(out, "  dec r0\n");
  fprintf(out, "  jne _print_string_loop\n");
  fprintf(out, "  b *r11\n\n");
}

void TI99::insert_vdp_command()
{
  fprintf(out, "_vdp_command:\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  b *r11\n\n");
}

void TI99::insert_clear_screen()
{
  fprintf(out, "_clear_screen:\n");
  fprintf(out, "  li r0, 0x0040\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  s r0, r0\n");
  fprintf(out, "  li r1, 0x300\n");
  fprintf(out, "_clear_screen_loop:\n");
  fprintf(out, "  movb r0, @VDP_WRITE\n");
  fprintf(out, "  dec r1\n");
  fprintf(out, "  jne _clear_screen_loop\n");
  fprintf(out, "  b *r11\n\n");
}

void TI99::insert_plot()
{
  fprintf(out, ";; plot(r0, r1, r9)\n");
  fprintf(out, "_plot:\n");
  fprintf(out, "  sla r1, 5\n");
  fprintf(out, "  a r1, r0\n");
  fprintf(out, "  ai r0, 0x4000\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r9\n");
  fprintf(out, "  movb r9, @VDP_WRITE\n");
  fprintf(out, "  b *r11\n\n");
}

void TI99::insert_set_colors()
{
  // Screen image is 300 bytes long (24x32) (defaults to 0x000)
  // Color table is 32 bytes long. (defaults to 0x380)
  // Character pattern table is 2048k (256 entries * 8 bytes) defaults to 0x800)
  fprintf(out, "_set_colors:\n");
  fprintf(out, "  ;; Set color table\n");
  fprintf(out, "  li r0, 0x8043\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  s r0, r0\n");
  fprintf(out, "  li r1, 32\n");
  fprintf(out, "_set_colors_loop:\n");
  fprintf(out, "  movb r0, @VDP_WRITE\n");
  fprintf(out, "  ai r0, 0x1000\n");
  fprintf(out, "  dec r1\n");
  fprintf(out, "  jne _set_colors_loop\n");
  fprintf(out, "  ;; Set pattern table\n");
  fprintf(out, "  li r0, 0x0048\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  li r0, 0xffff\n");
  fprintf(out, "  li r1, 2048\n");
  fprintf(out, "_set_patterns_loop:\n");
  fprintf(out, "  movb r0, @VDP_WRITE\n");
  fprintf(out, "  dec r1\n");
  fprintf(out, "  jne _set_patterns_loop\n");
  fprintf(out, "  b *r11\n\n");
}

void TI99::insert_set_sound_freq()
{
  fprintf(out, ";; set_sound_freq(voice=r0, freq=r1);\n");
  fprintf(out, "_set_sound_freq:\n");
  fprintf(out, "  sla r0, 13\n");
  fprintf(out, "  ori r0, 0x8000\n");
  fprintf(out, "  soc r1, r0\n");
  fprintf(out, "  movb r0, @0x8400\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @0x8400\n");
  fprintf(out, "  b *r11\n\n");
}

void TI99::insert_set_sound_volume()
{
  fprintf(out, ";; set_sound_volume(voice=r0, volume=r1);\n");
  fprintf(out, "_set_sound_volume:\n");
  fprintf(out, "  sla r0, 13\n");
  fprintf(out, "  ori r0, 0x9000\n");
  fprintf(out, "  soc r1, r0\n");
  fprintf(out, "  movb r0, @0x8400\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @0x8400\n");
  fprintf(out, "  b *r11\n\n");
}

void TI99::insert_set_sprite_visible()
{
  // Sprite attributes table is at 0x300-0x380
  fprintf(out, ";; set_sprite_visible(index=r0, visible=r1)\n");
  fprintf(out, "_set_sprite_visible:\n");
  fprintf(out, "  sla r0, 2\n");
  fprintf(out, "  sla r1, 8\n");
  fprintf(out, "  ai r0, 0x4300\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r1\n");
  fprintf(out, "  movb r1, @VDP_WRITE\n");
  fprintf(out, "  b *r11\n\n");
}

void TI99::insert_set_sprite_image()
{
  // Sprite patterns table is at 0x3a0-0x780
  fprintf(out, ";; set_sprite_image(index=r0, image=r1)\n");
  fprintf(out, "_set_sprite_image:\n");
  fprintf(out, "  mov r0, r9\n");
  fprintf(out, "  sla r0, 5\n");
  fprintf(out, "  ai r0, 0x4000|0x1800\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  mov @-2(r1), r0\n");
  fprintf(out, "_set_sprites_image_loop:\n");
  fprintf(out, "  movb *r1+, @VDP_WRITE\n");
  fprintf(out, "  dec r0\n");
  fprintf(out, "  jne _set_sprites_image_loop\n");
  // Sprite attributes table is at 0x300
  // Need to set the pattern number for this sprite
  fprintf(out, "  mov r9, r0\n");
  fprintf(out, "  sla r0, 2\n");
  fprintf(out, "  ai r0, 0x4302\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  sla r9, 2\n");
  fprintf(out, "  swpb r9\n");
  fprintf(out, "  movb r9, @VDP_WRITE\n");
  fprintf(out, "  b *r11\n\n");
}

void TI99::insert_set_sprite_pos()
{
  // Sprite attributes table is at 0x300
  fprintf(out, ";; set_sprite_pos(index=r0, x=r1, y=r9)\n");
  fprintf(out, "_set_sprite_pos:\n");
  fprintf(out, "  sla r0, 2\n");
  fprintf(out, "  ai r0, 0x4300\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r9\n");
  fprintf(out, "  swpb r1\n");
  fprintf(out, "  movb r9, @VDP_WRITE\n");
  fprintf(out, "  movb r1, @VDP_WRITE\n");
  fprintf(out, "  b *r11\n\n");
}

void TI99::insert_set_sprite_color()
{
  // Sprite attributes table is at 0x300
  fprintf(out, ";; set_sprite_color(index=r0, color=r1)\n");
  fprintf(out, "_set_sprite_color:\n");
  fprintf(out, "  sla r0, 2\n");
  fprintf(out, "  ai r0, 0x4303\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r1\n");
  fprintf(out, "  movb r1, @VDP_WRITE\n");
  fprintf(out, "  b *r11\n\n");
}



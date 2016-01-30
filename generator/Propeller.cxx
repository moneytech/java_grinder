/**
 *  Java Grinder
 *  Author: Michael Kohn
 *   Email: mike@mikekohn.net
 *     Web: http://www.mikekohn.net/
 * License: GPL
 *
 * Copyright 2014-2016 by Michael Kohn
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Propeller.h"

#define REG_STACK(a) (a)

// ABI is:

Propeller::Propeller() :
  reg(0),
  reg_max(0),
  stack(0),
  is_main(0)
{

}

Propeller::~Propeller()
{
}

int Propeller::open(const char *filename)
{
  if (Generator::open(filename) != 0) { return -1; }

  fprintf(out, ".propeller\n");

  // Set where RAM starts / ends
  //fprintf(out, "ram_start equ 0\n");
  //fprintf(out, "ram_end equ 0x8000\n");

  return 0;
}

int Propeller::start_init()
{
  // Add any set up items (stack, registers, etc).
  //fprintf(out, ".org ???\n");
  fprintf(out, "start:\n");

  return 0;
}

int Propeller::insert_static_field_define(const char *name, const char *type, int index)
{
  return -1;
}

int Propeller::init_heap(int field_count)
{
  fprintf(out, "  ;; Set up heap and static initializers\n");
  //fprintf(out, "  mov #ram_start+%d, &ram_start\n", (field_count + 1) * 2);

  return -1;
}

int Propeller::insert_field_init_boolean(char *name, int index, int value)
{

  return -1;
}

int Propeller::insert_field_init_byte(char *name, int index, int value)
{
  return insert_field_init_int(name, index, value);
}

int Propeller::insert_field_init_short(char *name, int index, int value)
{
  return insert_field_init_int(name, index, value);
}

int Propeller::insert_field_init_int(char *name, int index, int value)
{
  return -1;
}

int Propeller::insert_field_init(char *name, int index)
{
  return -1;
}

void Propeller::method_start(int local_count, int max_stack, int param_count, const char *name)
{
}

void Propeller::method_end(int local_count)
{
}

int Propeller::push_integer(int32_t n)
{
  return -1;
}

int Propeller::push_integer_local(int index)
{
  return -1;
}

int Propeller::push_ref_static(const char *name, int index)
{
  return -1;
}

int Propeller::push_ref_local(int index)
{
  return push_integer_local(index);
}

int Propeller::push_fake()
{
  return -1;
}

int Propeller::push_long(int64_t n)
{
  return -1;
}

int Propeller::push_float(float f)
{
  return -1;
}

int Propeller::push_double(double f)
{
  return -1;
}

int Propeller::push_byte(int8_t b)
{
  int32_t value = (int32_t)b;

  return push_integer(value);
}

int Propeller::push_short(int16_t s)
{
  int32_t value = (int32_t)s;

  return push_integer(value);
}

int Propeller::push_ref(char *name)
{
  // Need to move the address of name to the top of stack
  return -1;
}

int Propeller::pop_integer_local(int index)
{
  return -1;
}

int Propeller::pop_ref_local(int index)
{
  return pop_integer_local(index);
}

int Propeller::pop()
{
  return -1;
}

int Propeller::dup()
{
  return -1;
}

int Propeller::dup2()
{
  return -1;
}

int Propeller::swap()
{
  return -1;
}

int Propeller::add_integer()
{
  return -1;
}

int Propeller::add_integer(int num)
{
  return -1;
}

int Propeller::sub_integer()
{
  return -1;
}

int Propeller::sub_integer(int num)
{
  return -1;
}

int Propeller::mul_integer()
{
  return -1;
}

int Propeller::div_integer()
{
  return -1;
}

int Propeller::mod_integer()
{
  return -1;
}

int Propeller::neg_integer()
{
  return -1;
}

int Propeller::shift_left_integer()
{
  return -1;
}

int Propeller::shift_left_integer(int num)
{
  return -1;
}

int Propeller::shift_right_integer()
{
  return -1;
}

int Propeller::shift_right_integer(int num)
{
  return -1;
}

int Propeller::shift_right_uinteger()
{
  return -1;
}

int Propeller::shift_right_uinteger(int num)
{
  return -1;
}

int Propeller::and_integer()
{
  return -1;
}

int Propeller::and_integer(int num)
{
  return -1;
}

int Propeller::or_integer()
{
  return -1;
}

int Propeller::or_integer(int num)
{
  return -1;
}

int Propeller::xor_integer()
{
  return -1;
}

int Propeller::xor_integer(int num)
{
  return -1;
}

int Propeller::inc_integer(int index, int num)
{
  return -1;
}

int Propeller::integer_to_byte()
{
  return -1;
}

int Propeller::integer_to_short()
{
  return -1;
}

int Propeller::jump_cond(const char *label, int cond, int distance)
{
  return -1;
}

int Propeller::jump_cond_integer(const char *label, int cond, int distance)
{
  return -1;
}

int Propeller::return_local(int index, int local_count)
{
  return -1;
}

int Propeller::return_integer(int local_count)
{
  return -1;
}

int Propeller::return_void(int local_count)
{
  return -1;
}

int Propeller::jump(const char *name, int distance)
{
  return -1;
}

int Propeller::call(const char *name)
{
  return -1;
}

int Propeller::invoke_static_method(const char *name, int params, int is_void)
{
  return -1;
}

int Propeller::put_static(const char *name, int index)
{
  return -1;
}

int Propeller::get_static(const char *name, int index)
{
  return -1;
}

int Propeller::brk()
{
  return -1;
}

int Propeller::new_array(uint8_t type)
{
  return -1;
}

int Propeller::insert_array(const char *name, int32_t *data, int len, uint8_t type)
{
  if (type == TYPE_BYTE)
  { return insert_db(name, data, len, TYPE_INT); }
    else
  if (type == TYPE_SHORT)
  { return insert_dw(name, data, len, TYPE_INT); }
    else
  if (type == TYPE_INT)
  { return insert_dc32(name, data, len, TYPE_INT); }

  return -1;
}

int Propeller::insert_string(const char *name, uint8_t *bytes, int len)
{
  return -1;
}

int Propeller::push_array_length()
{
  return -1;
}

int Propeller::push_array_length(const char *name, int field_id)
{
  return -1;
}

int Propeller::array_read_byte()
{
  return -1;
}

int Propeller::array_read_short()
{
  return -1;
}

int Propeller::array_read_int()
{
  return -1;
}

int Propeller::array_read_byte(const char *name, int field_id)
{
  return -1;
}

int Propeller::array_read_short(const char *name, int field_id)
{
  return -1;
}

int Propeller::array_read_int(const char *name, int field_id)
{
  return -1;
}

int Propeller::array_write_byte()
{
  return -1;
}

int Propeller::array_write_short()
{
  return -1;
}

int Propeller::array_write_int()
{
  return -1;
}

int Propeller::array_write_byte(const char *name, int field_id)
{
  return -1;
}

int Propeller::array_write_short(const char *name, int field_id)
{
  return -1;
}

int Propeller::array_write_int(const char *name, int field_id)
{
  return -1;
}

int propeller_setClock_I()
{
  return -1;
}

int propeller_getCogId()
{
  return -1;
}

int propeller_stopCog_I()
{
  return -1;
}

int propeller_stopCog_I(int value)
{
  fprintf(out, "  cogstop #%d\n");
  return 0;
}



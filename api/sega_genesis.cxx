/**
 *  Java Grinder
 *  Author: Michael Kohn
 *   Email: mike@mikekohn.net
 *     Web: http://www.mikekohn.net/
 * License: GPLv3
 *
 * Copyright 2014-2018 by Michael Kohn
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "api/sega_genesis.h"

#define CHECK_FUNC(funct,sig) \
  if (strcmp(#funct#sig, method_name) == 0) \
  { \
    return generator->sega_genesis_##funct##sig(); \
  }

#define CHECK_FUNC_CONST(funct,sig) \
  if (strcmp(#funct#sig, method_name) == 0) \
  { \
    return generator->sega_genesis_##funct##sig(const_val); \
  }

#define CHECK_FUNC_CONST_2(funct,sig) \
  if (strcmp(#funct#sig, function) == 0) \
  { \
    return generator->sega_genesis_##funct##sig(const_val1, const_val2); \
  }

int sega_genesis(JavaClass *java_class, Generator *generator, const char *method_name)
{
  CHECK_FUNC(setPalettePointer,_I)
  CHECK_FUNC(setPaletteColor,_I)
  CHECK_FUNC(initBitmap,)
  CHECK_FUNC(clearBitmap,)
  CHECK_FUNC(clearPatterns,_I)
  CHECK_FUNC(plot,_III)
  CHECK_FUNC(setPlotAddress,_I)
  CHECK_FUNC(fastPlot,_IIII)
  CHECK_FUNC(inVerticalBlank,)
  CHECK_FUNC(waitVerticalBlank,)
  CHECK_FUNC(waitHorizontalBlank,)
  CHECK_FUNC(loadFonts,)
  CHECK_FUNC(clearText,)
  CHECK_FUNC(setCursor,_II)
  CHECK_FUNC(printChar,_C)
  CHECK_FUNC(print,_X)
  CHECK_FUNC(setHorizontalScrollA,_II)
  CHECK_FUNC(setHorizontalScrollB,_II)
  CHECK_FUNC(setVerticalScrollA,_I)
  CHECK_FUNC(setVerticalScrollB,_I)
  CHECK_FUNC(setHorizontalScrollModeLine,)
  CHECK_FUNC(setHorizontalScrollModeFull,)
  CHECK_FUNC(setPatternTable,_aI)
  CHECK_FUNC(setPatternTableAtIndex,_IaI)
  CHECK_FUNC(setPatternLocation,_II)
  CHECK_FUNC(putPattern,_I)
  CHECK_FUNC(setImageData,_aS)
  CHECK_FUNC(setPaletteColors,_aS)
  CHECK_FUNC(setPaletteColorsAtIndex,_IaS)
  CHECK_FUNC(setSpritePosition,_III)
  CHECK_FUNC(setSpriteConfig1,_II)
  CHECK_FUNC(setSpriteConfig2,_II)
  CHECK_FUNC(getJoypadValuePort1,)
  CHECK_FUNC(getJoypadValuePort2,)
  CHECK_FUNC(loadZ80,_aB)
  CHECK_FUNC(resetZ80,)
  CHECK_FUNC(pauseZ80,)
  CHECK_FUNC(startZ80,)

  return -1;
}

int sega_genesis(JavaClass *java_class, Generator *generator, const char *method_name, int const_val)
{
  CHECK_FUNC_CONST(setPalettePointer,_I)
  CHECK_FUNC_CONST(setPaletteColor,_I)
  CHECK_FUNC_CONST(printChar,_C)
  CHECK_FUNC_CONST(putPattern,_I)

  return -1;
}

int sega_genesis(JavaClass *java_class, Generator *generator, const char *function, int const_val1, int const_val2)
{
  CHECK_FUNC_CONST_2(setCursor,_II)

  return -1;
}


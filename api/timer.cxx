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

#include "api/timer.h"

#define CHECK_FUNC(funct,sig) \
  if (strcmp(#funct#sig, function) == 0) \
  { \
    return generator->timer_##funct##sig(); \
  }

#define CHECK_FUNC_CONST_1(funct,sig) \
  if (strcmp(#funct#sig, function) == 0) \
  { \
    return generator->timer_##funct##sig(const_val); \
  }

#define CHECK_FUNC_CONST_2(funct,sig) \
  if (strcmp(#funct#sig, function) == 0) \
  { \
    return generator->timer_##funct##sig(const_val1, const_val2); \
  }

int timer(JavaClass *java_class, Generator *generator, const char *function)
{
  CHECK_FUNC(setInterval,_II)
  CHECK_FUNC(setListener,_Z)
  CHECK_FUNC(getValue,)
  CHECK_FUNC(setValue,_I)

  return -1;
}

int timer(JavaClass *java_class, Generator *generator, const char *function, int const_val)
{
  CHECK_FUNC_CONST_1(setListener,_Z)
  CHECK_FUNC_CONST_1(setValue,_I)
  return -1;
}

int timer(JavaClass *java_class, Generator *generator, const char *function, int const_val1, int const_val2)
{
  CHECK_FUNC_CONST_2(setInterval,_II)
  return -1;
}




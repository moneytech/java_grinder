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

#include "api/uart.h"

#define CHECK_FUNC(funct,sig) \
  if (strcmp(#funct#sig, method_name) == 0) \
  { \
    return generator->uart_##funct##sig(port); \
  }

#define CHECK_FUNC_CONST(funct,sig) \
  if (strcmp(#funct#sig, method_name) == 0) \
  { \
    return generator->uart_##funct##sig(port, const_val); \
  }

int uart(JavaClass *java_class, Generator *generator, const char *method_name, int port)
{
  CHECK_FUNC(init,_I)
  CHECK_FUNC(send,_I)
  CHECK_FUNC(read,)
  CHECK_FUNC(isDataAvailable,)
  CHECK_FUNC(isSendReady,)

  return -1;
}

int uart(JavaClass *java_class, Generator *generator, const char *method_name, int port, int const_val)
{
  CHECK_FUNC_CONST(init,_I)

  return -1;
}




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
#include <stdint.h>

int16_t read_int16(FILE *in)
{
  uint32_t i;

  i = (uint32_t)getc(in) << 8;
  i |= getc(in);

  return (int16_t)i;
}

int32_t read_int32(FILE *in)
{
  uint32_t i;

  i = (uint32_t)getc(in) << 24;
  i |= (uint32_t)getc(in) << 16;
  i |= (uint32_t)getc(in) << 8;
  i |= (uint32_t)getc(in);

  return (int32_t)i;
}

int64_t read_int64(FILE *in)
{
  uint64_t i;

  i = ((uint64_t)getc(in)) << 56;
  i |= ((uint64_t)getc(in)) << 48;
  i |= ((uint64_t)getc(in)) << 40;
  i |= ((uint64_t)getc(in)) << 32;
  i |= ((uint64_t)getc(in)) << 24;
  i |= ((uint64_t)getc(in)) << 16;
  i |= ((uint64_t)getc(in)) << 8;
  i |= getc(in);

  return (int64_t)i;
}




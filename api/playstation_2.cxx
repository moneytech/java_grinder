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

#include "api/playstation_2.h"

#define CHECK_FUNC(funct,sig) \
  if (strcmp(#funct#sig, method_name) == 0) \
  { \
    return generator->playstation2_##funct##sig(); \
  }

#define CHECK_FUNC_CONST_1(funct,sig) \
  if (strcmp(#funct#sig, method_name) == 0) \
  { \
    return generator->playstation2_##funct##sig(const_val); \
  }

#define CHECK_FUNC_CONST_2(funct,sig) \
  if (strcmp(#funct#sig, method_name) == 0) \
  { \
    return generator->playstation2_##funct##sig(const_val1, const_val2); \
  }

int playstation2(JavaClass *java_class, Generator *generator, const char *method_name)
{
  CHECK_FUNC(waitVsync,)
  CHECK_FUNC(clearContext,_I)
  CHECK_FUNC(showContext,_I)
  CHECK_FUNC(vu0UploadCode, _aB)
  CHECK_FUNC(vu0UploadData, _IaB)
  CHECK_FUNC(vu0UploadData, _IaI)
  CHECK_FUNC(vu0UploadData, _IaF)
  CHECK_FUNC(vu0DownloadData, _IaB)
  CHECK_FUNC(vu0DownloadData, _IaI)
  CHECK_FUNC(vu0DownloadData, _IaF)
  CHECK_FUNC(vu0Start,)
  CHECK_FUNC(vu0Stop,)
  CHECK_FUNC(vu0IsRunning,)
  CHECK_FUNC(performanceCountEnable,_I)
  CHECK_FUNC(performanceCountDisable,)
  CHECK_FUNC(performanceCountGet,)
  CHECK_FUNC(performanceCountReset,)
  CHECK_FUNC(randomInit,_I)
  CHECK_FUNC(randomGet,)
  CHECK_FUNC(randomNext,)
  CHECK_FUNC(spuInit,)
  CHECK_FUNC(spuUploadSoundData,_aB)
  CHECK_FUNC(spuSetVolume,_II)
  CHECK_FUNC(spuSetMasterVolume,_I)
  CHECK_FUNC(spuSetPitch,_II)
  CHECK_FUNC(spuKeyOn,_I)
  CHECK_FUNC(spuKeyOff,_I)

  return -1;
}

int playstation2(JavaClass *java_class, Generator *generator, const char *method_name, int const_val)
{
  return -1;
}

int playstation2(JavaClass *java_class, Generator *generator, const char *function, int const_val1, int const_val2)
{
  return -1;
}


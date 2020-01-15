/**
 *  Java Grinder
 *  Author: Michael Kohn
 *   Email: mike@mikekohn.net
 *     Web: http://www.mikekohn.net/
 * License: GPLv3
 *
 * Copyright 2014-2018 by Michael Kohn
 *
 * SNES by Joe Davisson
 *
 */

#ifndef JAVA_GRINDER_API_SNES_API_H
#define JAVA_GRINDER_API_SNES_API_H

#include "common/JavaClass.h"
#include "generator/Generator.h"

int snes(JavaClass *java_class, Generator *generator, const char *method_name);
int snes(JavaClass *java_class, Generator *generator, const char *method_name, int const_val);
int snes(JavaClass *java_class, Generator *generator, const char *method_name, int const_val1, int const_val2);

#endif


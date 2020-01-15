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

#ifndef JAVA_GRINDER_API_ATARI_2600_H
#define JAVA_GRINDER_API_ATARI_2600_H

#include "common/JavaClass.h"
#include "generator/Generator.h"

int atari_2600(JavaClass *java_class, Generator *generator, const char *method_name);
int atari_2600(JavaClass *java_class, Generator *generator, const char *method_name, int const_val);
int atari_2600(JavaClass *java_class, Generator *generator, const char *method_name, int const_val1, int const_val2);

#endif


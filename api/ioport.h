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

#ifndef JAVA_GRINDER_API_IOPORT_H
#define JAVA_GRINDER_API_IOPORT_H

#include "common/JavaClass.h"
#include "generator/Generator.h"

int ioport(JavaClass *java_class, Generator *generator, const char *method_name, int port);
int ioport(JavaClass *java_class, Generator *generator, const char *method_name, int port, int const_val);

#endif


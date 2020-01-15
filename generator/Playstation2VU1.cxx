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

#include "generator/Playstation2.h"

void Playstation2::add_vu1_code()
{
#if 0
  fprintf(out,
    ".align 128\n"
    "vu1_start:\n"
    "  dc32 (VIF_MSCAL << 24), 0, 0, 0\n\n");
#endif

  // This is from naken_asm's samples/playstation2/rotation_vu1.asm

  fprintf(out,
  ".ps2_ee_vu1\n"
  //".org 0\n"
  ".align 128\n"
  "_rotation_vu1:\n"

  "  sub.xyzw vf29, vf29, vf29   iaddiu vi01, vi00, 4\n"
  "  nop                         iaddiu vi04, vi00, 6\n\n"

  "  ;; Setup count/vi03, vi10=do_rot_x, vi11=do_rot_y, vi12=do_rot_z\n"
  "  nop                         ilw.x vi03, 3(vi00)\n"
  "  nop                         ilw.y vi15, 3(vi00)\n"
  "  nop                         iaddiu vi13, vi00, 1\n"
  "  nop                         iand vi10, vi15, vi13\n"
  "  nop                         iaddiu vi13, vi00, 2\n"
  "  nop                         iand vi11, vi15, vi13\n"
  "  nop                         iaddiu vi13, vi00, 4\n"
  "  nop                         iand vi12, vi15, vi13\n"
  "  nop                         ilw.z vi14, 3(vi00)\n"
  "  nop                         iadd vi04, vi04, vi14\n\n"

  "  ;; Load sin / cos from the data sent from EE\n"
  "  nop                         lq.xyzw vf05, 0(vi00)\n"
  "  nop                         lq.xyzw vf06, 1(vi00)\n\n"

  "  ;; vf02 = { 0, dz, dy, dx }\n"
  "  nop                         lq.xyzw vf02, 2(vi00)\n\n"

  "  ;; Build rotation matrixes if needed\n\n"

  "  ;; Check if rotation X matrix should be made\n"
  "  nop                         ibeq vi10, vi00, skip_rot_matrix_x\n"
  "  nop                         nop\n\n"

  "  ;; Build X rotational matrix\n"
  "  ;; [ 1    0       0    ]\n"
  "  ;; [ 0  cos(r) -sin(r) ]\n"
  "  ;; [ 0  sin(r)  cos(r) ]\n"
  "  nop                         move.xyzw vf11, vf29\n"
  "  addw.x vf11, vf00, vf00w    move.xyzw vf12, vf29\n"
  "  addy.y vf12, vf00, vf05y    move.xyzw vf13, vf29\n"
  "  subx.z vf12, vf00, vf05x    nop\n"
  "  addy.z vf13, vf00, vf05y    nop\n"
  "  addx.y vf13, vf00, vf05x    nop\n\n"

  "skip_rot_matrix_x:\n\n"

  "  ;; Check if rotation Y matrix should be made\n"
  "  nop                         ibeq vi11, vi00, skip_rot_matrix_y\n"
  "  nop                         nop\n\n"

  "  ;; Build Y rotational matrix\n"
  "  ;; [  cos(r)  0   sin(r) ]\n"
  "  ;; [   0      1     0    ]\n"
  "  ;; [ -sin(r)  0   cos(r) ]\n"
  "  nop                         move.xyzw vf14, vf29\n"
  "  addw.x vf14, vf00, vf05w    move.xyzw vf15, vf29\n"
  "  addz.z vf14, vf00, vf05z    move.xyzw vf16, vf29\n"
  "  addw.y vf15, vf00, vf00w    nop\n"
  "  subz.x vf16, vf00, vf05z    nop\n"
  "  addw.z vf16, vf00, vf05w    nop\n\n"

  "skip_rot_matrix_y:\n\n"

  "  ;; Check if rotation Z matrix should be made\n"
  "  nop                         ibeq vi12, vi00, skip_rot_matrix_z\n"
  "  nop                         nop\n\n"

  "  ;; Build Z rotational matrix\n"
  "  ;; [ cos(r) -sin(r)  0 ]\n"
  "  ;; [ sin(r)  cos(r)  0 ]\n"
  "  ;; [   0       0     1 ]\n"
  "  nop                         move.xyzw vf17, vf29\n"
  "  addy.x vf17, vf00, vf06y    move.xyzw vf18, vf29\n"
  "  subx.y vf17, vf00, vf06x    move.xyzw vf19, vf29\n"
  "  addx.x vf18, vf00, vf06x    nop\n"
  "  addy.y vf18, vf00, vf06y    nop\n"
  "  addw.z vf19, vf00, vf00w    nop\n"
  "skip_rot_matrix_z:\n\n"

  "next_point:\n"
  "  ;; Load next point from data RAM.\n"
  "  nop                         lq.xyzw vf10, 0(vi04)\n\n"

  "  ;; Check if rotation X should be done\n"
  "  nop                         ibeq vi10, vi00, skip_rot_x\n"
  "  nop                         nop\n\n"

  "  ;; Multiply X rotation matrix with points\n"
  "  mul.xyzw vf30, vf11, vf10   move.xyzw vf31, vf29\n"
  "  nop                         esum P, vf30\n"
  "  nop                         waitp\n"
  "  mul.xyzw vf30, vf12, vf10   mfp.x vf31, P\n"
  "  nop                         esum P, vf30\n"
  "  nop                         waitp\n"
  "  mul.xyzw vf30, vf13, vf10   mfp.y vf31, P\n"
  "  nop                         esum P, vf30\n"
  "  nop                         waitp\n"
  "  nop                         mfp.z vf31, P\n"
  "  nop                         move.xyz vf10, vf31\n"
  "skip_rot_x:\n\n"

  "  ;; Check if rotation Y should be done\n"
  "  nop                         ibeq vi11, vi00, skip_rot_y\n"
  "  nop                         nop\n\n"

  "  ;; Multiply Y rotation matrix with points\n"
  "  mul.xyzw vf30, vf14, vf10   move.xyzw vf31, vf29\n"
  "  nop                         esum P, vf30\n"
  "  nop                         waitp\n"
  "  mul.xyzw vf30, vf15, vf10   mfp.x vf31, P\n"
  "  nop                         esum P, vf30\n"
  "  nop                         waitp\n"
  "  mul.xyzw vf30, vf16, vf10   mfp.y vf31, P\n"
  "  nop                         esum P, vf30\n"
  "  nop                         waitp\n"
  "  nop                         mfp.z vf31, P\n"
  "  nop                         move.xyz vf10, vf31\n"
  "skip_rot_y:\n\n"

  "  ;; Check if rotation Z should be done\n"
  "  nop                         ibeq vi12, vi00, skip_rot_z\n"
  "  nop                         nop\n\n"

  "  ;; Multiply Z rotation matrix with points\n"
  "  mul.xyzw vf30, vf17, vf10   move.xyzw vf31, vf29\n"
  "  nop                         esum P, vf30\n"
  "  nop                         waitp\n"
  "  mul.xyzw vf30, vf18, vf10   mfp.x vf31, P\n"
  "  nop                         esum P, vf30\n"
  "  nop                         waitp\n"
  "  mul.xyzw vf30, vf19, vf10   mfp.y vf31, P\n"
  "  nop                         esum P, vf30\n"
  "  nop                         waitp\n"
  "  nop                         mfp.z vf31, P\n"
  "  nop                         move.xyz vf10, vf31\n"
  "skip_rot_z:\n\n"

  "  ;; Transpose point by { 0, dz, 0, 0 } vector.\n"
  "  ;; Also subtract 1 from count.\n"
  "  add.z   vf10, vf10, vf02    isubiu vi03, vi03, 1\n\n"

  "  ;; Project 3D (x,y,z) to 2D (x,y)\n"
  "  ;; x = -d * (x / z)\n"
  "  ;; y = -d * (y / z)\n"
  "  ;; Going to try d as 2048.\n"
  "  nop                         iaddiu vi13, vi00, 2048\n"
  "  nop                         mfir.xy vf20, vi13\n"
  "  nop                         ercpr P, vf10z\n"
  "  nop                         waitp\n"
  "  nop                         mfp.xy vf22, P\n"
  "  itof0.xy vf20, vf20         iaddiu vi13, vi00, 4096\n"
  "  mul.xy vf10, vf10, vf20     nop\n"
  "  mul.xy vf10, vf10, vf22     mfir.z vf20, vi13\n"
  "  itof0.z vf20, vf20          nop\n"
  "  sub.z vf10, vf20, vf10      nop\n\n"

  "  ;; Transpose point by { 0, 0, dy, dx } vector.\n"
  "  add.xy vf10, vf10, vf02    nop\n\n"

  "  ;; Convert to X and Y to fixed point 12:4 and Z to just an integer.\n"
  "  ftoi4.xy vf10, vf10         nop\n"
  "  ftoi0.z  vf10, vf10         nop\n\n"

  "  ;; Save back into GIF packet.\n"
  "  nop                         sq.xyzw vf10, 0(vi04)\n\n"

  "  ;; Increment registers and finish for loop.\n"
  "  ;nop                         iaddiu vi04, vi04, 2\n"
  "  nop                         iadd vi04, vi04, vi14\n\n"

  "  nop                         ibne vi03, vi00, next_point\n"
  "  nop                         nop\n\n"

  "  ;; Send GIF packet to the GS\n"
  "  nop                         xgkick vi01\n"
  "  nop                         nop\n\n"

  "  ;; End micro program\n"
  "  nop[E]                      nop\n"
  "  nop                         nop\n"

  "_rotation_vu1_end:\n\n");

  fprintf(out, ".ps2_ee\n\n");
}


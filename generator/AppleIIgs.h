/**
 *  Java Grinder
 *  Author: Michael Kohn
 *   Email: mike@mikekohn.net
 *     Web: http://www.mikekohn.net/
 * License: GPLv3
 *
 * Copyright 2014-2019 by Michael Kohn
 *
 */

#ifndef JAVA_GRINDER_GENERATOR_APPLE_II_GS_H
#define JAVA_GRINDER_GENERATOR_APPLE_II_GS_H

#include "generator/W65816.h"

class AppleIIgs : public W65816
{
public:
  AppleIIgs();
  virtual ~AppleIIgs();

  virtual int open(const char *filename);
  virtual int finish();
  virtual int appleiigs_plotChar_IC();
  virtual int appleiigs_printChar_C();
  virtual int appleiigs_hiresEnable_I();
  virtual int appleiigs_hiresClear_I();
  virtual int appleiigs_hiresUpdate_II();
  virtual int appleiigs_hiresPlot_III();
  virtual int appleiigs_hiresLine_IIIII();
  virtual int appleiigs_hiresSpan_IIII();
  virtual int appleiigs_hiresRead_II();
  virtual int appleiigs_hiresSprite_aBIIII();
  virtual int appleiigs_hiresPalette_IaI();
  virtual int appleiigs_hiresSetRow_II();
  virtual int appleiigs_rnd();

  virtual int appleiigs_loadWaveTable_aBI();
  virtual int appleiigs_enableOscillators_I();
  virtual int appleiigs_setMasterVolume_I();
  virtual int appleiigs_setSoundVolume_II();
  virtual int appleiigs_setSoundFrequency_II();
  virtual int appleiigs_setWaveTable_III();

private:
  void insert_hires_enable();
  void insert_hires_clear();
  void insert_hires_update();
  void insert_hires_plot();
  void insert_hires_line();
  void insert_hires_span();
  void insert_hires_read();
  void insert_hires_sprite();
  void insert_hires_palette();
  void insert_hires_set_row();
  void insert_hires_calc_address();
  void insert_rnd();
  void insert_glu();

  bool need_hires_enable:1;
  bool need_hires_clear:1;
  bool need_hires_update:1;
  bool need_hires_plot:1;
  bool need_hires_line:1;
  bool need_hires_span:1;
  bool need_hires_read:1;
  bool need_hires_sprite:1;
  bool need_hires_palette:1;
  bool need_hires_set_row:1;
  bool need_rnd:1;
};

#endif


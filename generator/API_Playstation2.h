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

#ifndef JAVA_GRINDER_GENERATOR_API_PLAYSTATION2_H
#define JAVA_GRINDER_GENERATOR_API_PLAYSTATION2_H

class API_Playstation2
{
public:
  virtual int playstation2_waitVsync() { return -1; }
  virtual int playstation2_clearContext_I() { return -1; }
  virtual int playstation2_showContext_I() { return -1; }
  virtual int playstation2_vu0UploadCode_aB() { return -1; }
  virtual int playstation2_vu0UploadData_IaB() { return -1; }
  virtual int playstation2_vu0UploadData_IaI() { return -1; }
  virtual int playstation2_vu0UploadData_IaF() { return -1; }
  virtual int playstation2_vu0DownloadData_IaB() { return -1; }
  virtual int playstation2_vu0DownloadData_IaI() { return -1; }
  virtual int playstation2_vu0DownloadData_IaF() { return -1; }
  virtual int playstation2_vu0Start() { return -1; }
  virtual int playstation2_vu0Stop() { return -1; }
  virtual int playstation2_vu0IsRunning() { return -1; }
  virtual int playstation2_performanceCountEnable_I() { return -1; }
  virtual int playstation2_performanceCountDisable() { return -1; }
  virtual int playstation2_performanceCountGet() { return -1; }
  virtual int playstation2_performanceCountReset() { return -1; }
  virtual int playstation2_randomInit_I() { return -1; }
  virtual int playstation2_randomGet() { return -1; }
  virtual int playstation2_randomNext() { return -1; }
  virtual int playstation2_spuInit() { return -1; }
  virtual int playstation2_spuUploadSoundData_aB() { return -1; }
  virtual int playstation2_spuSetVolume_II() { return -1; }
  virtual int playstation2_spuSetMasterVolume_I() { return -1; }
  virtual int playstation2_spuSetPitch_II() { return -1; }
  virtual int playstation2_spuKeyOn_I() { return -1; }
  virtual int playstation2_spuKeyOff_I() { return -1; }
};

#endif


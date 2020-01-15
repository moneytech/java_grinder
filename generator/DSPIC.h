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

#ifndef JAVA_GRINDER_GENERATOR_DSPIC_H
#define JAVA_GRINDER_GENERATOR_DSPIC_H

#include "generator/Generator.h"

enum
{
  DSPIC30F3012,
  DSPIC33FJ06GS101A,
};

class DSPIC : public Generator
{
public:
  DSPIC(uint8_t chip_type);
  virtual ~DSPIC();

  virtual int open(const char *filename);
  virtual int start_init();
  virtual int insert_static_field_define(std::string &name, std::string &type, int index);
  virtual int init_heap(int field_count);
  //virtual int field_init_boolean(char *name, int index, int value);
  //virtual int field_init_byte(char *name, int index, int value);
  //virtual int field_init_short(char *name, int index, int value);
  virtual int field_init_int(std::string &name, int index, int value);
  virtual int field_init_ref(std::string &name, int index);
  virtual void method_start(int local_count, int max_stack, int param_count, std::string &name);
  virtual void method_end(int local_count);
  virtual int push_local_var_int(int index);
  virtual int push_local_var_ref(int index);
  virtual int push_ref_static(std::string &name, int index);
  virtual int push_fake();
  virtual int push_int(int32_t n);
  //virtual int push_long(int64_t n);
  //virtual int push_float(float f);
  //virtual int push_double(double f);
  virtual int push_ref(std::string &name);
  virtual int pop_local_var_int(int index);
  virtual int pop_local_var_ref(int index);
  virtual int pop();
  virtual int dup();
  virtual int dup2();
  virtual int swap();
  virtual int add_integer();
  virtual int sub_integer();
  virtual int mul_integer();
  virtual int div_integer();
  virtual int mod_integer();
  virtual int neg_integer();
  virtual int shift_left_integer();
  virtual int shift_left_integer(int count);
  virtual int shift_right_integer();
  virtual int shift_right_integer(int count);
  virtual int shift_right_uinteger();
  virtual int shift_right_uinteger(int count);
  virtual int and_integer();
  virtual int or_integer();
  virtual int xor_integer();
  virtual int inc_integer(int index, int num);
  virtual int integer_to_byte();
  virtual int integer_to_short();
  virtual int jump_cond(std::string &label, int cond, int distance);
  virtual int jump_cond_integer(std::string &label, int cond, int distance);
  virtual int ternary(int cond, int value_true, int value_false);
  virtual int ternary(int cond, int compare, int value_true, int value_false);
  virtual int return_local(int index, int local_count);
  virtual int return_integer(int local_count);
  virtual int return_void(int local_count);
  virtual int jump(std::string &name, int distance);
  virtual int call(std::string &name);
  virtual int invoke_static_method(const char *name, int params, int is_void);
  virtual int put_static(std::string &name, int index);
  virtual int get_static(std::string &name, int index);
  virtual int brk();
  virtual int new_array(uint8_t type);
  virtual int insert_array(std::string &name, int32_t *data, int len, uint8_t type);
  virtual int insert_string(std::string &name, uint8_t *bytes, int len);
  virtual int push_array_length();
  virtual int push_array_length(std::string &name, int field_id);
  virtual int array_read_byte();
  virtual int array_read_short();
  virtual int array_read_int();
  virtual int array_read_byte(std::string &name, int field_id);
  virtual int array_read_short(std::string &name, int field_id);
  virtual int array_read_int(std::string &name, int field_id);
  virtual int array_write_byte();
  virtual int array_write_short();
  virtual int array_write_int();
  virtual int array_write_byte(std::string &name, int field_id);
  virtual int array_write_short(std::string &name, int field_id);
  virtual int array_write_int(std::string &name, int field_id);
  //virtual void close();

  // GPIO functions
  virtual int ioport_setPinsAsInput_I(int port);
  virtual int ioport_setPinsAsInput_I(int port, int const_val);
  virtual int ioport_setPinsAsOutput_I(int port);
  virtual int ioport_setPinsAsOutput_I(int port, int const_val);
  virtual int ioport_setPinsValue_I(int port);
  virtual int ioport_setPinsHigh_I(int port);
  virtual int ioport_setPinsHigh_I(int port, int const_val);
  virtual int ioport_setPinsLow_I(int port);
  virtual int ioport_setPinsLow_I(int port, int const_val);
  virtual int ioport_setPinAsOutput_I(int port);
  virtual int ioport_setPinAsOutput_I(int port, int const_val);
  virtual int ioport_setPinAsInput_I(int port);
  virtual int ioport_setPinAsInput_I(int port, int const_val);
  virtual int ioport_setPinHigh_I(int port);
  virtual int ioport_setPinHigh_I(int port, int const_val);
  virtual int ioport_setPinLow_I(int port);
  virtual int ioport_setPinLow_I(int port, int const_val);
  virtual int ioport_isPinInputHigh_I(int port);
  virtual int ioport_getPortInputValue(int port);
  //virtual int ioport_setPortOutputValue_I(int port);

  // SPI functions
  virtual int spi_init_II(int port);
  virtual int spi_init_II(int port, int clock_divisor, int mode);
  virtual int spi_init16_II(int port);
  virtual int spi_init16_II(int port, int clock_divisor, int mode);
  virtual int spi_send_I(int port);
  virtual int spi_send16_I(int port);
  virtual int spi_read_I(int port);
  virtual int spi_read16_I(int port);
  virtual int spi_isDataAvailable(int port);
  virtual int spi_isBusy(int port);
  virtual int spi_disable(int port);
  virtual int spi_enable(int port);

  // CPU functions
  virtual int cpu_setClock16();
  virtual int cpu_nop();

  // Memory
  virtual int memory_read8_I();
  virtual int memory_write8_IB();
  virtual int memory_read16_I();
  virtual int memory_write16_IS();

  // DSP (dsPIC stuff)
  virtual int dsp_getA();
  virtual int dsp_getB();
  virtual int dsp_getUpperA();
  virtual int dsp_getUpperB();
  virtual int dsp_getLowerA();
  virtual int dsp_getLowerB();
  virtual int dsp_getRoundedA();
  virtual int dsp_getRoundedB();
  virtual int dsp_clearA();
  virtual int dsp_clearB();
  virtual int dsp_loadA();
  virtual int dsp_loadB();
  virtual int dsp_negA();
  virtual int dsp_negB();
  virtual int dsp_addABAndStoreInA();
  virtual int dsp_addABAndStoreInB();
  virtual int dsp_subABAndStoreInA();
  virtual int dsp_subBAAndStoreInB();
  virtual int dsp_addToA();
  virtual int dsp_addToB();
  virtual int dsp_squareToA();
  virtual int dsp_squareToB();
  virtual int dsp_mulToA();
  virtual int dsp_mulToB();
  //virtual int dsp_euclideanDistanceToA();
  //virtual int dsp_euclideanDistanceToB();
  virtual int dsp_squareAndAddToA();
  virtual int dsp_squareAndAddToB();
  virtual int dsp_mulAndAddToA();
  virtual int dsp_mulAndAddToB();
  virtual int dsp_mulAndSubFromA();
  virtual int dsp_mulAndSubFromB();
  //virtual int dsp_euclideanDistanceAndAddToA();
  //virtual int dsp_euclideanDistanceAndAddToB();
  virtual int dsp_shiftA();
  virtual int dsp_shiftB();

protected:
  virtual int get_int_size() { return 2; }

private:
  int dsp_mul(const char *instr, const char *accum);
  int dsp_square(const char *instr, const char *accum);
  int dsp_store(const char *instr, const char *accum, int shift);
  void pop_reg(char *dst);
  //void push_w0();
  int set_periph(const char *instr, const char *periph, bool reverse=false);
  int stack_alu(const char *instr);
  int stack_alu_div();
  int stack_shift(const char *instr);
  int get_pin_number(int const_val);
  int get_values_from_stack(int *value1, int *value2, int *value3);
  int get_values_from_stack(int *value1, int *value2);

  int reg;            // count number of registers are are using as stack
  int reg_max;        // size of register stack 
  int stack;          // count how many things we put on the stack
  uint8_t chip_type;
  bool is_main;
  bool need_stack_set;
  bool need_tables;
  //int flash_start;
};

#endif


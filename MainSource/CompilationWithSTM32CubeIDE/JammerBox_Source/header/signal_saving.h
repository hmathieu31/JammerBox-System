#ifndef _SIGNAL_SAVING_H_
#define _SIGNAL_SAVING_H_

#include <stdint.h>


uint8_t crk_save(uint32_t timestamp, uint8_t value);


void crk_wipe();


uint8_t cam_save(uint32_t timestamp, uint8_t value);


void cam_wipe();


void print_signals();


int crk_get_size();


int cam_get_size();


uint8_t *crk_get_array();


uint8_t *cam_get_array();

#endif
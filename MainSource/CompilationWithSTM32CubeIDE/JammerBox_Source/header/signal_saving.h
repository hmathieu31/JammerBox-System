/**
 ******************************************************************************
 * @file    	  signal_saving.h
 * @brief   	  Module handling the saving of input signals CAM and CRK
 * 				  Project name	: STM32-Jammerbox
 * 				  Controller	: STM32F103RB
 * @date		  May 30, 2022
 ******************************************************************************
 * @attention
 *
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

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

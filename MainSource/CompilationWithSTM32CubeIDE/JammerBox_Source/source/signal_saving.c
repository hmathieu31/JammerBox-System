/**
 ******************************************************************************
 * @file    	  signal_saving.c
 * @brief   	  Module implementing the saving of input signals CAM and CRK.
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

#include "../../JammerBox_Source/header/signal_saving.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define CRK_MAX_SIZE 60000
#define CAM_MAX_SIZE 40000

uint8_t *crk_array;
int crk_index = 0;
uint8_t *cam_array;
int cam_index = 0;


uint32_t digit_array_to_timestamp(const uint8_t *array) {
    return (array[0] << 24) | (array[1] << 16) | (array[2] << 8) | array[3];
}

void print_signal(uint8_t *array, int size) {
    for (int i = 0; i < size; i += 5) {
        printf("%u, ", array[i]);
        printf("%u, ", digit_array_to_timestamp(array + i + 1));
    }
    printf("\n");
}

/**
 * @brief Prints each signal on two seperate lines in reverse order
 * First line for the values
 * Second line for the timestamps
*/
void print_signals() {
    printf("---CRK---\n");
    print_signal(crk_array, crk_index);
    printf("\n---CAM---\n");
    print_signal(cam_array, cam_index);
}

void timestamp_to_digit_array(uint32_t timestamp, uint8_t *array) {
    array[3] = timestamp & 0xffU;
    array[2] = (timestamp & 0xff00U) >> 8;
    array[1] = (timestamp & 0xff0000U) >> 16;
    array[0] = (timestamp & 0xff000000U) >> 24;
}

/**
 * @brief Saves the CRK signal value recorded at the specified timestamp
 * @param timestamp: Timestamp of the captured value (in µs)
 * @param signal: The signal value
 * @retval 0 if the array is not full, 1 if the array is full, after saving the given signal
*/
uint8_t crk_save(uint32_t timestamp, uint8_t value) {
    if (crk_array == NULL) {
        crk_array = malloc(sizeof(uint8_t) * CRK_MAX_SIZE); // 60 KB array for CRK signal
    } else if (crk_index >= CRK_MAX_SIZE) {
        return 1;
    }

    crk_array[crk_index] = value;
    timestamp_to_digit_array(timestamp, crk_array + crk_index + 1);

    crk_index += 5;
    if (crk_index >= CRK_MAX_SIZE) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Saves the CAM signal value recorded at the specified timestamp
 * @param timestamp: Timestamp of the captured value (in µs)
 * @param signal: The signal value
 * @retval 0 if the array is not full, 1 if the array is full, after saving the given signal
*/
uint8_t cam_save(uint32_t timestamp, uint8_t value) {
    if (cam_array == NULL) {
        cam_array = malloc(sizeof(uint8_t) * CAM_MAX_SIZE); // 40 KB array for CAM signal
    } else if (cam_index >= CAM_MAX_SIZE) {
        return 1;
    }

    cam_array[cam_index] = value;
    timestamp_to_digit_array(timestamp, cam_array + cam_index + 1);

    cam_index += 5;
    if (cam_index >= CAM_MAX_SIZE) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Wipes all the saved CRK signals
 * Also wipes the usart CRK buffer
*/
void crk_wipe() {
    free(crk_array);
    crk_array = NULL;
    crk_index = 0;
}

/**
 * @brief Wipes all the saved CAM signals
 * Also wipes the usart CAM buffer
*/
void cam_wipe() {
    free(cam_array);
    cam_array = NULL;
    cam_index = 0;
}

/**
 * @retval The number of 8 byte values stored in the CRK array
*/
int crk_get_size() {
    return crk_index;
}

/**
 * @retval The number of 8 byte values stored in the CAM array
*/
int cam_get_size() {
    return cam_index;
}

/**
 * @brief If we received a 1 at timestamp 2484285499, it is stored as such:
 * {1, byte3, byte2, byte1, byte0}
 * byte3 is the MSB of the timestamp and byte0 is the LSB, the timestamp being a 4 byte value
 * @retval The array containing the recorded CRK signals
*/
uint8_t *crk_get_array() {
    return crk_array;
}

/**
 * @brief If we received a 1 at timestamp 2484285499, it is stored as such:
 * {1, byte3, byte2, byte1, byte0}
 * byte3 is the MSB of the timestamp and byte0 is the LSB, the timestamp being a 4 byte value
 * @retval The array containing the recorded CAM signals
*/
uint8_t *cam_get_array() {
    return cam_array;
}

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

uint8_t CRK_save(uint32_t timestamp, uint8_t value) {
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

uint8_t CAM_save(uint32_t timestamp, uint8_t value) {
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

void CRK_wipe() {
    free(crk_array);
    crk_array = NULL;
    crk_index = 0;
}

void CAM_wipe() {
    free(cam_array);
    cam_array = NULL;
    cam_index = 0;
}

int CRK_get_size() {
    return crk_index;
}

int CAM_get_size() {
    return cam_index;
}

uint8_t *CRK_get_array() {
    return crk_array;
}

uint8_t *CAM_get_array() {
    return cam_array;
}
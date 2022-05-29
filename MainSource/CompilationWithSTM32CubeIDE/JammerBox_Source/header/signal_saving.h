#ifndef _SIGNAL_SAVING_H_
#define _SIGNAL_SAVING_H_

#include <stdint.h>

/*
 * @brief Saves the CRK signal value recorded at the specified timestamp
 * @param timestamp: Timestamp of the captured value (in µs)
 * @param signal: The signal value
 * @retval 0 if the array is not full, 1 if the array is full, after saving the given signal
*/
uint8_t crk_save(uint32_t timestamp, uint8_t value);

/*
 * @brief Wipes all the saved CRK signals
 * Also wipes the usart CRK buffer
*/
void crk_wipe();

/*
 * @brief Saves the CAM signal value recorded at the specified timestamp
 * @param timestamp: Timestamp of the captured value (in µs)
 * @param signal: The signal value
 * @retval 0 if the array is not full, 1 if the array is full, after saving the given signal
*/
uint8_t cam_save(uint32_t timestamp, uint8_t value);

/*
 * @brief Wipes all the saved CAM signals
 * Also wipes the usart CAM buffer
*/
void cam_wipe();

/*
 * @brief Prints each signal on two seperate lines in reverse order
 * First line for the values
 * Second line for the timestamps
*/
void print_signals();

/*
 * @retval The number of 8 byte values stored in the CRK array
*/
int crk_get_size();

/*
 * @retval The number of 8 byte values stored in the CAM array
*/
int cam_get_size();

/*
 * @brief If we received a 1 at timestamp 2484285499, it is stored as such:
 * {1, byte3, byte2, byte1, byte0}
 * byte3 is the MSB of the timestamp and byte0 is the LSB, the timestamp being a 4 byte value
 * @retval The array containing the recorded CRK signals
*/
uint8_t *crk_get_array();

/*
 * @brief If we received a 1 at timestamp 2484285499, it is stored as such:
 * {1, byte3, byte2, byte1, byte0}
 * byte3 is the MSB of the timestamp and byte0 is the LSB, the timestamp being a 4 byte value
 * @retval The array containing the recorded CAM signals
*/
uint8_t *cam_get_array();

#endif
/*********************************************************************
 * \file   interrupt_configuration.h                                 *
 * \brief  Configuration of the interrupts used						 *
 *                                                                   *
 * \author Hugo Mathieu                                              *
 * \date   May 2022													 *
 ********************************************************************/

#ifndef INTERRUPT_CONFIG
#define INTERRUPT_CONFIG

// ### Hardware specific includes ###
#include "misc.h"

// ### Functions ###

/** \brief Initialize the interrupt configuration
 *
 * This function enables the interrupt for timer1 in the NVIC
 *
 * \return void
 */
void interrupt_enable_timer1(void);

/** \brief Initialize the interrupt configuration
 *
 * This function enables the interrupt for timer2 in the NVIC
 *
 * \return void
 */
void interrupt_enable_timer2(void);

/** \brief Initialize the interrupt configuration
 *
 * This function enables the interrupt for timer3 in the NVIC
 *
 * \return void
 */
void interrupt_enable_timer3(void);

/** \brief Initialize the interrupt configuration
 *
 * This function enables the interrupt for timer4 in the NVIC
 *
 * \return void
 */
void interrupt_enable_timer4(void);

#endif /* INTERRUPT_CONFIG */
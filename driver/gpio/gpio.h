/******************************************************************************
*@file    motor.h
*@brief   example of led operation
*
*  ---------------------------------------------------------------------------
*
*  Copyright (c) 2018 Quectel Technologies, Inc.
*  All Rights Reserved.
*  Confidential and Proprietary - Quectel Technologies, Inc.
*  ---------------------------------------------------------------------------
*******************************************************************************/
#ifndef __GPIO_H__
#define __GPIO_H__

#include "quectel_gpio.h"

#define GPIO_RED PIN_E_GPIO_21		//D9
 
#define GPIO_BLUE PIN_E_GPIO_06		//D2

#define GPIO_GREEN PIN_E_GPIO_05	//D3

#define GPIO_MOTOR  PIN_E_GPIO_09   //motor

void led_gpio_config();
void motor_gpio_config();
void gpio_config(MODULE_PIN_ENUM m_pin,qapi_GPIO_Direction_t gpio_dir,qapi_GPIO_Pull_t gpio_pull,qapi_GPIO_Drive_t gpio_drive);
void gpio_high_low(bool on, uint8_t pin_gpio);

#endif

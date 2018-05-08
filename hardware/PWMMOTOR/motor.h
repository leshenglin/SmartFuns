/* Copyright (C) 
* 2018 - BeckOS
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
* 
*/
/**
* @file motor.h
* @Synopsis  对pwm电机的抽象和封装
* @author BeckOS
* @version V1.1.0
* @date 2018-05-08
*/


#ifndef MOTOR_H__
#define MOTOR_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f10x.h"

#define MOTORPINPWM				GPIO_Pin_5
#define MOTORPINENABLE			GPIO_Pin_6
#define MOTORPINDIRECTION		GPIO_Pin_7


typedef enum{
	ACW = 0,
	CCW = 1
}FANDIRECT;

typedef enum{
	ENABLEMOTOR = 0,
	DISABLEMOTOR = 1
}FANENABLE;

typedef struct{
	void (*init) ( u16 pinPwm, u16 pinEnable, u16 pinDirection );
	void (*enable) ( FANENABLE en );
	void (*setDirection) ( FANDIRECT direct );
	void (*setSpeed) ( u8 speed );
}Motor;

extern Motor PwmMotor;
void pwmMotorInit( void );


#ifdef __cplusplus
}
#endif
#endif //MOTOR_H__

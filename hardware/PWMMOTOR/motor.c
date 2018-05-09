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
* @file motor.c
* @Synopsis  对PWM电机的接口函数的实现
* @author BeckOS
* @version V1.1.0
* @date 2018-05-08
*/


#include "motor.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"


#define    MAXDUTY 	899


/* --------------------------------------------------------------------------*/
/**
* @Synopsis  对Pwm的引脚GPIO初始化
*
* @Param pin Pwm对应的引脚
*/
/* ----------------------------------------------------------------------------*/
static void pwmGpioInit( u16 pin )
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = pin;  //TIM_CH2  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
}

/* --------------------------------------------------------------------------*/
/**
* @Synopsis  对Pwm的引脚Time功能初始化,包括周期和分频,PB5 对应的Time3 
*
* @Param arr 设置在自动重装载周期值,72000/900=8Khz
* @Param psc 设置预分频值 不分频
*/
/* --------------------------------------------------------------------------*/
static void pwmTimeInit( u16 arr, u16 psc )
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  

	TIM_TimeBaseStructure.TIM_Period = arr;  
	TIM_TimeBaseStructure.TIM_Prescaler = psc;  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim  
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM 向上计数模式  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
}

/* --------------------------------------------------------------------------*/
/**
* @Synopsis  PWM输出使能
*/
/* ----------------------------------------------------------------------------*/
static void pwmOutEnable( void )
{
	TIM_Cmd(TIM3, ENABLE); 
}

/* --------------------------------------------------------------------------*/
/**
* @Synopsis  PWM输出禁止
*/
/* ----------------------------------------------------------------------------*/
static void pwmOutDisable( void )
{
	TIM_Cmd(TIM3, DISABLE); 
}

/* --------------------------------------------------------------------------*/
/**
* @Synopsis  Pwm 模式初始化
*/
static void pwmOCInit( void )
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择 PWM 模式 2  
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能  
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性高  
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //④初始化外设 TIM3 OC2  
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能预装载寄存器  
}

/* --------------------------------------------------------------------------*/
/**
* @Synopsis  设置PWM频率
*
* @Param fre 设置的频率
*/
/* ----------------------------------------------------------------------------*/
static void pwmSetFre( u16 fre )
{
	TIM_PrescalerConfig(TIM3, fre, TIM_PSCReloadMode_Immediate);	
}

/* --------------------------------------------------------------------------*/
/**
* @Synopsis  设置PWM占空比
*
* @Param num 占空比的数值
*/
/* ----------------------------------------------------------------------------*/
static void pwmSetDuty( u16 num )
{
	TIM_SetCompare2( TIM3, num );
}
/* --------------------------------------------------------------------------*/
/**
* @Synopsis  对Pwm的引脚Pwm功能初始化,主要是time部分的初始化，还有重映射功能
*
* @Param pin Pwm对应的引脚
*/
/* ----------------------------------------------------------------------------*/
static void pwmInit( u16 pin )
{
	pwmGpioInit( pin );
	pwmTimeInit( MAXDUTY, 0 );
	pwmOCInit( );
}

/* --------------------------------------------------------------------------*/
/**
* @Synopsis  对Enable引脚的GPIO初始化
*
* @Param pin Enable对应的引脚
*/
/* ----------------------------------------------------------------------------*/
static void pinEnableGpioInit( u16 pin )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //Only support the GPIOF as OutPut
	GPIO_InitStructure.GPIO_Pin = pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//GPIO_ResetBits(GPIOB, pin );
	GPIO_SetBits(GPIOB, pin );
}

/* --------------------------------------------------------------------------*/
/**
* @Synopsis  对Direction方向引脚的初始化
*
* @Param pin Direction对应的引脚
*/
/* ----------------------------------------------------------------------------*/
static void pinDirectionGpioInit( u16 pin )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //Only support the GPIOF as OutPut
	GPIO_InitStructure.GPIO_Pin = pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//GPIO_ResetBits(GPIOB, pin );
	GPIO_SetBits(GPIOB, pin );
}


/* --------------------------------------------------------------------------*/
/**
* @Synopsis  电机使能或者失能
*
* @Param en ENABLEMOTOR 或者　DISABLEMOTOR
*/
/* ----------------------------------------------------------------------------*/
static void motorEnable( FANENABLE en )
{
	if( ENABLEMOTOR == en )
		GPIO_ResetBits(GPIOB, MOTORPINENABLE );
	else if( DISABLEMOTOR == en )
		GPIO_SetBits(GPIOB, MOTORPINENABLE );
}

/* --------------------------------------------------------------------------*/
/**
* @Synopsis  设置电机旋转的方向
*
* @Param direct ACW-逆时针选择　CCW-顺时针选择
*/
/* ----------------------------------------------------------------------------*/
static void motorSetDirection( FANDIRECT direct )
{
	if( ACW == direct )
		GPIO_ResetBits(GPIOB, MOTORPINDIRECTION );
	if( CCW == direct )
		GPIO_SetBits(GPIOB, MOTORPINDIRECTION );
}

/* --------------------------------------------------------------------------*/
/**
* @Synopsis  电机设置转速，百分比，因为不同的电压下转速不一样
*
* @Param speed  范围0-100，用百分比表示转速
*/
/* ----------------------------------------------------------------------------*/
static void motorSetSpeed ( u8 speed )
{
	u32 tmp = speed;
	tmp = tmp*MAXDUTY/100;
	pwmSetDuty( (u16) tmp);
}

/* --------------------------------------------------------------------------*/
/**
* @Synopsis  对motor电机的抽象类初始化，包括引脚和PWM功能
*
* @Param pinPwm 对应的Pwm引脚
* @Param pinEnable 对应的Enable引脚
* @Param pinDirection 对应的Direction引脚
*/
/* ----------------------------------------------------------------------------*/
static void motorInit( u16 pinPwm, u16 pinEnable, u16 pinDirection )
{
	pwmInit( pinPwm );
	pinEnableGpioInit( pinEnable );
	pinDirectionGpioInit( pinDirection );
	
	motorEnable( DISABLEMOTOR );
	motorSetDirection( ACW );
	motorSetSpeed( 0 );
}

/* --------------------------------------------------------------------------*/
/**
* @Synopsis  电机启动
*/
/* ----------------------------------------------------------------------------*/
static void motorStart( void )
{
	motorEnable( ENABLEMOTOR );
	pwmOutEnable( );
}

/* --------------------------------------------------------------------------*/
/**
* @Synopsis  电机停止
*/
/* ----------------------------------------------------------------------------*/
static void motorStop( void )
{
	motorEnable( DISABLEMOTOR );
	pwmOutDisable( );
}

/* --------------------------------------------------------------------------*/
/**
* @Synopsis  实例化一个PWM 电机
* 电压：DC12V        电流：0.45 A           转速：1800 转
* 电压：DC15V        电流：0.68 A           转速：2800 转
* 电压：DC18V        电流：0.8 A           转速：4000 转
* 电压：DC24V        电流：1  A                转速：7000 转
*/
/* ----------------------------------------------------------------------------*/
Motor PwmMotor;

/* --------------------------------------------------------------------------*/
/**
* @Synopsis  对实例化的PwmMotor 初始化
*/
/* ----------------------------------------------------------------------------*/
void pwmMotorInit( void )
{
	PwmMotor.init = motorInit;
	PwmMotor.enable = motorEnable;
	PwmMotor.setDirection = motorSetDirection;
	PwmMotor.setSpeed = motorSetSpeed;
	PwmMotor.start = motorStart;
	PwmMotor.stop = motorStop;
	PwmMotor.init( MOTORPINPWM, MOTORPINENABLE, MOTORPINDIRECTION );
}



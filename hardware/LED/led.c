#include "led.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_flash.h"
#include "delay.h"
#include "usart.h"

#if 0
static void LedInit( LED* led );
static void LedOn( LED* led );
static void LedOff( LED* led );
static void SetValue( LED* led, u8 value );
static u8 GetLedStatus( LED* led );
static void LedBlink( LED*led, u16 time );
static void LedRollBack( LED* led );
#endif


static void ledInit( LED* led )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //Only support the GPIOF as OutPut
	GPIO_InitStructure.GPIO_Pin = led->pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOD, led->pin );
}

static void setValue( LED* led, u8 value )
{
	if(value == LedStatus_ON)
		GPIO_ResetBits( GPIOD, led->pin );
	else if( value == LedStatus_OFF )
		GPIO_SetBits( GPIOD, led->pin );
}

static u8 getLedStatus( LED* led )
{
	return GPIO_ReadOutputDataBit( GPIOD, led->pin );
}

static void ledOn( LED* led )
{
	led->SetValue( led, LedStatus_ON );
}

static void ledOff( LED* led )
{
	led->SetValue( led, LedStatus_OFF );
}

static void ledBlink( LED* led, u16 time )
{
	led->LedON( led );
	delay_ms( time );
	led->LedOFF( led );
	delay_ms( time );
}

static void ledRollBack( LED* led )
{
	(led->GetLedStatus(led) == LedStatus_ON) ? led->LedOFF(led) : led->LedON(led);
}


LED LedRed;
LED LedGreen;

void LED_Init( void )
{
	LedRed.pin = LEDRED;
    LedRed.LedInit = ledInit;
    LedRed.LedON = ledOn;
    LedRed.LedOFF = ledOff;
    LedRed.SetValue = setValue;
    LedRed.GetLedStatus = getLedStatus;
    LedRed.LedBlink = ledBlink;
    LedRed.LedRollBack = ledRollBack;
	LedRed.LedInit( &LedRed );

	LedGreen.pin = LEDGREEN;
    LedGreen.LedInit = ledInit;
    LedGreen.LedON = ledOn;
    LedGreen.LedOFF = ledOff;
    LedGreen.SetValue = setValue;
    LedGreen.GetLedStatus = getLedStatus;
    LedGreen.LedBlink = ledBlink;
    LedGreen.LedRollBack = ledRollBack;
	LedGreen.LedInit( &LedGreen );
}



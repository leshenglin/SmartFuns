#include "hardwareinit.h"
//#include "led.h"
//#include "usart.h"
#include "delay.h"

#if 0
void LED_Init( void )
{

	LedRed.pin = LEDRED;
    LedRed.LedInit = LedInit;
    LedRed.LedON = LedOn;
    LedRed.LedOFF = LedOff;
    LedRed.SetValue = SetValue;
    LedRed.GetLedStatus = GetLedStatus;
    LedRed.LedBlink = LedBlink;
    LedRed.LedRollBack = LedRollBack;
	LedRed.LedInit( &LedRed );

	LedGreen.pin = LEDGREEN;
    LedGreen.LedInit = LedInit;
    LedGreen.LedON = LedOn;
    LedGreen.LedOFF = LedOff;
    LedGreen.SetValue = SetValue;
    LedGreen.GetLedStatus = GetLedStatus;
    LedGreen.LedBlink = LedBlink;
    LedGreen.LedRollBack = LedRollBack;
	LedGreen.LedInit( &LedGreen );
}

void BEEP_INIT( void )
{
	Beep.BeepInit = BeepInit ;
	Beep.BeepOn = BeepOn ;
	Beep.BeepOff = BeepOff ;
	Beep.BeepOnHzTime = BeepOnHzTime ;
	Beep.PlayMusic = PlayMusic ;

	Beep.BeepInit( );
}
#endif


void HardInit( void )
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init( 168 );
//	uart_init( 115200 );

//	LED_Init( );

}


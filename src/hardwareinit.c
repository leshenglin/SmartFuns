#include "hardwareinit.h"
#include "led.h"
//#include "usart.h"
#include "delay.h"
#include "motor.h"


#if 0
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
	delay_init( 72 );
//	uart_init( 115200 );

	LED_Init( );
	pwmMotorInit( );

}


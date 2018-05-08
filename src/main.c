#include "stm32f10x.h"
#include "hardwareinit.h"
#include "led.h"
#include "motor.h"

static void delayGuo( int num )
{
	for(int x=0; x<1000; x++ )
		for( int j=0; j<5000; j++ );
}

int main(int argc, char *argv[])
{
	u8 speed = 0;
	HardInit( );

	while(1)
	{
		//LedBlink( &LedGreen, 500 );
		//LedRollBack( &LedGreen );
		LedGreen.LedRollBack( &LedGreen );
		delay_ms(500);
		PwmMotor.enable( ENABLEMOTOR );
		PwmMotor.setSpeed( (speed++)%100 );
	}
}


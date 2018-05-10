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
	u8 tmp = 0;
	HardInit( );

	PwmMotor.start( );

	while(1)
	{
		LedGreen.LedRollBack( &LedGreen );
		delay_ms(500);
		speed = tmp?speed-1:speed+1;
		if(speed>97)
			tmp = 1;
		if(speed<2)
			tmp = 0;
		PwmMotor.setSpeed( (speed)%100 );

	}
}


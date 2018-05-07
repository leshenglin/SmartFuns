#include "stm32f10x.h"
#include "hardwareinit.h"
#include "led.h"

static void delayGuo( int num )
{
	for(int x=0; x<1000; x++ )
		for( int j=0; j<5000; j++ );
}

int main(int argc, char *argv[])
{
	HardInit( );

	while(1)
	{
		//LedBlink( &LedGreen, 500 );
		LedRollBack( &LedGreen );
		delay_ms(1000);

	}
}


#include "stm32f10x.h"
#include "hardwareinit.h"
//#include "led.h"


int main(int argc, char *argv[])
{
	u16 x = 0;
	u16 y = 790;

	HardInit( );


	while(1)
	{
		delay_ms(1000);
	}
}


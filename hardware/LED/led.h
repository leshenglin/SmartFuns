#ifndef  __LED_H__
#define  __LED_H__

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


//void LED_Init( void );


//#define LedRed    GPIO_Pin_9
//#define LedGreen  GPIO_Pin_10
#define LEDRED    GPIO_Pin_8
#define LEDGREEN  GPIO_Pin_9


#define LedStatus_ON   0
#define LedStatus_OFF  1

typedef struct _LED LED;




#if 1	
typedef struct _LED{
	u16  pin;
	void (*LedInit) ( LED* );
	void (*LedON) ( LED* );
	void (*LedOFF) ( LED* );
	void (*SetValue) ( LED*, u8 );
    u8   (*GetLedStatus) ( LED* );
	void (*LedBlink) ( LED*, u16 );
	void (*LedRollBack) ( LED* );
	
}LED;
#endif	

extern LED LedRed;
extern LED LedGreen;

void LED_Init( void );


#endif

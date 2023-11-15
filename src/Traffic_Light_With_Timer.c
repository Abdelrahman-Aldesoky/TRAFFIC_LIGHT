/*
 * main.c
 *
 *  Created on: Sep 8, 2023
 *      Author: Abdelrahman Mohamed
 */

#include "../inc/STD_TYPES.h"
#include "../inc/BIT_MATH.h"
#include "../lib/CLCD_interface.h"
#include "../lib/TIMER0_interface.h"
#include "../lib/TL_TIMER_interface.h"

/*Not a clean code by any means no comments and not a structured code
 * didn't fully edit the other .h files just making it work
 * TIMER ISR contains for loops for doing LCD custom chars its just a slow ISR
 * would have been much better project without the LCD
 * when i tried putting my LCD code in the main while(1) loop
 * i couldn't sync the time displayed in LCD correctly with my timer for the 7SEG which is written in the Timer ISR*/
int main(void)
{
	TL_voidInit();

	/*LEFT half of LCD is displayed for cars
	 *Right half of LCD is displayed for Pedestrians
	 Timer 0 callback function*/
	TIMER0_voidSetCallBack(TL_voidTrafficLight);

	CLCD_voidSendCommand(DISPLAY_CLEAR);
	CLCD_voidSendString(" TRAFFIC LIGHT! ");
	CLCD_voidSetPostion(SECOND_LINE, 0);
	CLCD_voidSendString("   INACCURATE   ");

	while (1)
	{
	}
	return 0;
}

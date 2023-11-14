/****************TL_TIMER Program****************/
/**********Author: Abdelrahman Mohamed.**********/
/********************Ver.: 01********************/
/****************Date:08/09/2023.****************/
/************************************************/

#include "../inc/STD_TYPES.h"
#include "../inc/BIT_MATH.h"
#include "DIO_interface.h"
#include "GIE_interface.h"
#include "TIMER0_interface.h"
#include "CLCD_interface.h"
#include "SSD_interface.h"
#include "TL_TIMER_interface.h"
#include "TL_TIMER_private.h"
#include "TL_TIMER_config.h"


void TL_voidInit(void)
{
	GIE_voidEnable();
	TIMER0_voidInit();
	SSD_voidInit();
	CLCD_voidInit();
	DIO_voidSetPinDirection(LED_PORT, RED_PIN, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(LED_PORT, YELLOW_PIN, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(LED_PORT, GREEN_PIN, PIN_DIRECTION_OUTPUT);
}

void TL_voidTrafficLight(void)
{
	static u8 Local_u8TimeInSeconds=0;
	static u16 Local_s8CountDown=RED_TIME+YELLOW_TIME+GREEN_TIME;
	Local_u8TimeInSeconds++;

	/*Stolen from the Internet with minor modifications
	 *Credit to YouTube channel: Teach Me Something
	 *Link: https://www.youtube.com/@TeachMeSomething*/
	u8 Local_u8CustomMan[][8] =
	{
			{0b00001,0b00001,0b00011,0b00011,0b00011,0b00001,0b00000,0b00001},
			{0b11111,0b11111,0b11101,0b11101,0b11111,0b11111,0b11111,0b11111},
			{0b00000,0b10000,0b11000,0b00000,0b11000,0b11100,0b11000,0b10000},
			{0b00011,0b00111,0b00111,0b00111,0b00111,0b00001,0b00011,0b00111},
			{0b11111,0b11111,0b11111,0b11111,0b11111,0b11011,0b10001,0b10001},
			{0b11000,0b11100,0b11100,0b11100,0b11100,0b10000,0b11000,0b11100}
	};

	/*Made by me and its ugly xD "car in lcd custom chars"*/
	u8 Local_u8CustomCar[][8] =
	{
			{0b00000,0b00000,0b00000,0b11111,0b01111,0b11111,0b01111,0b00000},
			{0b00001,0b00001,0b00001,0b11111,0b11111,0b11111,0b10001,0b10101},
			{0b11111,0b10001,0b10001,0b11111,0b10111,0b11111,0b11111,0b00000},
			{0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b00000},
			{0b11111,0b10001,0b10001,0b11111,0b10111,0b11111,0b11111,0b00000},
			{0b10000,0b10000,0b11100,0b11111,0b11111,0b11111,0b10001,0b10101},
			{0b00000,0b00000,0b00000,0b11100,0b11111,0b11111,0b11100,0b00000}
	};

	if(RED)
	{
		SSD_voidPovSendNumber(Local_s8CountDown-YELLOW_TIME-GREEN_TIME);
		DIO_voidSetPinValue(LED_PORT, GREEN_PIN, PIN_VALUE_LOW);
		DIO_voidSetPinValue(LED_PORT, RED_PIN, PIN_VALUE_HIGH);
		CLCD_voidSendCommand(DISPLAY_CLEAR);
		CLCD_voidSendString("Time: ");
		CLCD_voidSendNumber(Local_s8CountDown-YELLOW_TIME-GREEN_TIME);
		CLCD_voidSetPostion(FIRST_LINE, 8);
		CLCD_voidSendData(255);
		CLCD_voidSetPostion(SECOND_LINE, 2);
		CLCD_voidSendString("STOP!");
		CLCD_voidSetPostion(SECOND_LINE, 8);
		CLCD_voidSendData(255);
		for(u8 i=0;i<6;i++)
		{
			CLCD_voidDrawSpecialChar(i, Local_u8CustomMan[i]);
		}
		CLCD_voidSendCommand(SET_DDRAM_ADDRESS);
		for(u8 j=10;j<14;j++)
		{

			CLCD_voidSetPostion(FIRST_LINE, 10);
			CLCD_voidSendString("      ");
			CLCD_voidSetPostion(SECOND_LINE, 10);
			CLCD_voidSendString("      ");
			CLCD_voidSetPostion(FIRST_LINE, j);
			for(u8 i=0;i<6;i++)
			{
				if(i>=3) CLCD_voidSetPostion(SECOND_LINE, (j-3)+i);
				CLCD_voidSendData(i);
			}
		}
		CLCD_voidSetPostion(FIRST_LINE, 10);
		CLCD_voidSendString("GO!");
		CLCD_voidSetPostion(SECOND_LINE, 10);
		CLCD_voidSendString("GO!");
		Local_s8CountDown--;
	}
	else if (YELLOW)
	{
		SSD_voidPovSendNumber(Local_s8CountDown-GREEN_TIME);
		DIO_voidSetPinValue(LED_PORT, RED_PIN, PIN_VALUE_LOW);
		DIO_voidSetPinValue(LED_PORT, YELLOW_PIN, PIN_VALUE_HIGH);
		CLCD_voidSendCommand(DISPLAY_CLEAR);
		CLCD_voidSendString("    Time: ");
		CLCD_voidSendNumber(Local_s8CountDown-GREEN_TIME);
		CLCD_voidSetPostion(SECOND_LINE, 0);
		CLCD_voidSendString("GET READY");
		CLCD_voidSendData(255);
		CLCD_voidSendString(" STOP!");
		Local_s8CountDown--;
	}
	else if (GREEN)
	{
		SSD_voidPovSendNumber(Local_s8CountDown);
		DIO_voidSetPinValue(LED_PORT, YELLOW_PIN, PIN_VALUE_LOW);
		DIO_voidSetPinValue(LED_PORT, GREEN_PIN, PIN_VALUE_HIGH);
		CLCD_voidSendCommand(DISPLAY_CLEAR);
		CLCD_voidSetPostion(FIRST_LINE, 8);
		CLCD_voidSendString("Time: ");
		CLCD_voidSendNumber(Local_s8CountDown);
		CLCD_voidSetPostion(FIRST_LINE, 7);
		CLCD_voidSendData(255);
		CLCD_voidSetPostion(SECOND_LINE, 0);
		CLCD_voidSendString("GO! GO!");
		CLCD_voidSetPostion(SECOND_LINE, 7);
		CLCD_voidSendData(255);
		for(u8 i=0;i<7;i++)
		{
			CLCD_voidDrawSpecialChar(i, Local_u8CustomCar[i]);
		}
		CLCD_voidSendCommand(SET_DDRAM_ADDRESS);
		CLCD_voidSetPostion(FIRST_LINE, 0);
		for(u8 i=0;i<7;i++)
		{
			CLCD_voidSendData(i);
		}
		CLCD_voidSetPostion(SECOND_LINE, 10);
		CLCD_voidSendString("STOP!");
		Local_s8CountDown--;
	}
	else
	{
		Local_u8TimeInSeconds=0;
		Local_s8CountDown=RED_TIME+YELLOW_TIME+GREEN_TIME;
	}
}

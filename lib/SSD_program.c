/******************SSD Program*******************/
/**********Author: Abdelrahman Mohamed.**********/
/********************Ver.: 01********************/
/****************Date:17/08/2023.****************/
/************************************************/

#include "../inc/STD_TYPES.h"
#include "../inc/BIT_MATH.h"
#include "DIO_interface.h"
#include "SSD_private.h"
#include "SSD_config.h"
#include "SSD_interface.h"
#include <util/delay.h>

u8 ssd_arr[]={63,6,91,79,102,109,125,7,127,111};  //array in decimals from 0-9 for 7seg display.

void SSD_voidInit(void)
{
#if NUMBER_OF_SSD == ONE
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,FIRST_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
#elif NUMBER_OF_SSD == TWO
	DIO_voidSetPortDirection(FIRST_SSD_PORT, PORT_DIRECTION_OUTPUT);
	DIO_voidSetPortDirection(SECOND_SSD_PORT, PORT_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,FIRST_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,SECOND_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
#elif NUMBER_OF_SSD == THREE
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,FIRST_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,SECOND_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,THIRD_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
#elif NUMBER_OF_SSD == FOUR
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,FIRST_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,SECOND_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,THIRD_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,FOURTH_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
#elif NUMBER_OF_SSD == FIVE
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,FIRST_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,SECOND_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,THIRD_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,FOURTH_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,FIFTH_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
#elif NUMBER_OF_SSD == SIX
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,FIRST_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,SECOND_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,THIRD_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,FOURTH_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,FIFTH_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT,SIXTH_SSD_ENABLE, PIN_DIRECTION_OUTPUT);
#else
#error("Wrong Number of SSDs");
#endif
}

void SSD_voidSendNumber(SSD_t SSD_config,u8 Copy_u8num)
{
	if(SSD_config.activestate==COMMON_CATHODE)
	{
		DIO_voidSetPortValue(SSD_config.dataport, ssd_arr[Copy_u8num]);
	}
	else if(SSD_config.activestate==COMMON_ANODE)
	{
		DIO_voidSetPortValue(SSD_config.dataport, ~(ssd_arr[Copy_u8num]));
	}
}

void SSD_voidEnable(SSD_t SSD_config)
{
	if(SSD_config.activestate==COMMON_CATHODE)
	{
		DIO_voidSetPinValue(SSD_config.controlport, SSD_config.controlpin, PIN_VALUE_LOW);
	}
	else if(SSD_config.activestate==COMMON_ANODE)
	{
		DIO_voidSetPinValue(SSD_config.controlport, SSD_config.controlpin, PIN_VALUE_HIGH);
	}
}

void SSD_voidDisable(SSD_t SSD_config)
{
	if(SSD_config.activestate==COMMON_CATHODE)
	{
		DIO_voidSetPinValue(SSD_config.controlport, SSD_config.controlpin, PIN_VALUE_HIGH);
	}
	else if(SSD_config.activestate==COMMON_ANODE)
	{
		DIO_voidSetPinValue(SSD_config.controlport, SSD_config.controlpin, PIN_VALUE_LOW);
	}
}

void SSD_voidPovSendNumber(u32 Copy_u32Number)
{
#if NUMBER_OF_SSD == ONE
	SSD_t SSD_1 = {SSD_PORT,SSD_ENABLE_PORT,FIRST_SSD_ENABLE,FIRST_SSD_TYPE};

	SSD_voidSendNumber(SSD_1, UNITS(Copy_u32Number));
	SSD_voidEnable(SSD_1);

#elif NUMBER_OF_SSD == TWO
	SSD_t SSD_1 = {FIRST_SSD_PORT,SSD_ENABLE_PORT,FIRST_SSD_ENABLE,FIRST_SSD_TYPE};
	SSD_t SSD_2 = {SECOND_SSD_PORT,SSD_ENABLE_PORT,SECOND_SSD_ENABLE,SECOND_SSD_TYPE};

	SSD_voidEnable(SSD_1);
	SSD_voidEnable(SSD_2);
	SSD_voidSendNumber(SSD_1, UNITS(Copy_u32Number));
	SSD_voidSendNumber(SSD_2, TENS(Copy_u32Number));

#elif NUMBER_OF_SSD == SIX
	SSD_t SSD_1 = {SSD_PORT,SSD_ENABLE_PORT,FIRST_SSD_ENABLE,FIRST_SSD_TYPE};
	SSD_t SSD_2 = {SSD_PORT,SSD_ENABLE_PORT,SECOND_SSD_ENABLE,SECOND_SSD_TYPE};
	SSD_t SSD_3 = {SSD_PORT,SSD_ENABLE_PORT,THIRD_SSD_ENABLE,THIRD_SSD_TYPE};
	SSD_t SSD_4 = {SSD_PORT,SSD_ENABLE_PORT,FOURTH_SSD_ENABLE,FOURTH_SSD_TYPE};
	SSD_t SSD_5 = {SSD_PORT,SSD_ENABLE_PORT,FIFTH_SSD_ENABLE,FIFTH_SSD_TYPE};
	SSD_t SSD_6 = {SSD_PORT,SSD_ENABLE_PORT,SIXTH_SSD_ENABLE,SIXTH_SSD_TYPE};

		SSD_voidDisable(SSD_2);
		SSD_voidDisable(SSD_3);
		SSD_voidDisable(SSD_4);
		SSD_voidDisable(SSD_5);
		SSD_voidDisable(SSD_6);
		SSD_voidSendNumber(SSD_1, UNITS(Copy_u32Number));
		SSD_voidEnable(SSD_1);

		SSD_voidDisable(SSD_1);
		SSD_voidDisable(SSD_3);
		SSD_voidDisable(SSD_4);
		SSD_voidDisable(SSD_5);
		SSD_voidDisable(SSD_6);
		SSD_voidSendNumber(SSD_2, TENS(Copy_u32Number));
		SSD_voidEnable(SSD_2);

		SSD_voidDisable(SSD_1);
		SSD_voidDisable(SSD_2);
		SSD_voidDisable(SSD_4);
		SSD_voidDisable(SSD_5);
		SSD_voidDisable(SSD_6);
		SSD_voidSendNumber(SSD_3, HUNDREDS(Copy_u32Number));
		SSD_voidEnable(SSD_3);

		SSD_voidDisable(SSD_1);
		SSD_voidDisable(SSD_2);
		SSD_voidDisable(SSD_3);
		SSD_voidDisable(SSD_5);
		SSD_voidDisable(SSD_6);
		SSD_voidSendNumber(SSD_4, THOUSANDS(Copy_u32Number));
		SSD_voidEnable(SSD_4);

		SSD_voidDisable(SSD_1);
		SSD_voidDisable(SSD_2);
		SSD_voidDisable(SSD_3);
		SSD_voidDisable(SSD_4);
		SSD_voidDisable(SSD_6);
		SSD_voidSendNumber(SSD_5, TEN_THOUSANDS(Copy_u32Number));
		SSD_voidEnable(SSD_5);

		SSD_voidDisable(SSD_1);
		SSD_voidDisable(SSD_2);
		SSD_voidDisable(SSD_3);
		SSD_voidDisable(SSD_4);
		SSD_voidDisable(SSD_5);
		SSD_voidSendNumber(SSD_6, HUNDRED_THOUSANDS(Copy_u32Number));
		SSD_voidEnable(SSD_6);
#else
#error("Wrong Number of SSDS")
#endif
}

/*****************SSD Interface******************/
/**********Author: Abdelrahman Mohamed.**********/
/********************Ver.: 01********************/
/****************Date:17/08/2023.****************/
/************************************************/

#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

#define UNITS(time_in_seconds) time_in_seconds % 10
#define TENS(time_in_seconds) (time_in_seconds / 10) % 10
#define HUNDREDS(time_in_seconds) (time_in_seconds / 100) % 10
#define THOUSANDS(time_in_seconds) (time_in_seconds / 1000) % 10
#define TEN_THOUSANDS(time_in_seconds) (time_in_seconds / 10000) % 10
#define HUNDRED_THOUSANDS(time_in_seconds) (time_in_seconds / 100000) % 10

typedef struct
{
	u8 dataport;
	u8 controlport;
	u8 controlpin;
	u8 activestate;
} SSD_t;

void SSD_voidInit(void);
void SSD_voidSendNumber(SSD_t SSD_config, u8 Copy_u8num);
void SSD_voidEnable(SSD_t SSD_config);
void SSD_voidDisable(SSD_t SSD_config);
void SSD_voidPovSendNumber(u32 Copy_u32Number);

#endif

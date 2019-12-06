/*
 * ADC_int.h
 *
 *  Created on: Nov 23, 2019
 *      Author: Ahmed
 */

#ifndef ADC_INT_H_
#define ADC_INT_H_

#include "std_types.h"		// to use u16

// function prototypes
void ADC_voidInit(void);
u16 ADC_u16GetData(void);
void ADC_voidStartConv(void);
void ADC_voidChangeChannel(u8 local_channelNo);
void ADC_voidSetISRPtr(void (*local_fptr)(void));

#endif /* ADC_INT_H_ */

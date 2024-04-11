#ifndef __FUN_H__
#define __FUN_H__

#include "stm32g4xx.h"

void lcd_show(void);
double get_vol(ADC_HandleTypeDef *hadc);

#endif // __FUN_H__

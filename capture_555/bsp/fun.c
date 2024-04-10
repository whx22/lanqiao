#include "headfile.h"

uint32_t frequence1, capture_value1, frequence2, capture_value2;
char text[20];

void lcd_show() {
	sprintf(text, "        test        ");
	LCD_DisplayStringLine(Line0, (uint8_t *)text);
	sprintf(text, "    frequence1:%d    ", frequence1);
	LCD_DisplayStringLine(Line2, (uint8_t *)text);
	sprintf(text, "    frequence2:%d    ", frequence2);
	LCD_DisplayStringLine(Line4, (uint8_t *)text);
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	// 频率输出1 R39
	if (htim->Instance == TIM16) { 
		/* 读取当前CNT的值，计算距上次置0的间隔时钟周期 */
		capture_value1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); 
		// 或 capture_value = TIM17->CCR1; // 在捕获上升沿时，会将CNT赋值给CCR
		
		/* PWM上升沿，将CNT值置0 */
		TIM16->CNT = 0; 
		frequence1  = 80000000 / (80 * capture_value1);
	}
	
	// 频率输出2 R40
	if (htim->Instance == TIM2) { 
		/* 读取当前CNT的值，计算距上次置0的间隔时钟周期 */
		capture_value2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); 
		// 或 capture_value = TIM17->CCR1; // 在捕获上升沿时，会将CNT赋值给CCR
		
		/* PWM上升沿，将CNT值置0 */
		TIM2->CNT = 0; 
		frequence2 = 80000000 / (80 * capture_value2);
	}
}

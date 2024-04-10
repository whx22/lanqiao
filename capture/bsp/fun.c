#include "headfile.h"

uint32_t frequence, capture_value;
char text[20];

void lcd_show() {
	sprintf(text, "        test        ");
	LCD_DisplayStringLine(Line0, (uint8_t *)text);
	sprintf(text, "    frequence:%d    ", frequence);
	LCD_DisplayStringLine(Line0, (uint8_t *)text);
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	/* TIM17 CHANNEL1 捕获PWM上升沿触发中断 */
	if (htim->Instance == TIM17) { 
		/* 读取当前CNT的值，计算距上次置0的间隔时钟周期 */
		capture_value = HAL_TIM_ReadCapturedValue(&htim17, TIM_CHANNEL_1); 
		// 或 capture_value = TIM17->CCR1; // 在捕获上升沿时，会将CNT赋值给CCR
		
		/* PWM上升沿，将CNT值置0 */
		TIM17->CNT = 0; 
		frequence  = 80000000 / (80 * capture_value);
	}
}

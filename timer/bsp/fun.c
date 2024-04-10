#include "headfile.h"

int count = 0;
uint8_t led_mode = 0;

void led_show(uint8_t led, uint8_t mode) {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
	if (mode) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8 << (led - 1), GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8 << (led - 1), GPIO_PIN_SET);	
	}
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
}

uint8_t B1_state;
uint8_t B1_last_state;
uint8_t B2_state;
uint8_t B2_last_state;
uint8_t B3_state;
uint8_t B3_last_state;
uint8_t B4_state;
uint8_t B4_last_state;

void key_scan() {
	B1_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
	B2_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
	B3_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2);
	B4_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	if (B1_state == 0 && B1_last_state == 1) {
		count++;
	}
	if (B2_state == 0 && B2_last_state == 1) {
		count--;
	}
	if (B3_state == 0 && B3_last_state == 1) {
		led_show(2, 1);
	}
	if (B4_state == 0 && B4_last_state == 1) {
		led_show(2, 0);
	}
	B1_last_state = B1_state;
	B2_last_state = B2_state;
	B3_last_state = B3_state;
	B4_last_state = B4_state;
}


char text[20];

void lcd_show() {
	sprintf(text, "        test        ");
	LCD_DisplayStringLine(Line0, (uint8_t *)text);
	sprintf(text, "     count : %d     ", count);
	LCD_DisplayStringLine(Line3, (uint8_t *)text);
	
	led_show(1, led_mode);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM2) {
		led_mode++;
		led_mode = led_mode % 2;
	}
}
/*
 * uart_communiation_fsm.c
 *
 *  Created on: Dec 11, 2022
 *      Author: lephu
 */

#include "uart_communiation_fsm.h"

/* Define State */
#define INIT 0
#define WAIT_RST 1
#define ADC_RESPONSE 2
#define WAIT_OK 3

uint32_t uart_state = INIT;
uint32_t ADC_value = 0;
char str[50];

void uart_communiation_fsm(void)
{
	switch (uart_state)
	{
	case INIT:
		uart_state = WAIT_RST;
		break;
	case WAIT_RST:
		if(command_flag == 1 && command_data == RST)
		{
			command_flag = 0;
			uart_state = ADC_RESPONSE;
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r"), 1000);
		}
		break;
	case ADC_RESPONSE:
		ADC_value = HAL_ADC_GetValue(&hadc1);
		HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "%ld\r", ADC_value), 1000);
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		command_data = NO_COMMAND;
		setTimer(3000, 0);
		uart_state = WAIT_OK;
		break;
	case WAIT_OK:
		if(command_flag == 1 && command_data == OK)
		{
			command_flag = 0;
			uart_state = WAIT_RST;
		}
		if(isTimerOut(0) == 1)
			uart_state = ADC_RESPONSE;
		break;
	}
}

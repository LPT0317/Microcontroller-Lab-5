/*
 * command_parser_fsm.h
 *
 *  Created on: Dec 8, 2022
 *      Author: lephu
 */

#ifndef INC_COMMAND_PARSER_FSM_H_
#define INC_COMMAND_PARSER_FSM_H_

#include "main.h"
#include <stdio.h>

#define MAX_BUFFER_SIZE 50

/* Define Command */
#define NO_COMMAND 0
#define RST 100
#define OK 101

extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t buffer_flag;
extern uint8_t index_buffer;

extern uint32_t command_data;
extern uint8_t command_flag;

void command_parser_fsm(void);

#endif /* INC_COMMAND_PARSER_FSM_H_ */

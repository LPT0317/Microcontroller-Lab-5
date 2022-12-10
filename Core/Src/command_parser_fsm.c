/*
 * command_parser_fsm.c
 *
 *  Created on: Dec 8, 2022
 *      Author: lephu
 */

#include "command_parser_fsm.h"

/* Define State */
#define COMMAND_INIT 0
#define COMMAND_BEGIN 1
#define COMMAND_WAIT 2
#define WAIT_S 11
#define WAIT_T 12
#define WAIT_K 21
#define COMMAND_RST 3
#define COMMAND_OK 4
#define COMMAND_END 5

uint8_t buffer_flag = 0;
uint8_t index_buffer = 0;
uint8_t buffer[MAX_BUFFER_SIZE];

uint32_t command_state = COMMAND_BEGIN;
uint32_t command_data = NO_COMMAND;
uint8_t command_flag = 0;
uint32_t index_command = 0;

void command_parser_fsm(void)
{
  if(index_command >= MAX_BUFFER_SIZE)
	  index_command = 0;
  switch(command_state)
  {
//  case COMMAND_INIT:
//	  index_command = 0;
//	  command_state = COMMAND_BEGIN;
//	  command_data = NO_COMMAND;
//	  command_flag = 0;
//	  break;
  case COMMAND_BEGIN:
	  /*
	   * command: "!" -> next state
	   *          other -> no change
	   */
	  if(buffer[index_command] == '!')
	    command_state = COMMAND_WAIT;
	  index_command++;
	  break;
  case COMMAND_WAIT:
	  /*
	   * command: "!!!!!!R" -> wait for S
	   *          "!!!!!!O" -> wait for K
	   *          "!!abd!!" -> no change
	   */
	  if(buffer[index_command] == 'R' || buffer[index_command] == 'r')
		  command_state = WAIT_S;
	  else if(buffer[index_command] == 'O' || buffer[index_command] == 'o')
		  command_state = WAIT_K;
	  index_command++;
	  break;
  case WAIT_S:
	  /*
	   * command: "!!!RRRRS" -> Wait for T
	   *          "!!!RRabc" -> Return to Command_Wait
	   */
	  if(buffer[index_command] == 'S' || buffer[index_command] == 's')
		  command_state = WAIT_T;
	  else if(buffer[index_command] == 'R' || buffer[index_command] == 'r')
		  command_state = WAIT_S;
	  else
		  command_state = COMMAND_WAIT;
	  index_command++;
	  break;
  case WAIT_T:
	  /*
	   * command: "!!!RRRSSST" -> wait for #
	   *          "!!!RRSSabc" -> return to Command_Wait
	   */
	  if(buffer[index_command] == 'T' || buffer[index_command] == 't')
		  command_state = COMMAND_RST;
	  else if(buffer[index_command] == 'S' || buffer[index_command] == 's')
		  command_state = WAIT_T;
	  else
		  command_state = COMMAND_WAIT;
	  index_command++;
	  break;
  case WAIT_K:
	  /*
	   * command: "!!!!OOOK" -> wait for #
	   *          "!!!OOOab" -> return to Command_wait
	   */
	  if(buffer[index_command] == 'K' || buffer[index_command] == 'k')
		  command_state = COMMAND_OK;
	  else if(buffer[index_command] == 'O' || buffer[index_command] == 'o')
		  command_state = WAIT_K;
	  else
		  command_state = COMMAND_WAIT;
	  index_command++;
	  break;
  case COMMAND_RST:
	  /*
	   * command: "!!RRRSSSTaTaTabc#" -> command_flag and command data = RST
	   *
	   */
	  if(buffer[index_command] == '#')
	  {
		  command_flag = 1;
		  command_state = COMMAND_BEGIN;
	  }
	  command_data = RST;
	  index_command++;
	  break;
  case COMMAND_OK:
	  /*
	   * command: "!!OOOKabdKKK#" -> command_flag and command data = OK
	   *
	   */
	  if(buffer[index_command] == '#')
	  {
		  command_flag = 1;
		  command_state = COMMAND_BEGIN;
	  }
	  command_data = OK;
	  index_command++;
	  break;
  }
}

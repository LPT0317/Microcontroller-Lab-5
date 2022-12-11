/*
 * timer.h
 *
 *  Created on: Dec 11, 2022
 *      Author: lephu
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

/* Define */
#define NO_Timer 1
#define TIME_CYCLE 10

/* Function -----*/
//Set time on timer[index] = duration
void setTimer(int duration, int index);
//Check timer out on timer[index]
int isTimerOut(int index);
//Run timer (counter on timer)
void timerRun(void);

#endif /* INC_TIMER_H_ */

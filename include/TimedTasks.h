/*
timedTasks.h:
provide the possibility to run commands in regular intervals (using timer Interrupts)
 */

#ifndef TIMEDTASKS_H
#define TIMEDTASKS_H

void initTimedTasks(void);

void ftm0_isr(void);

void task0 (void);
//void task1 (void);
//void task2 (void);
//void task3 (void);
//void task4 (void);
//void task5 (void);
//void task6 (void);
//void task7 (void);


#endif // !TIMEDTASKS_H
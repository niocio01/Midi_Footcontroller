/*
timedTasks.h:
provide the possibility to run commands in regular intervals (using timer Interrupts)
 */

#ifndef TIMEDTASKS_H
#define TIMEDTASKS_H

namespace TimedTasks
{

void timerInit(void);

void task0 (void);
void task1 (void);
//void task2 (void);
//void task3 (void);
//void task4 (void);
//void task5 (void);
//void task6 (void);
//void task7 (void);

void resetTask1(void);

} // end namespace

#endif // !TIMEDTASKS_H
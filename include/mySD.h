/*
mySD.h:
mount the SD-Card and allow access to the data on it to other moules
 */

#ifndef MYSD_H
#define MYSD_H

void initSD(void);

void sdWriteTest(void);

//void loadConfiguration(const char *filename, Config &config);

//void saveConfiguration(const char *filename, const Config &config);

void printFile(const char *filename);

#endif // !MYSD_H
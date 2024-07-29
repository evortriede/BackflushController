#include <fsm.h>

void (*reboot)(void);

void startbf(void *data);
void startpd(void *data);
void startsandbf(void *data);
void done(void *data);

#include "States.h"

#define KILLSW 2
#define BFVALVE 3
#define LBYPASS 4
#define UBYPASS 5
#define RELAYS 6
#define VALVE1 7
#define VALVE24 8
#define BWBUTTON 9
#define STARTBUTTON 10

#define OFF HIGH
#define ON LOW

//define TESTING TRUE

#ifndef TESTING
#define ZEOLITE_BF_TIME 600000L
#define ZEOLITE_PD_TIME 120000L
#define SAND_BF_TIME 7200000L
#else
#define ZEOLITE_BF_TIME 60000L
#define ZEOLITE_PD_TIME 10000L
#define SAND_BF_TIME 72000L
#endif


int buttonState;
long tstamp;
int buttonValue;

#include "BackflushController.h"

void logMethod(const char *msg)
{
  Serial.print(msg);
}

void setup()
{
  Serial.begin(9600);
  pinMode(KILLSW, OUTPUT);
  pinMode(BFVALVE, OUTPUT);
  pinMode(LBYPASS, OUTPUT);
  pinMode(UBYPASS, OUTPUT);
  pinMode(RELAYS, OUTPUT);
  pinMode(VALVE1, OUTPUT);
  pinMode(VALVE24, OUTPUT);
  pinMode(BWBUTTON, OUTPUT);
  pinMode(STARTBUTTON, INPUT_PULLUP);
  
  digitalWrite(KILLSW, OFF);
  digitalWrite(BFVALVE, OFF);
  digitalWrite(LBYPASS, OFF);
  digitalWrite(UBYPASS, OFF);
  digitalWrite(RELAYS, OFF);
  digitalWrite(VALVE1, OFF);
  digitalWrite(VALVE24, OFF);
  digitalWrite(BWBUTTON, OFF);

  fsm.setLogMethod(&logMethod);
}

bool debouncePin(int pin, int &pinState, long &stamp, int &pinValue)
{
  if (stamp==0)
  {
    pinState=digitalRead(pin);
    if (pinState != pinValue)
    {
      stamp=millis();
    }
    return false;
  }
  
  // we know that we're timing an event (i.e., stamp != 0)
  
  if (millis()-stamp > 30)
  {
    stamp = 0;
    if (pinState == digitalRead(pin))
    {
      pinValue = pinState;
      return true;
    }
  }
  return false;
}

void loop()
{
  if (debouncePin(STARTBUTTON, buttonState, tstamp, buttonValue))
  {
    if (buttonValue==LOW)
    {
      fsm.enqueue(button_ev,0);
    }
  }
  fsm.processEvents();
}

void startbf(void *data)
{
  digitalWrite(KILLSW, ON);
  digitalWrite(BFVALVE, ON);
  digitalWrite(UBYPASS, ON);
  digitalWrite(VALVE1, ON);
  fsm.setTickTimer(ZEOLITE_BF_TIME, 0); // 10 minutes
}

void startpd(void *data)
{
  digitalWrite(BFVALVE, OFF);
  digitalWrite(UBYPASS, OFF);
  digitalWrite(VALVE1, OFF);
  digitalWrite(VALVE24, ON);
  digitalWrite(LBYPASS, ON);
  fsm.setTickTimer(ZEOLITE_PD_TIME, 0); // 2 minutes
}

void startsandbf(void *data)
{
  digitalWrite(VALVE24, OFF);
  digitalWrite(LBYPASS, OFF);
  digitalWrite(KILLSW, OFF);
  digitalWrite(RELAYS, ON);
  digitalWrite(BWBUTTON, ON);
  delay(250); // 1/4 second
  digitalWrite(BWBUTTON, OFF);
  fsm.setTickTimer(SAND_BF_TIME, 0); // 2 hours
}

void done(void *data)
{
  digitalWrite(RELAYS, OFF);
}

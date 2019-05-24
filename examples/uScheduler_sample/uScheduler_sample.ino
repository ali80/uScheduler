#include <uscheduler.h>

void printer();
void blinker();

uScheduler t_blinker(250,blinker, -1);
uScheduler t_printer(1000, printer, -1);

int ledpin = 16;

void blinker()
{
  digitalWrite(ledpin, !digitalRead(ledpin));
}
void printer()
{
  char str[50];
  sprintf(str,"Ran for %.3f:\ntblinker=%d\n",millis()/1000.0f, t_blinker.counter);
  Serial.println(str);
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  pinMode(ledpin, OUTPUT);
}

void loop()
{
  t_blinker.checkRun();
  t_printer.checkRun();
  yield();
}

#ifndef USCHEDULER
#define USCHEDULER

#include "uScheduler_hal.h"

typedef enum
{
  USCH_CHECK_SKIP   = 0,
  USCH_CHECK_RUN    = 1
}uScheduler_check_t;

class uScheduler
{
  private:
    uint32_t _interval;         //  main interval
    uint32_t _tickPrev;     // previous tick in ms
    uint32_t _tickNow;
    uint32_t _tickDiff;
    int _semaphore;

    uScheduler_check_t tickCheck();
    uScheduler_check_t semCheck();
    void (*_callback)(void);
    void timerReset(){_tickPrev = millis();};    //  resets the internal timer

  public:
    uint32_t tick();
    void tick(uint32_t);
    uScheduler_check_t checkRun();
    uint32_t counter;
    void runLaterOnce(int interval, void (*callback)(void))
    {
      _tickPrev = millis();
      _semaphore = 1;
      _interval = interval;
      _callback = callback;

    }
    void runLaterOnce(int interval)
    {
      _tickPrev = millis();
      _semaphore = 1;
      _interval = interval;
    }
    void runLaterOnce()
    {
      _tickPrev = millis();
      _semaphore = 1;
    }

    void semaphore(int semaphore) { _semaphore = semaphore;}
    int semaphore() {return _semaphore;}
    uint32_t elapsed() {return millis() - _tickPrev;}

    uScheduler(uint32_t interval, void (*callback)(void), int semaphore = -1)
    {
      _tickPrev = millis();         //  first run is calculated from the time of the setting
      _interval = interval;
      _callback = callback;
      _semaphore = semaphore;
    }
};

#endif



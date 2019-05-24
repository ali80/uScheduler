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
    uint32_t _tick;         //  main interval
    uint32_t _prevtick;     // previous tick in ms
    uint32_t _nowtick;
    uint32_t _tickDiff;
    int _semaphore;

    uScheduler_check_t tickCheck();
    uScheduler_check_t semCheck();
    void (*_callback)(void);

  public:
    uint32_t tick();
    void tick(uint32_t);
    uScheduler_check_t checkRun();
    uint32_t counter;

    void semaphore(int semaphore)
    {
      _semaphore = semaphore;
    }
    int semaphore()
    {
      return _semaphore;
    }

    uScheduler(uint32_t interval, void (*callback)(void), int semaphore = -1)
    {
      _tick = interval;
      _callback = callback;
      _semaphore = semaphore;
    }
};

#endif



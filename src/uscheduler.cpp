#include "uscheduler.h"

uint32_t uScheduler::setInterval()
{
  return _interval;
}
void uScheduler::setInterval(uint32_t tick)
{
  _interval = tick;
}

uScheduler_check_t uScheduler::tickCheck()
{
  _tickDiff = _tickNow - _tickPrev;
  if (_tickDiff >= _interval)
  {
    _tickPrev = _tickNow;
    if (_tickDiff < (1<<31))         //  check for overflow on millis between two consecutive runs happens every 49.7 days
    {
      return(USCH_CHECK_RUN);
    }
    else
    {
      _tickPrev = 0;    //  !!! introduces error in timing after overflow
    }

  }
  return USCH_CHECK_SKIP;
}

uScheduler_check_t uScheduler::semCheck()
{
  if (_semaphore == -1)
  {
    return USCH_CHECK_RUN;
  }
  else if (_semaphore > 0)
  {
    _semaphore--;
    return USCH_CHECK_RUN;
  }
  return USCH_CHECK_SKIP;
}

uScheduler_check_t uScheduler::checkRun()
{
  _tickNow = millis();    //  this should be run as fast as possible to get most accurate tick
  if (tickCheck())
  {
    if (semCheck())
    {
      if (_callback != NULL) _callback();
      counter++;
      return USCH_CHECK_RUN;
    }
  }
  return USCH_CHECK_SKIP;
}
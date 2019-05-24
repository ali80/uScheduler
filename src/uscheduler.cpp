#include "uscheduler.h"

uint32_t uScheduler::tick()
{
  return _tick;
}
void uScheduler::tick(uint32_t tick)
{
  _tick = tick;
}

uScheduler_check_t uScheduler::tickCheck()
{
  _tickDiff = _nowtick - _prevtick;
  if (_tickDiff > _tick)
  {
    _prevtick = _nowtick;
    if (_tickDiff < (1<<31))         //  check for overflow on millis between two consecutive runs
    {
      return(USCH_CHECK_RUN);
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
  _nowtick = millis();    //  this should be run as fast as possible to get most accurate tick
  if (tickCheck())
  {
    if (semCheck())
    {
      _callback();
      counter++;
      return USCH_CHECK_RUN;
    }
  }
  return USCH_CHECK_SKIP;
}
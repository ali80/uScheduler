# uScheduler

## usage

- use interval to set intervals between execution in milli seconds
- use ```semaphore > 0``` to specify number of runs, ```semaphore = -1``` for infinity
- each execution reduces semaphore by 1, and semahpore = 0 skips code execution
- semaphore can be set/get with ```semaphore``` function

```C++
void callback(void)
{
  //  do something
  // delay is set by the constructor, no need to add delay here
}
task1 uScheduler(uint32_t interval, void (*callback)(void), int semaphore = -1);
loop()
{
  task1.checkRun();     //  check if the interval has past and semaphore !=0 run else skip
}
```

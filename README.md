# uScheduler

## usage

- approximately 5us to run the scheduler on esp8266
- use interval to set intervals between execution in milli seconds
- use ```semaphore > 0``` to specify number of runs, ```semaphore = -1``` for infinity
- each execution reduces semaphore by 1, and semahpore = 0 skips code execution
- semaphore can be set with ```setSemaphore``` function
- there is a functionless mode added for those who dont need/like function pointers just input NULL as the callback argument

```C++
void callback(void)
{
  // do something
  // delay is set by the constructor, no need to add delay here
}
task1 uScheduler(500, callback, 10);    // run callback() 10 times each 500ms
task2 uScheduler(200, NULL, -1);        // checkRun returns true every 200ms for unlimited times(-1)
loop()
{
  task1.checkRun();     //  check if the interval has past and semaphore !=0 run else skip
  if (task2.checkRun())
  {
    //  do something, no need to define seperate function
  }

  // since no delay function is nessesary, add this so esp as some time to do background tasks
  yield();
}
```


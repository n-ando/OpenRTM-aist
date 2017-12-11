#include <semLib.h>
#include <sysLib.h>
#include <taskLib.h>

#include <iostream>

static SEM_ID syncSemId1000;


void update_function(void)
{
    semFlush(syncSemId1000);
}

STATUS interrupt_wait(void)
{
    return semTake(syncSemId1000, WAIT_FOREVER);
}


void start_interrupt_handler(void)
{
    const double sleep_time = 2.0;
    const int loop_count = 6;
    syncSemId1000 = semBCreate(SEM_Q_FIFO, SEM_EMPTY);



    while(true)
    {
        int count = 0;
        int tps = sysClkRateGet();
        taskDelay((int)(sleep_time*tps) + 1);

        while(count < loop_count)
        {
            update_function();
            count++;
        }
    }
}




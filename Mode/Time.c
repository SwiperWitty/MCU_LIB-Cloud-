#include "time.h"
#include "API.h"

//防止被编译器优化，并且只能在本文件使用
/*
 * while(a);
 * 和
 * while(get(a));
 * 不一样
 */


struct _SYS_Time SYS_Time = {
    .Watch.hour = 23,
    .Watch.minutes = 59,
    .Watch.second = 56,
};

void Time_Init(int SET)
{
#ifdef Exist_SYS_TIME
    Sys_Time_Init (SET);

#endif
}

/*
 * Set_Time只精确到秒
 */
void Set_TIME (struct Caven_Watch time)
{
#ifdef Exist_SYS_TIME
    int Seconds;
    Seconds = Hourly_to_Seconds(time);
    SET_SysTick((U64)Seconds*(SystemCoreClock));

#endif
}


struct Caven_Watch Get_TIME (void)
{
#ifdef Exist_SYS_TIME

    struct Caven_Watch temp = {0};
    int Seconds = (GET_SysTick() / SystemCoreClock);
    int Freq = SystemCoreClock / 1000000;           //1us
    temp = Seconds_to_Hourly(Seconds);

    if(Seconds / 86400)        //下一天
    {
        Destroy(&temp,sizeof(temp));
        Set_TIME (temp);    //重设时间戳

    }
    temp.time_us = (GET_SysTick() % SystemCoreClock) / Freq;

    return temp;
#endif
}

void Delay_10us(int num)
{

}

void Delay_ms(int num)
{

}

void Delay_S(char num)
{

}

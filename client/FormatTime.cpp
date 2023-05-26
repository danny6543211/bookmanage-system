#include<time.h>
#include<stdio.h>

time_t FormatTime(char * szTime)
{
       struct tm tm1;
       time_t time1;
       sscanf(szTime, "%d %d %d %d %d %d",
                 &tm1.tm_year,
                 &tm1.tm_mon,
                 &tm1.tm_mday,
                 &tm1.tm_hour,
                 &tm1.tm_min,
                 &tm1.tm_sec);

       tm1.tm_year -= 1900;
       tm1.tm_mon --;
       tm1.tm_isdst=-1;

       time1 =mktime(&tm1);
       return time1;
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

enum { YEAR_REF_POINT = 25, MONTH_REF_POINT = 9, DAY_REF_POINT = 7 };
enum { DATE_SIZE = 12, SECONDS_IN_MINUTE = 60, MINUTES_IN_HOUR = 60 };
enum { HOURS_IN_DAY = 24, MONTHS_IN_YEAR = 12, DAYS_IN_MONTH = 30 };
enum { DAYS_IN_YEAR = 360, BASE_YEAR = 1900, BASE_HOUR = 12 };

int main(void)
{
    struct tm T, ref_time;

    memset(&ref_time, 0, sizeof(ref_time));
    memset(&T, 0, sizeof(T));
    ref_time.tm_year = YEAR_REF_POINT, ref_time.tm_mon = MONTH_REF_POINT,
    ref_time.tm_mday = DAY_REF_POINT, ref_time.tm_isdst = -1;
    long long ref_seconds = mktime(&ref_time);

    char str[DATE_SIZE];
    while(fgets(str, DATE_SIZE, stdin) != NULL) {
        sscanf(str, "%d %d %d", &T.tm_year, &T.tm_mon, &T.tm_mday);

        T.tm_year -= BASE_YEAR, T.tm_mon -= 1, T.tm_isdst = -1, T.tm_hour = BASE_HOUR;

        long long seconds = mktime(&T) - ref_seconds;

        long long days_in_overall = seconds / SECONDS_IN_MINUTE / MINUTES_IN_HOUR / HOURS_IN_DAY;
        long long years = days_in_overall / DAYS_IN_YEAR;
        long long months = (days_in_overall % DAYS_IN_YEAR) / DAYS_IN_MONTH;
        long long days = (days_in_overall % DAYS_IN_YEAR) % DAYS_IN_MONTH;

        printf("%lld %lld %lld\n", years + 1, months + 1, days + 1);
    }
    return 0;
}

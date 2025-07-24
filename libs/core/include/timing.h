#pragma once
#include "./types.h"
#include "./stringutils.h"

#define SECONDS_IN_MINUTE 60
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_DAY 86400

#define SECONDS_IN_WEEK 604800L
#define SECONDS_IN_MONTH 22628000L
#define SECONDS_IN_YEAR 31540000L

#define sec_to_min(sec) (sec / SECONDS_IN_MINUTE)
#define sec_to_hour(sec) (sec / SECONDS_IN_HOUR)
#define sec_to_day(sec) (sec / SECONDS_IN_DAY)

#define sec_to_week(sec) (sec / SECONDS_IN_WEEK)
#define sec_to_month(sec)(sec / SECONDS_IN_MONTH)
#define sec_to_year(sec) (sec / SECONDS_IN_YEAR)

#define nano_to_micro(nano) (nano / 100)
#define nano_to_millisec(nano) (nano / 100000)
#define nano_to_second(nano) (nano / 100000000)

typedef struct Time_Instance Time_Instance;

Class(TimeShort,
__INIT(u64 day; u64 hour; u64 minute; u64 second;),
__FIELD(u64 day; u64 hour; u64 minute; u64 second;),
	
      	interface(Formatter);
	inst(Time) method(TimeShort, ToTime);
)
Class(TimeLong,
__INIT(u64 year; u64 month; u64 week; u64 day;),
__FIELD(u64 year; u64 month; u64 week; u64 day;),
	
      	interface(Formatter);
	inst(Time) method(TimeLong, ToTime);
)
Class(TimeTiny,
__INIT(u64 second; u64 millisecond; u64 microsecond; u64 nanosecond;),
__FIELD(u64 second; u64 millisecond; u64 microsecond; u64 nanosecond;),
	
      	interface(Formatter);
	inst(Time) method(TimeTiny, ToTime);
)

Class(Time,
__INIT(u64 seconds; u64 nanosec;),
__FIELD(u64 seconds; u64 nanosec;),
      	
      	interface(Formatter);

	errvt method(Time, GetNow);
	errvt method(Time, FromCTime,, struct timespec c_time);
      	inst(Time) method(Time, Difference,, inst(Time) time2);
      	bool method(Time, Compare,, inst(Time) time2, inst(Time) tolarance);
      	inst(TimeShort) method(Time, ToTimeShort);
      	inst(TimeLong) method(Time, ToTimeLong);
      	inst(TimeTiny) method(Time, ToTimeTiny);
)

Class(TimeWatch,
__INIT(inst(Time) limit; bool start),
__FIELD(),
      	
      	interface(Formatter);
	
	errvt method(TimeWatch,Start);
	inst(Time) method(TimeWatch,Check);
	inst(Time) method(TimeWatch,Stop);
	inst(Time) method(TimeWatch, getStartTime);

)



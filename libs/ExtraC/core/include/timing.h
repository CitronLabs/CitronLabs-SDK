#pragma once
#include "./types.h"
#include "./stringutils.h"
#include "error.h"

// Note: These are for rough, user-friendly conversions.
// For precise date/time calculations, use a dedicated calendar library.
#define SECONDS_IN_MINUTE 60
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_DAY 86400

#define SECONDS_IN_WEEK (7 * SECONDS_IN_DAY)
#define SECONDS_IN_MONTH (30.44 * SECONDS_IN_DAY) // Average
#define SECONDS_IN_YEAR (365.25 * SECONDS_IN_DAY) // Average with leap year

#define sec_to_min(sec) ((double)(sec) / SECONDS_IN_MINUTE)
#define sec_to_hour(sec) ((double)(sec) / SECONDS_IN_HOUR)
#define sec_to_day(sec) ((double)(sec) / SECONDS_IN_DAY)
#define sec_to_week(sec) ((double)(sec) / SECONDS_IN_WEEK)
#define sec_to_month(sec) ((double)(sec) / SECONDS_IN_MONTH)
#define sec_to_year(sec) ((double)(sec) / SECONDS_IN_YEAR)

#define nano_to_micro(nano) ((double)(nano) / 1000)
#define nano_to_millisec(nano) ((double)(nano) / 1000000)
#define nano_to_second(nano) ((double)(nano) / 1000000000)

typedef struct Time_Instance Time_Instance;

Enum(TimeScale,
	TimeScale_UTC,
	TimeScale_TAI,
	TimeScale_TT,
	TimeScale_TDB,
	TimeScale_Relative,
)

Type(DateTime,
	u64 year;   u8  month; 
	u8  week;   u8  day;
	u8  hour;   u8  minute;
	u8  second; u8  timezone;
	u64 nanosec;
)
Type(JuilenTime,
	double time;
	double modified_time;
)


#define date(string) (Date.fromString(push(Date), s(string)))
#define Date(string) (Date.fromString(new(Date),  s(string)))

Class(Date, 
__INIT(inst(Time) time),
__FIELD(
      TimeScale scale;
      union{
      	DateTime   time;
	JuilenTime juilen;
      }date;
),
	interface(Formatter);

      	inst(Time) method(Date, toTime);
      	inst(Date) method(Date, fromString,, inst(String) string);
)




Class(Time,
__INIT(u64 seconds; u64 nanosec),
__FIELD(u64 seconds; u64 nanosec),

	interface(Formatter);
	
	inst(Time) method(Time, GetNow,, TimeScale scale);
	errvt method(Time, Difference,, inst(Time) time2, inst(Time) result);
	bool  method(Time, Compare,, inst(Time) time2, inst(Time) tolerance);
	namespace(Utils,
	    namespace(sec,
		u64 vmethod(toMinutes, u64 sec);
		u64 vmethod(toHours,   u64 sec);
		u64 vmethod(toDays,    u64 sec);
		u64 vmethod(toMonths,  u64 sec);
		u64 vmethod(toYears,   u64 sec);
	    )	
	    namespace(nano,
		u64 vmethod(toMicro,   u64 nanosec);
		u64 vmethod(toMilli,   u64 nanosec);
		u64 vmethod(toSecond,  u64 nanosec);
	    )	
	)
)


Class(TimeWatch,
__INIT(inst(Time) limit; bool start),
__FIELD(inst(Time) start_time;),
	interface(Formatter);

    errvt method(TimeWatch, Start);
    inst(Time) method(TimeWatch, Check);
    inst(Time) method(TimeWatch, Stop);
)


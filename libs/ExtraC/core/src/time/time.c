#include "./time.h"

errvt methodimpl(Time, GetNow){
	
	struct timespec res = {0};

	if(TIME_UTC != timespec_get(&res, TIME_UTC)){ 
	      return ERR(
		ERR_FAIL, "could not get current time");
	}

return Time.FromCTime(self, res);
}

struct timespec methodimpl(Time, ToCTime){
	
return (struct timespec){
		.tv_sec = self->seconds,
		.tv_nsec = self->nanosec
	};
}


inst(TimeTiny)  methodimpl(Time, ToTimeTiny){
	
	u64 time_carry = 0;

	u64 second = self->seconds;
	
	time_carry = self->nanosec / 100000;
	u64 millisecond = time_carry;
	
	time_carry = self->nanosec / 100 - (time_carry * 100);
	u64 microsecond = time_carry;
	
	u64 nanosecond = self->nanosec - (time_carry * 100);

return new(TimeTiny, second, millisecond, microsecond, nanosecond);
}
inst(TimeShort) methodimpl(Time, ToTimeShort){
	
	u64 time_carry = 0,
	days = sec_to_day(self->seconds); 

	time_carry = days;
	u64 day = time_carry;

	time_carry = sec_to_hour(self->seconds) - (time_carry * 24);
	u64 hour = time_carry;

	time_carry = sec_to_min(self->seconds) - (time_carry * 60);
	u64 minute = time_carry;

	u64 second = self->seconds - (time_carry * 60);

return new(TimeShort, day, hour, minute, second);
}
inst(TimeLong)  methodimpl(Time, ToTimeLong){

	u64 time_carry = 0,
	days = sec_to_day(self->seconds); 

	time_carry = days / 365;		
	u64 year = time_carry;

	time_carry = days / 30 - (year * 12);
	u64 month = time_carry;

	time_carry = days / 7 - (month * 4);
	u64 week = time_carry;

	u64 day = days - (week * 30);

return new(TimeLong, year, month, week, day);
}

errvt methodimpl(Time, FromCTime,, struct timespec c_time){
	self->nanosec = c_time.tv_nsec;
	self->seconds = c_time.tv_sec;
return OK;
}

inst(Time) methodimpl(TimeShort, ToTime){
	u64 seconds = 
		(self->day * SECONDS_IN_DAY) +
		(self->hour * SECONDS_IN_HOUR) +
		(self->minute * SECONDS_IN_MINUTE) +
		 self->second;
return new(Time, seconds, 0);
}
inst(Time) methodimpl(TimeLong, ToTime){
	
	u64 seconds = 
		(self->year * SECONDS_IN_YEAR) +
		(self->month * SECONDS_IN_MONTH) +
		(self->week * SECONDS_IN_WEEK) +
		(self->day * SECONDS_IN_DAY);


return new(Time, seconds, 0);
}
inst(Time) methodimpl(TimeTiny, ToTime){
	
	u64 nanosec = 
		(self->millisecond * 100000) +
		(self->microsecond * 100) +
		self->nanosecond;
	
return new(Time, self->second, nanosec);
}
inst(Time) methodimpl(Time, Difference,, inst(Time) time_cmp){

	u64 sec = self->seconds < time_cmp->seconds ?
		time_cmp->seconds - self->seconds :
		self->seconds - time_cmp->seconds;
	
	u64 nsec = self->nanosec < time_cmp->nanosec ?
		time_cmp->nanosec - self->nanosec :
		self->nanosec - time_cmp->nanosec;


return new(Time, sec, nsec);
}

bool methodimpl(Time, Compare,, inst(Time) time_cmp, inst(Time) tolerence){
	
	inst(Time) differ = Time.Difference(self, time_cmp);
	if(tolerence == NULL)
		return   differ->seconds == 0 &&
			 differ->nanosec == 0;
	else{
		return   differ->seconds > tolerence->seconds &&
			 differ->nanosec > tolerence->nanosec;
	}
		
return false;
}
u64 imethodimpl(TimeLong, Print,, FormatID* formats, inst(StringBuilder) out){

	self(TimeLong);

	u64 formated_len =
	StringBuilder.Append(out, NULL,
		"D-", $(self->day),
		" W-", $(self->week),
		" M-", $(self->month),
		" Y-", $(self->year),
		endstr
	);

return formated_len;
}

u64 imethodimpl(TimeLong, Scan,, FormatID* formats, inst(String) in){
	u64 scanned_len = 0;

return scanned_len;
}

private(TimeLong);
construct(TimeLong,
	.ToTime = TimeLong_ToTime,
	.Formatter = {
		.Print = TimeLong_Print, 
		.Scan = TimeLong_Scan
	}
){
      	self->year = args.year;
      	self->month = args.month;
      	self->week = args.week;
      	self->day = args.day;
	
return self;
}

u64 imethodimpl(TimeShort, Print,, FormatID* formats, inst(StringBuilder) out){
	
	self(TimeShort);

	u64 formated_len =
	StringBuilder.Append(out, NULL,
		"Day ", $(self->day),", ",$(self->hour),":",$(self->minute),":",$(self->second), endstr);

return formated_len;
}

u64 imethodimpl(TimeShort, Scan,, FormatID* formats, inst(String) in){
	
	self(TimeShort);
	
	TimeShort_Instance result = {
		.__methods = self->__methods,
		.__private = self->__private,
	};

	u64 i = 0;

	if(
	    in->txt[i]     != 'D' ||
	    in->txt[i + 1] != 'a' ||
	    in->txt[i + 2] != 'y' ||
	    in->txt[i + 3] != ' '
	){
	    ERR(ERR_INVALID, "invalid time string format");
	    return 0;
	}

	i += 4;
	i += String.Scan(String_CutFrntCpy(in, i), $(result.day), endstr) + 1;

	if(' ' != in->txt[i]){
		ERR(ERR_INVALID, "invalid time string format");
		return 0;
	}

	i += 1;
	i += String.Scan(String_CutFrntCpy(in, i), $(result.hour), endstr) + 1;
	i += String.Scan(String_CutFrntCpy(in, i), $(result.minute), endstr) + 1;
	i += String.Scan(String_CutFrntCpy(in, i), $(result.second), endstr) + 1;
	*self = result;
return i;
}


private(TimeShort);
construct(TimeShort,
	.ToTime = TimeShort_ToTime,
	.Formatter = {
		.Print = TimeShort_Print,
		.Scan = TimeShort_Scan
	}
){

	self->day = args.day;
	self->hour = args.hour;
	self->minute = args.minute;
	self->second = args.second;
	
return self;
}

u64 imethodimpl(TimeTiny, Print,, FormatID* formats, inst(StringBuilder) out){

	self(TimeTiny);

	u64 formated_len =
	StringBuilder.Append(out, NULL, 
		$(self->second), " sec, ",
		$(self->millisecond)," ms, ",
		$(self->microsecond)," us, ",
		$(self->nanosecond)," ns", 
		endstr);

return formated_len;
}

u64 imethodimpl(TimeTiny, Scan,, FormatID* formats, inst(String) in){
	u64 scanned_len = 0;

return scanned_len;
}

private(TimeTiny);
construct(TimeTiny,
	.ToTime = TimeTiny_ToTime,
	.Formatter = {
		.Print = TimeTiny_Print,
		.Scan = TimeTiny_Scan
	}
){

	self->second = args.second;
	self->millisecond = args.millisecond;
	self->microsecond = args.microsecond;
	self->nanosecond = args.nanosecond;
	
return self;
}

u64 imethodimpl(Time, Print,, FormatID* formats, inst(StringBuilder) out){
	
	self(Time);

	return StringBuilder.Append(out, NULL,
		$(self->seconds), " secs, ",
		$(self->nanosec), " nsecs",
		endstr
	);
}


private(Time);
construct(Time,
	.FromCTime = Time_FromCTime,
	.ToTimeLong = Time_ToTimeLong,
	.ToTimeShort = Time_ToTimeShort,
	.ToTimeTiny = Time_ToTimeTiny,
	.Compare = Time_Compare,
	.Difference = Time_Difference,
	.GetNow = Time_GetNow,
	.Formatter = {
		.Print = Time_Print

	}
){

	self->nanosec = args.nanosec;
	self->seconds = args.seconds;

return self;
}





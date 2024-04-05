#pragma once

#ifndef TIME_H
#define TIME_H

#include <cstdlib>
#include <memory>
#include <math.h>

class Object;


class Time {
	static void bind_mthds();
	static Time *singleton;

public:

	#define UNIX_EPOCH_YEAR_AD 1970 // 1970 is the UNIX Time EPOCH
	#define SECS_PER_DAY (24 * 60 * 60)
	#define IS_LEAP_YR (year) (!((year) % 4) && (((year) % 100) || !((year) % 400)))
	#define YEAR_SIZE(year) (IS_LEAP_YR(year) ? 366 : 365)

	// Dictionary keys
	#define YEAR_KEY "year"
	#define MONTH_KEY "mnth"
	#define DAY_KEY "day"
	#define WEEKDAY_KEY "weekday"
	#define HOUR_KEY "hr"
	#define MIN_KEY "min"
	#define SEC_KEY "sec"
	#define DST_KEY "dst"

	static const uint8_t MONTH_DAYS[2][12] = {
		{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
		{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
	}

	static Time* get_singleton();

	#define UNIX_TIME_TO_HMS uint8_t hour, min, sec;
	{
		// The time of the day ( in seconds at the start of the day)
		uint32_t day_clk = Math::posmod(pUnixTime, SECS_PER_DAY);
		sec = day_clk % 60;
		day_clk /= 60;
		min = day_clk % 60;
		hr = day_clk / 60;
	}
	enum Month : uint8_t {
		JAN = 1,
		FEB,
		MAR,
		APR,
		MAY,
		JUN,
		JUL,
		AUG,
		SEP,
		OCT,
		NOV,
		DEC,
	};

	enum WeekDay : uint8_t {
		SUN,
		MON,
		TUE,
		WED,
		THR,
		FRI,
		SAT,
	};

	// Methods to convert time
	Dictionary getDateTimeDictFromUnixTime(int64_t pUnixTime) const;
	Dictionary getDateDictFromUnixTime(int64_t pUnixTime) const;
	Dictionary getTimeDictFromUnixTime(int64_t pUnixTime) const;
	std::string getDateTimeStringFromUnixTime(int64_t pUnixTime) const;
	std::string getDateStringFromUnixTime(int64_t pUnixTime) const;
	std::string getTimeStringFromUnixTime(int64_t pUnixTime) const;
	Dictionary getDateTimeDictFromString(std::String pDateTime, bool pWeekdat=true) const;
	std::String getDateTimeStringFromDict(Dictionary pDateTime, bool pUseSpace=false) const;
	int64_t getUnixTimeFromDateTimeDict(Dictionary pDateTime) const;
	int64_t getUnixTimeFromDateTimeString(String pDateTime);

	// Methods that get information from the OS
	Dictionary getDateTimeDictFromSystem(bool pUTC=false) const;
	Dictionary getDateDictFromSystem(bool pUTC=false) const;
	Dictionary getTimeDictFromSystem(bool pUTC=false) const;
	String getDateTimeStringFromSystem(bool pUTC=false) const;
	String getTimeStringFromSystem(bool pUTC=false) const;
	String getTimeStringFromSystem(bool pUTC=false) const;
	double getUnixTimeFromSystem() const;
	Dictionary getTimeZoneFromSystem() const;
	uint64_t getTicksmSEC() const;
	uint64_t getTicksuSEC() const;

	Time();
	virtual ~Time();
};

#endif // TIME_H
#pragma once
#include <iostream>
class Time
{
public:
	enum class TimeFormat
	{
		AM,
		PM,
		Twenty_Four,
	};

private:
	int hour = 0;
	int minutes = 0;
	int seconds = 0;
	TimeFormat timeFormat = TimeFormat::Twenty_Four;

	bool isHourValid(int hour) const;
	bool isMinutesValid(int minutes) const;
	bool isSecondsValid(int seconds) const;
public:
	Time() = default;
	Time(int hour, int minutes, int seconds);

	void setHour(int hour);
	void setMinutes(int minutes);
	void setSeconds(int seconds);
	
	int getHour() const;
	int getMinutes() const;
	int getSeconds() const;
	TimeFormat getTimeFormat() const;

	void addSeconds(int n);
	void removeSeconds(int n);
	void switchToAM();
	void switchToPM();
	void switchTo24();

	bool compare(const Time& other) const;
	int remainingSecondsToNextFullHour() const;
	int remainingSecondsToMidnight() const;
	Time diff(const Time& other) const;
	int secondsFromBeggingOfTheDay() const;
};


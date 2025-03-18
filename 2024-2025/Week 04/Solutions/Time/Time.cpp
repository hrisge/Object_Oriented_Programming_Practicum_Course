#include "Time.h"

bool Time::isHourValid(int hour) const
{
    return(hour >= 0 && hour < 12) || (hour >= 0 && hour < 24 && TimeFormat::Twenty_Four == getTimeFormat());        
}

bool Time::isMinutesValid(int minutes) const
{
    return minutes >= 0 && minutes < 60;
}

bool Time::isSecondsValid(int seconds) const
{
    return seconds >= 0 && seconds < 60;
}

int Time::secondsFromBeggingOfTheDay() const
{
    int toReturn = getSeconds() + 60 * getMinutes();
    if (getTimeFormat() == TimeFormat::PM)
        toReturn += 12 * 60 * 60;
    toReturn += 12 * 60 * getHour();
    return toReturn;
}

Time::Time(int hour, int minutes, int seconds)
{
    setHour(hour);
    setMinutes(minutes);
    setSeconds(seconds);
}

void Time::setHour(int hour)
{
    if (isHourValid(hour))
        this->hour = hour;
    else
        this->hour = 0;
}

void Time::setMinutes(int minutes)
{
    if (isMinutesValid(minutes))
        this->minutes = minutes;
    else
        this->minutes = 0;
}

void Time::setSeconds(int seconds)
{
    if (isSecondsValid(seconds))
        this->seconds = seconds;
    else
        this->seconds = 0;
}

int Time::getHour() const
{
    return hour;
}

int Time::getMinutes() const
{
    return minutes;
}

int Time::getSeconds() const
{
    return seconds;
}

Time::TimeFormat Time::getTimeFormat() const
{
    return timeFormat;
}

void Time::addSeconds(int n)
{
    int temp = getSeconds() + n;
    if (temp < 60) {
        setSeconds(temp);
        return;
    }

    setSeconds(temp % 60);
    int temp2 = getMinutes() + (temp / 60);
    if (temp2 < 60) {
        setMinutes(temp2);
        return;
    }

    int temp3 = getHour() + (temp2 / 60);
    if ((temp3 < 12) || (temp3 < 24 && getTimeFormat() == TimeFormat::Twenty_Four)) {
        setHour(temp3);
        return;
    }
    else if (getTimeFormat() == TimeFormat::Twenty_Four) {
        setHour(temp3 / 24);
        return;
    }

    setHour(temp3 / 12);
}

void Time::removeSeconds(int n)
{
    int temp = getSeconds() - n;
    if (temp >= 0) {
        setSeconds(temp);
        return;
    }

    int minsToTake = std::abs((temp / 60) - 1);
    if (minsToTake < getMinutes()) {
        setMinutes(getMinutes() - minsToTake);
        setSeconds(60 + getSeconds() + (temp % 60));
        return;
    }

    int hourToTake = (minsToTake / 60) + 1;
    if (hourToTake > getHour()) {
        setHour(0);
        setMinutes(0);
        setSeconds(0);
        return;
    }

    setHour(getHour() - hourToTake);
    setMinutes(getMinutes() + 60 - minsToTake);
    setSeconds(60 + getSeconds() + (temp % 60));
}

void Time::switchToAM()
{
    if (getTimeFormat() == TimeFormat::Twenty_Four) 
        setHour(getHour() - 12);

    timeFormat = TimeFormat::AM;
}

void Time::switchToPM()
{
    if (getTimeFormat() == TimeFormat::Twenty_Four)
        setHour(getHour() - 12);

    timeFormat = TimeFormat::PM;
}

void Time::switchTo24()
{
    if (getTimeFormat() == TimeFormat::PM)
        setHour(getHour() + 12);
    timeFormat = TimeFormat::Twenty_Four;
}

bool Time::compare(const Time& other) const
{
    return secondsFromBeggingOfTheDay() - other.secondsFromBeggingOfTheDay() > 0;
}

int Time::remainingSecondsToNextFullHour() const
{
    return 60 * (60 - getMinutes()) + (60 - getSeconds());
}

int Time::remainingSecondsToMidnight() const
{
    return 60 * 60 * 24 - secondsFromBeggingOfTheDay();
}

Time Time::diff(const Time& other) const
{
    Time toReturn;
    int diffSeconds = std::abs(secondsFromBeggingOfTheDay() - other.secondsFromBeggingOfTheDay());

    toReturn.setHour(diffSeconds / (60 * 60));
    diffSeconds -= toReturn.getHour() * 60 * 60;
    toReturn.setMinutes(diffSeconds / 60);
    diffSeconds -= toReturn.getMinutes() * 60;
    toReturn.setSeconds(diffSeconds);

    return toReturn;
}

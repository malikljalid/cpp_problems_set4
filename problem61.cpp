#include <iostream>

enum enDateComparaisonCases { OLDER = -1, EQUAL, LATEST };

struct stDate
{
    short int Day;
    short int Month;
    short int Year;
};

struct stPeriod
{
    stDate      StartDate;
    stDate      EndDate;
    short int   DurationDays;
};

stDate initDate(short int Day, short int Month, short int Year)
{
    stDate Date;

    Date.Day    =   Day;
    Date.Month  =   Month;
    Date.Year   =   Year;

    return (Date);
}

int readNumber(std::string msg)
{
    int Number;

    std::cout << msg;
    std::cin >> Number;

    return (Number);
}

bool Date1IsLatestThanDate2(stDate date1, stDate date2)
{
    return ((date1.Year > date2.Year) ||
            (date1.Year == date2.Year && date1.Month > date2.Month) ||
            (date1.Year == date2.Year && date1.Month == date2.Month && date1.Day > date2.Day));
}

bool Date1IsEqualToDate2(stDate date1, stDate date2)
{
    return (date1.Year == date2.Year && date1.Month == date2.Month && date1.Day == date2.Day);
}

bool Date1IsOlderThanDate2(stDate date1, stDate date2)
{
    return (!Date1IsEqualToDate2(date1, date2) && !Date1IsLatestThanDate2(date1, date2));
}

enDateComparaisonCases compareTwoDates(stDate date, stDate toCompareWith)
{
    return (Date1IsEqualToDate2(date, toCompareWith) ? EQUAL : (Date1IsLatestThanDate2(date, toCompareWith) ? LATEST : OLDER));
}

bool leapYear(short int year)
{
    return ((year % 4 == 0) ? ((year % 100 == 0) ? ((year % 400 == 0) ? true : false ) : true) : false);
}

short int getMonthDays(short int Month, short int Year)
{
    short int listOfDays[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return ((Month == 2) ? (leapYear(Year) ? 29 : 28) : listOfDays[Month]); 
}

bool isLastDayInMonth(short int Day, short int Month, short int Year)
{
    return (Day == getMonthDays(Month, Year));
}

bool isLastMonth(short int Month)
{
    return (Month == 12);
}

stDate increaseDateByOneDay(stDate Date)
{
    if (isLastDayInMonth(Date.Day, Date.Month, Date.Year))
    {
        if (isLastMonth(Date.Month))
        {
            Date.Year++;
            Date.Month = 1;
        }
        else
            Date.Month++;

        Date.Day = 1;
    }
    else
        Date.Day++;

    return (Date);
}

int differenceBetweenDate1AndDate2(stDate date1, stDate date2)
{
    int DaysDifference = 0;

    if (Date1IsEqualToDate2(date1, date2))
        return (0);

    if (Date1IsLatestThanDate2(date1, date2))
    {
        while (Date1IsEqualToDate2(date1, date2) == false)
        {
            date2 = increaseDateByOneDay(date2);
            DaysDifference++;
        }
        return (DaysDifference);
    }

    return (differenceBetweenDate1AndDate2(date2, date1));
}

int setPeriodDurationInDays(stPeriod Period)
{
    return (differenceBetweenDate1AndDate2(Period.StartDate, Period.EndDate));
}

stPeriod initPeriod(void)
{
    stPeriod Period;

    std::cout << "Period 1 Start Date ?\n";
    Period.StartDate   = initDate(readNumber(" Please enter Day   : "), readNumber(" Please enter Month : "), readNumber(" Please enter Year  : "));
    std::cout << "Period 1 End Date ?\n";
    Period.EndDate     = initDate(readNumber(" Please enter Day   : "), readNumber(" Please enter Month : "), readNumber(" Please enter Year  : "));

    Period.DurationDays = setPeriodDurationInDays(Period);

    return (Period);
}

bool periodsOverlap(stPeriod period1, stPeriod period2)
{
    enDateComparaisonCases Period1StartVsPeriod2End   = compareTwoDates(period1.StartDate, period2.EndDate);
    enDateComparaisonCases Period1EndVsPeriod2Start   = compareTwoDates(period1.EndDate, period2.StartDate);

    if (Period1StartVsPeriod2End == LATEST || Period1EndVsPeriod2Start == OLDER)
        return (false);

    return (true);
}

stDate getOlderDate(stDate date1, stDate date2)
{
    if (compareTwoDates(date1, date2) == OLDER)
        return (date1);
    return (date2);
}

stDate getLatestDate(stDate date1, stDate date2)
{
    if (compareTwoDates(date1, date2) == LATEST)
        return (date1);
    return (date2);
}

int getOverlapDaysWithin2Periods(stPeriod period1, stPeriod period2)
{
    stDate startOfOverlap           = getLatestDate(period1.StartDate, period2.StartDate);
    stDate endOfOverlap             = getOlderDate(period1.EndDate, period2.EndDate);
    bool   periodsDoesNotOverlap    = !periodsOverlap(period1, period2);

    if (periodsDoesNotOverlap)
        return (0);

    return (differenceBetweenDate1AndDate2(startOfOverlap, endOfOverlap));
}

int main(void)
{
    stPeriod period1 = initPeriod();
    stPeriod period2 = initPeriod();

    std::cout << "Days of overlap between 2 periods : " << getOverlapDaysWithin2Periods(period1, period2);

    return (0);
}

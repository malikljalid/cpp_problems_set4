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

bool periodsOverlap(stPeriod period1, stPeriod period2)
{
    enDateComparaisonCases Period1StartVsPeriod2End   = compareTwoDates(period1.StartDate, period2.EndDate);
    enDateComparaisonCases Period1EndVsPeriod2Start   = compareTwoDates(period1.EndDate, period2.StartDate);

    if (Period1StartVsPeriod2End == LATEST || Period1EndVsPeriod2Start == OLDER)
        return (false);

    return (true);
}

int main(void)
{
    stPeriod period1;
    stPeriod period2;

    std::cout << "Period 1 Start Date ?\n";
    period1.StartDate   = initDate(readNumber(" Please enter Day   : "), readNumber(" Please enter Month : "), readNumber(" Please enter Year  : "));
    std::cout << "Period 1 End Date ?\n";
    period1.EndDate     = initDate(readNumber(" Please enter Day   : "), readNumber(" Please enter Month : "), readNumber(" Please enter Year  : "));

    std::cout << "Period 2 Start Date ?\n";
    period2.StartDate   = initDate(readNumber(" Please enter Day   : "), readNumber(" Please enter Month : "), readNumber(" Please enter Year  : "));
    std::cout << "Period 2 End Date ?\n";
    period2.EndDate     = initDate(readNumber(" Please enter Day   : "), readNumber(" Please enter Month : "), readNumber(" Please enter Year  : "));


    if (periodsOverlap(period1, period2))
        std::cout << "YES!.. Periods do OVERLAP wow!\n";
    else
        std::cout << "Periods do NOT overlap.\n";

    return (0);
}

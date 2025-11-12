#include <iostream>

enum enDateComparaisonCases { OLDER = -1, EQUAL, LATEST };

struct stDate
{
    short int Day;
    short int Month;
    short int Year;
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

int main(void)
{
    stDate date1 = initDate(readNumber(" Please enter Date1 Day   : "), readNumber(" Please enter Date1 Month : "), readNumber(" Please enter Date1 Year  : "));
    stDate date2 = initDate(readNumber(" Please enter Date2 Day   : "), readNumber(" Please enter Date2 Month : "), readNumber(" Please enter Date2 Year  : "));

    std::cout << "Compare results : " << compareTwoDates(date1, date2) << std::endl;

    return (0);
}

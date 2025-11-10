#include <iostream>

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

bool leapYear(short int year)
{
    return ((year % 4 == 0) ? ((year % 100 == 0) ? ((year % 400 == 0) ? true : false ) : true) : false);
}

short int getMonthDays(short int Month, short int Year)
{
    short int listOfDays[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return ((Month == 2) ? (leapYear(Year) ? 29 : 28) : listOfDays[Month]); 
}

short int getNumberOfDaysFromStartOf(short int Day, short int Month, short int Year)
{
    short int Days = Day;

    for (short int i = 1; i < Month; i++)
        Days += getMonthDays(i, Year);

    return (Days);
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

int  differenceBetweenDate1AndDate2(stDate date1, stDate date2)
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

int  differenceBetweenDate1AndDate2(stDate date1, stDate date2, bool includeEndDay)
{
    return (differenceBetweenDate1AndDate2(date1, date2) + includeEndDay);
}

int main(void)
{
    stDate date1 = initDate(readNumber(" Please enter Date1 Day   : "), readNumber(" Please enter Date1 Month : "), readNumber(" Please enter Date1 Year  : "));
    stDate date2 = initDate(readNumber(" Please enter Date2 Day   : "), readNumber(" Please enter Date2 Month : "), readNumber(" Please enter Date2 Year  : "));

    std::cout << "Difference between 2 dates is : " << differenceBetweenDate1AndDate2(date1, date2) << " Day(s)" << std::endl;
    std::cout << "Difference between 2 dates is : " << differenceBetweenDate1AndDate2(date1, date2, false) << " Day(s)" << std::endl;
    std::cout << "Difference between 2 dates is : " << differenceBetweenDate1AndDate2(date1, date2, true) << " Day(s)" << std::endl;

    return (0);
}

#pragma  warning(4996)
#include <iostream>
#include <ctime>

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

stDate getTodayDate(void)
{
    time_t  timeNow = time(NULL);
    tm     *DateNow = localtime(&timeNow);

    return (initDate(DateNow->tm_mday, DateNow->tm_mon + 1, DateNow->tm_year + 1900));
}

int main(void)
{
    stDate myBirthday = initDate(readNumber("Please enter Your Birthday Day   : "), readNumber("Please enter Your Birthday Month : "), readNumber("Please enter Your Birthday Year  : "));

    std::cout << "Difference between your Birthday and today is : " << differenceBetweenDate1AndDate2(myBirthday, getTodayDate()) << " Day(s)." << std::endl;

    return (0);
}

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

void printDate(stDate Date)
{
    std::cout << Date.Day << "/" << Date.Month << "/" << Date.Year << std::endl;
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

stDate decreaseDateByOneDay(stDate Date)
{
    if (Date.Day == 1)
    {
        if (Date.Month == 1)
        {
            Date.Year--;
            Date.Month = 12;
        }
        else
            Date.Month--;

        Date.Day = getMonthDays(Date.Month, Date.Year);
    }
    else
        Date.Day--;

    return (Date);
}

stDate decreaseDateByXDays(stDate Date, short int DaysToSub)
{
    while (DaysToSub--)
        Date = decreaseDateByOneDay(Date);

    return (Date);
}

stDate decreaseDateByOneWeek(stDate Date)
{
    return (decreaseDateByXDays(Date, 7));
}

int main(void)
{
    short int Year  = readNumber(" Please enter a Year  : ");
    short int Month = readNumber(" Please enter a Month : ");
    short int Day   = readNumber(" Please enter a Day   : ");


    stDate Date = initDate(Day, Month, Year);

    printDate(Date);
    printDate(decreaseDateByOneWeek(Date));

    return (0);
}

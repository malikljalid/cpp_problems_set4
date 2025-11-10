#include <iostream>

struct stDate
{
    short int Day;
    short int Month;
    short int Year;
};

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

int main(void)
{
    short int Year  = readNumber(" Please enter a Year  : ");
    short int Month = readNumber(" Please enter a Month : ");
    short int Day   = readNumber(" Please enter a Day   : ");


    stDate Date = initDate(Day, Month, Year);

    printDate(Date);
    printDate(increaseDateByOneDay(Date));

    return (0);
}

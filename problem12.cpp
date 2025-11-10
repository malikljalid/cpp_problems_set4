#include <iostream>
#include <iomanip>
#include <cmath>

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

short int last2DigitsOf(int Number)
{
    return (Number % 100);
}

short int first2DigitsOf(int Number)
{
    return (Number / 100);
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

stDate getDDMMYYfromDaysFromStartOfYear(short Year, short int DaysFromStartOfYear)
{
    stDate      Date;
    short int   Month = 0;

    for (Month = 1; Month < 12; Month++)
    {
        if (DaysFromStartOfYear < getMonthDays(Month, Year))
            break;
        DaysFromStartOfYear -= getMonthDays(Month, Year);
    }

    if (Month == 12 && DaysFromStartOfYear > getMonthDays(12, Year))
        return (getDDMMYYfromDaysFromStartOfYear(Year + 1, DaysFromStartOfYear - getMonthDays(12, Year)));
    
    Date.Day    = DaysFromStartOfYear;
    Date.Month  = Month;
    Date.Year   = Year;

    return (Date); 
}

void printNumberOfDaysFromStartOf(short int Day, short int Month, short int Year)
{
    std::cout << "\nNumber of days form the beggining of " << Year << " is : " << getNumberOfDaysFromStartOf(Day, Month, Year) << std::endl;
}

void printDateFromGivenDaysFromStartOfYear(int Year, int DaysFromStartOfYear)
{
    stDate Date = getDayMonthYearFromSumOfDaysFromStartOfYear(Year, DaysFromStartOfYear);

    std::cout << "Date : " << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";
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

    printDate(getDDMMYYfromDaysFromStartOfYear(Year, readNumber("How many days you want to add ? : ")));

    return (0);
}

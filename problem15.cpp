#include <iostream>

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

bool isLastDayInMonth(short int Day, short int Month, short int Year)
{
    return (Day == getMonthDays(Month, Year));
}

bool isLastMonth(short int Month)
{
    return (Month == 12);
}

void printIfMonthAndDayAreLast(short int Day, short Month, short int Year)
{
    if (isLastDayInMonth(Day, Month, Year))
        std::cout << "Yes, this is day in " << Month << std::endl;
    else
        std::cout << "No, this is NOT last day in " << Month << std::endl;
    
    if (isLastMonth(Month))
        std::cout << "Yes, this is last month in the year\n";
    else
        std::cout << "Yes, this is NOT last month in the year\n";
}

int main(void)
{
    printIfMonthAndDayAreLast(readNumber("Enter Day : "), readNumber("Enter Month : "), readNumber("Enter Year : "));

    return (0);
}

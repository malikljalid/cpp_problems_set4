#include <iostream>
#include <iomanip>
#include <cmath>

int readNumber(std::string msg)
{
    int Number;

    std::cout << "Please enter a " << msg << " : ";
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
    short int listOfDays[13] = { 0, 31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return ((Month == 2) ? (leapYear(Year) ? 29 : 28) : listOfDays[Month]); 
}

short int getNumberOfDaysFromStartOf(short int Day, short int Month, short int Year)
{
    short int Days = Day;

    for (short int i = 1; i <= Month; i++)
        Days += getMonthDays(i, Year);

    return (Days);
}

void printNumberOfDaysFromStartOf(short int Day, short int Month, short int Year)
{
    std::cout << "\nNumber of days form the beggining of " << Year << " is : " << getNumberOfDaysFromStartOf(Day, Month, Year) << std::endl;
}

int main(void)
{
    printNumberOfDaysFromStartOf(readNumber("Day"), readNumber("Month"), readNumber("Year"));

    return (0);
}

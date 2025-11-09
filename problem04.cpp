#include <iostream>

int readNumber(void)
{
    int Number;

    std::cout << "Please enter a Year to check : ";
    std::cin >> Number;

    return (Number);
}

bool leapYear(short int year)
{
    return ((year % 4 == 0) ? ((year % 100 == 0) ? ((year % 400 == 0) ? true : false ) : true) : false);
}

void printYearData(short int Year)
{
    int Days    = leapYear(Year) ? 366 : 365;
    int Hours   = Days * 24;
    int Minutes = Hours * 60;
    int Seconds = Minutes * 60;

    std::cout << std::endl;
    std::cout << "Days in " << Year << " : " << Days << std::endl;
    std::cout << "Hours in " << Year << " : " << Hours << std::endl;
    std::cout << "Minutes in " << Year << " : " << Minutes << std::endl;
    std::cout << "Seconds in " << Year << " : " << Seconds << std::endl;
}

int main(void)
{
    printYearData(readNumber());

    return (0);
}

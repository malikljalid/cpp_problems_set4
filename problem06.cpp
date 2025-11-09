#include <iostream>

int readNumber(std::string msg)
{
    int Number;

    std::cout << "Please enter a " << msg << " to check : ";
    std::cin >> Number;

    return (Number);
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

void printMonthData(short int Month, short int Year)
{
    std::string _months[13] = { "", "January", "February", "March", "April", "Mai", "June", "July", "Aghust", "September", "October", "Novemeber", "December" };

    int Days    = getMonthDays(Month, Year);
    int Hours   = Days * 24;
    int Minutes = Hours * 60;
    int Seconds = Minutes * 60;

    std::cout << std::endl;
    std::cout << "Days in " << _months[Month] << " : " << Days << std::endl;
    std::cout << "Hours in " << _months[Month] << " : " << Hours << std::endl;
    std::cout << "Minutes in " << _months[Month] << " : " << Minutes << std::endl;
    std::cout << "Seconds in " << _months[Month] << " : " << Seconds << std::endl;
}

int main(void)
{
    printMonthData(readNumber("Month"), readNumber("Year"));

    return (0);
}

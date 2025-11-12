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

bool dateIsValid(stDate Date)
{
    if (Date.Month < 1 || Date.Month > 12)
        return (false);
    if (Date.Day < 1 || Date.Day > getMonthDays(Date.Month, Date.Year))
        return (false);
    return (true);
}

int main(void)
{
    stDate date1 = initDate(readNumber("Please enter a day : "), readNumber("Please enter a Month : "), readNumber("Please enter a Year : "));

    if (dateIsValid(date1))
        std::cout << "Date is VALID !\n";
    else
        std::cout << "Date is NOT valid.\n";
    return (0);
}

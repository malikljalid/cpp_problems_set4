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

bool Date1IsLessThanDate2(stDate date1, stDate date2)
{
    if (date1.Year > date2.Year)
        return (true);
    else if (date1.Month > date2.Month)
        return (true);
    else if (date1.Day > date2.Day)
        return (true);

    return (false);
}

int main(void)
{
    stDate date1 = initDate(readNumber(" Please enter a Day   : "), readNumber(" Please enter a Month : "), readNumber(" Please enter a Year  : "));
    stDate date2 = initDate(readNumber(" Please enter a Day   : "), readNumber(" Please enter a Month : "), readNumber(" Please enter a Year  : "));

    return (0);
}

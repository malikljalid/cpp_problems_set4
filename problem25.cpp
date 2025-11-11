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

stDate increaseDateByOneYear(stDate Date)
{
    Date.Year++;

    return (Date);
}

int main(void)
{
    short int Year  = readNumber(" Please enter a Year  : ");
    short int Month = readNumber(" Please enter a Month : ");
    short int Day   = readNumber(" Please enter a Day   : ");


    stDate Date = initDate(Day, Month, Year);

    printDate(Date);
    printDate(increaseDateByOneYear(Date));

    return (0);
}

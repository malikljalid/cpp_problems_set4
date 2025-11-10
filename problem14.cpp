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

bool Date1IsEqualToDate2(stDate date1, stDate date2)
{
    return (date1.Year == date2.Year && date1.Month == date2.Month && date1.Day == date2.Day);
}

int main(void)
{
    stDate date1 = initDate(readNumber(" Please enter Date1 Day   : "), readNumber(" Please enter Date1 Month : "), readNumber(" Please enter Date1 Year  : "));
    stDate date2 = initDate(readNumber(" Please enter Date2 Day   : "), readNumber(" Please enter Date2 Month : "), readNumber(" Please enter Date2 Year  : "));

    if (Date1IsEqualToDate2(date1, date2))
        std::cout << "Yes, Date1 is EQUAL To Date 2.\n";
    else
        std::cout << "No, Date1 is NOT equal Date 2.\n";

    return (0);
}

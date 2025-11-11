#include <iostream>
#include <cmath>

enum enDayOfWeek { SAT, SUN, MON, TUE, WED, THU, FRI };

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

    std::cout << "Please enter a " << msg << " : ";
    std::cin >> Number;

    return (Number);
}

std::string dayName(enDayOfWeek Day)
{
    std::string week[7] = { "Saturday", "Sunday", "Monday", "Thuesday", "Wedensday", "Thursday", "Friday" };

    return (week[Day]);
}

short int last2DigitsOf(int Number)
{
    return (Number % 100);
}

short int first2DigitsOf(int Number)
{
    return (Number / 100);
}

short int zeller_formula(short int Day, short int Month, short int Year)
{
    if (Month < 3)
    {
        Month += 12;
        Year  -= 1;
    }

    return ((Day + (int)std::floor(13 * (Month + 1) / (double)5) + last2DigitsOf(Year) + (int)std::floor(last2DigitsOf(Year) / (double)4) + (int)std::floor(first2DigitsOf(Year) / (double)4) + 5 * first2DigitsOf(Year)) % 7);
}

enDayOfWeek zeller_formula(stDate Date)
{
    return ((enDayOfWeek)zeller_formula(Date.Day, Date.Month, Date.Year));
}

void printDayOfWeek(stDate Date)
{
    std::cout << "\nToday is : " << dayName(zeller_formula(Date)) << ", ";
    printDate(Date);
    std::cout << std::endl;
}

int main(void)
{
    stDate Date = initDate(readNumber("day"), readNumber("month"), readNumber("year"));

    printDayOfWeek(Date);


    return (0);
}

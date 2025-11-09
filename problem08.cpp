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

short int zeller_formula(short int Day, short int Month, short int Year)
{
    if (Month < 3)
    {
        Month += 12;
        Year  -= 1;
    }

    return ((Day + (int)std::floor(13 * (Month + 1) / (double)5) + last2DigitsOf(Year) + (int)std::floor(last2DigitsOf(Year) / (double)4) + (int)std::floor(first2DigitsOf(Year) / (double)4) + 5 * first2DigitsOf(Year)) % 7);
}

short int zeller_to_sakamoto(short int zeller)
{
    if (zeller > 0)
        return (zeller - 1);
    return (6);
}

void printDayOfWeek(short int Day, short int Month, short int Year)
{
    std::string week[7] = { "Saturday", "Sunday", "Monday", "Thuesday", "Wedensday", "Thursday", "Friday" };

    std::cout << "it's " << week[zeller_formula(Day, Month, Year)] << " Baby !" << std::endl;
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

void showCalendar(short int Month, short int Year)
{
    std::string _m[13] = { "", "Jan", "Feb", "Mar", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

    short int firstDay = zeller_to_sakamoto(zeller_formula(1, Month, Year));
    short int lastDay  = getMonthDays(Month, Year);

    std::cout << "   _____________ " << _m[Month] << " _______________\n\n";
    std::cout << "   Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

    for (int i = 0; i < firstDay; i++)
        printf("     ");
    for (int i = firstDay, j = 1; j <= lastDay; j++)
    {
        printf("%5d", j);
        if (++i == 7)
        {
            i = 0;
            printf("\n");
        }
    }

    std::cout << "\n   _________________________________\n";
}

int main(void)
{
    // showCalendar(readNumber("Month"), readNumber("Year"));
    // showCalendar(1, 2024);
    // showCalendar(12, 2024);
    showCalendar(1, 2025);
    showCalendar(2, 2025);
    showCalendar(3, 2025);

    return (0);
}

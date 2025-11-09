#include <iostream>
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
        Year  += 1;
    }

    return ((Day + (int)std::floor(13 * (Month + 1) / (double)5) + last2DigitsOf(Year) + (int)std::floor(last2DigitsOf(Year) / (double)4) + (int)std::floor(first2DigitsOf(Year) / (double)4) + 5 * first2DigitsOf(Year)) % 7);
}

void printDayOfWeek(short int Day, short int Month, short int Year)
{
    std::string week[7] = { "Saturday", "Sunday", "Monday", "Thuesday", "Wedensday", "Thursday", "Friday" };

    std::cout << "it's " << week[zeller_formula(Day, Month, Year)] << " Baby !" << std::endl;
}

int main(void)
{
    printDayOfWeek(readNumber("Day"), readNumber("Month"), readNumber("Year"));

    return (0);
}

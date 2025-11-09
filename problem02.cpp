#include <iostream>

int readNumber(void)
{
    int Number;

    std::cout << "Please enter a number : ";
    std::cin >> Number;

    return (Number);
}

bool leapYear(short int year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
                return (true);
            else
                return (false);
        }
        return (true);
    }

    return (false);
}

int main(void)
{
    if (leapYear(readNumber()))
        std::cout << "Leap Year\n";
    else
        std::cout << "NOT a Leap Year!\n";
    
    return (0);
}

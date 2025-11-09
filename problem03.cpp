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
    return ((year % 4 == 0) ? ((year % 100 == 0) ? ((year % 400 == 0) ? true : false ) : true) : false);
}

int main(void)
{
    if (leapYear(readNumber()))
        std::cout << "Leap Year\n";
    else
        std::cout << "NOT a Leap Year!\n";
    
    return (0);
}

#include <iostream>
#include <cstdlib>
#include <string>

std::string a[10] = { "one", "two", "three", "for", "five", "six", "seven", "egth", "nine" };
std::string b[10] = { "eleven", "twelve", "therthteen", "forthteen", "fivetheen", "sixtheen", "seventheen", "egththeen", "nineteen" };
std::string c[10] = { "ten", "twenty", "threthy", "forthy", "fivethy", "sixthy", "seventhy", "egthy", "ninethy" };
std::string d[10] = { "hundred", "tousend", "million", "billion", "trilion" };

int readNumber(void)
{
    int Number;

    std::cout << "Please enter a number : ";
    std::cin >> Number;

    return (Number);
}

short int digit(char c)
{
    return (c - '0');
}

std::string stringFormatOf(int Number)
{
    std::string s = "";

    if (Number > 99)
        s = std::to_string(Number);
    else if (Number > 9)
        s = "0" + std::to_string(Number);
    else
        s = "00" + std::to_string(Number);
    
    return (s);
}

void printHunderedPart(std::string s)
{
    if (s[0] != '0')
        std::cout << a[digit(s[0]) - 1] << " " << d[0] << " ";
    if (s[1] != '0')
    {
        if (s[1] == '1' && s[2] != 0)
            std::cout << b[digit(s[2]) - 1] << " ";
        else
            std::cout << c[digit(s[1]) -1] << " ";
    }
    if (s[2] != '0' && s[1] != '1')
        std::cout << a[digit(s[2]) - 1] << " ";
}

void printNumberInLetters(int x, int i)
{
    int rest = x % 1000;
    int div  = x / 1000;

    if (div != 0)
        printNumberInLetters(div, i + 1);

    std::string hunderedPart = stringFormatOf(rest);
    
    printHunderedPart(hunderedPart);

    if (i > 0)
        std::cout << d[i] << " ";
}

int main(void)
{
    printNumberInLetters(readNumber(), 0);

    return (0);
}

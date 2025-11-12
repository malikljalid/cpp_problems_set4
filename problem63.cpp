#include <iostream>
#include <string>

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

void printString(std::string str)
{
    std::cout << "Your date string : " << str << std::endl;
}

std::string readString(void)
{
    std::string S;

    std::cout << "Please enter Date in format DD/MM/YYY : ";
    std::cin >> S;

    return (S);
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

stDate stringToDate(std::string strDate)
{
    short  int  i = 0;
    stDate      Date;

    i           = strDate.find("/", 0);
    Date.Day    = std::stoi(strDate.substr(0, i));
    strDate     = strDate.substr(i + 1);

    i           = strDate.find("/", 0);
    Date.Month  = std::stoi(strDate.substr(0, i));
    strDate     = strDate.substr(i + 1);

    i           = strDate.find("/", 0);
    Date.Year   = std::stoi(strDate.substr(0, i));
    strDate     = strDate.substr(i + 1);

    return (Date);
}

std::string dateToString(stDate Date)
{
    std::string strDate = "";

    strDate += std::to_string(Date.Day) + "/";
    strDate += std::to_string(Date.Month) + "/";
    strDate += std::to_string(Date.Year);

    return (strDate);
}

int main(void)
{
    stDate date = stringToDate(readString());

    printDate(date);
    printString(dateToString(date));

    return (0);
}

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

    std::cout << "Please enter  " << msg << " : ";
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

bool leapYear(short int year)
{
    return ((year % 4 == 0) ? ((year % 100 == 0) ? ((year % 400 == 0) ? true : false ) : true) : false);
}

short int getMonthDays(short int Month, short int Year)
{
    short int listOfDays[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return ((Month == 2) ? (leapYear(Year) ? 29 : 28) : listOfDays[Month]); 
}

bool Date1IsLatestThanDate2(stDate date1, stDate date2)
{
    return ((date1.Year > date2.Year) ||
            (date1.Year == date2.Year && date1.Month > date2.Month) ||
            (date1.Year == date2.Year && date1.Month == date2.Month && date1.Day > date2.Day));
}

bool Date1IsEqualToDate2(stDate date1, stDate date2)
{
    return (date1.Year == date2.Year && date1.Month == date2.Month && date1.Day == date2.Day);
}

bool isLastDayInMonth(short int Day, short int Month, short int Year)
{
    return (Day == getMonthDays(Month, Year));
}

bool isLastMonth(short int Month)
{
    return (Month == 12);
}

stDate increaseDateByOneDay(stDate Date)
{
    if (isLastDayInMonth(Date.Day, Date.Month, Date.Year))
    {
        if (isLastMonth(Date.Month))
        {
            Date.Year++;
            Date.Month = 1;
        }
        else
            Date.Month++;

        Date.Day = 1;
    }
    else
        Date.Day++;

    return (Date);
}

bool isWeekend(stDate Date)
{
    return (zeller_formula(Date) == SUN);
}

bool isBusinessDay(stDate Date)
{
    return (!isWeekend(Date));
}

stDate endOfVacationDate(stDate Start, short int VacationDays)
{
    while (VacationDays)
    {
        if (isBusinessDay(Start))
            VacationDays--;
        Start = increaseDateByOneDay(Start);
    }

    if (isWeekend(Start))
        Start = increaseDateByOneDay(Start);

    return (Start);
}

void printDayOfWeek(stDate Date, std::string msg)
{
    std::cout << "\n" << msg << dayName(zeller_formula(Date)) << ", ";
    printDate(Date);
    std::cout << std::endl;
}

int main(void)
{
    stDate VacationDate1;
    stDate VacationDate2;

    VacationDate1 = initDate(readNumber("day"), readNumber("month"), readNumber("year"));

    printDayOfWeek(VacationDate1, "Vacation Start: ");

    VacationDate2 = endOfVacationDate(VacationDate1, readNumber("Vacation Days"));
    printDayOfWeek(VacationDate2, "Vacation End : ");

    return (0);
}

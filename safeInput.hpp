#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>

namespace safeInput
{
    void clearInput(void)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    bool getBool(const std::string &prompt)
    {
       bool value = false;
       
       while (true)
       {
            std::cout << prompt;
            std::cin >> value;

            if (!std::cin.fail())
            {
                clearInput();
                return (value);
            }

            std::cout << "Invalid bool input! Please try again...\n";
            clearInput();
       }
    }

    char getChar(const std::string &prompt)
    {
       char value = '\0';
       
       while (true)
       {
            std::cout << prompt;
            std::cin >> value;

            if (!std::cin.fail())
            {
                clearInput();
                return (value);
            }

            std::cout << "Invalid char input! Please try again...\n";
            clearInput();
       }
    }

    int getInt(const std::string &prompt)
    {
        int value = -404;

        while (true)
        {
            std::cout << prompt;
            std::cin >> value;

            if (!std::cin.fail())
            {
                clearInput();
                return (value);
            }

            std::cout << "Invalid integer input! Please try again...\n";
            clearInput();
        }
    }

    double getDouble(const std::string &prompt)
    {
        double value = -404.404;

        while (true)
        {
            std::cout << prompt;
            std::cin >> value;

            if (!std::cin.fail())
            {
                clearInput();
                return (value);
            }

            std::cout << "Invalid double input! Please try again...\n";
            clearInput();
        }
    }

    std::string getString(const std::string &prompt)
    {
        std::string value = "error 404";

        std::cout << prompt;
        getline(std::cin, value);

        return (value);
    }
}

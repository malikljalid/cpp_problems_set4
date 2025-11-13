#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include "safeInput.hpp"

enum enMenuOptions  { LIST=1, ADD, DELETE, UPDATE, FIND, TRANSACTION, EXIT };
enum enTransactions { DEPOSITE=1, WITHDRAW, BALANCES, BACKMENU };

struct stListFile
{
    std::string Name;
    std::string Delim;
};

struct stBankRecord
{
    std::string Name;
    std::string PhoneNumber;
    std::string AccountNumber;
    int   PinCode;
    int   Balance;
};

struct stOperation
{
    enMenuOptions   Basic;
    enTransactions  Transaction;
};

struct stBank
{   
    stListFile                      ListFile;
    std::vector <stBankRecord>      vListVector;
    stOperation                     Operation;
};

stBankRecord readBankRecord(void)
{
    stBankRecord BR;

    BR.Name = safeInput::getString("Please enter your name : ");

    BR.PhoneNumber = safeInput::getString("Please enter your Phone number : ");

    BR.AccountNumber = safeInput::getString("Please enter your Account Number : ");

    BR.PinCode = safeInput::getInt("Please enter your PinCode : ");

    BR.Balance = safeInput::getInt("Please enter your Balance : ");

    return (BR);
}

stBankRecord readBankRecord(const std::string &ClientID)
{
    stBankRecord BR;

    BR.Name = safeInput::getString("Please enter your name : ");

    BR.PhoneNumber = safeInput::getString("Please enter your Phone number : ");

    BR.AccountNumber = ClientID;

    std::cout << "Please enter your PinCode : ";
    std::cin >> BR.PinCode;

    std::cout << "Please enter your Balance : ";
    std::cin >> BR.Balance;

    return (BR);
}

std::string readAccountNumber(void)
{
    return (safeInput::getString("Please enter an account number : "));
}

enMenuOptions readUserOperation(void)
{
    return ((enMenuOptions)safeInput::getInt("\nChoose what do you want to do [1 ~ 7] ? : "));
}

enTransactions readUserTransaction(void)
{
    return ((enTransactions)safeInput::getInt("\nChoose what do you want to do [1 ~ 4] ? : "));
}

int readDepositeAmount(void)
{
    return (safeInput::getInt("Please enter the amount to deposite : "));
}

int readWithdrawAmount(short int Balance)
{
    int WithdrawAmount;

    do
    {
        WithdrawAmount = safeInput::getInt("Please enter the amount to withdraw : ");

        if (WithdrawAmount > Balance)
            std::cout << "\nAmount exceeds balance, you can withdraw up to " << Balance << "\n\n";
    }
    while (WithdrawAmount > Balance);

    return (WithdrawAmount);
}

void printBankRecord(const stBankRecord &BR)
{
    std::cout << "Name           : " << BR.Name << std::endl;

    std::cout << "Phone Number   : " << BR.PhoneNumber << std::endl;

    std::cout << "Account Number : " << BR.AccountNumber << std::endl;

    std::cout << "PinCode : " << BR.PinCode << std::endl;

    std::cout << "Balance : " << BR.Balance << std::endl;
}

void fillBankRecordInfo(std::string &bankRecordInfo, std::string &line, const std::string &delim)
{
    int i = line.find(delim);
    bankRecordInfo = line.substr(0, i);
    line.erase(0, i + delim.length());
}

void fillBankRecordInfo(int &bankRecordInfo, std::string &line, const std::string &delim)
{
    int i = line.find(delim);
    bankRecordInfo = std::stoi(line.substr(0, i));
    line.erase(0, i + delim.length());
}

stBankRecord convertLineToBankRecord(std::string &line, const std::string &delim = ":")
{
    stBankRecord    BR;

    fillBankRecordInfo(BR.Name, line, delim);
    fillBankRecordInfo(BR.PhoneNumber, line, delim);
    fillBankRecordInfo(BR.AccountNumber, line, delim);
    fillBankRecordInfo(BR.PinCode, line, delim);
    fillBankRecordInfo(BR.Balance, line, delim);

    return (BR);
}

std::string  convertBankRecordToLine(const stBankRecord &BR, std::string delim = ":")
{
    return (BR.Name + delim + BR.PhoneNumber + delim + BR.AccountNumber + delim + std::to_string(BR.PinCode) + delim + std::to_string(BR.Balance));
}

std::vector <stBankRecord> LoadDataFromFileToVector(const std::string &fileName, const std::string &delim)
{
    std::fstream                file;
    std::vector <stBankRecord>  vRecords;

    file.open(fileName, std::ios::in);

    if (file.is_open())
    {
        std::string Line = "";

        while (getline(file, Line))
            vRecords.push_back(convertLineToBankRecord(Line, delim));;
        file.close();
    }

    return (vRecords);
}

std::vector <stBankRecord> LoadDataFromFileToVector(const std::string &fileName, const std::string &delim, const std::string &ExceptionClientAccountNumber)
{
    std::fstream                file;
    std::vector <stBankRecord>  vRecords;
    stBankRecord                BR;

    file.open(fileName, std::ios::in);

    if (file.is_open())
    {
        std::string Line = "";

        while (getline(file, Line))
        {
            BR = convertLineToBankRecord(Line, delim);
            if (BR.AccountNumber == ExceptionClientAccountNumber)
                BR = readBankRecord(ExceptionClientAccountNumber);
            vRecords.push_back(BR);

        }
        file.close();
    }

    return (vRecords);
}

std::vector <stBankRecord> LoadDataFromFileToVector(const std::string &fileName, const std::string &delim, const std::string &ExceptionClientAccountNumber, short int newBalance)
{
    std::fstream                file;
    std::vector <stBankRecord>  vRecords;
    stBankRecord                BR;

    file.open(fileName, std::ios::in);

    if (file.is_open())
    {
        std::string Line = "";

        while (getline(file, Line))
        {
            BR = convertLineToBankRecord(Line, delim);
            if (BR.AccountNumber == ExceptionClientAccountNumber)
                BR.Balance = newBalance;
            vRecords.push_back(BR);

        }
        file.close();
    }

    return (vRecords);
}

std::vector <stBankRecord> LoadDataFromFileToVectorExceptFor(std::string fileName, std::string delim, std::string ExceptionClientAccountNumber)
{
    std::fstream                file;
    std::vector <stBankRecord>  vRecords;
    stBankRecord                BR;

    file.open(fileName, std::ios::in);

    if (file.is_open())
    {
        std::string Line = "";

        while (getline(file, Line))
        {
            BR = convertLineToBankRecord(Line, delim);
            if (BR.AccountNumber != ExceptionClientAccountNumber)
                vRecords.push_back(BR);
        }
        file.close();
    }

    return (vRecords);
}

void saveDataFromVectorToFile(std::vector <stBankRecord> &vRecords, std::string fileName, std::string delim)
{
    std::fstream file;

    file.open(fileName, std::ios::out);

    if (file.is_open())
    {
        for (stBankRecord & i : vRecords)
        {
            file << convertBankRecordToLine(i, delim) << std::endl;
        }
        file.close();
    }
}


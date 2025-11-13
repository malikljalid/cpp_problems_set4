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

std::vector <stBankRecord> LoadDataFromFileToVector(const stListFile &fileList)
{
    std::fstream                file;
    std::vector <stBankRecord>  vRecords;

    file.open(fileList.Name, std::ios::in);

    if (file.is_open())
    {
        std::string Line = "";

        while (getline(file, Line))
            vRecords.push_back(convertLineToBankRecord(Line, fileList.Delim));;
        file.close();
    }

    return (vRecords);
}

std::vector <stBankRecord> LoadDataFromFileToVector(const stListFile fileList, const std::string &ExceptionClientAccountNumber)
{
    std::fstream                file;
    std::vector <stBankRecord>  vRecords;
    stBankRecord                BR;

    file.open(fileList.Name, std::ios::in);

    if (file.is_open())
    {
        std::string Line = "";

        while (getline(file, Line))
        {
            BR = convertLineToBankRecord(Line, fileList.Delim);
            if (BR.AccountNumber == ExceptionClientAccountNumber)
                BR = readBankRecord(ExceptionClientAccountNumber);
            vRecords.push_back(BR);

        }
        file.close();
    }

    return (vRecords);
}

std::vector <stBankRecord> LoadDataFromFileToVector(const stListFile &fileList, const std::string &ExceptionClientAccountNumber, const int &newBalance)
{
    std::fstream                file;
    std::vector <stBankRecord>  vRecords;
    stBankRecord                BR;

    file.open(fileList.Name, std::ios::in);

    if (file.is_open())
    {
        std::string Line = "";

        while (getline(file, Line))
        {
            BR = convertLineToBankRecord(Line, fileList.Delim);
            if (BR.AccountNumber == ExceptionClientAccountNumber)
                BR.Balance = newBalance;
            vRecords.push_back(BR);

        }
        file.close();
    }

    return (vRecords);
}

std::vector <stBankRecord> LoadDataFromFileToVectorExceptFor(const stListFile fileList, const std::string &ExceptionClientAccountNumber)
{
    std::fstream                file;
    std::vector <stBankRecord>  vRecords;
    stBankRecord                BR;

    file.open(fileList.Name, std::ios::in);

    if (file.is_open())
    {
        std::string Line = "";

        while (getline(file, Line))
        {
            BR = convertLineToBankRecord(Line, fileList.Delim);
            if (BR.AccountNumber != ExceptionClientAccountNumber)
                vRecords.push_back(BR);
        }
        file.close();
    }

    return (vRecords);
}

void saveDataFromVectorToFile(std::vector <stBankRecord> &vRecords, const stListFile &fileList)
{
    std::fstream file;

    file.open(fileList.Name, std::ios::out);

    if (file.is_open())
    {
        for (stBankRecord &i : vRecords)
            file << convertBankRecordToLine(i, fileList.Delim) << std::endl;
        file.close();
    }
}

stBankRecord getRecordInList(const stListFile &fileList, const std::string &AccountNumberToFind)
{
    std::vector <stBankRecord>  vRecords = LoadDataFromFileToVector(fileList);
    stBankRecord                NOTFOUND = {"", "", "", 0, 0};

    for (std::vector <stBankRecord>::iterator i = vRecords.begin(); i != vRecords.end(); i++)
    {
        if ((*i).AccountNumber == AccountNumberToFind)
            return (*i);
    }
    return (NOTFOUND);
}

bool clientExistInList(const stListFile &fileList, const std::string &AccountNumberToFind)
{
    std::vector <stBankRecord>  vRecords = LoadDataFromFileToVector(fileList);

    for (std::vector <stBankRecord>::iterator i = vRecords.begin(); i != vRecords.end(); i++)
    {
        if ((*i).AccountNumber == AccountNumberToFind)
            return (true);
    }
    return (false);
}

void addLineToFile(const std::string &line, const std::string &fileName)
{
    std::fstream file;

    file.open(fileName, std::ios::app);

    if (file.is_open())
    {
        file << line << std::endl;
        file.close();
    }
}

void addRecordToFile(const std::string &ClientID, const stListFile &fileList)
{
        std::cout << "--- Adding a new client ---\n\n";
        addLineToFile(convertBankRecordToLine(readBankRecord(ClientID), fileList.Delim), fileList.Name);
        std::cout << "\nClient Added Successfuly!\n";
}

void updateClient(const stListFile &fileList, const std::string &toUpdate)
{
    std::vector <stBankRecord> vNewRecords;
    
    if (clientExistInList(fileList, toUpdate) == false)
        std::cout << "Account " << toUpdate << " does not exist!\n";
    else
    {
        vNewRecords = LoadDataFromFileToVector(fileList, toUpdate);
        saveDataFromVectorToFile(vNewRecords, fileList);
        std::cout << "Client " << toUpdate << " Updated Successfuly!\n\n";
    }
}

void updateClient(const stListFile &fileList, const std::string &toUpdate, short int newBalance)
{
    std::vector <stBankRecord> vNewRecords;
    
    if (clientExistInList(fileList, toUpdate) == false)
        std::cout << "Account " << toUpdate << " does not exist!\n";
    else
    {
        vNewRecords = LoadDataFromFileToVector(fileList, toUpdate, newBalance);
        saveDataFromVectorToFile(vNewRecords, fileList);
        std::cout << "Client " << toUpdate << " Updated Successfuly!\n\n";
    }
}

void deleteClient(const stListFile &fileList, std::string toDelete)
{
    std::vector <stBankRecord> vNewRecords;

    if (clientExistInList(fileList, toDelete) == false)
        std::cout << "Account " << toDelete << " does not exist!\n";
    else
    {
        vNewRecords = LoadDataFromFileToVectorExceptFor(fileList, toDelete);
        saveDataFromVectorToFile(vNewRecords, fileList);
        std::cout << "Client " << toDelete << " Deleted Successfuly!\n\n";
    }
}

void findClient(const stListFile &fileList, std::string toFindAccountNumber)
{
    stBankRecord client = getRecordInList(fileList, toFindAccountNumber);

    if (client.AccountNumber.empty())
        std::cout << "Client With Account Number " << toFindAccountNumber << " NOT FOUND!\n";
    else
    {
        std::cout << "\n-- The following are the clients details --\n";
        printBankRecord(client);
    }
}

void addClient(const std::string &ClientID, stBank &Menu)
{
    if (clientExistInList(Menu.ListFile, ClientID))
        std::cout << "Account " << ClientID << " already exist!\n";
    else
        addRecordToFile(ClientID, Menu.ListFile);
}

void depositeClient(const std::string &ClientID, stBank &Menu)
{
    stBankRecord client = getRecordInList(Menu.ListFile, ClientID);

    if (client.Name.empty())
        std::cout << "Client " << ClientID << " does not exist!\n";
    else
    {
        client.Balance += readDepositeAmount();
        updateClient(Menu.ListFile, ClientID, client.Balance);
    }
}

void withdrawClient(const std::string &ClientID, stBank &Menu)
{
    stBankRecord client = getRecordInList(Menu.ListFile, ClientID);

    if (client.Name.empty())
        std::cout << "Client " << ClientID << " does not exist!\n";
    else
    {
        client.Balance -= readWithdrawAmount(client.Balance);
        updateClient(Menu.ListFile, ClientID, client.Balance);
    }
}


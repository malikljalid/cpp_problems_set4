#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include "safeInput.hpp"

enum enMenuOptions      { WITHDRAWQ=1, WITHDRAWN, DEPOSIT, BALANCE, LOGOUT, EXIT };

struct stBankRecord
{
    std::string Name;
    std::string PhoneNumber;
    std::string AccountNumber;
    int   PinCode;
    int   Balance;
};

struct stListFile
{
    std::string Name;
    std::string Delim;
};

struct stBank
{
    std::vector <stBankRecord>      vListVector;
    stListFile                      ListFile;
    enMenuOptions                   Operation;
    stBankRecord                    CurrentClient;
};

stBankRecord readBankRecord(void)
{
    stBankRecord BR;

    BR.Name = safeInput::getString("Please enter your name : ");

    BR.PhoneNumber   = safeInput::getString("Please enter your Phone number : ");

    BR.AccountNumber = safeInput::getString("Please enter your Account Number : ");

    BR.PinCode = safeInput::getInt("Please enter your PinCode : ");

    BR.Balance = safeInput::getInt("Please enter your Balance : ");

    return (BR);
}

stBankRecord readBankRecord(const std::string &ClientID)
{
    stBankRecord BR;

    BR.Name = safeInput::getString("Please enter your Name : ");

    BR.PhoneNumber = safeInput::getString("Please enter your Phone number : ");

    BR.AccountNumber = ClientID;

    BR.PinCode = safeInput::getInt("Please enter your PinCode : ");

    BR.Balance = safeInput::getInt("Please enter your Balance : ");

    return (BR);
}

std::string readAccountNumber(void)
{
    return (safeInput::getString("Please enter an account number : "));
}

enMenuOptions readUserOperation(void)
{
    return ((enMenuOptions)safeInput::getInt("\nChoose what do you want to do [1 ~ 6] ? : "));
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
        if (WithdrawAmount % 50 != 0)
            std::cout << "\nNo proper paper for your amount \n\n";
    }
    while (WithdrawAmount > Balance || WithdrawAmount % 50 != 0);

    return (WithdrawAmount);
}

int selectQuickWithdrawAmount(int Balance)
{
    short int quickAmount[8] = { 50, 100, 200, 300, 500, 600, 800, 1000 };
    short int choice         = 0;

    do
        choice = safeInput::getInt("Choose what to withdraw, from [1] to [8] : ");
    while (choice < 1 || choice > 8);

    if (quickAmount[--choice] > Balance)
    {
        std::cout << quickAmount[--choice] << "<--- this is the right one!\n";
        for (short int upAmount = 0; upAmount < 8; upAmount++)
        {
            if (quickAmount[upAmount] > Balance)
            {
                std::cout << "\nAmount exceeds balance, you can withdraw up to " << quickAmount[--upAmount] << "\n\n";
                break;
            }
        }

        return (selectQuickWithdrawAmount(Balance));
    }

    return (quickAmount[choice]);
}

void printBankRecord(const stBankRecord &BR)
{
    std::cout << "Name           : " << BR.Name << std::endl;

    std::cout << "Phone Number   : " << BR.PhoneNumber << std::endl;

    std::cout << "Account Number : " << BR.AccountNumber << std::endl;

    std::cout << "PinCode : " << BR.PinCode << std::endl;

    std::cout << "Balance : " << BR.Balance << std::endl;
}

void fillStructMember(std::string &structMember, std::string &line, const std::string &delim)
{
    int i = line.find(delim);
    structMember = line.substr(0, i);
    line.erase(0, i + delim.length());
}

void fillStructMember(int &structMember, std::string &line, const std::string &delim)
{
    int i = line.find(delim);
    structMember = std::stoi(line.substr(0, i));
    line.erase(0, i + delim.length());
}

stBankRecord convertLineToBankRecord(std::string &line, const std::string &delim = ":")
{
    stBankRecord    BR;

    fillStructMember(BR.Name, line, delim);
    fillStructMember(BR.PhoneNumber, line, delim);
    fillStructMember(BR.AccountNumber, line, delim);
    fillStructMember(BR.PinCode, line, delim);
    fillStructMember(BR.Balance, line, delim);

    return (BR);
}

std::string  convertBankRecordToLine(const stBankRecord &BR, const std::string &delim = ":")
{
    return (BR.Name + delim + BR.PhoneNumber + delim + BR.AccountNumber + delim + std::to_string(BR.PinCode) + delim + std::to_string(BR.Balance));
}

std::vector <stBankRecord> LoadClientDataFromFileToVector(const stListFile &fileList)
{
    std::fstream                file;
    std::vector <stBankRecord>  vRecords;

    file.open(fileList.Name, std::ios::in);

    if (file.is_open())
    {
        std::string Line = "";

        while (getline(file, Line))
        {
            vRecords.push_back(convertLineToBankRecord(Line, fileList.Delim));
        }
        file.close();
    }
    return (vRecords);
}

std::vector <stBankRecord> LoadClientDataFromFileToVector(const stListFile fileList, const std::string &ExceptionClientAccountNumber)
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

std::vector <stBankRecord> LoadClientDataFromFileToVector(const stListFile &fileList, const std::string &ExceptionClientAccountNumber, const int &newBalance)
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

std::vector <stBankRecord> LoadClientDataFromFileToVectorExceptFor(const stListFile &fileList, const std::string &ExceptionClientAccountNumber)
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

void saveClientDataFromVectorToFile(std::vector <stBankRecord> &vRecords, const stListFile &fileList)
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
    std::vector <stBankRecord>  vRecords = LoadClientDataFromFileToVector(fileList);
    stBankRecord                NOTFOUND = { "", "", "", 0, 0 };

    for (std::vector <stBankRecord>::iterator i = vRecords.begin(); i != vRecords.end(); i++)
    {
        if ((*i).AccountNumber == AccountNumberToFind)
            return (*i);
    }

    return (NOTFOUND);
}

bool clientExistInList(const stListFile &fileList, const std::string &AccountNumberToFind)
{
    std::vector <stBankRecord>  vRecords = LoadClientDataFromFileToVector(fileList);

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
        vNewRecords = LoadClientDataFromFileToVector(fileList, toUpdate);
        saveClientDataFromVectorToFile(vNewRecords, fileList);
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
        vNewRecords = LoadClientDataFromFileToVector(fileList, toUpdate, newBalance);
        saveClientDataFromVectorToFile(vNewRecords, fileList);
        std::cout << "Client " << toUpdate << " Updated Successfuly!\n\n";
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

void depositeClient(const std::string &ClientID, stBank &Bank)
{
    stBankRecord client = getRecordInList(Bank.ListFile, ClientID);

    if (client.Name.empty())
        std::cout << "Client " << ClientID << " does not exist!\n";
    else
    {
        client.Balance += readDepositeAmount();
        updateClient(Bank.ListFile, ClientID, client.Balance);
    }
}

void withdrawClient(const std::string &ClientID, stBank &Menu)
{
    stBankRecord client = getRecordInList(Menu.ListFile, ClientID);

    if (client.Name.empty())
        std::cout << "Client " << ClientID << " does not exist!\n";
    else
    {
        if (client.Balance > 0)
        {
            client.Balance -= readWithdrawAmount(client.Balance);
            updateClient(Menu.ListFile, ClientID, client.Balance);
        }
        else
            std::cout << "\nYour Balance is not suficent!\n\n";
    }
}

void withdrawClientQuick(const std::string &ClientID, stBank &Menu)
{
    stBankRecord client = getRecordInList(Menu.ListFile, ClientID);

    if (client.Name.empty())
        std::cout << "Client " << ClientID << " does not exist!\n";
    else
    {   if (client.Balance >= 100)
        {
            client.Balance -= selectQuickWithdrawAmount(client.Balance);
            updateClient(Menu.ListFile, ClientID, client.Balance);
        }
        else
            std::cout << "\nYour Balance is not suficent for Bar Minimum Withdraw!\n\n";
    }
}

stBankRecord login(const stBank &Bank)
{
    std::string         username;
    int                 password;
    stBankRecord        loginUser;

    username     = safeInput::getString("Please enter your Account Number : ");
    password     = safeInput::getInt("Please enter your PinCode        : ");
    loginUser    = getRecordInList(Bank.ListFile, username);

    if (loginUser.AccountNumber == username && loginUser.PinCode == password)
        return (loginUser);
    else
    {
        std::cout << "\nInvalid AccountNumber/PinCode! Please try again... \n\n";
        return (login(Bank));
    } 
}

void printBalance(const std::string &ClientID, stBank &Menu)
{
    for (stBankRecord i : Menu.vListVector)
    {
        if (i.AccountNumber == ClientID)
            std::cout << "Your Balance is : " << i.Balance << std::endl;
    }
}

void showQuickAmounts(void)
{
    short int m[8] = { 50, 100, 200, 300, 500, 600, 800, 1000 };

    for (short int i = 0; i < 8; i += 2)
        std::cout << "\t[" << i+1 << "] " << m[i] << "\t[" << i+2 << "] " << m[i+1] << std::endl;

    std::cout << "---------------------------------------\n";
    std::cout << "---------------------------------------\n";
}

void showMenuOf(enMenuOptions Option)
{
    std::cout << "---------------------------------------\n";
    switch (Option)
    {
        case (WITHDRAWQ) :
        {
            std::cout << "|\t Quick Withdraw Screen        |\n";
            break;
        }
        case (WITHDRAWN) :
        {
            std::cout << "|\t Normal Withdraw Screen       |\n";
            break;
        }
        case (DEPOSIT) :
        {
            std::cout << "|\t    Deposit Screen            |\n";
            break;
        }
        case (BALANCE) :
        {
            std::cout << "|\t    Total Balance Screen      |\n";
            break;
        }
        case (LOGOUT) :
        {
            std::cout << "|\t        LOGIN                 |\n";
            break;     
        }
        case (EXIT) :
        {
            std::cout << "|\t    Program ENDS :)           |\n";
            break;
        }
        default :
            break;
    }
    std::cout << "---------------------------------------\n";
}

void showMenu(void)
{
    std::cout << "---------------------------------------\n";
    std::cout << "|\tATM Main Menu Screen          |\n";
    std::cout << "---------------------------------------\n";
    std::cout << "\t[1] : Quick Withdraw\n";
    std::cout << "\t[2] : Normal Withdraw\n";
    std::cout << "\t[3] : Deposite\n";
    std::cout << "\t[4] : Check Balance\n";
    std::cout << "\t[5] : Logout\n";
    std::cout << "\t[6] : Exit\n";
    std::cout << "---------------------------------------\n";
    std::cout << "---------------------------------------\n";
}

void executeUserOperation(stBank &Menu)
{
    switch (Menu.Operation)
    {
        case (WITHDRAWQ) :
        {
            showMenuOf(WITHDRAWQ);
            showQuickAmounts();
            withdrawClientQuick(Menu.CurrentClient.AccountNumber, Menu);
            break;
        }
        case (WITHDRAWN) :
        {
            showMenuOf(WITHDRAWN);
            withdrawClient(Menu.CurrentClient.AccountNumber, Menu);

            break;
        }
        case (DEPOSIT) :
        {
            showMenuOf(DEPOSIT);
            depositeClient(Menu.CurrentClient.AccountNumber, Menu);
            break;
        }
        case (BALANCE) :
        {
            showMenuOf(BALANCE);
            printBalance(Menu.CurrentClient.AccountNumber, Menu);
            break;
        }
        case (LOGOUT) :
        {
            showMenuOf(LOGOUT);
            Menu.CurrentClient = login(Menu);
            break;
        }
        case (EXIT) :
            break;
    }

    if (Menu.Operation == WITHDRAWQ || Menu.Operation == WITHDRAWN || Menu.Operation == DEPOSIT)
        Menu.vListVector = LoadClientDataFromFileToVector(Menu.ListFile);
}

stBank initBank(const std::string &ListFileName, const std::string &ListDelim)
{
    stBank Menu;

    showMenuOf(LOGOUT);

    Menu.ListFile.Name      = ListFileName;
    Menu.ListFile.Delim     = ListDelim;

    Menu.vListVector        = LoadClientDataFromFileToVector(Menu.ListFile);
    Menu.CurrentClient      = login(Menu);

    return (Menu);
}

void runBank(stBank Bank)
{
    while (true)
    {
        showMenu();
        Bank.Operation = readUserOperation();
        if (Bank.Operation == EXIT)
        {
            showMenuOf(EXIT);
            break;
        }
        executeUserOperation(Bank);
    }
}

int main(void)
{
    runBank(initBank("fclients.txt", ":"));

    return (0);
}
 
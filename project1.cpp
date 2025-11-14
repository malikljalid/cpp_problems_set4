#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include "safeInput.hpp"

enum enMenuOptions  { LIST=1, ADD, DELETE, UPDATE, FIND, TRANSACTION, EXIT };
enum enTransactions { DEPOSITE=1, WITHDRAW, BALANCES, BACKMENU };

struct stPermission
{
    bool ShowClientList;
    bool AddClient;
    bool UpdateClient;
    bool DeleteClient;
    bool FindClient;
    bool Transactions;
    bool ManageUsers;
};

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

struct stOperation
{
    enMenuOptions   Basic;
    enTransactions  Transaction;
};

struct stUser
{
    stBankRecord    Info;
    stPermission    Permission;
};

struct stBank
{
    std::vector <stUser>            Users;
    std::vector <stBankRecord>      vListVector;
    stListFile                      ListFile;
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

stBank initBank(const std::string &fileName, const std::string &delim)
{
    stBank Menu;

    Menu.ListFile.Name  = fileName;
    Menu.ListFile.Delim = delim;
    Menu.vListVector    = LoadDataFromFileToVector(Menu.ListFile);

    return (Menu);
}

void printHeader(std::vector <stBankRecord> vClients)
{
    std::cout << "\n\t\t\t    Client List(" << vClients.size() << ") Client(s)\n";
    std::cout << "  ______________________________________________________________________________\n\n";
    std::cout << " | " << std::setw(15) << std::left << "Account Number";
    std::cout << " | " << std::setw(9)  << std::left << "Pin Code";
    std::cout << " | " << std::setw(20) << std::left << "Client Name";
    std::cout << " | " << std::setw(12) << std::left << "Phone";
    std::cout << " | " << std::setw(6)  << std::left << "Balance |\n";
    std::cout << "  ______________________________________________________________________________\n\n";

    for (std::vector <stBankRecord>::iterator  i = vClients.begin(); i != vClients.end(); i++)
    {
        std::cout << " | " << std::setw(15) << (*i).AccountNumber;
        std::cout << " | " << std::setw(9)  << (*i).PinCode;
        std::cout << " | " << std::setw(20) << (*i).Name;
        std::cout << " | " << std::setw(12) << (*i).PhoneNumber;
        std::cout << " | " << std::setw(6)  << (*i).Balance << "  |\n";
    }

    std::cout << "  ______________________________________________________________________________\n\n";
}

void printBalancesHeader(std::vector <stBankRecord> vClients)
{
    int TotalBalances = 0;

    std::cout << "\n\t\tBalances List(" << vClients.size() << ") Client(s)\n";
    std::cout << "  __________________________________________________\n\n";
    std::cout << " | " << std::setw(15) << std::left << "Account Number";
    std::cout << " | " << std::setw(20) << std::left << "Client Name";
    std::cout << " | " << std::setw(6)  << std::left << "Balance |\n";
    std::cout << "  __________________________________________________\n\n";

    for (std::vector <stBankRecord>::iterator  i = vClients.begin(); i != vClients.end(); i++)
    {
        std::cout << " | " << std::setw(15) << (*i).AccountNumber;
        std::cout << " | " << std::setw(20) << (*i).Name;
        std::cout << " | " << std::setw(6)  << (*i).Balance << "  |\n";
        
        TotalBalances += (*i).Balance;
    }

    std::cout << "  _________________________________________________\n\n";
    std::cout << " |\t\t\t   Total Balances : "  << std::setw(8) << std::left << TotalBalances << "|\n";
    std::cout << "  _________________________________________________\n\n";

}

void showMenuOf(enMenuOptions Option)
{
    std::cout << "---------------------------------------\n";
    switch (Option)
    {
        case (ADD) :
        {
            std::cout << "|\t    Add Client Screen          |\n";
            break;
        }
        case (DELETE) :
        {
            std::cout << "|\t    Delete Client Screen       |\n";
            break;
        }
        case (UPDATE) :
        {
            std::cout << "|\t    Update Client Screen        |\n";
            break;
        }
        case (FIND) :
        {
            std::cout << "|\t    Find Client Screen          |\n";
            break;
        }
        case (EXIT) :
        {
            std::cout << "|\t    Program ENDS :)           |\n";
        }
        default :
            break;
    }
    std::cout << "---------------------------------------\n";
}

void showMenuOf(enTransactions Option)
{
    std::cout << "---------------------------------------\n";
    switch (Option)
    {
        case (DEPOSITE) :
        {
            std::cout << "|\t    Deposite Screen           |\n";
            break;
        }
        case (WITHDRAW) :
        {
            std::cout << "|\t    Withdraw Screen           |\n";
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
    std::cout << "|\t    Main Menu Screen          |\n";
    std::cout << "---------------------------------------\n";
    std::cout << "\t[1] : Show Clients List\n";
    std::cout << "\t[2] : Add New Client\n";
    std::cout << "\t[3] : Delete Client\n";
    std::cout << "\t[4] : Update Client Info\n";
    std::cout << "\t[5] : Find Client\n";
    std::cout << "\t[6] : Transactions\n";
    std::cout << "\t[7] : Exit\n";
    std::cout << "---------------------------------------\n";
    std::cout << "---------------------------------------\n";
}

void showTransactionMenu(void)
{
    std::cout << "---------------------------------------\n";
    std::cout << "|\tTransactions Menu Screen      |\n";
    std::cout << "---------------------------------------\n";
    std::cout << "\t[1] : Deposite \n";
    std::cout << "\t[2] : Withdraw \n";
    std::cout << "\t[3] : Total Balances \n";
    std::cout << "\t[4] : Main Menu \n";
    std::cout << "---------------------------------------\n";
    std::cout << "---------------------------------------\n";
}

void executeUserTransaction(stBank &Menu)
{
    switch (Menu.Operation.Transaction)
    {
        case (DEPOSITE) :
        {
            showMenuOf(DEPOSITE);
            depositeClient(readAccountNumber(), Menu);
            break;
        }
        case (WITHDRAW) :
        {
            showMenuOf(WITHDRAW);
            withdrawClient(readAccountNumber(), Menu);
            break;
        }
        case (BALANCES) :
        {
            printBalancesHeader(Menu.vListVector);
            break;
        }
        case (BACKMENU) :
            break;
    }

    if (Menu.Operation.Transaction == DEPOSITE || Menu.Operation.Transaction == WITHDRAW)
        Menu.vListVector = LoadDataFromFileToVector(Menu.ListFile);
}

void executeUserOperation(stBank &Menu)
{
    switch (Menu.Operation.Basic)
    {
        case (LIST) :
        {
            printHeader(Menu.vListVector);
            break;
        }
        case (ADD)  :
        {
            showMenuOf(ADD);
            addClient(readAccountNumber(), Menu);
            break;
        }
        case (FIND) :
        {
            showMenuOf(FIND);
            findClient(Menu.ListFile, readAccountNumber());
            break;
        }
        case (DELETE) :
        {
            showMenuOf(DELETE);
            deleteClient(Menu.ListFile, readAccountNumber());
            break;
        }
        case (UPDATE) :
        {
            showMenuOf(UPDATE);
            updateClient(Menu.ListFile, readAccountNumber());
            break;
        }
        case (TRANSACTION) :
        {
            while (1)
            {
                showTransactionMenu();
                Menu.Operation.Transaction = readUserTransaction();
                if (Menu.Operation.Transaction == BACKMENU)
                    break;
                executeUserTransaction(Menu);
            }
        }
        case (EXIT) :
            break;
    }

    if (Menu.Operation.Basic == ADD || Menu.Operation.Basic == DELETE || Menu.Operation.Basic == UPDATE)
        Menu.vListVector = LoadDataFromFileToVector(Menu.ListFile);
}

int main(void)
{
    stBank Bank = initBank("clients_bankRecords.txt", ":");

    while (true)
    {
        showMenu();
        Bank.Operation.Basic = readUserOperation();
        if (Bank.Operation.Basic == EXIT)
        {
            showMenuOf(EXIT);
            break;
        }
        executeUserOperation(Bank);
    }

    return (0);
}

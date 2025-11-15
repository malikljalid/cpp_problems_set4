#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include "safeInput.hpp"

enum enMenuOptions      { LIST=1, ADD, DELETE, UPDATE, FIND, TRANSACTION, USERS, LOGOUT, EXIT };
enum enUserManagement   { LISTU=1, ADDU, DELETEU, UPDATEU, FINDU, MAINMENU };
enum enTransactions     { DEPOSITE=1, WITHDRAW, BALANCES, BACKMENU };

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

struct stUser
{
    std::string     Name;
    std::string     Password;
    stPermission    Permission;
    int             PermissionID;
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
    enMenuOptions       Basic;
    enTransactions      Transaction;
    enUserManagement    UserManagement;
};

struct stBank
{
    std::vector <stUser>            vUsersVector;
    std::vector <stBankRecord>      vListVector;
    stListFile                      ListFile;
    stListFile                      UsersFile;
    stOperation                     Operation;
    stUser                          CurrentUser;
};




stPermission readUserPermission(const std::string &username)
{
    stPermission Permission;

    std::cout << "Do you want to give "<< username <<" access to : \n";

    Permission.ShowClientList   = safeInput::getBool("Listing Clients ? (Y/N) : ");
    Permission.AddClient        = safeInput::getBool("Adding Clients ? (Y/N) : ");
    Permission.DeleteClient     = safeInput::getBool("Deleting Clients ? (Y/N) : ");
    Permission.UpdateClient     = safeInput::getBool("Updating Clients ? (Y/N) : ");
    Permission.FindClient       = safeInput::getBool("Finding Clients ? (Y/N) : ");
    Permission.ManageUsers      = safeInput::getBool("Manage Clients ? (Y/N) : ");
    Permission.Transactions     = safeInput::getBool("Transactions ? (Y/N) : ");

    return (Permission);
}

short int convertUserPermissionsToInt(const stPermission &P)
{
    bool       key[6]           = { P.AddClient, P.DeleteClient, P.UpdateClient, P.FindClient, P.ManageUsers, P.Transactions };
    short int  value[6]         = { 1, 2, 4, 8, 16, 32 };
    short int  PermissionsID    = 0;

    for (short int i = 0; i < 6; i++)
    {
        if (key[i] == true)
            PermissionsID += value[i];
    }

    return (PermissionsID);
}

stPermission convertIntToUserPermission(const short int &id)
{
    stPermission P;

    bool       *key[6]     = { &P.AddClient, &P.DeleteClient, &P.UpdateClient, &P.FindClient, &P.ManageUsers, &P.Transactions };
    short int   value[6]   = { 1, 2, 4, 8, 16, 32 };

    for (short int i = 0; i < 6; i++)
        *key[i] = ((id & value[i]) == value[i]);

    return (P);
}

stUser readUserInfo(const std::string &username)
{
    stUser User;

    User.Name           = username;

    User.Password       = safeInput::getString("Please enter password : ");

    if (safeInput::getBool("Do you want to give full access to " + username + " ? (Y/N) : ") == false)
    {
        User.Permission     = readUserPermission(User.Name);
        User.PermissionID   = convertUserPermissionsToInt(User.Permission);
    }
    else
        User.Permission    = { true, true, true, true, true, true, true };

    return (User);
}

std::string readUserName(void)
{
    return (safeInput::getString("Please enter a username : "));
}

std::string readUserPassword(void)
{
    return (safeInput::getString("Please enter a password : "));
}

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
    return ((enMenuOptions)safeInput::getInt("\nChoose what do you want to do [1 ~ 7] ? : "));
}

enTransactions readUserTransaction(void)
{
    return ((enTransactions)safeInput::getInt("\nChoose what do you want to do [1 ~ 4] ? : "));
}

enUserManagement readUserManagementOperation(void)
{
    return ((enUserManagement)safeInput::getInt("\nChoose what do you want to do [1 ~ 6] ? : "));
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

void printUserInfo(const stUser &user)
{
    std::cout << "username   : " << user.Name << std::endl;

    std::cout << "password   : " << user.Password << std::endl;

    std::cout << "Permissions : " << user.PermissionID << std::endl;
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

stUser convertLineToUserInfo(std::string &line, const std::string &delim = ":")
{
    stUser User;

    fillStructMember(User.Name, line, delim);
    fillStructMember(User.Password, line, delim);
    fillStructMember(User.PermissionID, line, delim);
    
    User.Permission = convertIntToUserPermission(User.PermissionID);

    return (User);
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

std::string convertUserInfoToLine(const stUser &User, const std::string &delim = ":")
{
    return (User.Name + delim + User.Password + delim + std::to_string(User.PermissionID));
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
            vRecords.push_back(convertLineToBankRecord(Line, fileList.Delim));;
        file.close();
    }

    return (vRecords);
}

std::vector <stUser> LoadUserDataFromFileToVector(const stListFile &fileList)
{
    std::fstream                file;
    std::vector <stUser>        vUsers;

    file.open(fileList.Name, std::ios::in);

    if (file.is_open())
    {
        std::string Line = "";

        while (getline(file, Line))
            vUsers.push_back(convertLineToUserInfo(Line, fileList.Delim));;
        file.close();
    }

    return (vUsers);
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

std::vector <stUser> LoadUserDataFromFileToVector(const stListFile fileList, const std::string &ExceptionUserName)
{
    std::fstream                file;
    std::vector <stUser>        vUsers;
    stUser                      User;

    file.open(fileList.Name, std::ios::in);

    if (file.is_open())
    {
        std::string Line = "";

        while (getline(file, Line))
        {
            User = convertLineToUserInfo(Line, fileList.Delim);
            if (User.Name == ExceptionUserName)
                User = readUserInfo(ExceptionUserName);
            vUsers.push_back(User);

        }
        file.close();
    }

    return (vUsers);
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

std::vector <stUser> LoadUserDataFromFileToVector(const stListFile &fileList, const std::string &ExceptionUserName, const std::string &newPassword)
{
    std::fstream          file;
    std::vector <stUser>  vUsers;
    stUser                User;

    file.open(fileList.Name, std::ios::in);

    if (file.is_open())
    {
        std::string Line = "";

        while (getline(file, Line))
        {
            User = convertLineToUserInfo(Line, fileList.Delim);
            if (User.Name == ExceptionUserName)
                User.Password = newPassword;
            vUsers.push_back(User);
        }
        file.close();
    }

    return (vUsers);
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

std::vector <stUser> LoadUserDataFromFileToVectorExceptFor(const stListFile &fileList, const std::string &ExceptionUserName)
{
    std::fstream          file;
    std::vector <stUser>  vUsers;
    stUser                User;

    file.open(fileList.Name, std::ios::in);

    if (file.is_open())
    {
        std::string Line = "";

        while (getline(file, Line))
        {
            User = convertLineToUserInfo(Line, fileList.Delim);
            if (User.Name != ExceptionUserName)
                vUsers.push_back(User);
        }
        file.close();
    }

    return (vUsers);
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

void saveUserDataFromVectorToFile(std::vector <stUser> &vUsers, const stListFile &fileList)
{
    std::fstream file;

    file.open(fileList.Name, std::ios::out);

    if (file.is_open())
    {
        for (stUser &i : vUsers)
            file << convertUserInfoToLine(i, fileList.Delim) << std::endl;
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

stUser  getUserInList(const stListFile &fileList, const std::string &UserNameToFind)
{
    std::vector <stUser>    vUsers      = LoadUserDataFromFileToVector(fileList);
    stUser                  NOTFOUND    = { "", "", {0, 0, 0, 0, 0, 0, 0}, 0};

    for (std::vector <stUser>::iterator i = vUsers.begin(); i != vUsers.end(); i++)
    {
        if ((*i).Name == UserNameToFind)
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

bool userExistInList(const stListFile &fileList, const std::string &UserNameToFind)
{
    std::vector <stUser>  vUsers = LoadUserDataFromFileToVector(fileList);

    for (std::vector <stUser>::iterator i = vUsers.begin(); i != vUsers.end(); i++)
    {
        if ((*i).Name == UserNameToFind)
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

void addUserToFile(const std::string &username, const stListFile &fileList)
{
        std::cout << "--- Adding a new user ---\n\n";
        addLineToFile(convertUserInfoToLine(readUserInfo(username), fileList.Delim), fileList.Name);
        std::cout << "\nUser Added Successfuly!\n";
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

void updateUser(const stListFile &fileList, const std::string &toUpdate)
{
    std::vector <stUser> vNewUsers;
    
    if (clientExistInList(fileList, toUpdate) == false)
        std::cout << "Account " << toUpdate << " does not exist!\n";
    else
    {
        vNewUsers = LoadUserDataFromFileToVector(fileList, toUpdate);
        saveUserDataFromVectorToFile(vNewUsers, fileList);
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
        vNewRecords = LoadClientDataFromFileToVectorExceptFor(fileList, toDelete);
        saveClientDataFromVectorToFile(vNewRecords, fileList);
        std::cout << "Client " << toDelete << " Deleted Successfuly!\n\n";
    }
}

void deleteUser(const stListFile &fileList, std::string toDelete)
{
    std::vector <stUser> vNewUsers;

    if (clientExistInList(fileList, toDelete) == false)
        std::cout << "Account " << toDelete << " does not exist!\n";
    else
    {
        vNewUsers = LoadUserDataFromFileToVectorExceptFor(fileList, toDelete);
        saveUserDataFromVectorToFile(vNewUsers, fileList);
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

void findUser(const stListFile &fileList, std::string toFindUserName)
{
    stUser user = getUserInList(fileList, toFindUserName);

    if (user.Name.empty())
        std::cout << "Client With Account Number " << toFindUserName << " NOT FOUND!\n";
    else
    {
        std::cout << "\n-- The following are the clients details --\n";
        printUserInfo(user);
    }
}

void addClient(const std::string &ClientID, stBank &Bank)
{
    if (clientExistInList(Bank.ListFile, ClientID))
        std::cout << "Account " << ClientID << " already exist!\n";
    else
        addRecordToFile(ClientID, Bank.ListFile);
}

void addUser(const std::string &username, stBank &bank)
{
    if (userExistInList(bank.UsersFile, username))
        std::cout << "User [" << username << "] already exist!\n";
    else
        addUserToFile(username, bank.UsersFile);
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
        client.Balance -= readWithdrawAmount(client.Balance);
        updateClient(Menu.ListFile, ClientID, client.Balance);
    }
}





stUser login(const stBank &Bank)
{
    std::string username;
    std::string password;
    stUser      loginUser;

    username     = readUserName();
    password     = readUserPassword();
    loginUser    = getUserInList(Bank.UsersFile, username);

    if (loginUser.Name == username && loginUser.Password == password)
        return (loginUser);
    else
    {
        std::cout << "\nInvalid username/Password! Please try again... \n\n";
        return (login(Bank));
    } 
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

void printHeader(std::vector <stUser> vUsers)
{
    std::cout << "\n\t\t\t    Client List(" << vUsers.size() << ") Client(s)\n";
    std::cout << "  ______________________________________________________________________________\n\n";
    std::cout << " | " << std::setw(15) << std::left << "User Name";
    std::cout << " | " << std::setw(9)  << std::left << "Password";
    std::cout << " | " << std::setw(20) << std::left << "Permissions |\n";
    std::cout << "  ______________________________________________________________________________\n\n";

    for (std::vector <stUser>::iterator  i = vUsers.begin(); i != vUsers.end(); i++)
    {
        std::cout << " | " << std::setw(15) << (*i).Name;
        std::cout << " | " << std::setw(9)  << (*i).Password;
        std::cout << " | " << std::setw(20) << (*i).PermissionID  << "  |\n";
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
        {
            std::cout << "ACCESS DENIED!\nYou don't have permissions to do this,\nPlease contact your admin.\n";
            break;
        }
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
    std::cout << "\t[7] : Manage Users\n";
    std::cout << "\t[8] : Logout\n";
    std::cout << "\t[9] : Exit\n";
    std::cout << "---------------------------------------\n";
    std::cout << "---------------------------------------\n";
}

void showTransactionMenu(void)
{
    std::cout << "\n---------------------------------------\n";
    std::cout << "|\tTransactions Menu Screen      |\n";
    std::cout << "---------------------------------------\n";
    std::cout << "\t[1] : Deposite \n";
    std::cout << "\t[2] : Withdraw \n";
    std::cout << "\t[3] : Total Balances \n";
    std::cout << "\t[4] : Main Menu \n";
    std::cout << "---------------------------------------\n";
    std::cout << "---------------------------------------\n";
}

void showUserManagementMenu(void)
{
    std::cout << "---------------------------------------\n";
    std::cout << "|\tUser Management Menu Screen      |\n";
    std::cout << "---------------------------------------\n";
    std::cout << "\t[1] : Show Users List\n";
    std::cout << "\t[2] : Add New User\n";
    std::cout << "\t[3] : Delete User\n";
    std::cout << "\t[4] : Update User Info\n";
    std::cout << "\t[5] : Find User\n";
    std::cout << "\t[5] : Main Menu\n";
    std::cout << "---------------------------------------\n";
    std::cout << "---------------------------------------\n";
}

void executeUserManagementOperation(stBank &Menu)
{
    switch (Menu.Operation.UserManagement)
    {
        case (LISTU) :
        {
            if (Menu.CurrentUser.Permission.ShowClientList == true)
                printHeader(Menu.vUsersVector);
            else
                showMenuOf((enMenuOptions)13);
            break;
        }
        case (ADDU)  :
        {
            if (Menu.CurrentUser.Permission.AddClient == true)
            {
                showMenuOf(ADD);
                addUser(readUserName(), Menu);
            }
            else
                showMenuOf((enMenuOptions)13);
            break;
        }
        case (FINDU) :
        {
            if (Menu.CurrentUser.Permission.FindClient == true)
            {
                showMenuOf(FIND);
                findUser(Menu.UsersFile, readUserName());
            }
            else
                showMenuOf((enMenuOptions)13);
            break;
        }
        case (DELETEU) :
        {
            if (Menu.CurrentUser.Permission.DeleteClient == true)
            {
                showMenuOf(DELETE);
                deleteUser(Menu.UsersFile, readUserName());
            }
            else
                showMenuOf((enMenuOptions)13);
            break;
        }
        case (UPDATEU) :
        {
            if (Menu.CurrentUser.Permission.UpdateClient == true)
            {
                showMenuOf(UPDATE);
                updateUser(Menu.UsersFile, readUserName());
            }
            else
                showMenuOf((enMenuOptions)13);
            break;
        }
        case (MAINMENU) :
            break;
    }

    if (Menu.Operation.UserManagement == ADDU || Menu.Operation.UserManagement == DELETEU || Menu.Operation.UserManagement == UPDATEU)
        Menu.vUsersVector = LoadUserDataFromFileToVector(Menu.UsersFile);
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
        Menu.vListVector = LoadClientDataFromFileToVector(Menu.ListFile);
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
            break;
        }
        case (USERS) :
        {
            while (1)
            {
                showUserManagementMenu();
                Menu.Operation.UserManagement = readUserManagementOperation();
                if (Menu.Operation.UserManagement == MAINMENU)
                    break;
                executeUserManagementOperation(Menu);
            }
            break;
        }
        case (LOGOUT) :
        {
            showMenuOf(LOGOUT);
            Menu.CurrentUser = login(Menu);
            break;
        }
        case (EXIT) :
            break;
    }

    if (Menu.Operation.Basic == ADD || Menu.Operation.Basic == DELETE || Menu.Operation.Basic == UPDATE)
        Menu.vListVector = LoadClientDataFromFileToVector(Menu.ListFile);
}

stBank initBank(const std::string &ListFileName, const std::string &ListDelim, const std::string &UsersFileName, const std::string &UsersDelim)
{
    stBank Menu;

    showMenuOf(LOGOUT);

    Menu.ListFile.Name      = ListFileName;
    Menu.ListFile.Delim     = ListDelim;
    Menu.UsersFile.Name     = UsersFileName;
    Menu.UsersFile.Delim    = UsersDelim;
    Menu.vListVector        = LoadClientDataFromFileToVector(Menu.ListFile);
    Menu.vUsersVector       = LoadUserDataFromFileToVector(Menu.UsersFile);
    Menu.CurrentUser        = login(Menu);

    return (Menu);
}

int main(void)
{
    stBank Bank = initBank("fclients.txt", ":", "fusers.txt", ":");

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

// Banking_management_system.c++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// In this project i amde a project with the help of file handling where we just do the Open account , check balance, search, deposite amount, withdraw amount  ,delete account, and cehck balance.
// All data will be store in .dat format in the given location every this will be automatic and line create a folder and then create a file every thing....

#include <iostream>
#include<windows.h>
#include<string>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>
#include<direct.h>
using namespace std;
ofstream humanRead;
class Bank {
public:
    int avaliable_balance;
    string first_name, last_name, address, account_number, phone_number;
    void information() {
        avaliable_balance = 0;
        cin.ignore();
        cout << "Please enter your First Name: ";
        getline(cin, first_name);
        cout << "Please enter your Last Name: ";
        getline(cin, last_name);
        cout << "Please enter your Address: ";
        getline(cin, address);
        cout << "Please enter your Phone number: ";
        cin >> phone_number;
        cout << "Please enter your account number: ";
        cin >> account_number;
        cout << "\t\t\t\tYour account has been Created Successfully:)" << endl;
    }
    void display() {
        cout << "Your name is " << first_name << " " << last_name << endl;
        cout << "Your address is " << address << endl;
        cout << "Your contact number is " << phone_number << endl;
        cout << "Your account number is " << account_number << endl;
        cout << " Your bank balance is: " << avaliable_balance << endl;
    }
    void humamReadfile()
    {
        cout << "YES" << endl;
        humanRead << "Name: " + first_name + " " + last_name + "\n";
        humanRead << "Address: " + address + "\n";
        humanRead << "Contact Number: " + phone_number + "\n";
        humanRead << "Account Number: " + account_number + "\n";
        humanRead << "Avaliable balance: " + to_string(avaliable_balance) + "\n";
        humanRead << "\n\n";
    }
    void welcome() {
        cout << "\t\t\t\t\t\t WelCome to My Bank!!!!!!:)\n" << endl;;
        cout << "Please select from the below option frrom 1 to 8:  " << endl;;
        cout << " 1. Account Opeaning:\n 2. Deposite amount:\n 3. Withdraw amount: \n 4. Update account: \n 5. Search account:\n 6. Delete account:\n 7. Check balance:  \n 8. Exit:\n";
    }
};
int main()
{
    int operation = 0;
    int k = _mkdir("G:\\DB\\Binary file");
    Bank Bnk_sys;
    do {
        Bnk_sys.welcome();
        cin >> operation;
        if (operation == 1)
        {
            Bnk_sys.information();
            ofstream Bnk_DB("G:\\DB\\Binary file\\bankDB.dat", ios::app);
            Bnk_DB.write((char*)&Bnk_sys, sizeof(Bnk_sys));
            Bnk_DB.close();
            Bnk_sys.display();
            Sleep(3000);
            system("cls");
        }
        else if (operation == 2)
        {
            string account_number;
            cout << "Enter the account number: ";
            cin >> account_number;
            ifstream read_bnk_db("G:\\DB\\Binary file\\bankDB.dat");
            bool validAccount = false;
            while (read_bnk_db.read((char*)&Bnk_sys, sizeof(Bnk_sys)))
            {
                if (Bnk_sys.account_number == account_number)
                {
                    int amount = 0;
                    cout << "Account Holder name: " << Bnk_sys.first_name << " " << Bnk_sys.last_name << endl;
                    cout << "Balance: " << Bnk_sys.avaliable_balance << endl;
                    cout << "Enter the amount that you want to deposite:  ";
                    cin >> amount;
                    Bnk_sys.avaliable_balance += amount;
                    cout << "Account Holder name: " << Bnk_sys.first_name << " " << Bnk_sys.last_name << endl;
                    cout << "Balance: " << Bnk_sys.avaliable_balance << endl;
                    ofstream another_bnk_db("G:\\DB\\Binary file\\bankDB1.dat", ios::app);
                    ifstream read_file("G:\\DB\\Binary file\\bankDB.dat");
                    another_bnk_db.write((char*)&Bnk_sys, sizeof(Bnk_sys));
                    while (read_file.read((char*)&Bnk_sys, sizeof(Bnk_sys)))
                    {
                        if (Bnk_sys.account_number != account_number)
                        {
                            another_bnk_db.write((char*)&Bnk_sys, sizeof(Bnk_sys));
                        }
                    }
                    another_bnk_db.close();
                    read_file.close();
                    validAccount = true;
                }
            }
            read_bnk_db.close();
            if (validAccount)
            {
                remove("G:\\DB\\Binary file\\bankDB.dat");
                int l = rename("G:\\DB\\Binary file\\bankDB1.dat", "G:\\DB\\Binary file\\bankDB.dat");
            }
            else
            {
                cout << "Computer is finding your account or You don't have any sort of account in this bank....:)" << endl;
                cout << "Please Enter a valid account number or Opean a Account.....:)" << endl;
            }
            Sleep(3000);
            system("cls");
        }
        else if (operation == 3)
        {
            // function for Withdrwan
            string acc_no;
            cout << "Enter the account number: " << endl;
            cin >> acc_no;
            ifstream readDB("G:\\DB\\Binary file\\bankDB.dat");
            bool withdraw = false;
            while (readDB.read((char*)&Bnk_sys, sizeof(Bnk_sys)))
            {
                if (Bnk_sys.account_number == acc_no)
                {
                    int amount;
                    cout << "Account Holder Name is: " << Bnk_sys.first_name << " " << Bnk_sys.last_name << endl;
                    cout << "Current Balance: " << Bnk_sys.avaliable_balance << endl;
                    cout << "Please enter the amount: ";
                    cin >> amount;
                    if (amount > Bnk_sys.avaliable_balance - 1000)
                    {
                        cout << "Insufficient balance....." << endl;
                        break;
                    }
                    else
                    {
                        Bnk_sys.avaliable_balance -= amount;
                        withdraw = true;
                        cout << "Account Holder Name is: " << Bnk_sys.first_name << " " << Bnk_sys.last_name << endl;
                        cout << "Current Balance: " << Bnk_sys.avaliable_balance << endl;
                        ifstream readAnotherDB("G:\\DB\\Binary file\\bankDB.dat");
                        ofstream anotherBnkDB("G:\\DB\\Binary file\\bankDB1.dat", ios::app);
                        anotherBnkDB.write((char*)&Bnk_sys, sizeof(Bnk_sys));
                        while (readAnotherDB.read((char*)&Bnk_sys, sizeof(Bnk_sys)))
                        {
                            if (acc_no != Bnk_sys.account_number)
                            {
                                anotherBnkDB.write((char*)&Bnk_sys, sizeof(Bnk_sys));
                            }
                        }
                        readAnotherDB.close();
                        anotherBnkDB.close();
                    }
                }
            }
            readDB.close();
            if (withdraw == false)
            {
                cout << "Either computer is searching or Your account is not ther please check your account number and Try again........:))" << endl;
            }
            else
            {
                remove("G:\\DB\\Binary file\\bankDB.dat");
                int l = rename("G:\\DB\\Binary file\\bankDB1.dat", "G:\\DB\\Binary file\\bankDB.dat");
            }
            Sleep(3000);
            system("cls");
        }
        else if (operation == 4)
        {
            // function for update
            string acc_no;
            cout << "Please enter the account number: ";
            cin >> acc_no;
            ifstream readDB("G:\\DB\\Binary file\\bankDB.dat");
            bool update_details = false;
            while (readDB.read((char*)&Bnk_sys, sizeof(Bnk_sys)))
            {
                if (Bnk_sys.account_number == acc_no)
                {
                    char key;
                c:    cout << "Pleaae select from the below:)\n Please press f for first name \n Please press l for last name \n Please press a for address \n Please press p for phone number\n";
                    cin >> key;
                    ifstream readanotherdb("G:\\DB\\Binary file\\bankDB.dat");
                    ofstream anotherDB("G:\\DB\\Binary file\\bankDB1.dat", ios::app);
                    cout << "Account Holder Name: " << Bnk_sys.first_name << " " << Bnk_sys.last_name << endl;
                    cout << "Account Holder address: " << Bnk_sys.address << endl;
                    if (key == 'f' or key == 'F')
                    {
                        cin.ignore();
                        string first_name = "";
                        cout << "Please Enter first name: ";
                        getline(cin, first_name);
                        Bnk_sys.first_name = first_name;
                        cout << "Account Holder Name: " << Bnk_sys.first_name << " " << Bnk_sys.last_name << endl;
                        anotherDB.write((char*)&Bnk_sys, sizeof(Bnk_sys));
                        while (readanotherdb.read((char*)&Bnk_sys, sizeof(Bnk_sys)))
                        {
                            if (Bnk_sys.account_number != acc_no)
                                anotherDB.write((char*)&Bnk_sys, sizeof(Bnk_sys));
                        }
                        update_details = true;
                    }
                    else if (key == 'l' or key == 'L')
                    {
                        cin.ignore();
                        string last_name = "";
                        cout << "Please Enter last name: ";
                        getline(cin, last_name);
                        Bnk_sys.last_name = last_name;
                        cout << "Account Holder Name: " << Bnk_sys.first_name << " " << Bnk_sys.last_name << endl;
                        anotherDB.write((char*)&Bnk_sys, sizeof(Bnk_sys));
                        while (readanotherdb.read((char*)&Bnk_sys, sizeof(Bnk_sys)))
                        {
                            if (Bnk_sys.account_number != acc_no)
                                anotherDB.write((char*)&Bnk_sys, sizeof(Bnk_sys));
                        }
                        update_details = true;
                    }
                    else if (key == 'a' or key == 'A')
                    {
                        cin.ignore();
                        string address = "";
                        cout << "Please enter address: ";
                        getline(cin, address);
                        Bnk_sys.address = address;
                        anotherDB.write((char*)&Bnk_sys, sizeof(Bnk_sys));
                        cout << "Account Holder address: " << Bnk_sys.address << endl;
                        while (readanotherdb.read((char*)&Bnk_sys, sizeof(Bnk_sys)))
                        {
                            if (Bnk_sys.account_number != acc_no)
                                anotherDB.write((char*)&Bnk_sys, sizeof(Bnk_sys));
                        }
                        update_details = true;
                    }
                    else if (key == 'p' or key == 'P')
                    {
                        cin.ignore();
                        string phn_no = "";
                        cout << "Please enter Phone number: ";
                        getline(cin, phn_no);
                        Bnk_sys.phone_number = phn_no;
                        cout << "Account Holder Phone number: " << Bnk_sys.phone_number << endl;
                        anotherDB.write((char*)&Bnk_sys, sizeof(Bnk_sys));
                        while (readanotherdb.read((char*)&Bnk_sys, sizeof(Bnk_sys)))
                        {
                            if (Bnk_sys.account_number != acc_no)
                                anotherDB.write((char*)&Bnk_sys, sizeof(Bnk_sys));
                        }
                        update_details = true;
                    }
                    else
                    {
                        cout << "Please select for the above functionality:)" << endl;
                    }
                    readanotherdb.close();
                    anotherDB.close();
                    if (readanotherdb.is_open() == true)
                        readanotherdb.close();
                    if (anotherDB.is_open() == true)
                        anotherDB.close();
                }
            }
            readDB.close();
            if (update_details == true)
            {
                remove("G:\\DB\\Binary file\\bankDB.dat");
                int l = rename("G:\\DB\\Binary file\\bankDB1.dat", "G:\\DB\\Binary file\\bankDB.dat");
            }
            else
            {
                cout << "Either computer is searching or Your account is not ther please check your account number and Try again........:))" << endl;
            }
            Sleep(3000);
            system("cls");
        }
        else if (operation == 5)
        {
            // function for search
            string acc_no;
            cout << "Enter the account number: ";
            cin >> acc_no;
            ifstream readDb("G:\\DB\\Binary file\\bankDB.dat");
            bool avaliable_account = false;
            while (readDb.read((char*)&Bnk_sys, sizeof(Bnk_sys)))
            {
                if (Bnk_sys.account_number == acc_no)
                {
                    cout << "Account Holder Name is: " << Bnk_sys.first_name << " " << Bnk_sys.last_name << endl;
                    cout << "Address: " << Bnk_sys.address << endl;
                    cout << "Phone Number: " << Bnk_sys.phone_number << endl;
                    cout << "Current Balance: " << Bnk_sys.avaliable_balance << endl;
                    avaliable_account = true;
                    break;
                }
            }
            if (avaliable_account == false)
            {
                cout << "Either computer is searching or Your account is not ther please check your account number and Try again........:))" << endl;
            }
            readDb.close();
            Sleep(3000);
            system("cls");
        }
        else if (operation == 6)
        {
            // function for Delete
            string acc_no = "";
            cout << "Enter the account number: ";
            cin >> acc_no;
            ifstream readDb("G:\\DB\\Binary file\\bankDB.dat");
            bool account_closed = false;
            char key;
            while (readDb.read((char*)&Bnk_sys, sizeof(Bnk_sys))) {
                if (Bnk_sys.account_number == acc_no)
                {
                    cout << "Account Holder name: " << Bnk_sys.first_name << " " << Bnk_sys.last_name << endl;
                    cout << "Current Bnak Balance: " << Bnk_sys.avaliable_balance << endl;
                    cout << "Do you want to delete account? (y/n):  ";
                    cin >> key;
                    if (key == 'Y' || key == 'y')
                    {
                        ofstream anotherBnkDB("G:\\DB\\Binary file\\bankDB1.dat", ios::app);
                        ifstream readAnotherDB("G:\\DB\\Binary file\\bankDB.dat");
                        while (readAnotherDB.read((char*)&Bnk_sys, sizeof(Bnk_sys)))
                        {
                            if (Bnk_sys.account_number != acc_no) {
                                anotherBnkDB.write((char*)&Bnk_sys, sizeof(Bnk_sys));
                            }
                        }
                        anotherBnkDB.close();
                        readAnotherDB.close();
                        account_closed = true;
                        cout << "Account Deleted Successfully........:)" << endl;
                    }
                    else
                    {
                        cout << "Account is not Colsed......." << endl;
                    }
                }
            }
            readDb.close();
            if (account_closed == false)
            {
                cout << "Either computer is searching or Your account is not ther please check your account number and Try again........:))" << endl;
            }
            if (account_closed == true)
            {
                cout << "HI" << endl;
                remove("G:\\DB\\Binary file\\bankDB.dat");
                int l = rename("G:\\DB\\Binary file\\bankDB1.dat", "G:\\DB\\Binary file\\bankDB.dat");
            }

            Sleep(3000);
            system("cls");
        }
        else if (operation == 7)
        {
            // function for Check balance
            string acc_no;
            cout << "Enter the account number: ";
            cin >> acc_no;
            ifstream readDb("G:\\DB\\Binary file\\bankDB.dat");
            if (readDb.is_open())
            {
                bool avaliable_account = false;
                while (readDb.read((char*)&Bnk_sys, sizeof(Bnk_sys)))
                {
                    if (Bnk_sys.account_number == acc_no)
                    {
                        cout << "Account Holder Name is: " << Bnk_sys.first_name << " " << Bnk_sys.last_name << endl;
                        cout << "Current Balance: " << Bnk_sys.avaliable_balance << endl;
                        avaliable_account = true;
                        break;
                    }
                }
                if (avaliable_account == false)
                {
                    cout << "Either computer is searching or Your account is not ther please check your account number and Try again........:))" << endl;
                }
                readDb.close();
            }
            else
                break;
            readDb.close();
            Sleep(3000);
            system("cls");
        }
        else if (operation != 8)
        {
            cout << "Please select from the above menu......:)" << endl;
            Sleep(3000);
            system("cls");
        }

    } while (operation != 8);
    cout << "\t\t\t\t\t Thank You and Visit Again!!!!" << endl;
    ifstream f("G:\\DB\\Binary file\\bankDB.dat");
    humanRead.open("G:\\DB\\human read\\humanReadFile.txt");
    while (f.read((char*)&Bnk_sys, sizeof(Bnk_sys))) {
        Bnk_sys.humamReadfile();
    }
    f.close();
    humanRead.close();
    system("pause");
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

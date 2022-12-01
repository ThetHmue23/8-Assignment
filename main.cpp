#include "iostream"
#include "BankDatabase.h"
using namespace std;

int userInterFace();
void registerAcc(BankDatabase& inDB);
void login(BankDatabase& inDB);
void admin(BankDatabase& inDB);

int main ()
{
    BankDatabase theBDB;
    bool done = false;
    while (!done)
    {
        int section = userInterFace();
        switch (section)
        {
            case 1:
                registerAcc(theBDB);
                break;
            case 2:
                login(theBDB);
                break;
            case 3:
                admin(theBDB);
                break;
            case 4:
                done = true;
                break;
            default:
                cout << "UNKNOWN COMMEND!"<<endl;
                break;
        }
    }
}

int userInterFace()
{
    int section=0;
    cout <<"-------------------------"<<endl;
    cout << "WELCOME TO OUR NCC BANK"<<endl;
    cout << "1) REGISTER ACCOUNT IN NCC " <<endl;
    cout << "2) LONGIN TO YOUR ACCOUNT " << endl;
    cout << "3) ONLY ADMIN ACCESS FILES DATA "<<endl;
    cout << "4) EXIT "<<endl;
    cout <<"--> ";
    cin >> section;
    return section;
}

void registerAcc(BankDatabase& inDB)
{
    string firstName , lastName , NRCNo ,password;
    long long phoneNo;
    cout <<"ENTER FIRST NAME : ";
    cin >> firstName;
    cout << "ENTER LAST NAME : ";
    cin >> lastName;
    cout << "ENTER PHONE NUMBER : ";
    cin >> phoneNo;
    cout << "ENTER NRC NUMBER : ";
    cin >> NRCNo;
    cout << "ENTER STRONG PASSWORD : ";
    cin >> password;
    try
    {
        inDB._accRegister(firstName, lastName, phoneNo, NRCNo, password);
    }catch (const exception&)
    {
        cerr << "SORRY, UNABLE TO REGISTER !"<<endl;
       cout <<"------------------------------------"<<endl;
    }
}

void login(BankDatabase& inDB)
{
    string firstName, lastName, password;
    cout <<"ENTER FIRST NAME : ";
    cin >> firstName;
    cout << "ENTER LAST NAME : ";
    cin >> lastName;
    cout << "ENTER PASSWORD : ";
    cin >> password;
    try
    {
        inDB._accLogin(firstName, lastName, password);
    }catch (const exception& e)
    {
        cerr << "PLEASE, CHECK YOUR USERNAME AND PASSWORD"<<endl;
    }
}

void admin(BankDatabase& inDB)
{
    Banks theBank;
    string passcode;
    cout << "ENTER ADMIN PASSCODE :";
    cin >> passcode;
    if (passcode == theBank.getPasscode()){
        int chose;
        cout <<"1) REGISTERED ACCOUNTS"<<endl;
        cout <<"2) RECORDED ALL DATA"<<endl;
        cout <<"3) QUIT"<<endl;
        cout <<"-> :";
        cin >> chose;
        if (chose == 1 )
        {
            inDB._displayAll();
        }else if(chose == 2)
        {
            BankDatabase::_allRecord();
        }else
        {
            cout << "BYE BYE"<<endl;
        }
    }else {
        cerr<< "ACCESS DENIED!"<<endl;
        cout << "------------"<<endl;
    }
}
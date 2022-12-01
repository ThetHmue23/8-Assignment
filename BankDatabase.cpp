#include "iostream"
#include "fstream"
#include "sstream"
#include "stdexcept"
#include <ctime>
#include "BankDatabase.h"
using namespace std;
vector<Banks> BankDatabase::checkFile() {
    /* first check the data in the file . Put data into its belong by using vector .*/
    Banks theBank;
    string firstName,lastName,NRCNo,password;
    long long phoneNo;int money;
    int count=0;

    string data;
    string registerFile;
    ifstream regiFile("RegisteredUser'sDataFile.txt");
    if (regiFile.is_open())
    {
        while (getline(regiFile, registerFile))
        {
            if (!registerFile.empty())
            {
                registerFile += " ";
                for (auto &ch: registerFile)
                {
                    if (ch == ' ')
                    {
                        if (count == 0)
                        {
                            firstName = data;
                            data = "";
                            count++;
                        } else if (count == 1)
                        {
                            lastName = data;
                            /* put the username into the setUserName */
                            theBank.setUserName(firstName, lastName);
                            data = "";
                            count++;
                        } else if (count == 2)
                        {
                            stringstream ss;
                            ss << data;
                            ss >> phoneNo;
                            /* put the phone number into the setPhoneNo */
                            theBank.setPhoneNo(phoneNo);
                            data = "";
                            count++;
                        } else if (count == 3)
                        {
                            NRCNo = data;
                            /* put the NRC number into the setNRCno */
                            theBank.setNRCno(NRCNo);
                            data = "";
                            count++;
                        } else if (count == 4)
                        {
                            password = data;
                            /* put the password into the setPassword */
                            theBank.setPassword(password);
                            data = "";
                            count++;
                        }else if (count == 5)
                        {
                            stringstream tt;
                            tt << data;
                            tt >> money;
                            /* put the deposit money into the setDeposit */
                            theBank.setDeposit(money);
                            data="";
                            count = 0;
                        }
                    } else
                    {
                        string cha(1, ch);
                        data += cha;
                    }
                }
                /* all data from the file put into mBankData using vector */
                mBankData.push_back(theBank);
            }
        }

    }
    return mBankData;
}

Banks& BankDatabase::_accRegister(std::string inFirstName, std::string inLastName, long long inPhoneNo,
                                  std::string inNRCNo, std::string inPassword) {

    int inAmount=0;
    Banks theBank;
    checkFile();
    string userName = inFirstName + ' ' + inLastName;
    if (!mBankData.empty())
    {
        /*check the username it has already used or not*/
        for (auto &iter: mBankData)
        {
            if (userName != iter.getUserName())
            {
                theBank.setUserName(inFirstName, inLastName);
            }else
            {
                cerr << userName << " IS ALREADY EXIT! ";
                throw exception();
            }
        }
        /*check the phone number it has already used or not*/
        for (auto &iter: mBankData)
        {
            if (inPhoneNo != iter.getPhoneNo())
            {
                theBank.setPhoneNo(inPhoneNo);
            }else
            {
                cerr << inPhoneNo << " IS ALREADY EXIT !";
                throw exception();
            }
        }
        /*check the NRC number it has already used or not*/
        for (auto &iter: mBankData)
        {
            if (inNRCNo != iter.getNRCno())
            {
                theBank.setNRCno(inNRCNo);
            }else
            {
                cerr << inNRCNo << " IS ALREADY EXIT! " ;
                throw exception();
            }
        }
        /*check the password it has already used or not*/
        for (auto &iter: mBankData)
        {
            if (inPassword != iter.getPassword())
            {
                theBank.setPassword(inPassword);
            }else
            {
                cerr << inPassword << " IS ALREADY EXIT! " ;
                throw exception();
            }
        }
        mBankData.push_back(theBank);
    }
        /* if RegisteredUser'sDataFile is empty, set the data directly */
    else
    {
        theBank.setUserName(inFirstName, inLastName);
        theBank.setPhoneNo(inPhoneNo);
        theBank.setNRCno(inNRCNo);
        theBank.setPassword(inPassword);
    }
    cout<< "REGISTERING ACCOUNT HAVE BE DONE!"<< endl;
    /* registering account is just new account. so we need to set deposit value for the new account*/
    _depositForNew(theBank, inAmount);
    mBankData.push_back(theBank);
    /* open the file put all data user's set into the file*/
    ofstream register_file;
    register_file.open("RegisteredUser'sDataFile.txt",ios::app);
    register_file << theBank.getUserName() << " " << theBank.getPhoneNo() << " " << theBank.getNRCno() << " "
                  << theBank.getPassword() << " " << theBank.getDeposit() << endl;
    register_file.close();

}

void BankDatabase::_depositForNew(Banks& theBank, int inAmount) {
    Deposit:
    cout << "FOR A NEW ACCOUNT, AT LEAST YOU CAN DEPOSIT FORM 1,000 kyat TO MAXIMUM 1,000,000 Kyat!" << endl;
    cout << "PLEASE, ENTER AMOUNT : ";
    cin >> inAmount;
    if (inAmount >= 1000)
    {
        theBank.setDeposit(inAmount);
    }else
    {
        cout << "AT LEAST DEPOSIT AMOUNT MUST BE 1000 Kyat" << endl;
        goto Deposit;
    }
}

Banks& BankDatabase::_accLogin(const string& inFirstName, const string& inLastName, const string& inPassword) {
    string userName = inFirstName+" "+inLastName;
    checkFile();
    if (mBankData.empty()){
        cout << "THERE IS NO DATA IN THE FILE!" << endl;
    }
    for ( auto &iter : mBankData)
    {
        if (iter.getUserName() == userName && iter.getPassword() == inPassword)
        {
            int section;
            cout << "LOGIN SUCCESS:" << endl ;
            Choose:
            cout << "1) TRANSFER SECTION "<<endl;
            cout << "2) WITHDRAW SECTION "<<endl;
            cout << "3) DEPOSIT SECTION "<<endl;
            cout << "4) RENDER SECTION "<<endl;
            cout << "5) QUIT "<<endl;
            cout << "-> :";
            cin >> section;
            if ( section == 1)
            {
                int tranAmount=0;
                _transfer(iter,tranAmount);
                goto Choose;
            }
            else if (section == 2)
            {
                int wAmount=0;
                _withdraw(iter,wAmount);
                goto Choose;
            }
            else if (section == 3)
            {
                int dAmount=0;
                _depositMore(iter, dAmount);
                goto Choose;
            }
            else if(section == 4)
            {
                _display(iter);
                goto Choose;
            }
            else if (section == 5)
            {
                break;
            }
            else
            {
                cout<< "TYPED NUMBER IS WRONG!"<<endl;
                goto Choose;
            }
        }
    }
    cerr << "ENABLE TO LOGIN YOUR ACCOUNT.INVALID USERNAME OR PASSWORD !" << endl;
    throw exception();
}


void BankDatabase::_transfer(Banks& theBank, int tranAmount) {

    /* to record the transfer time */
    time_t recordTime = time(nullptr);
    string rec_time = asctime(localtime(&recordTime));

    /* to place the transfer record data to the file*/
    ofstream recordTranData;
    recordTranData.open("recordTransferData.txt",ios::app);

    int option;
    Choose:
    cout << "1) TRANSFER BY PHONE NUMBER" << endl;
    cout << "2) TRANSFER BY NRC NUMBER" << endl;
    cout <<"-> :";
    cin >> option;

    /* transfer by phone number */
    if (option == 1 )
    {
        long long phone_no;
        cout << "ENTER RECEIVER'S PHONE NUMBER : ";
        cin >> phone_no;

        /* Checking the receiver's phone number by using for loop */
        for (auto &iter : mBankData)
        {
            if ( iter.getPhoneNo() == phone_no)
            {
                cout << "ENTER AMOUNT TO TRANSFER : ";
                cin >> tranAmount;

                /* check the transfer amount */
                if (theBank.getDeposit() >= tranAmount + 1000)
                {
                    /* add money to receiver account */
                    int reAmount = iter.getDeposit();
                    iter.setDeposit(reAmount + tranAmount);

                    /* subtract money from sender account */
                    int seAmount = theBank.getDeposit();
                    theBank.setDeposit(seAmount - tranAmount);

                    recordTranData << "FROM " << theBank.getUserName() << " TRANSFERRED " << tranAmount << " KYAT TO "
                                   << iter.getUserName() << " at " << rec_time ;
                }else
                {
                    cout << "YOU CAN NOT TRANSFER. MUST LEFT 1000 KYAT IN YOUR ACCOUNT."<<endl;
                }
            }
        }
    }
    /* transfer by NRC number */
    else if (option == 2)
    {
        string nrc_no;
        cout <<"ENTER RECEIVER'S NRC NUMBER : ";
        cin >> nrc_no;
        for (auto &iter : mBankData)
        {
            if (iter.getNRCno() == nrc_no)
            {
                cout << "ENTER AMOUNT TO TRANSFER : ";
                cin >>tranAmount;
                if (theBank.getDeposit() >= tranAmount + 1000)
                {
                    /* add money to receiver account */
                    int inAmount = iter.getDeposit();
                    iter.setDeposit(inAmount + tranAmount);

                    /* subtract money from sender account */
                    int seAmount = theBank.getDeposit();
                    theBank.setDeposit(seAmount - tranAmount);

                    recordTranData << theBank.getUserName() << " TRANSFERRED " << tranAmount << " KYAT TO "
                                   << iter.getUserName() << " at " << rec_time;
                }else
                {
                    cout << "YOU CAN NOT TRANSFER. MUST LEFT 1000 KYAT IN YOUR ACCOUNT."<<endl;
                }
            }
        }
    }else
    {
        cout << "TYPED NUMBER IS WRONG!"<<endl;
        goto Choose;
    }
    /* reallocate the changes amount in the file */
    ofstream register_file;
    register_file.open("RegisteredUser'sDataFile.txt",ios::ate);
    for (auto &iter :mBankData)
    {
        register_file << iter.getUserName() << " " << iter.getPhoneNo() << " " << iter.getNRCno() << " "
                      << iter.getPassword() << " " << iter.getDeposit() << endl;
    }
    register_file.close();
    recordTranData.close();
}

void BankDatabase::_withdraw(Banks& theBank, int wAmount) {
    time_t recordTime = time(nullptr);
    string rec_time = asctime(localtime(&recordTime));

    ofstream recordTranData;
    recordTranData.open("recordTransferData.txt",ios::app);

    Withdraw:
    cout<< "ENTER AMOUNT OF MONEY TO WITHDRAW :" <<endl;
    cin >> wAmount;

    if ( theBank.getDeposit() >= wAmount + 1000)
    {
        int inAmount = theBank.getDeposit();
        theBank.setDeposit(inAmount - wAmount);
        cout << wAmount << " KYAT SUCCESSFUL WITHDRAW BY " << theBank.getUserName() << endl;

        recordTranData << wAmount << " KYAT : WITHDRAW BY " <<theBank.getUserName() << " : " << rec_time;
    }else
    {
        cout << "CAN NOT WITHDRAW. MUST LEFT 1000 KYAT IN YOUR ACCOUNT."<<endl;
        goto Withdraw;
    }
    /* reallocate the changes amount in the file */
    ofstream register_file;
    register_file.open("RegisteredUser'sDataFile.txt",ios::ate);
    for (auto &iter :mBankData)
    {
        register_file << iter.getUserName() << " " << iter.getPhoneNo() << " " << iter.getNRCno() << " "
                      << iter.getPassword() << " " << iter.getDeposit() << endl;
    }
    register_file.close();
}

void BankDatabase::_depositMore(Banks& theBank, int dAmount) {
    time_t recordTime = time(nullptr);
    string rec_time = asctime(localtime(&recordTime));

    ofstream recordTranData;
    recordTranData.open("recordTransferData.txt",ios::app);

    Deposit:
    cout << "ENTER AMOUNT OF MONEY TO DEPOSIT : "<<endl;
    cin >> dAmount;
    if ((dAmount + theBank.getDeposit()) <= 1000000)
    {
        int inAmount = theBank.getDeposit();
        theBank.setDeposit(inAmount + dAmount);
        cout << "DEPOSIT MONEY "<< dAmount << " SUCCESSFULLY ADD TO YOUR ACCOUNT."<<endl;
        recordTranData << dAmount << " KYAT : DEPOSITED TO ACCOUNT " <<theBank.getUserName() << " : " << rec_time;
    }else
    {
        cout << "YOUR ACCOUNT ONLY CAN DEPOSIT UNDER 1,000,000 KYAT." << endl;
        goto Deposit;
    }
    /* reallocate the changes amount in the file */
    ofstream register_file;
    register_file.open("RegisteredUser'sDataFile.txt",ios::ate);
    for (auto &iter :mBankData)
    {
        register_file << iter.getUserName() << " " << iter.getPhoneNo() << " " << iter.getNRCno() << " "
                      << iter.getPassword() << " " << iter.getDeposit() << endl;
    }
    register_file.close();
}

void BankDatabase::_display(Banks& theBank) { /* only show for the login success user*/
    theBank.display();
}

void BankDatabase::_displayAll() {/* display all register account only can access admin */
    checkFile();
    cout << "  ##**REGISTERED ACCOUNTS**##" <<endl;
    cout << "_______________________________"<<endl;
    for (auto &iter : mBankData)
    {
        iter.display();
    }
}

void BankDatabase::_allRecord() {/* display all transfer record only can access admin */
    string record;
    int no =1;
    ifstream record_data("recordTransferData.txt");
    if ( record_data.is_open())
    {
         while(getline(record_data,record))
         {
             cout << no<<")-" << record <<endl;
             no++;
         }
    }
}
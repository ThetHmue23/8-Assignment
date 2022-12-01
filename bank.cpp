#include "iostream"
#include "bank.h"


void Banks::setUserName(std::string& inFirstName, std::string& inLastName) {
    mName = inFirstName + " " + inLastName;
}

std::string Banks::getUserName() const{
    return mName;
}

void Banks::setNRCno(std::string& inNRCno) {
    mNRCno = inNRCno;
}

std::string Banks::getNRCno() const{
    return mNRCno;
}

void Banks::setPhoneNo(long long inPhoneNo) {
    mPhoneNO = inPhoneNo;
}

long long Banks::getPhoneNo() const{
    return mPhoneNO;
}

void Banks::setPassword(std::string &inPassword) {
    mPassword = inPassword;
}

std::string Banks::getPassword() const {
    return mPassword;
}

void Banks::setDeposit(int inAmount) {
    mAmount = inAmount;
}
int Banks::getDeposit() const {
    return mAmount;
}
std::string Banks::getPasscode() const {
    return aPasscode;
}
void Banks::display() const {
    std::cout<< "  Account Name : "<< getUserName() << std::endl;
    std::cout<< "  Phone Number : "<< getPhoneNo() << std::endl;
    std::cout<< "  NRC Number   : "<< getNRCno() << std::endl;
    std::cout<< "  Password     : "<< getPassword() << std::endl;
    std::cout<< "  Amount       : "<< getDeposit() <<std::endl;
    std::cout<< "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_"<<std::endl;
}
#include "iostream"

class Banks {
public:
    void        setUserName(std::string& inFirstName, std::string& inLastName);
    std::string getUserName()const;
    void        setPhoneNo(long long inPhoneNo);
    long long   getPhoneNo()const;
    void        setNRCno(std::string& inNRCno);
    std::string getNRCno()const;
    void        setPassword(std::string& inPassword);
    std::string getPassword()const;
    void        setDeposit(int inAmount);
    int         getDeposit() const;
    std::string   getPasscode   ()const;
    void        display()const;

private:
    int         mAmount;
    std::string mName;
    long long   mPhoneNO;
    std::string mNRCno;
    std::string mPassword;
    std::string aPasscode = "admin9999";
};
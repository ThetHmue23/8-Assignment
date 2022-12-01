#include "iostream"
#include "bank.h"
#include "vector"

class BankDatabase{

public:
    std::vector<Banks> checkFile();
    Banks&        _accRegister  (std::string inFirstName, std::string inLastName, long long inPhoneNo,
                                 std::string inNRCNo, std::string inPassword);
    Banks&        _accLogin     (const std::string& inFirstName, const std::string& inLastName, const std::string& inPassword);
    static void   _depositForNew(Banks&, int inAmount);
    void          _transfer     (Banks&, int tranAmount);
    void          _withdraw     (Banks&, int wAmount);
    void          _depositMore  (Banks&, int dAmount);
    void          _displayAll   ();
    static void   _display      (Banks&);
    static void   _allRecord    ();

protected:
    std::vector<Banks>mBankData;
};
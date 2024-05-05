#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>


class Account
{
public:
	Account()
		:holderName(" "), accountNumber(-1), balance(-1), accountPassword(-1){}
	Account(std::string n, int aN, int b, int aP)
		:holderName(n), accountNumber(aN), balance(b), accountPassword(aP){}

	std::string getHolderName() { return holderName; }
	int getAccountNumber() { return accountNumber; }
	int getBalance() { return balance; }
	int getAccountPassword() { return accountPassword; }
	//std::string getAccountType() { return accountType; }


	void setHolderName(std::string n) { holderName = n; }
	void setAccountNumber(int aN) { accountNumber = aN; }
	void setBalance(int b) { balance = b; }
	void setAccountPassword(int aP) { accountPassword = aP; }
	//void setAccountType(std::string type) { accountType = type; }

	void deposit(int depositAmount);
	void withdrawal(int withdrawalAmount);
	void balanceCheck();


protected:
	std::string holderName;
	int accountNumber;
	int balance;
	int accountPassword;
	//std::string accountType;
};

#endif
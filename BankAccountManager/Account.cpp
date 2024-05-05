#include "Account.h"

void Account::deposit(int depositAmount)
{
	balance += depositAmount;
	std::cout << "You deposited $" << depositAmount << "!" << std::endl;
	std::cout << "New balance is $" << balance << "!" << std::endl;
	std::cout << std::endl;


}

void Account::withdrawal(int withdrawalAmount)
{
	if (balance > withdrawalAmount){
		balance -= withdrawalAmount;
		std::cout << "You withdrawaled $" << withdrawalAmount << "!" << std::endl;
		std::cout << "New balance is $" << balance << "!" << std::endl;
		std::cout << std::endl;

	}
	else
		std::cout << "You don't have enough money in your account!" << std::endl;
	std::cout << std::endl;

}

void Account::balanceCheck()
{
	std::cout << "You have $" << balance << " in your account!" << std::endl;
	std::cout << std::endl;

}

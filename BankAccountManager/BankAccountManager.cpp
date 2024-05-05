#include <iostream>
#include "Account.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>


std::vector<Account> readAccountFromFile(const std::string& filename);

void writeAccountToFile(std::vector<Account>& books, const std::string& filename);

void deleteAccountFromFile(Account& target, const std::string& filename);


int main()
{
	
	std::cout << "\t  BANK ACCOUNT MANAGER" << std::endl << std::endl;

	while (true) {
		int accountNumber;

		std::cout << "  Please give your account number : ";
		std::cin >> accountNumber;
		//looking for is it int!
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << std::endl;
			std::cout << "Invalid input! Account number must be number. Please give valid input" << std::endl;
		}

		//creating vector for filling class
		std::vector<Account> allAccounts = readAccountFromFile("allAccount.txt");

		//filling the vector with correct data
		auto it = allAccounts.begin();
		while (it != allAccounts.end()) {
			if (it->getAccountNumber() == accountNumber) {
				break;
			}
			else
			{
				it++;
			}
		}
		if (it == allAccounts.end()) { // if there is no class with given input
			std::cout << std::endl;
			std::cout << "There is no account such as this account number!" << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
		}
		else
		{
			//creating class and initiliazing with vector
			Account choosedAccount = *it;

			//Account choosedAccount = *it;
			int tempPass;
			std::cout << "Please give your password(You have 5 attempt) = ";
			std::cin >> tempPass;

			//looking for password.
			int countForRemainingAttempt = 1;
			while (choosedAccount.getAccountPassword() != tempPass) {
				if (countForRemainingAttempt < 5) {
					std::cout << "Please try again: ";
					std::cin >> tempPass;
					//again looking for is it int
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << std::endl;
						std::cout << "Invalid input! Password must be number. Please give valid input" << std::endl;
					}
					countForRemainingAttempt++;
				}
				else
				{
					std::cout << std::endl;
					std::cerr << "YOU GIVE A LOT WRONG ANSWER! QUITTING APP" << std::endl;
					exit(1);
				}
			}
			//cleaning the terminal
			system("CLS");
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "  \t[Welcome back " << choosedAccount.getHolderName() << "!]" << std::endl << std::endl;
			std::cout << "  What u want to do!" << std::endl << std::endl;
			//looking for what action will take
			while(true){
				std::string chosenNumber;

				std::cout << "  1 - Check balance" << std::endl;
				std::cout << "  2 - Deposit" << std::endl;
				std::cout << "  3 - Withdrawal" << std::endl;
				std::cout << "  For exitting [exit]" << std::endl;
				std::cout << "Please choose something: ";
				std::cin >> chosenNumber;
				
				if (chosenNumber == "1") {
					std::cout << std::endl << std::endl;
					choosedAccount.balanceCheck();
				}
				else if (chosenNumber == "2")
				{
					std::vector<Account> tempForWriting;
					int depositAmount;
					std::cout << "  Please give amount to deposit: ";
					std::cin >> depositAmount;
					std::cout << std::endl;
					deleteAccountFromFile(choosedAccount, "allAccount.txt");
					choosedAccount.deposit(depositAmount);
					tempForWriting.push_back(choosedAccount);
					writeAccountToFile(tempForWriting, "allAccount.txt");
				}
				else if (chosenNumber == "3")
				{
					std::vector<Account> tempForWriting;
					int withdrawalAmount;
					std::cout << "  Please give amount to withdrawal: ";
					std::cin >> withdrawalAmount;
					std::cout << std::endl;
					deleteAccountFromFile(choosedAccount, "allAccount.txt");
					choosedAccount.withdrawal(withdrawalAmount);
					tempForWriting.push_back(choosedAccount);
					writeAccountToFile(tempForWriting, "allAccount.txt");

				}
				else if (chosenNumber == "EXIT" || chosenNumber == "Exit" || chosenNumber == "exit")
				{
					std::cout << std::endl;
					std::cout << "You exit the program!" << std::endl;
					exit(0);
				}
				else
				{
					std::cout << "PLEASE GIVE VALID INPUT" << std::endl;
				}

			}

		}

	}
	

}

// reading file func
std::vector<Account> readAccountFromFile(const std::string& filename) {
	std::vector<Account> bankAccounts;
	std::ifstream inFile(filename);
	if (inFile.is_open()) {
		std::string line;
		while (std::getline(inFile, line)) {
			std::istringstream iss(line);
			std::string accountName_str, accountNumber_str, accountPassword_str ,balance_str, accountType_str;
			if (std::getline(iss, accountName_str, '_') && std::getline(iss, accountNumber_str, '_') && std::getline(iss, accountPassword_str, '_') && std::getline(iss, balance_str, '_')) {
				int accountNumber = std::stoi(accountNumber_str);
				int balance = std::stoi(balance_str);
				int accountPassword = std::stoi(accountPassword_str);
				bankAccounts.emplace_back(accountName_str, accountNumber, balance, accountPassword);
			}
		}
		inFile.close();
	}
	else {
		std::cerr << "Unable to open file: " << filename << std::endl;
	}
	return bankAccounts;
}

//writing file func
void writeAccountToFile(std::vector<Account>& bankAccounts, const std::string& filename) {
	std::ofstream outFile(filename, std::ios_base::app);
	if (outFile.is_open()) {
		for (auto& bankAcc: bankAccounts) {
			outFile << bankAcc.getHolderName() << "_" << bankAcc.getAccountNumber() << "_" << bankAcc.getAccountPassword() << "_" << bankAcc.getBalance() << std::endl;
		}
		outFile.close();
	}
	else {
		std::cerr << "Unable to open file: " << filename << std::endl;
	}
}

//deleting from file func
void deleteAccountFromFile(Account& target, const std::string& filename) {
	std::vector<Account> accounts = readAccountFromFile(filename);

	std::ofstream outFile(filename + ".tmp");
	if (outFile.is_open()) {

		for (auto& account : accounts) {
			if (!(account.getHolderName() == target.getHolderName() && account.getAccountNumber() == target.getAccountNumber() && account.getAccountPassword() == target.getAccountPassword())) {
				outFile << account.getHolderName() << "_" << account.getAccountNumber() << "_" << account.getAccountPassword() << "_" << account.getBalance() << std::endl;
			}
		}
		outFile.close();

		remove("allAccount.txt");

		if (std::rename((filename + ".tmp").c_str(), filename.c_str()) != 0) {
			std::cerr << "Error replacing file: " << filename << std::endl;
		}
	}
	else {
		std::cerr << "Unable to open file: " << filename << std::endl;
	}
}
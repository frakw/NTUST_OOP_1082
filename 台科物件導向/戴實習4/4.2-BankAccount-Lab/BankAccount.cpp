#include"BankAccount.h"
int BankAccount::total = 0;
BankAccount::BankAccount() {
	balance = 0;
}
BankAccount::BankAccount(int input) {
	balance = input;
	total += input;
}
void BankAccount::withdraw(int output) {
	balance -= output;
	total -= output;
}
void BankAccount::save(int input) {
	balance += input;
	total += input;
}
int BankAccount::getBalance() {
	return balance;
}

int BankAccount::getAllMoneyInBank() {
	return total;
}
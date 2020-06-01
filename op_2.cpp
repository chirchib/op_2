#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Account
{
private:
	string FirstName, LastName;
	int Age, ID;

public:
	Account() : ID(0), LastName("Empty"), FirstName("Empty"), Age(0)
	{}

	Account(int _ID, string _LastName, string _FirstName, int _Age) :
		ID(_ID), LastName(_LastName), FirstName(_FirstName), Age(_Age)
	{}

	void getFullInf() const
	{
		cout << Age << "\t" <<LastName << "\t" << FirstName << endl;
	}

};

class displayAccount
{
public:
	void operator() (const Account* ptrP) const
	{
		ptrP->getFullInf();
	}
};

class Staff : public Account
{
private:
	

public:
	Staff(int id, string Last_Name, string  First_Name, int Age_) : Account(id, Last_Name, First_Name, Age_)
	{}

	
};

class Client : public Account
{
private:

	double balance;

public:

	Client(int ID_, string Last_Name, string  First_Name, int Age_) : Account(ID_, Last_Name, First_Name, Age_)
	{}

	void setBalance(double _balance)
	{
		balance = _balance;
	}


	double getBalance()
	{
		return balance;
	}

	double credit(double _credit)
	{
		return balance += _credit;
	}

	double debit(double _debit)
	{
		return balance -= _debit;
	}
};


int main()
{
	vector<Client*> ClientVector;
	vector<Staff*> StaffVector;

	Client* ptrC1 = new Client(3, "Deuville", "William", 26);
	Client* ptrC2 = new Client(7, "McDonald", "Stacey", 54);
	Client* ptrC3 = new Client(12, "Fredericks", "Roger", 38);
	ClientVector.push_back(ptrC1);
	ClientVector.push_back(ptrC2);
	ClientVector.push_back(ptrC3);

	Staff* ptrS1 = new Staff(242, "KuangThu", "Bruce", 32);
	Staff* ptrS2 = new Staff(130, "McDonald", "Amanda", 38);
	StaffVector.push_back(ptrS1);
	StaffVector.push_back(ptrS2);

	bool tmp = true;

	while (!true)
	{
		cout << "1. Client" << "\n2. Staff" << "\n0" << endl;
		char choice;
		cout << "Enter the number: " << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			string FName, LName;
			int Ag, Id;

			cout << "Please enter your ID" << endl;
			cin >> Id;
			cout << "Please enter your Last Name" << endl;
			cin >> LName;
			cout << "Please enter your First Name" << endl;
			cin >> FName;
			cout << "Please enter your Age" << endl;
			cin >> Ag;
			cout << "Welcome " << LName << " " << FName << endl;

			Client* Dmitry = new Client(Id, LName, FName, Ag);
			ClientVector.push_back(Dmitry);
			cout << "Please enter the opening balance of the account." << endl;
			double bill;
			cin >> bill;
			Dmitry->setBalance(bill);
			bool var = false;
			while (!var)
			{
				char num;
				cout << "What woulde you like? Please enter number." << endl;
				cout << "1. Credit.\n2. Debit.\n0. Quite." << endl;
				cin >> num;
				switch (num)
				{
				case 1:
					double putMoney;
					cout << "How much do you want to put money into the account?" << endl;
					cin >> putMoney;
					cout << "Your current account balance is - " << Dmitry->credit(putMoney) << "$" << endl;
					break;
				case 2:
					double withdrawMoney;
					cout << "How much do you want to withdraw money from the account?" << endl;
					cin >> withdrawMoney;
					if (withdrawMoney > Dmitry->getBalance())
					{
						cout << "The requested amount exceeds the account balance." << endl;
						break;
					}
					else
						cout << "Your current account balance is - " << Dmitry->debit(withdrawMoney) << "$" << endl;
					break;
				case 0:
					var++;
					break;
				default:
					cout << "Your choice is incorrect. Please enter the number again." << endl;
					break;
				}
			}
			delete Dmitry;
			break;

		case 2:
			cout << "\n1. Print the clients" << "\n0. Quite" << endl;
			cout << "Enter the number" << endl;
			bool var1 = false;
			char num1;
			cin >> num1;
			while (!var1)
			{
				switch (num1)
				{
				case 1:
					for_each(ClientVector.begin(),
						ClientVector.end(), displayAccount());
					break;
				case 0:
					var1++;
					break;
				default:
					cout << "Your choice is incorrect. Please enter the number again." << endl;
					break;
				}
			}
			break;

		case 0:
			tmp++;
			break;
		default:
			cout << "Your choice is incorrect. Please enter the number again." << endl;
			break;
		}

	}

	return 0;
}
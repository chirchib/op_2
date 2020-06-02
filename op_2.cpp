#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <fstream>

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
		cout << Age << "\t" << LastName << "\t" << FirstName << endl;
		return;
	}



	int getId()
	{
		return ID;
	}

	string getFirstName()
	{
		return FirstName;
	}

	string getLastName()
	{
		return LastName;
	}

	int getAge()
	{
		return Age;
	}

	void setId(int id)
	{
		ID = id;
	}

	void setFirstName(string firstName)
	{
		FirstName = firstName;
	}
	
	void setLastName(string lastName)
	{
		LastName = lastName;
	}

	void setAge(int age)
	{
		Age = age;
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

class Client : public Account
{
private:

	double balance = 0;

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


class Bank
{
private:
	vector<Client> _clients;

public:
	void add(Client client)
	{
		_clients.push_back(client);
	}

	void print()
	{
		for (auto it : _clients)
		{
			it.getFullInf();
		}
	}

	void save()
	{
		std::ofstream fp;
		fp.open("file.txt", std::ios_base::trunc | std::ios::out);
		for (auto it : _clients)
		{
			fp << it.getId() << " ";
			fp << it.getFirstName() << " ";
			fp << it.getLastName() << " ";
			if ((*(_clients.end() - 1)).getId() == it.getId())fp << it.getAge();
			else fp << it.getAge() << std::endl;
		}
		fp.close();
	}


	void load()
	{
		std::ifstream fp;
		fp.open("file.txt");
		while (!fp.eof())
		{
			int id;
			string firstName;
			string lastName;
			int age;

			fp >> id;
			fp >> firstName;
			fp >> lastName;
			fp >> age;

			_clients.push_back(Client(id, lastName, firstName, age));
		}
		fp.close();
	}
};



int main()
{
	auto bank = Bank();

	bank.load();

	bool tmp = false;
	int choice = -1;

	while (!tmp)
	{
		system("cls");
		cout << "1. Client" << "\n2. Staff" << "\n0. Exit" << endl;
		choice = _getch() - 48;
		switch (choice)
		{
		case 1:
		{
			system("cls");
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

			auto client = Client(Id, LName, FName, Ag);
			
			cout << "Please enter the opening balance of the account." << endl;
			double bill;
			cin >> bill;
			client.setBalance(bill);

			
			bool var = false;
			while (!var)
			{
				system("cls");
				int num;
				cout << "What woulde you like? Please enter number." << endl;
				cout << "1. Credit.\n2. Debit.\n0. Back." << endl;
				num = _getch() - 48;
				switch (num)
				{
				case 1:
					double putMoney;
					cout << "How much do you want to put money into the account?" << endl;
					cin >> putMoney;
					cout << "Your current account balance is - " << client.credit(putMoney) << "$" << endl;
					break;
				case 2:
					double withdrawMoney;
					cout << "How much do you want to withdraw money from the account?" << endl;
					cin >> withdrawMoney;
					if (withdrawMoney > client.getBalance())
					{
						cout << "The requested amount exceeds the account balance." << endl;
						break;
					}
					else
						cout << "Your current account balance is - " << client.debit(withdrawMoney) << "$" << endl;
					break;
				case 0:
					var++;
					break;
				default:
					//cout << "Your choice is incorrect. Please enter the number again." << endl;
					break;
				}
			}
			bank.add(client);
			
		}
			break;

		case 2:
		{
			int num1 = -1;
			while (num1 != 0)
			{
				system("cls");
				cout << "1. Print the clients" << "\n0. Back" << endl;
				bool var1 = false;
				
				num1 = _getch() - 48;
				switch (num1)
				{
				case 1:
				{
					bank.print();
					system("pause");
				}
				break;
				case 0:
					var1++;
					break;
				default:
					//cout << "Your choice is incorrect. Please enter the number again." << endl;
					break;
				}
			}
			break;
		}
			

		case 0:
		{
			tmp++;
		}
			break;
		default:
			//cout << "Your choice is incorrect. Please enter the number again." << endl;
			break;
		}

	}
	bank.save();
	return 0;
}

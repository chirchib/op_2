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

	///<summary>
	/// Геттер ID
	///</summary>
	int getId()
	{
		return ID;
	}
	///<summary>
	/// Геттер FirstName
	///</summary>
	string getFirstName()
	{
		return FirstName;
	}

	///<summary>
	/// Геттер LastName
	///</summary>
	string getLastName()
	{
		return LastName;
	}
	///<summary>
	/// Геттер Age
	///</summary>
	int getAge()
	{
		return Age;
	}
	///<summary>
	/// Сеттер ID
	///</summary>
	void setId(int id)
	{
		ID = id;
	}
	///<summary>
	/// Сеттер FirstName
	///</summary>
	void setFirstName(string firstName)
	{
		FirstName = firstName;
	}
	///<summary>
	/// Сеттер LastName
	///</summary>
	void setLastName(string lastName)
	{
		LastName = lastName;
	}
	///<summary>
	/// Сеттер Age
	///</summary>
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



///<summary>
/// Класс описывающий банк
///</summary>
class Bank
{
private:
///<summary>
/// Вектор клиентов банка
///</summary>
	vector<Client> _clients;

public:
///<summary>
/// Добавляет клиента в базу
///</summary>
	void add(Client client)
	{
		_clients.push_back(client);
	}


///<summary>
/// Выводит всех клиентов банка
///</summary>
	void print()
	{
		for (auto it : _clients)
		{
			it.getFullInf();
		}
	}
	///<summary>
	/// Сохраняет клиентов в базу из файла file.txt
	///</summary>
	void save()
	{
		ofstream fp;//Файловый поток записи
		fp.open("file.txt", ios_base::trunc | ios::out);//Открытие файла и очистка его содержимого
		for (auto it : _clients)//Перебор вектора клентов
		{
			//Запись в поток
			fp << it.getId() << " ";
			fp << it.getFirstName() << " ";
			fp << it.getLastName() << " ";
			if ((*(_clients.end() - 1)).getId() == it.getId())fp << it.getAge();//Если поеследний элемент - не делать переход на новую строку
			else fp << it.getAge() << std::endl;
		}
		fp.close();//Закрыть файл
	}

///<summary>
/// Загружает клиентов из файла file.txt в базу
///</summary>
	void load()
	{
		ifstream fp;//Файловый поток чтения
		fp.open("file.txt");//Открытие файла
		while (!fp.eof())//Пока не конец файла
		{
			int id;
			string firstName;
			string lastName;
			int age;

			//Инициализация переменных из файлового потока
			fp >> id;
			fp >> firstName;
			fp >> lastName;
			fp >> age;
			//Добавить клиента в базу
			_clients.push_back(Client(id, lastName, firstName, age));
		}
		fp.close();//Закрыть файл
	}
};



int main()
{
	auto bank = Bank();//Банк

	bank.load();//Загрузка банка

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
	bank.save();//Сохранение банка
	return 0;
}

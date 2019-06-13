//============================================================================
// Name        : Banking.cpp
// Author      : Sai
// Version     : 1st
// Copyright   : Rights Reserved
// Description : EasyBanking
//============================================================================

#include <iostream>
#include <fstream>
#define filename "BankDB.txt"
using namespace std;
static int acc_counter=100;

class Account
{
	int acc_no;
	char name[45];
	unsigned long int balance;
public:
	void getData();
	void putData();
	int returnAcc();
	unsigned long int returnBal();
	void saveBalance(unsigned long int);
};

class Details:Account
{

};
void Account::getData()
{
	acc_no=++acc_counter;
	cout<<"\nEnter Name:";
	cin>>name;
	cout<<"\nEnter Balance Amount:";
	cin>>balance;
}

void Account::putData()
{
	//cout<<"\nAccount no:"<<acc_no<<"\t|\tAccount Holder Name:"<<name<<"\t\t\t|\tBalance:"<<balance;
	cout<<"\n"<<acc_no<<"\t\t|\t\t"<<name<<"\t\t\t\t|\t\t"<<balance;
}

int Account::returnAcc()
{
	return acc_no;
}

unsigned long int Account::returnBal()
{
	return balance;
}

void Account::saveBalance(unsigned long int new_bal)
{
	balance=new_bal;
}

void writeFile()
{
	Account obj;
	ofstream fout;

	fout.open(filename,ios::app | ios::binary);
	if(!fout)
		cout<<"\nError in opening file!!!";
	else
	{
		obj.getData();
		fout.write((char*)&obj,sizeof(Account));
	}
	fout.close();
}

void readFile()
{
	Account obj;
	ifstream fin;

	fin.open(filename,ios::in);
	if(!fin)
		cout<<"\nError in opening file!!!";
	else
	{
		while(fin.read((char*)&obj,sizeof(Account)))
		{
			obj.putData();
		}
	}
	fin.close();
}

void readRecord()
{
	Account obj;
	ifstream fin;
	int tmp;

	cout<<"\n\nEnter Account no:";
	cin>>tmp;

	fin.open(filename,ios::in);
	if(!fin)
		cout<<"\nError in opening file!!!";
	else
	{
		while(fin.read((char*)&obj,sizeof(Account)))
		{
			if(tmp==obj.returnAcc())
			{
				obj.putData();
				break;
			}
		}
	}
	fin.close();
}

void deposite()
{
	int n;
	unsigned long int tmp;
	fstream file;
		file.open(filename, ios::in | ios::out | ios::binary);

		Account obj;
		cout<<"\nEnter Account No.:";
		cin>>n;

		while (file.read((char*) &obj, sizeof(obj)))
		{
			if (obj.returnAcc()==n)
			{
				cout << "\nEnter Amount to be desposited:";
				cin>>tmp;

				obj.saveBalance(obj.returnBal()+tmp);

				int pos = -1 * sizeof(obj);
				file.seekp(pos, ios::cur);

				file.write((char*) &obj, sizeof(obj));

			}
		}
		cout<<"\nDeposite Successful...";
		file.close();
}

void withdraw()
{
	int n;
	unsigned long int tmp;
	fstream file;
		file.open(filename, ios::in | ios::out | ios::binary);

		Account obj;
		cout<<"\nEnter Account No.:";
		cin>>n;

		while (file.read((char*) &obj, sizeof(obj)))
		{
			if (obj.returnAcc()==n)
			{
				cout << "\nEnter Amount to be Withdrawn:";
				cin>>tmp;

				if(obj.returnBal()==0 || obj.returnBal()<tmp)
					cout<<"\nNot sufficient balance...";
				else
				{
					obj.saveBalance(obj.returnBal()-tmp);

					int pos = -1 * sizeof(obj);
					file.seekp(pos, ios::cur);

					file.write((char*) &obj, sizeof(obj));
					cout<<"\Withdraw Successful...";
				}

			}
		}

		file.close();
}

int main()
{
	int ch;
	do
	{
		cout<<"\n\n1. Create New Account";
		cout<<"\n2. Check Account status:";
		cout<<"\n3. Display Account Info";
		cout<<"\n4. Deposite";
		cout<<"\n5. Withdraw";
		cout<<"\n6. Exit";
		cout<<"\n\nEnter Choice:";
		cin>>ch;

		switch(ch)
		{
		case 1: writeFile();
			break;
		case 2: readRecord();
			break;
		case 3: cout<<"\nAccount no\t|\tAccount Holder Name\t\t\t|\t\tBalance";
			cout<<"\n------------------------------------------------------------------------------------------";
			readFile();
			break;
		case 4: deposite();
			break;
		case 5: withdraw();
					break;
		case 6: cout<<"\nExit from Menu!!!";
			break;
		default: cout<<"\n\nWrong choice!!!";
		}

	}while(ch!=6);


	cout<<"\n\n***Exit From main()***";
	return 0;
}

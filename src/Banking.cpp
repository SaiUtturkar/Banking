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

int main()
{
	int ch;
	do
	{
		cout<<"\n\n1. Create New Account";
		cout<<"\n2. Check Account status:";
		cout<<"\n3. Display Account Info";
		cout<<"\n4. Exit";
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
		case 4: cout<<"\nExit from Menu!!!";
			break;
		default: cout<<"\n\nWrong choice!!!";
		}

	}while(ch!=4);


	cout<<"\n\n***Exit From main()***";
	return 0;
}

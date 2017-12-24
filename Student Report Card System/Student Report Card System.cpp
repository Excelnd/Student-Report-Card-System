// Student Report Card System.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include<fstream>
#include<iomanip>
#include <conio.h>
using namespace std;


class student {
	int rollno;
	char name[50];
	int plmarks, clmarks, mlmarks, elmarks, cslmarks;
	double per;
	char grade;
	void calculate();  // function to calculate grade
public:
	void getdata();				// fuction to accept data from user
	void showdata() const;		// function to show data on screen
	void show_tabular() const;
	int retrollno() const;

}; // class ends

void student::calculate()
{
	per = (plmarks + clmarks + mlmarks + elmarks + cslmarks) / 5.0;

	if (per >= 60) grade = 'A';
	else if (per >= 50) grade = 'B';
	else if (per >= 33)	grade = 'C';
	else grade = 'F';
}

void student::getdata()
{
	cout << "\nEnter The Roll Number of Student";
	cin >> rollno;

	cout << "\n\nEnter The Name of Student";
	cin.ignore();
	cin.getline(name, 50);

	cout << "\nEnter The marks in Physics out of 100: ";
	cin >> plmarks;

	cout << "\nEnter The marks in Chemistry out of 100: ";
	cin >> clmarks;

	cout << "\nEnter The marks in Maths out of 100: ";
	cin >> mlmarks;

	cout << "\nEnter The marks in English out of 100: ";
	cin >> elmarks;

	cout << "\nEnter The marks in Computer out of 100: ";
	cin >> cslmarks;

	calculate();
}

void student::showdata() const
{
	cout << "\nRoll number of student : " << rollno;
	cout << "\nName of student : " << name;
	cout << "\nmarks in Physics : " << plmarks;
	cout << "\nmarks in Chemistry : " << clmarks;
	cout << "\nmarks in Maths : " << mlmarks;
	cout << "\n marks in English : " << elmarks;
	cout << "\nmarks in Computer : " << cslmarks;
	cout << "\nPercentage of student is : " << per;
	cout << "\nGrade of studnet is : " << grade;
}

void student::show_tabular() const
{
	cout << rollno << setw(6) << " " << name << setw(10)
	<< plmarks << setw(4) << clmarks << setw(4) << mlmarks
	<< setw(4) << elmarks << setw(4) << cslmarks << setw(8)
	<< per << setw(6) << grade << endl;
}

int student::retrollno() const
{
		return rollno;
} 

// Function Declaration //########################

void write_student();		// write the record in binary file
void display_all();			// read all records from binary file
void display_sp(int);		// accept rollno and record from binary file
void modify_student(int);	// accept rollno and update record of binary file
void delete_student(int);	// accept rollno and delete selected records from binary file
void class_result();	// display all records in tabular format from binary file
void result();			// display result menu
void intro();			// display welcome screen
void entry_menu();		// display entry menu

	//+++++++++++++++++++++++++++++++++++++++
					// Main //
	//+++++++++++++++++++++++++++++++++++++++

int main()
{
	char ch;
	cout.setf(ios::fixed | ios::showpoint);
	cout << setprecision(2); // program outputs decimal number to two decimal places
	system("CLS");
	intro();
	do
	{
			system("CLS");
			cout << "\n\n\n\tMAIN MENU";
			cout << "n\n\t01. RESULT MENU";
			cout << "n\n\t02. ENTRY/EDIT MENU";
			cout << "\n\n\t03. EXIT";
			cout << "\n\n\tPlease select Your Option (1-3) ";
			cin >> ch;
			system("CLS");
			switch (ch)
			{
			case '1': result();
					break;
			case '2': result();
					break;
			case '3': result();
				break;
			default: cout << "\a";
			}
	} while (ch != '3');
    return 0;
}

	//++++++++++++++++++++++++++++++
	// function to write in the file
	//++++++++++++++++++++++++++++++

void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat", ios::binary | ios::app);
	st.getdata();
	outFile.write((char *) &st, sizeof(student));
	outFile.close();
	cout << "\n\nStudent record has been created ";
	_getch();

}

	//+++++++++++++++++++++++++++++++++++++++
	// function to read all records from file
	//+++++++++++++++++++++++++++++++++++++++

void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open! Press any Key...";
		_getch();
		return;
	}
	cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while (inFile.read((char *)&st, sizeof(student)))
	{
		st.showdata();
		cout << "\n\n++++++++++++++++++++++++++++++++++++\n";
	}
	inFile.close();
	_getch();

}

	//++++++++++++++++++++++++++++++++++++++++++++	
	// Function to read specific record from file
	//++++++++++++++++++++++++++++++++++++++++++++

void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if(!inFile)
	{
		cout << "File could not be open! Press any Key...";
		_getch();
		return;
	}
	int flag = 0;
	while (inFile.read((char *)&st, sizeof(student)))
	{
		if (st.retrollno() == n)
		{
			st.showdata();
			flag = 1;
		}
	}
	inFile.close();
	if (flag == 0)
		cout << "\n\nrecord not exist ";
	_getch();
}

	//++++++++++++++++++++++++++++++++++
	// function to modify record of file
	//++++++++++++++++++++++++++++++++++

void modify_student(int n)
{
	int found = 0;
	student st;
	fstream File;
	File.open("student.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File Could not be open!! Press any Key...";
		_getch();
		return;
	}
	while (File.read((char *)&st, sizeof(student)) && found == 0)
	{
		if (st.retrollno() == n)
		{
			st.showdata();
			cout << "\n\nPlease Enter The New Details of student" << endl;
			st.getdata();
			int pos = -1  *static_cast<int> (sizeof(st));
			File.seekp(pos, ios::cur);
			File.write((char *) &st, sizeof(student));
			cout << "\n\n\t Record Updated";
			found = 1;
		}
	}
	File.close();
	if (found == 0)
		cout << "\n\n Record Not Found";
	_getch();
}


	//++++++++++++++++++++++++++++++++++
	// function to delete record of file
	//++++++++++++++++++++++++++++++++++

void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not open !! Press any key...";
		_getch();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat", ios::out);
	inFile.seekg(0, ios::beg);
	while (inFile.read((char *)&st, sizeof(student)))
	{
		if (st.retrollno() != n)
		{
			outFile.write((char*)&st, sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat", "student.dat");
	cout << "\n\n\tRecord Deleted...";
	_getch();
}

	//++++++++++++++++++++++++++++++++++++++++++++++
	// function to display all students grade report
	//++++++++++++++++++++++++++++++++++++++++++++++

void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not open !! Press any key...";
		_getch();
		return;
	}
	cout << "n\n\t\tALL STUDENTS RESULT \n\n";
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "R.No		Name		P	C	M	E	CS	%age	Grade" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	while (inFile.read((char*)&st, sizeof(student)))
	{
		st.show_tabular();
	}
	_getch();
	inFile.close();
}


	//++++++++++++++++++++++++++++++++++
	// function to display result menu
	//++++++++++++++++++++++++++++++++++

void result()
{
	char ch;
	int rno;
	cout << "\n\n\n\tResult Menu";
	cout << "\n\n\n\t1. Class Result";
	cout << "\n\n\t2. Student Report Card";
	cout << "\n\n\t3. Back to Main Menu";
	cout << "\n\n\n\tEnter Choice (1/2/3)? ";
	cin >> ch;
	system("CLS");
	switch (ch)
	{
	case '1': class_result(); break;
	case '2': cout << "\n\n\tEnter Roll Number of Student : ";
		cin >> rno;
		display_sp(rno); break;
	case '3': break;
	default: cout << "\a";
	}

}

	//++++++++++++++++++++++++++++++++++
	//		INTRODUCTION FUNCTION
	//++++++++++++++++++++++++++++++++++

void intro()
{
	cout << "\n\n\n\t\t STUDENT";
	cout << "\n\n\n\tREPORT CARD";
	cout << "\n\n\t\t	PROJECT";
	cout << "\n\n\n\tMADE BY: IHS";
	_getch();
}

	//++++++++++++++++++++++++++++++++++
	//	ENTRY / EDIT MENU FUNCITON
	//++++++++++++++++++++++++++++++++++

void entry_menu()
{
	char ch;
	int num;
	cout << "\n\n\n\ENTRY MENU";
	cout << "\n\n\t1.CREATE STUDENT RECORD";
	cout << "\n\n\t2.DISLPAY ALL STUDENTS RECORDS";
	cout << "\n\n\t3.SEARCH STUDENT RECORD";
	cout << "\n\n\t4.MODIFY STUDENT RECORD";
	cout << "\n\n\t5.DELETE STUDENT RECORD";
	cout << "\n\n\t6.BACK TO MAIN MENU";
	cout << "\n\n\tPlease Enter Your Choice (1-6) ";
	cin >> ch;
	system("CLS");
	switch (ch)
	{
	case '1':	write_student(); break;

	case '2':	display_all(); break;

	case '3':	cout << "n\n\tPlease Enter The roll number "; cin >> num;
				display_sp(num); break;

	case '4':	cout << "n\n\tPlease Enter The roll number "; cin >> num;
				modify_student(num); break;

	case '5':	cout << "n\n\tPlease Enter The roll number "; cin >> num;
				delete_student(num); break;

	case '6':	break;
		   
	default:	cout << "\a"; entry_menu();
	}
}

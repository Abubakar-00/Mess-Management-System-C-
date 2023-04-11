#include<iostream>
#include<string> 
#include<fstream>
#include<sstream>
#include "Students.h"

using namespace std;

Students::Students() //default constructor
{
	
	id="Nil";
	password = "";
	name = "Nil";
	departement = "Nil";
	amount = 0.0;
	meals = 0;
}

// ======>  Setter function
void Students::setId(string i_id)  
{
	id = i_id;
}

void Students::setPass(string i_pass)
{
	password = i_pass;
}

void Students::setName(string i_name)
{
	name = i_name;
}

void Students::setDepartement(string i_dept)
{
	departement = i_dept;
}

void Students::setAmount(float i_amount)
{
	amount = i_amount;
}

void Students::setMeals(int i_meals)
{
	meals = i_meals;
}

//=======>  Getter functions
string Students::getId()  
{
	return id;
}

string Students::getPass()
{
	return password;
}

string Students::getName()
{
	return name;
}

string Students::getDepartement()
{
	return departement;
}

float Students::getAmount()
{
	return amount;
}

int Students::getMeals()
{
	return meals;
}

Students::~Students() //destructor
{
	
}

void Students::updateAmountMeals(string find, int amount_add) //function to update meal & amount when user order meal
{
	string id, password, name, departement, amount, meals;
	int iamount, imeals;
	
	fstream myfile;
	ofstream newfile;
	
	myfile.open("studentsAndadmins.csv");
	newfile.open("n.csv");
	
	while(myfile.good())
	{
		string cell;
		stringstream ss,dd;
		{
			getline(myfile , cell , ',');
			id = cell;
			getline(myfile , cell , ',');
			password = cell;
			getline(myfile , cell , ',');
			name = cell;
			getline(myfile , cell , ',');
			departement = cell;
			getline(myfile , cell , ',');
			
			if(find == id)
			{
				ss << cell;
				ss >> iamount;
				iamount += amount_add;	
			}
			else
			{
				amount = cell ;
			}
			
			getline(myfile , cell , '\n');
			
			if(find == id)
			{
				dd << cell;
				dd >> imeals;
				imeals += 1; 
			}
			else
			{
				meals = cell;		
			}
		}
		if(find == id)
		{
			newfile << id <<","<< password <<","<< name <<","<< departement <<","<<iamount<<","<<imeals<<"\n"; 	
		}
		else
		{
			newfile << id <<","<< password <<","<< name <<","<< departement <<","<<amount<<","<<meals<<"\n";
		}
	}
	
	myfile.close();
	newfile.close();
	
	if(remove("studentsAndadmins.csv") != 0)
	{
		cout<<"\tFile Doesn't removed!!"<<endl;
	}
	
	if(rename("n.csv" , "studentsAndadmins.csv") != 0)
	{
		cout<<"\tFile Doesn't renamed!!"<<endl;
	}
}

void Students::mealReview(string review , string id) //Function to store meal reviews along with IDs
{
    fstream fout;
    
    fout.open("MealReviews.txt", ios::out | ios::app);
	fout<<endl<<review<<" by ID: "<<id<<endl;
  	
	fout.close();
}

void Students::complain(string complain_ , string id) //Function to store complains along with IDs
{
	fstream fout;
    
    fout.open("Complains.txt", ios::out | ios::app);
	fout<<endl<<complain_<<" by ID: "<<id<<endl;
  	
	fout.close();
}

void Students::day_month()
{
	cout<<"\t**Note"<<endl;
	cout<<"\tPay your Bill before 10th of next Month."<<endl;
}

#include<iostream>
#include<string> 
#include<fstream>
#include<sstream>
#include "Admins.h"

using namespace std;

Admins::Admins() //Default constructor
{
	admin_id = "Nil";
	admin_password = "";
	admin_name = "Nil";
}

//Setters
void Admins::setAdminId(string i_id) 
{
	admin_id = i_id;
}

void Admins::setAdminPass(string i_pass)
{
	admin_password = i_pass;
}

void Admins::setAdminName(string i_name)
{
	admin_name = i_name;	
}		

//Getters
string Admins::getAdminId()
{
	return admin_id;
}

string Admins::getAdminPass()
{
	return admin_password;
}

string Admins::getAdminName()
{
	return admin_name;
}

Admins::~Admins()
{
	
}

void Admins::reviewReader() //function to read print review
{
	fstream viewfile;
	viewfile.open("MealReviews.txt",ios::in);
	 
	if (viewfile.is_open())
	{ 
    	string line;
    	while(getline(viewfile, line))
		{ 
    		cout << line << endl; 
    	}
    viewfile.close();
	}
}

void Admins::complainReader() //function to read print complains
{
	fstream viewfile;
	viewfile.open("Complains.txt",ios::in);
	 
	if (viewfile.is_open())
	{ 
    	string line;
    	while(getline(viewfile, line))
		{ 
    		cout << line << endl; 
    	}
    viewfile.close(); 
	}
}

void Admins::createAccount(string id, string pass, string name, string dept) //function to create new account of student
{
    fstream fout;
    fout.open("studentsAndadmins.csv", ios::out | ios::app);
    string amount="0", meals="0";
    fout << id << "," << pass << "," << name << "," << dept << "," << amount << ","<< meals<< "\n";
    fout.close();
}

void Admins::mealPriceChanger(string find, string itime, string iprice) //function to change meal price
{
	string day, price1, price2, price3;
	
	fstream myfile;
	ofstream newfile;
	
	myfile.open("price.csv");
	newfile.open("np.csv");
	
	while(myfile.good())
	{
		string cell;
		{
			getline(myfile , cell , ',');
			day = cell;
			getline(myfile , cell , ',');
			price1 = cell;
			getline(myfile , cell , ',');
			price2 = cell;
			getline(myfile , cell , '\n');
			price3 = cell;		
		}
		
		if(day == find)
		{
			if(itime[0] == '1')
			{
				newfile << day <<","<< iprice <<","<< price2 <<","<< price3 <<"\n";
				cout<<"\tSuccessFull Changed!!!"<<endl; 	
			}
			else if(itime[0] == '2')
			{
				newfile << day <<","<< price1 <<","<< iprice <<","<< price3 <<"\n";
				cout<<"\tSuccessFull Changed!!!"<<endl;
			}
			else if(itime[0] == '3')
			{
				newfile << day <<","<< price1 <<","<< price2 <<","<< iprice <<"\n";
				cout<<"\tSuccessFull Changed!!!"<<endl;
			}
		}
		else
		{
			newfile << day <<","<< price1 <<","<< price2 <<","<< price3 <<"\n";
		}
	}
	
	myfile.close();
	newfile.close();
	
	if(remove("price.csv") != 0)
	{
		cout<<"\tFile Doesn't removed!!"<<endl;
	}
	
	if(rename("np.csv" , "price.csv") != 0)
	{
		cout<<"\tFile Doesn't renamed!!"<<endl;
	}
}

void Admins::deleteRecord(string find) //Function delete student account
{
	string id, password, name, departement, amount, meals;

	fstream myfile;
	ofstream newfile;
	
	myfile.open("studentsAndadmins.csv");
	newfile.open("n.csv");
	
	while(myfile.good())
	{
		string cell;
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
			amount = cell ;
			getline(myfile , cell , '\n');
			meals = cell;		
			
		}
		if(id == find)
		{
			cout<<"\tRecord deleted Successfully!!!"<<endl<<endl;
			continue; 	
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

void Admins::viewDetails() //function to view details of students
{
	string id, password, name, departement, amount, meals;
	fstream myfile;
	
	cout<<"\tID\tPassword\tName\tDepartment\tAmount\tMeals"<<endl<<endl;
	myfile.open("studentsAndadmins.csv");
	
	while(myfile.good())
	{
		string cell;
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
			amount = cell;
			getline(myfile , cell , '\n');
			meals = cell;		
		}
		if (id[0] == 'b')
		{
			cout<<"\t"<< id <<"\t"<< password <<"\t\t"<< name <<"\t"<< departement <<"\t\t"<< amount <<"\t"<<meals <<endl; 	
		}
	}
}

void Admins::totalAmountMeals(float& iamount, int& imeals) //function print total meals & amount
{
	string id, password, name, departement, amount, meals;
	float temp_amount= 0.0;
	int temp_meals=0;
	fstream myfile;
	
	myfile.open("studentsAndadmins.csv");
	
	while(myfile.good())
	{
		string line,line_m;
		stringstream ss,dd;
		{
			getline(myfile , line , ',');
			id = line;
			getline(myfile , line , ',');
			password = line;
			getline(myfile , line , ',');
			name = line;
			getline(myfile , line , ',');
			departement = line;
			getline(myfile , line , ',');
			ss << line;
			ss >> temp_amount;
			iamount += temp_amount;	
			getline(myfile , line_m , '\n');
			dd << line_m;
			dd >> temp_meals;
			imeals =imeals + temp_meals;
			
			
			temp_amount = 0.0;
			temp_meals = 0; 
		}
	}
	myfile.close();
}

void Admins::mealChanger(string find, string itime, string imeal) //function to change meal
{
	string day, breakfast, lunch, dinner;
	
	fstream myfile;
	ofstream newfile;
	
	myfile.open("WeeklyMenu.csv");
	newfile.open("np.csv");
	
	while(myfile.good())
	{
		string cell;
		{
			getline(myfile , cell , ',');
			day = cell;
			getline(myfile , cell , ',');
			breakfast = cell;
			getline(myfile , cell , ',');
			lunch = cell;
			getline(myfile , cell , '\n');
			dinner = cell;		
		}
		
		if(day == find)
		{
			if(itime[0] == '1')
			{
				newfile << day <<","<< imeal <<","<< lunch <<","<< dinner <<"\n";
				cout<<"\tSuccessFull Changed!!!"<<endl; 	
			}
			else if(itime[0] == '2')
			{
				newfile << day <<","<< breakfast <<","<< imeal <<","<< dinner <<"\n";
				cout<<"\tSuccessFull Changed!!!"<<endl;
			}
			else if(itime[0] == '3')
			{
				newfile << day <<","<< breakfast <<","<< lunch <<","<< imeal <<"\n";
				cout<<"\tSuccessFull Changed!!!"<<endl;
			}
		}
		else
		{
			newfile << day <<","<< breakfast <<","<< lunch <<","<< dinner <<"\n";
		}
	}
	
	myfile.close();
	newfile.close();
	
	if(remove("WeeklyMenu.csv") != 0)
	{
		cout<<"\tFile Doesn't removed!!"<<endl;
	}
	
	if(rename("np.csv" , "WeeklyMenu.csv") != 0)
	{
		cout<<"\tFile Doesn't renamed!!"<<endl;
	}
}

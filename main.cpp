//Mess Management System
//Header files
#include<iostream>
#include<iomanip>
#include<string>
#include<sstream>
#include<fstream>
#include<ctime>
#include<conio.h>
#include<windows.h>
#include "Students.h"
#include "Admins.h"
#include "Students.cpp"
#include "Admins.cpp"

int Golden = 6;
int Blue = 9;

using namespace std;

//prototypes
void color(int);
void priceTeller();
void realTime(string& , string&);
void showWeeklyMenu();
void idPassChecker(string, string); 
void changePassword(string , string);
void foodPriceFinder_Database(string , string, int&);
void idPassChecker_Database(string ,string&, string&);
void studentAdminDataAssigner_Database(string ,string&, string&, float&, int&);

//main
int main()
{
	
	string sign_id , sign_password;
	
	label:
		
	cout<<endl<<"\t==============> Sign In <=============="<<endl;
	cout<<"\tEnter ID: "; 
	cin>>sign_id; 							//getting id from user
	cout<<"\tEnter Password:";
	cin>>sign_password; 					//getting password from user

	idPassChecker(sign_id, sign_password); // calling id & password checker function (includes database checker function inside)
	
	//main driver if-else
	
	if(sign_id[0] == 'b') //condition for student driver 
	{
		color(Blue);	
		Students *student = new Students; //object of Students class (student)
		
		string name, departement;
		float amount;
		int meals;
		
		studentAdminDataAssigner_Database( sign_id, name, departement, amount, meals);
		
		//assiging values	
		student->setId(sign_id); 
		student->setPass(sign_password);
		student->setName(name);
		student->setDepartement(departement);
		student->setAmount(amount);
		student->setMeals(meals);
		
		cout<<"\t=============> Dashboard <============"<<endl<<endl;
		cout<<"\t"<<"Name: "<<"\t\t"<<student->getName()<<endl;
		cout<<"\t"<<"ID: "<<"\t\t"<<student->getId()<<endl;
		cout<<"\t"<<"Departemet: "<<"\t"<<student->getDepartement()<<endl;
		cout<<"\t"<<"Meals Taken: "<<"\t"<<student->getMeals()<<endl;
		cout<<"\t"<<"Total Amount: "<<"\t"<<"Rs."<<student->getAmount()<<endl<<endl;
		
		string day_month, temp;
		realTime(day_month, temp);
		
		if(day_month[0] == '3' && day_month[1] == '0')
		{
			student->day_month();
		}
		
		
		string choice = "0";
		string meal_review, _complain;
		
		while(choice[0] != '6')
		{
			color(Blue);
			cout<<endl;
			cout<<"\t=============> Options <============"<<endl<<endl;
			cout<<endl<<"\tPress 1 to View this Week Mess Menu."<<endl;
			cout<<"\tPress 2 to Select Meal."<<endl;
			cout<<"\tPress 3 to Give Review on Meal."<<endl;
			cout<<"\tPress 4 to Register any Complain."<<endl;
			cout<<"\tPress 5 to Change Password."<<endl;
			cout<<"\tPress 6 to Logout."<<endl;
			cout<<"\tPress 7 to Exit Application."<<endl;
			
			cout<<endl<<"\tEnter choice: ";
			cin>>choice;
			
			if(choice[0] == '1')
			{
				showWeeklyMenu(); //passing menu array
				cout<<endl;
				priceTeller();
				cout<<endl;
				system("PAUSE");
				system("cls");
			}
			else if(choice[0] == '2')
			{
				string day, hour;
				int current_food_amount, hr;
				
				realTime(day , hour);
				stringstream ss;
				ss << hour;
				ss >> hr;
				
				if((hr >= 0 && hr <= 07) || (hr >= 9 && hr <= 11) || (hr >= 14 && hr <=18))
				{
					string user_decision;
					cout<<"\t Do you want to order: (y/n): ";
					cin.ignore();
					getline(cin,user_decision);
					if(user_decision[0] == 'y' || user_decision[0] == 'Y')
					{
						foodPriceFinder_Database( day, hour, current_food_amount);
						student->updateAmountMeals(student->getId(), current_food_amount);
					}
					else
					{
						break;
					}
				}
				else
				{
					cout<<endl<<"\tCan't pre-order Meal right now!!!"<<endl;
					cout<<"\tTry to pre-order breakfast between 12am to 7am"<<endl;
					cout<<"\tTry to pre-order lunch between 9am to 11am"<<endl;
					cout<<"\tTry for pre-order dinner between 2pm to 6pm"<<endl<<endl;
				}
				
				cout<<endl;
				system("PAUSE");
				system("cls");
			}
			else if(choice[0] == '3')
			{
				cout<<"\tEnter the meal review: ";
				cin.ignore();
				getline(cin,meal_review);
				student->mealReview(meal_review , student->getId());
				
				cout<<endl;
				system("PAUSE");
				system("cls");
			}
			else if(choice[0] == '4')
			{
				cout<<"\tEnter the complain: ";
				cin.ignore();
				getline(cin,_complain);
				student->complain(_complain , student->getId());
				
				cout<<endl;
				system("PAUSE");
				system("cls");
			}
			else if(choice[0] == '5')
			{
				string newPassword;
				cout<<endl<<"\tEnter new Password: ";
				cin.ignore();
				getline(cin,newPassword);
				changePassword(student->getId() , newPassword);
				
				cout<<endl;
				system("PAUSE");
				system("cls");
			}
			else if(choice[0] == '6')
			{
				break;
			}
			else if(choice[0] == '7')
			{
				return 0;
			}
			else
			{
				cout<<"\tYou Entered wrong number!!"<<endl;
				
				cout<<endl;
				system("PAUSE");
				system("cls");
			}	
		}
		
		cout<<"\tSuccessfully logout!"<<endl;
		student->~Students();
		
		cout<<endl;
		system("PAUSE");
		system("cls");
		
		goto label;			
	}
	else  //<<<<<<<<<<<<<<<for admin driver>>>>>>>>>>>>>>>>>>>
	{
		color(Golden);
		Admins *admin = new Admins;
		
		string adminId;
		string adminPassword;
		string adminName;
		string dummy1;
		float dummy2;
		int dummy3;
		
		studentAdminDataAssigner_Database( sign_id, adminName, dummy1,dummy2, dummy3);
		
		admin->setAdminId(sign_id);
		admin->setAdminName(adminName);
		float total_Amount = 0;
		int total_Meals = 0;
		admin->totalAmountMeals(total_Amount, total_Meals);
		
		cout<<"\t=============> Dashboard <============"<<endl<<endl;
		cout<<"\t"<<"Name: "<<"\t\t"<<admin->getAdminName()<<endl;
		cout<<"\t"<<"ID: "<<"\t\t"<<admin->getAdminId()<<endl<<endl;
		cout<<"\t"<<"Total Amount"<<"\t"<<"Rs."<<fixed<<setprecision(2)<<total_Amount<<endl;
		cout<<"\t"<<"Total Meals"<<"\t"<<total_Meals<<endl;
		
		string choice = "0";
		
		while(choice[0] != '1' && choice[1] != '1')
		{
			cout<<endl;
			cout<<"\t=============> Options <============"<<endl<<endl;
			cout<<"\tPress 1  to View this Week Mess Menu."<<endl;
			cout<<"\tPress 2  to Change Meal."<<endl;
			cout<<"\tPress 3  to View Meal Prices."<<endl;
			cout<<"\tPress 4  to Change Meal Price."<<endl;
			cout<<"\tPress 5  to View Students Details."<<endl;
			cout<<"\tPress 6  to Delete Student Account."<<endl;
			cout<<"\tPress 7  to Create a New Student Account."<<endl;
			cout<<"\tPress 8  to View Reviews on Meal."<<endl;
			cout<<"\tPress 9  to View Complains."<<endl;
			cout<<"\tPress 10 to Change Password."<<endl;
			cout<<"\tPress 11 to Logout."<<endl;
			cout<<"\tPress 12 to Exit Application."<<endl;
			
			cout<<endl<<"\tEnter choice: ";
			cin>>choice;
			
			if(choice[0] == '1' && choice[1] != '0' && choice[1] != '1' && choice[1] != '2')
			{
				showWeeklyMenu();
				cout<<endl;
				priceTeller();
				cout<<endl;
				
				cout<<endl;
				choice = '0';
				system("PAUSE");
				system("cls");
			}
			
			else if(choice[0] == '2')
			{
				string day, meal_time, meal;
				showWeeklyMenu();
				cout<<endl;
				priceTeller();
				cout<<endl;
				cout<<"\t To change Meal you have to Enter Day and Meal time as:"<<endl;
				cout<<"\t Mon, Tue, Wed, Thu, Fri, Sat, Sun"<<endl;
				cout<<"\t BreakFast = 1, Lunch = 2, Dinner = 3"<<endl<<endl;
				cout<<"\tEnter Day: ";
				cin.ignore();
				getline(cin,day);
				cout<<"\tEnter Meal Time: ";
				getline(cin,meal_time);
				cout<<"\tEnter new Meal: ";
				getline(cin,meal);
				cout<<endl;
				admin->mealChanger(day, meal_time, meal);
				cout<<endl;
				
				cout<<endl;
				system("PAUSE");
				system("cls");
			}
			
			else if(choice[0] == '3')
			{
				cout<<"\tDay\t\tBreakfast\t\tLunch\t\t\tDinner"<<endl<<endl;
				priceTeller();
				cout<<endl;
				
				cout<<endl;
				system("PAUSE");
				system("cls");
			}
			
			else if(choice[0] == '4')
			{
				string day, meal_time, price;
				showWeeklyMenu();
				cout<<endl;
				priceTeller();
				cout<<endl;
				cout<<"\t To change Meal price you have to Enter Day and Meal time as:"<<endl;
				cout<<"\t Mon, Tue, Wed, Thu, Fri, Sat, Sun"<<endl;
				cout<<"\t BreakFast = 1, Lunch = 2, Dinner = 3"<<endl<<endl;
				cout<<"\tEnter Day: ";
				cin.ignore();
				getline(cin,day);
				cout<<"\tEnter Meal Time: ";
				getline(cin,meal_time);
				cout<<"\tEnter new Meal price: ";
				getline(cin,price);
				cout<<endl;
				admin->mealPriceChanger(day, meal_time, price);
				cout<<endl;
				
				cout<<endl;
				system("PAUSE");
				system("cls");
			}
			
			else if(choice[0] == '5')
			{
				cout<<endl;
				admin->viewDetails();
				cout<<endl;
				
				cout<<endl;
				system("PAUSE");
				system("cls");
			}
			
			else if(choice[0] == '6')
			{
				string id;
				cout<<"\tEnter Student ID to delete record: ";
				cin.ignore();
				getline(cin,id);
				admin->deleteRecord(id);
				cout<<endl;
				
				cout<<endl;
				system("PAUSE");
				system("cls");
			}
			
			else if(choice[0] == '7')
			{
				string st_id, st_pass, st_name, st_dept;
				cout<<endl<<"Enter Student ID (must start with 'b'): ";
				cin.ignore();
				getline(cin,st_id);
				
				cout<<"Enter Student Password: ";
				cin.ignore();
				getline(cin,st_pass);
				
				cout<<"Enter Student Name: ";
				cin.ignore();
				getline(cin,st_name);
				
				cout<<"Enter Student's Department Name: ";
				cin.ignore();
				getline(cin,st_dept);
				
				admin->createAccount(st_id, st_pass, st_name, st_dept);
				cout<<"\tAccount Created SuccessFully!!"<<endl<<endl;
				
				cout<<endl;
				system("PAUSE");
				system("cls");
			}
			
			else if(choice[0] == '8')
			{
				cout<<endl;
				admin->reviewReader();
				cout<<endl;
				
				cout<<endl;
				system("PAUSE");
				system("cls");
			}
			
			else if(choice[0] == '9')
			{
				cout<<endl;
				admin->complainReader();
				cout<<endl;
				
				cout<<endl;
				system("PAUSE");
				system("cls");
			}
			
			else if(choice[0] == '1'&& choice[1] == '0')
			{
				string newPassword;
				cout<<endl<<"\tEnter new Password: ";
				cin.ignore();
				getline(cin,newPassword);
				changePassword(sign_id , newPassword);
				
				cout<<endl;
				system("PAUSE");
				system("cls");
			}
			
			else if(choice[0] == '1' && choice[1] == '1')
			{
				break;
			}
			
			else if(choice[0] == '1' && choice[1] == '2')
			{
				return 0;
			}
			
			else
			{
				cout<<"\tYou Entered wrong number!!"<<endl;
				
				cout<<endl;
				system("PAUSE");
				system("cls");
			}	
		}
		
		cout<<"\tSuccessfully logout!"<<endl;
		admin->~Admins();
		
		cout<<endl;
		system("PAUSE");
		system("cls");
		
		goto label;
	}
	
return 0;
};




/* =====> Purpose of this funtion
	this funcion takes first parameter find (id entered by user) which is used to locate similar id in 
	-- csv -- file. if id found then it copies id & pass to given next two parameters.
*/

void idPassChecker_Database(string find,string &passed_id, string &passed_password)
{	
	string  id, password ,dummy;  //dummy is to skip line
	fstream myfile;
	fstream adminfile;
	
	myfile.open("studentsAndadmins.csv");
	while(myfile.good())
	{
		string cell;
		{
			/* This getline funtion works in such a way that it open file and copy firts cell of
			   excel file in variable cell & then comma mean it moves to next cell
			*/
			   	
			getline(myfile , cell , ',');
			id = cell; 
			getline(myfile , cell , ',');
			password = cell;
			getline(myfile , cell , '\n');
			dummy = cell;		
		}
		if (find == id)
		{
			//copying the found id & pass in csv file
			passed_id = id; 
			passed_password = password;
			break;
		}
	}
	myfile.close();
}

void idPassChecker(string i_id="", string i_pass="") //function to check id & passowrd 
{	
	bool sign_checker = true;
	string check_id , check_pass;
	
	
	while(sign_checker)
	{
		idPassChecker_Database(i_id, check_id, check_pass); //calling this function to get id & password values from students.csv file
		if(i_id == check_id)
		{
			if(i_pass == check_pass)
			{
				sign_checker == false;
				cout<<endl<<"\tSuccessfully logged In"<<endl<<endl;
				system("PAUSE");
				system("cls");
				break;
			}
			else //condition if user entered wrong password
			{
				cout<<"\tEntered password is worng!! Type again"<<endl; 
				cout<<"\tEnter password: ";
				cin>>i_pass;
			}
		}
		else //condition if user entered wrong id
		{
			cout<<"\tEntered ID not found!!"<<endl;
			cout<<"\tEnter ID: ";
			cin>>i_id;
		}
	}
}

void studentAdminDataAssigner_Database(string find, string& iname, string& idept, float& iamount, int& imeals) //Dashboard data
{
	fstream myfile;
	string id,dummy, Name, Dept;
	float Amount;
	int Meals;
	myfile.open("studentsAndadmins.csv");
	
	while(myfile.good()){
		string cell;
		stringstream ss,dd;
		{
			getline(myfile , cell , ',');
			id = cell;
			getline(myfile , cell , ',');
			dummy = cell;
			getline(myfile , cell , ',');
			Name = cell;
			getline(myfile , cell , ',');
			Dept = cell;
			getline(myfile , cell , ',');
			ss << cell;
			ss >> Amount;
			getline(myfile , cell , '\n');
			dd << cell;
			dd>>Meals;		
		}
		if (find == id)
		{
			iname = Name;
			idept = Dept;
			iamount = Amount;
			imeals = Meals;
			break;
		}
	
	}
} 

void showWeeklyMenu() //function to display Mess menu
{
	cout<<endl;
	cout<<"\t\t\tBreakfast\t\tLunch\t\t\tDinner"<<endl<<endl;
	string day, breakfast, lunch, dinner;
	fstream myfile;
	

	myfile.open("WeeklyMenu.csv");
	
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
			cout<<"\t\t"<< day <<"\t"<< breakfast<<"\t\t"<< lunch <<"\t\t"<< dinner <<endl; 	
	}
	myfile.close();
}

void realTime(string &iday, string &ihour) //Function for time to get day & hour for condition
{
	time_t tt;
	struct tm * ti;
	time(&tt);
	ti = localtime(&tt);
	
	string day_date_time = asctime(ti);

	string day;
	for(int i=0; i<3; i++)
	{
		if(day_date_time[i] != ' ')
		 day += day_date_time[i];
	}
	
	string hour;
	
	for(int i=11; i<13; i++)
	{
		hour+=day_date_time[i];
	}
	
	iday = day;
	ihour = hour;
}

void foodPriceFinder_Database(string iday, string ihour, int& iamount) //Function to find price of specific meal
{
	string find,price1, price2, price3;
	int hrs;
	
	stringstream con;
	con << ihour;
	con >> hrs;
	
	fstream myfile;
	myfile.open("price.csv");
	
	while(myfile.good())
	{
		string cell;
		stringstream ss;
		{
			getline(myfile , cell , ',');
			find = cell;
			getline(myfile , cell , ',');
			price1 = cell;
			getline(myfile , cell , ',');
			price2 = cell;
			getline(myfile , cell , '\n');
			price3 = cell;		
		}
		if (find == iday)
		{
			if(hrs >= 0 && hrs <= 07)
			{
				ss << price1;
				ss >> iamount;
				break; 
			}
			else if(hrs >= 9 && hrs <= 11)
			{
				ss << price2;
				ss >> iamount;
				break;
			}
			else if(hrs >= 14 && hrs <=18)
			{
				ss << price3;
				ss >> iamount;
				break;
			}
			else
			{
				iamount = 0;
			}
				
		}
	}
}


void changePassword(string find , string newPass) //function to change password
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
			amount = cell;
			getline(myfile , cell , '\n');
			meals = cell;	
		}
		if(find == id)
		{
			newfile << id <<","<< newPass <<","<< name <<","<< departement <<","<<amount<<","<<meals<<"\n"; 	
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

void priceTeller()//function to print prices of meals
{	
	string find,price1, price2, price3;

	fstream myfile;
	myfile.open("price.csv");
	
	while(myfile.good())
	{
		string cell;
		
		getline(myfile , cell , ',');
		find = cell;
		getline(myfile , cell , ',');
		price1 = cell;
		getline(myfile , cell , ',');
		price2 = cell;
		getline(myfile , cell , '\n');
		price3 = cell;		
		
		cout<<"\t\t"<<find<<"\t"<<"Rs."<<price1<<"\t\t\t"<<"Rs."<<price2<<"\t\t\t"<<"Rs."<<price3<<endl;	
		
	}
}

void color(int n)
{
	HANDLE color;
	color = GetStdHandle( STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color,n);
}

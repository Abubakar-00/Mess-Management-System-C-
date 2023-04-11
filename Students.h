#ifndef STUDENTS_H 
#define STUDENTS_H

using namespace std;

class Students
{
private:
	string id;
	string password;
	string name;
	string departement;
	float amount;
	int meals;
	
public:
	Students();
	Students( string, string);
	
	void setId(string);
	void setPass(string);
	void setName(string);
	void setDepartement(string);
	void setAmount(float);
	void setMeals(int);
	
	string getId();
	string getPass();
	string getName();
	string getDepartement();
	float getAmount();
	int getMeals();

	void updateAmountMeals(string , int );
	void mealReview(string , string);
	void complain(string , string);
	void day_month();
	
	~Students();
};

#endif

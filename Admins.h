#ifndef ADMINS_H
#define ADMINS_H

using namespace std;

class Admins
{
	private:
		string admin_id;
		string admin_password;
		string admin_name;
	public:
		Admins();
		void setAdminId(string);
		void setAdminPass(string);
		void setAdminName(string);
		
		string getAdminId();
		string getAdminPass();
		string getAdminName();
		
		void totalAmountMeals(float& , int&);
		void reviewReader();
		void complainReader();
		void createAccount(string, string, string, string);
		void mealPriceChanger(string , string, string );
		void mealChanger(string, string, string);
		void viewDetails();
		void deleteRecord(string);
		
		~Admins();
};

#endif

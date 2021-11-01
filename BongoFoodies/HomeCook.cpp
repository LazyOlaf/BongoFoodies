#include "HomeCook.h"

extern bool logged_in;

HomeCook::HomeCook() {
	//cout << "hcctor\n";
}

HomeCook::~HomeCook() {
	//cout << "hcdtor\n";
}

HomeCook* HomeCook::Register(SAConnection& conn) {
	system("CLS");
	cout << "\n\t **** Registration ****\n\n";


	UserID++; 
	time_t now = time(0);
	struct tm* date = localtime(&now);
	string name, email, pass;
	cout << "Name:";
	cin >> name;
	cout << "Email:";
	cin >> email;
	cout << "Password:";
	cin >> pass;


	SACommand insert(&conn);
	try {
		insert.setCommandText(_TSA("INSERT INTO Users (UserID, name, email, pass, reg) VALUES (:1, :2, :3, :4, :5)"));
		insert << (unsigned short)UserID << name.c_str() << email.c_str() << pass.c_str() << SADateTime(1900 + date->tm_year, 1 + date->tm_mon, date->tm_mday);
		insert.Execute();
		conn.Commit();
		cout << "\nRegistration successful!\n" << endl;
		return Login(conn);
	}

	catch (SAException& e) {
		(void)e;
		conn.Rollback();
		cout << e.ErrText().GetMultiByteChars();
		cout << "\nEmail already registered!\n";
		cout << "1.Retry? 2.Login? ... ";
		int ch;
		cin >> ch;
		if (ch == 2)
			return Login(conn);
		else
			return Register(conn);
	}
}

HomeCook* HomeCook::Login(SAConnection& conn)
{
	Sleep(100);
	system("CLS");
	cout << "\n\t **** Login ****\n\n";


	string email, pass;
	cout << "Email:";
	cin >> email;
	cout << "Password:";
	cin >> pass;


	SACommand select(&conn);
	select.setCommandText(_TSA("SELECT UserID, name, pass, reg FROM Users WHERE email = :1"));
	select << email.c_str();
	select.Execute();

	if (!select.FetchNext()) {
		cout << "\nEmail not registered!\n";
		cout << "1.Retry? 2.Register? ... ";
		int ch;
		cin >> ch;
		if (ch == 2)
			return Register(conn);
	}
	else {
		if (pass != select.Field(_TSA("pass")).asString().GetMultiByteChars()) {
			cout << "\nIncorrect password!\n";
		}
		else {
			Name = select.Field(_TSA("name")).asString().GetMultiByteChars();
			UserID = select.Field(_TSA("UserID")).asLong();
			DOR = (struct tm)select.Field(_TSA("reg")).asDateTime();
			Email = email;
			Password = pass;
			cout << "\nLogin successful!\n" << endl;
			return this;
		}
	}

	return Login(conn);
}


void HomeCook::profile(SAConnection& conn)
{
	cout << "User ID: " << UserID << endl;
	cout << "Name: " << Name << endl;
	cout << "Email: " << Email << endl;
	cout << "Member since: " << DOR.tm_mday << "-" << DOR.tm_mon << "-" << DOR.tm_year << endl << "\n\n";


	cout << "1. Upload a new recipe\n";
	cout << "2. Edit an existing recipe\n";
	cout << "3. View all recipes\n";
	cout << "4. View pending orders\n";
	cout << "5. Logout\n";
	cout << "6. Return to Main Menu\n\n";
	cout << "\nEnter choice: ";
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1: {
		Recipe r;
		r.upload_recipe(conn, UserID);
	}
		  break;
	case 2:
		this->edit_recipe();
		break;
	case 3: {
		Recipe r;
		string t;
		cout<<"Enter recipe name : ";
		cin >> t;
		r.show_recipe_details(conn, t);
		break; }
	case 4:
		this->orders_to_be_fulfilled();
		break;
	case 5:
		logged_in = 0;
		cout << "Logging Out\n\n";
		break;
	default:
		break;
	}
}


void HomeCook::edit_recipe() {
}

void HomeCook::show_recipes() {
}


void HomeCook::orders_to_be_fulfilled() {
}






#include "User.h"
fstream database("user.txt");
vector<User> Users_database;
int User::ID = 0;

User::User()
{
	ID++;
	time_t tt;
	time(&tt);
	DOR = localtime(&tt);
}

User::~User()
{
	//dtor
}

string User::Register()
{
	cout << "\n\t **** Registration ****" << endl;
	string name, email, pass;

	cout << "Name:";
	cin >> name;

	string line;
	unordered_set<string> res;
	while (database >> line)
	{
		res.insert(line);
	}

	do {
		std::cout << "Email:";
		cin >> email;
		if (res.find("email:" + email) != res.end())
		{
			std::cout << "This email is already in use!\n";
		}
		else
			break;
	} while (true);

	cout << "Password:";
	cin >> pass;

	database.clear();
	database.seekp(0, ios::end);
	database << to_string(ID) + " " + name + " " + email + " " + pass << endl;
	cout << "\nRegistration successful!\n" << endl;

	return Login();
}

string User::Login()
{
	cout << "\n\t **** Login ****" << endl;
	string email, pass;

	database.clear();
	database.seekg(0, ios::beg);
	string line;
	int f = 0;
	User u;
	while (database >> line)
	{
		if (f == 1)
			u.Name = line;
		else if (f == 2)
			u.Email = line;
		else if (f == 3) {
			u.Password = line;
			Users_database.push_back(u);
			f = -1;
		}
		f++;
	}

email_nonexistent_flag:
	cout << "Email:";
	cin >> email;
	for (unsigned int i = 0; i < Users_database.size(); i++)
	{
		//cout << Users_database[i].Email << " " << Users_database[i].Password << endl;
		if (Users_database.at(i).Email == email)
		{
		password_incorrect_flag:
			cout << "Password:";
			cin >> pass;
			if (Users_database.at(i).Password != pass)
			{
				cout << "Incorrect password!\n";
				goto password_incorrect_flag;
			}

			cout << "\n\nLogin successful!\n" << endl;
			return Users_database.at(i).Name;
		}
	}
	cout << "Email not registered!\n";
	cout << "1.Retry? 2.Register? ... ";
	int ch;
	cin >> ch;
	if (ch == 2) {
		return Register();
	}
	else
		goto email_nonexistent_flag;
}

string login_interface()
{
	cout << "\n\n1.New User\n2.Existing User\n\n";
	int choice;
	cout << "Choice: ";
	cin >> choice;

	User user;
	string username;
	switch (choice)
	{
	case 1:
		username = user.Register();
		break;
		/*cout << "Do you wanna publish your recipes? (y/n)... ";
		string t;
		cin >> t;
		if (t == "y" || "Y") {
			HomeCook user;
			username = user.Register();
		}
		else {
			Foodie user;
			username = user.Register();
		}
		*/
	case 2:
		username = user.Login();
		break;
	}
	return username;
}
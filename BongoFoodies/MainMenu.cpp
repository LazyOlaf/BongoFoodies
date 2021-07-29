#include "MainMenu.h"

MainMenu::MainMenu() {
	logged_in = 0;
}
MainMenu::~MainMenu() {
	//dtor
}

void MainMenu::highlights() {
	cout << "showing highlights\n\n";
}
void MainMenu::browse() {
	cout << "redirecting to browse page\n\n";
}
void MainMenu::tips() {
	cout << "showing tips\n\n";
}
void MainMenu::login() {
	if (logged_in == 0) {
		username = login_interface();
		logged_in = 1;
	}
	else
		cout << "redirecting to profile page\n\n";
}

void main_menu()
{
	MainMenu menu;
	while (1) {
		system("PAUSE");
		system("CLS");
		cout << "\n\n\n\t\t\t\t\t ========== BongoFoodies ==========\n\n";
		cout << "1.Highlights\t\t2.Browse\t\t3.Tips & Tricks\t\t";
		if (menu.logged_in == 0)
			cout << "4.Register/Login\t\t";
		else
			cout << "4." << menu.username << "\t\t";
		cout << "5.Exit\n\n";

		cout << "\nEnter choice: ";
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			menu.highlights();
			break;
		case 2:
			menu.browse();
			break;
		case 3:
			menu.tips();
			break;
		case 4:
			menu.login();
			break;
		case 5:
			cout << "Come again :')\n\n";
			break;
		}
		if (choice == 5)
			break;
	}
}

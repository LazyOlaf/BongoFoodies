#include "Recipe.h"

int Recipe::RecipeID = 0;

Recipe::Recipe()
{

}

Recipe::~Recipe()
{
	//dtor
}

void Recipe::upload_recipe(SAConnection& conn, int cook_ID)
{
	Sleep(100);
	system("CLS");
	cout << "****Recipe Info****\n\n";

	RecipeID++;

	cout << "\n\nTitle: ";
	cin >> title;

	cout << "\nRegion: ";
	cin >> region;

	cout << "\nCooking time (in minutes): ";
	cin >> time;

	cout << "\nServings: ";
	cin >> servings;

	string ch;
	do
	{
		cout << "\nIngredient: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		string ingre;
		getline(cin, ingre);
		ingredients.push_back(ingre);
		cout << "Add more? (y/n)...";
		cin >> ch;
	} while (ch == "y" || ch == "Y");

	cout << "\nDirections: ";
	cin.ignore(256, '\n');
	getline(cin, procedure);

	cout << "\nAvailable for delivery? (y/n)...";
	cin >> ch;
	if (ch == "y" || ch == "Y") {

		do
		{
			cout << "\nDelivery area: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			string area;
			getline(cin, area);
			delivery_area.push_back(area);
			cout << "Add more? (y/n)...";
			cin >> ch;
		} while (ch == "y" || ch == "Y");

		cout << "\nPrice (in taka): ";
		cin >> price;
	}

	SACommand insert(&conn);
	try
	{
		insert.setCommandText(_TSA("INSERT INTO Recipes (RecipeID, Title, Cook, Region, Time, Servings, Price, Rating) VALUES (:1, :2, :3, :4, :5, :6, :7, :8)"));
		insert << (unsigned short)RecipeID << title.c_str() << (unsigned short)cook_ID << region.c_str() << (double)time << (unsigned short)servings << (double)price << (double)rating;
		insert.Execute();

		for (int i = 0; i < delivery_area.size(); i++)
		{
			insert.setCommandText(_TSA("INSERT INTO Delivery_Area (RecipeID, Area) VALUES (:1, :2)"));
			insert << (unsigned short)RecipeID << delivery_area[i].c_str();
			insert.Execute();
		}
	}
	catch (SAException& e)
	{
		(void)e;
		//conn.Rollback();
		cout << e.ErrText().GetMultiByteChars();
		cout << "\nProblem uploading!\n";
	}

	ofstream recipe_text;
	recipe_text.open(title + ".txt", ios::app);
	recipe_text.write((char*)this, sizeof(this));
	recipe_text.close();

	cout << "\nNew recipe uploaded!\n" << endl;
}


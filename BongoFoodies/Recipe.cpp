#include "Recipe.h"

int Recipe::RecipeID = 0;

//vector<string> file_list;

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
	cout << "\n";

	string ch;
	do
	{
		cout << "Ingredient: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		string ingre;
		getline(cin, ingre);
		ingredients.push_back(ingre);
		cout << "Add more? (y/n)...";
		cin >> ch;
	} while (ch == "y" || ch == "Y");

	cout << "\n\nDirections: ";
	cin.ignore(256, '\n');
	getline(cin, procedure);

	cout << "\nAvailable for delivery? (y/n)...";
	cin >> ch;
	cout << "\n";
	if (ch == "y" || ch == "Y") {

		do
		{
			cout << "Delivery area: ";
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
		conn.Commit();
		for (int i = 0; i < delivery_area.size(); i++)
		{
			insert.setCommandText(_TSA("INSERT INTO Delivery_Area (RecipeID, Area) VALUES (:1, :2)"));
			insert << (unsigned short)RecipeID << delivery_area[i].c_str();
			insert.Execute();
			conn.Commit();
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

void Recipe::show_recipe_details(SAConnection& conn, string filename)
{
	Sleep(100);
	system("CLS");

	SACommand select1(&conn), select2(&conn), select3(&conn);
	try
	{
		select1.setCommandText(_TSA("SELECT * FROM Recipes WHERE Title = :1"));
		select1 << filename.c_str();
		select1.Execute();
		select2.setCommandText(_TSA("SELECT Area FROM Delivery_area WHERE RecipeID = (SELECT RecipeID FROM Recipes WHERE Title = :1)"));
		select2 << filename.c_str();
		select2.Execute();
		select3.setCommandText(_TSA("SELECT Name FROM Users WHERE UserID = (SELECT Cook FROM Recipes WHERE Title = :1)"));
		select3 << filename.c_str();
		select3.Execute();

		while (select1.FetchNext())
		{

			RecipeID = select1.Field(_TSA("RecipeID")).asUShort();
			title = select1.Field(_TSA("Title")).asString().GetMultiByteChars();
			region = select1.Field(_TSA("Region")).asString().GetMultiByteChars();
			time = select1.Field(_TSA("Time")).asDouble();
			servings = select1.Field(_TSA("Servings")).asUShort();
			rating = select1.Field(_TSA("Rating")).asDouble();
			price = select1.Field(_TSA("Price")).asDouble();


			while (select3.FetchNext())
			{
				cook_name = select3.Field(_TSA("Name")).asString().GetMultiByteChars();
			}
			while (select2.FetchNext())
			{
				delivery_area.push_back(select2.Field(_TSA("Area")).asString().GetMultiByteChars());
			}

			/*ifstream recipe_text;
			Recipe r;
			recipe_text.open(title + ".txt", ios::in);
			recipe_text.seekg(0);
			recipe_text.read((char*)&r, sizeof(r));
			recipe_text.close();

			cout << "printing   ";
			for (auto it = r.ingredients.begin(); it != r.ingredients.end(); it++)
				cout << *it;
			cout << r.procedure;
			cout << "     printing   ";
			ingredients = r.ingredients;
			procedure = r.procedure;*/


			cout << "****Recipe Info****\n\n";
			cout << "\n\nTitle: " << title;
			cout << "\nCook name: " << cook_name;
			cout << "\nRegion: " << region;
			cout << "\nCooking time (in minutes): " << time;
			cout << "\nServings: " << servings;

			cout << "\nIngredients: ";
			int s = ingredients.size();
			for (auto it = ingredients.begin(); it != ingredients.end(); it++) {
				if (s > 1)
					cout << *it << ", ";
				else
					cout << *it;
				s--;
			}

			cout << "\nDirections: " << procedure;

			if (delivery_area.empty())
				cout << "\nDelivery service not available!";
			else {
				cout << "\nDelivery areas: ";
				int s = delivery_area.size();
				for (auto it = delivery_area.begin(); it != delivery_area.end(); it++) {
					if (s > 1)
						cout << *it << ", ";
					else
						cout << *it;
					s--;
				}
			}

			cout << "\nPrice (in taka): " << price << endl;
			cout << "\n\n";
		}
	}
	catch (SAException& e)
	{
		(void)e;
		//conn.Rollback();
		cout << e.ErrText().GetMultiByteChars();
		cout << "\nProblem uploading!\n";
	}
	system("pause");


}


vector<string> show_recipe(SAConnection& conn, string query, string field)
{
	system("CLS");
	cout << "\n\n";
	vector<string> file_list;

	SACommand select(&conn);
	try
	{
		select.setCommandText(_TSA(query.c_str()));
		select.Execute();

		int i = 1;
		while (select.FetchNext())
		{

			file_list.push_back(select.Field(_TSA(field.c_str())).asString().GetMultiByteChars());
			cout << i << ". " << file_list[(unsigned __int64)i - 1] << "\n";
			i++;
		}
		cout << "0. Back to categories\n\n";
		return file_list;
	}
	catch (SAException& e)
	{
		(void)e;
		//conn.Rollback();
		cout << e.ErrText().GetMultiByteChars();
		cout << "\nProblem uploading!\n";
	}
}









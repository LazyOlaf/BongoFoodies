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
    ofstream recipe_text(title + cook_name + ".txt");
    cout << "\nRegion: ";
    cin >> region;
    cout << "\nCooking time (in minutes): ";
    cin >> time;
    cout << "\nServings: ";
    cin >> servings;
    cout << "\n";
    string ch;
    string ing="";
    do
    {
        cout << "Ingredient: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string ingre;
        getline(cin, ingre);
        ing+=ingre+", ";
        ingredients.push_back(ingre);
        cout << "Add more? (y/n)...";
        cin >> ch;
    }
    while (ch == "y" || ch == "Y");
    for(int i=0; i<ing.size(); i++)
        recipe_text.put(ing[i]);
    recipe_text.put('\n');
    cout << "\n\nDirections: ";
    cin.ignore(256, '\n');
    getline(cin, procedure);
    for(int i=0; i<procedure.size(); i++)
        recipe_text.put(procedure[i]);
    recipe_text.put('\n');
    cout << "\nAvailable for delivery? (y/n)...";
    cin >> ch;
    cout << "\n";
    if (ch == "y" || ch == "Y")
    {
        string ar="";
        do
        {
            cout << "Delivery area: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string area;
            getline(cin, area);
            ar+=area+", ";
            delivery_area.push_back(area);
            cout << "Add more? (y/n)...";
            cin >> ch;
        }
        while (ch == "y" || ch == "Y");
        for(int i=0; i<ar.size(); i++)
            recipe_text.put(ar[i]);
        cout << "\nPrice (in taka): ";
        cin >> price;
    }

    SACommand insert(&conn);
    try
    {
        insert.setCommandText(_TSA("INSERT INTO Recipes (RecipeID, Title, Cook, Region, Time, Servings, Price, Rating) VALUES (:1, :2, :3, :4, :5, :6, :7, :8)"));
        insert << (unsigned short)RecipeID << title.c_str() << (unsigned short)cook_ID << region.c_str() << (double)time << (unsigned short)servings << (double)price << (double)rating;
        cout<<RecipeID<<endl;
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
            Recipe r;
            cout << "****Recipe Info****\n\n";
            cout << "\n\nTitle: " << title;
            cout << "\nCook name: " << cook_name;
            cout << "\nRegion: " << region;
            cout << "\nCooking time (in minutes): " << time;
            cout << "\nServings: " << servings;

            cout << "\nIngredients: ";
            const int MAX=1000;
            char buffer[MAX];
            ifstream read(title+".txt");
            read.getline(buffer,MAX);
            cout<<buffer<<endl;
            cout << "\nDirections: " << procedure;
            read.getline(buffer,MAX);
            cout<<buffer<<endl;
            if (delivery_area.empty())
                cout << "\nDelivery service not available!";
            else
            {
                cout << "\nDelivery areas: ";
                read.getline(buffer,MAX);
                cout<<buffer<<endl;
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

	this->recipe_options_interface(conn);

}


void Recipe::recipe_options_interface(SAConnection& conn)
{
	cout << "\n\n\n";
	cout << "1.Give feedback\n" << "2.Download recipe\n" << "3.Order recipe\n" << "4.Visit cook profile\n" << "5.Back\n";
	cout << "\nEnter choice: ";
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		this->give_feedback(conn);
		break;
	case 2:
		this->download_recipe(conn);
		break;
	case 3:
		this->order_recipe(conn);
		break;
	case 4:
		this->show_cook_profile(conn);
		break;
	case 5:
		break;
	}
}

void Recipe::download_recipe(SAConnection& conn)
{
	wchar_t* wc = NULL;
	SHGetKnownFolderPath(FOLDERID_Downloads, 0, NULL, &wc);
	wstring ws(wc);
	CoTaskMemFree(static_cast<void*>(wc));
	string dir(ws.begin(), ws.end());

	string path = dir + "\\" + title + ".txt";
	ofstream recipe_text;
	recipe_text.open(path, ios::trunc);

	recipe_text << "****Recipe Info****\n\n";
	recipe_text << "\n\nTitle: " << title;
	recipe_text << "\nCook name: " << cook_name;
	recipe_text << "\nRegion: " << region;
	recipe_text << "\nCooking time (in minutes): " << time;
	recipe_text << "\nServings: " << servings;

	recipe_text << "\nIngredients: ";
	int s = ingredients.size();
	for (auto it = ingredients.begin(); it != ingredients.end(); it++) {
		if (s > 1)
			recipe_text << *it << ", ";
		else
			recipe_text << *it;
		s--;
	}

	recipe_text << "\nDirections: " << procedure;
	recipe_text << "\nRating: " << rating;

	if (delivery_area.empty())
		recipe_text << "\nDelivery service not available!";
	else {
		recipe_text << "\nDelivery areas: ";
		int s = delivery_area.size();
		for (auto it = delivery_area.begin(); it != delivery_area.end(); it++) {
			if (s > 1)
				recipe_text << *it << ", ";
			else
				recipe_text << *it;
			s--;
		}
	}

	recipe_text << "\nPrice (in taka): " << price << endl;
	recipe_text.close();

	cout << "\nYour download has been completed. Check downloads folder!\n\n";
	system("pause");
}

void Recipe::give_feedback(SAConnection& conn)
{
	cout << "\n\n\nWanna show this recipe some love?";
	cout << "\n\n1. *\n" << "2. **\n" << "3. ***\n" << "4. ****\n" << "5. *****\n";
	cout << "\nEnter choice: ";
	int ch;
	cin >> ch;
	switch (ch)
	{
	case 1:
		star_count[4]++;
		break;
	case 2:
		star_count[3]++;
		break;
	case 3:
		star_count[2]++;
		break;
	case 4:
		star_count[1]++;
		break;
	case 5:
		star_count[0]++;
		break;
	}

	rating = star_count[0] * 5 + star_count[1] * 4 + star_count[2] * 3 + star_count[3] * 2 + star_count[4] * 1;
	rating /= star_count[0] + star_count[1] + star_count[2] + star_count[3] + star_count[4];
	rating = std::round(rating * 100.0) / 100.0;


	SACommand update(&conn);
	try
	{
		update.setCommandText(_TSA("UPDATE Rating_chart SET star5 = :1, star4 = :2, star3 = :3, star2 = :4, star1 = :5, Rating = :6 WHERE RecipeID = :7"));
		update << (unsigned short)star_count[0] << (unsigned short)star_count[1] << (unsigned short)star_count[2] << (unsigned short)star_count[3] << (unsigned short)star_count[4] << (double)rating << (unsigned short)RecipeID;
		update.Execute();
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

void Recipe::show_cook_profile(SAConnection& conn)
{
}

void Recipe::order_recipe(SAConnection& conn)
{
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









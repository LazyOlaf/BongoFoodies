#pragma once
#define NOMINMAX

#include <iostream>
#include <fstream>
<<<<<<< HEAD
#include <sstream>
=======
>>>>>>> dcd665399ffe2a42bf69a2124c478e77c7d6c5c1
#include <string>
#include <vector>
#include <cmath>
#include <windows.h>
#include <ShlObj.h>
#include <SQLAPI.h>

using namespace std;

class Recipe
{
protected:
	string title;
	string cook_name;
	string region;
<<<<<<< HEAD
	double time = 0.0;
	int servings = 0;
	double rating = 0.0;
=======
	double time=0.0;
	int servings=0;
	double rating;
>>>>>>> dcd665399ffe2a42bf69a2124c478e77c7d6c5c1
	vector<int> star_count;
	vector<string> delivery_area;
	vector<string> ingredients;
	string procedure;
	double price = 0;

public:
	Recipe();
	virtual ~Recipe();
	static int RecipeID;
<<<<<<< HEAD

=======
	
>>>>>>> dcd665399ffe2a42bf69a2124c478e77c7d6c5c1
	void show_recipe_details(SAConnection& conn, string filename);
	void recipe_options_interface(SAConnection& conn);
	void download_recipe(SAConnection& conn);
	void give_feedback(SAConnection& conn);
	void show_cook_profile(SAConnection& conn);
	void order_recipe(SAConnection& conn);

	void upload_recipe(SAConnection& conn, int cook_ID);
	//void edit_recipe(SAConnection& conn, int cook_ID);

	friend class HomeCook;
};

vector<string> show_recipe(SAConnection& conn, string query, string field);
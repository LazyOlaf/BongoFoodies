// FoodTE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "MainMenu.h"
using namespace std;

int main()
{
	cout << "\n\n\n\t\t ========== WELCOME TO BongoFoodies!! ==========\n\n" << flush;
	main_menu();
	return 0;
}


//bfadmin/foodislove@localhost/xepdb1
//DELETE FROM table_name;
/*
	CREATE TABLE Users 
	(
		UserID INT,
		Name VARCHAR2(20),
		Email VARCHAR2(20) UNIQUE,
		Pass VARCHAR2(20),
		Reg DATE,
		CONSTRAINT u_pk PRIMARY KEY(UserID)
	);
*/
/*
	CREATE TABLE Recipes
	(
		RecipeID INT,
		Title VARCHAR2(20),
		CookID INT,
		Region VARCHAR2(20), 
		Time NUMBER, 
		Servings INT, 
		Price NUMBER,
		CONSTRAINT r_pk PRIMARY KEY (RecipeID),
		CONSTRAINT r_fk FOREIGN KEY (CookID) references Users (UserID)
	);
*/
/*
	CREATE TABLE Delivery_Area
	(
		RecipeID INT,
		Area VARCHAR2(20),
		CONSTRAINT d_fk FOREIGN KEY (RecipeID) REFERENCES Recipes (RecipeID)
	);
*/
/*
	CREATE TABLE Rating_chart
	(
		RecipeID INT,
		star5 INT,
		star4 INT,
		star3 INT,
		star2 INT,
		star1 INT,
		Rating NUMBER,
		CONSTRAINT s_fk FOREIGN KEY (RecipeID) REFERENCES Recipes (RecipeID)
	);
*/
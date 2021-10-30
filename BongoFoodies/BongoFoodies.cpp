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
		Cook INT,
		Region VARCHAR2(20), 
		Time NUMBER, 
		Servings INT, 
		Rating NUMBER,
		Price NUMBER,
		CONSTRAINT r_pk PRIMARY KEY (RecipeID),
		CONSTRAINT r_fk FOREIGN KEY (Cook) references Users (UserID)
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
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <SQLAPI.h>
#include <Recipe.h>
using namespace std;


void browse_interface(SAConnection& conn);
void byTitle(SAConnection& conn, string str);
void byRegion(SAConnection& conn);
void byReview(SAConnection& conn);
void byPrice(SAConnection& conn);
void byArea(SAConnection& conn);
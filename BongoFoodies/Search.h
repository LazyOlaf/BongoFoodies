#pragma once
<<<<<<< HEAD
=======
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <SQLAPI.h>
>>>>>>> dcd665399ffe2a42bf69a2124c478e77c7d6c5c1
#include <Recipe.h>
using namespace std;


void browse_interface(SAConnection& conn);
void byTitle(SAConnection& conn, string str);
void byRegion(SAConnection& conn);
void byReview(SAConnection& conn);
void byPrice(SAConnection& conn);
void byArea(SAConnection& conn);
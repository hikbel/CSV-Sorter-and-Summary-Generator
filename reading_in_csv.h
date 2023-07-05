/************************************************
** File:    reading_in_csv.h
** Project: Data Summary
** Author:  Hikaru Belzer
** Date:    7/1/2023
**
** This is the header file, which contains the
** constants, function prototypes, and other
** generic information.
**
**
************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <limits>

using namespace std;

// Constants
const string EMPTY_STRING = "";
const char SPACE_CHAR = ' ';

// Function Prototypes
void loadFile(vector<int>& vectorOfNums);
int howToSort();
void writingToFile(const vector<int>& vectorOfNums);
void sorting(int choice, vector<int>& vectorOfNums);
double median(const vector<int>& vectorOfNums);
int sum(const vector<int>& vectorOfNums);
void displayInfo(const vector<int>& vectorOfNums);
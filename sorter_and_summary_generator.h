/******************************************************************************
** File:    sorter_and_summary_generator.h
** Project: CSV Sorter and Summary Generator
** Author:  Hikaru Belzer
** Date:    7/22/2023
**
** This is the header file, which contains the libraries, namespace, constants,
** and function prototypes.
**
** To compile: g++ -Wall sorter_and_summary_generator.cpp
** To run: ./sorter_and_summary_generator
**
******************************************************************************/

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
const string EMPTY_STRING = ""; // Used when initializing a variable to an empty string
const int WIDTH = 5; // Set the width for the data visualization to an arbitrary value

// Function Prototypes
int loadFile(vector<int>& vectorOfNums);
int howToSort();
void writingToFile(const vector<int>& vectorOfNums);
void sorting(int choice, vector<int>& vectorOfNums);
double median(const vector<int>& vectorOfNums);
int sum(const vector<int>& vectorOfNums);
void displayInfo(const vector<int>& vectorOfNums);
void writingToTxt(const vector<int>& vectorOfNums);

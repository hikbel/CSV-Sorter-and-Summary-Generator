/************************************************
** File:    reading_in_csv.cpp
** Project: Data Summary
** Author:  Hikaru Belzer
** Date:    7/1/2023
**
** This file reads in a csv file, then writes to
** a new file with all of the data sorted including
** mean, median, etc.
**
** Use the command g++ -Wall reading_in_csv.cpp
** to compile the code.
**
** Use ./reading_in_csv to run the code
**
************************************************/

#include "reading_in_csv.h"

//---------------------------------------------------------------------------
// Name: loadFile
// PreCondition:  
// PostCondition: 
//---------------------------------------------------------------------------
void loadFile(vector<int>& vectorOfNums) {
    string fileName = "";
    int counter = 0;
    string line = "";

    cout << "Type the name of the file you would like to open: (type 'test' for sample)" << endl;
    cin >> fileName;
    if (fileName == "test") {
        fileName = "data.csv";
    }

    ifstream loadedFile(fileName);
    // Check if the file can be opened
    if (!loadedFile.is_open()) {
        cout << "Invalid file - Could not open" << endl;
    } else {
        cout << "Opening " << fileName << endl;

        while (getline(loadedFile, line)) {
            string integer = "";

            // For all the integers except for the last
            for (unsigned int i = 0; i < line.size(); i++) {
                if (line.at(i) != ',') {
                    integer += line.at(i);
                } else {
                    int num = stoi(integer);  // Convert string to integer
                    vectorOfNums.push_back(num);  // Store integer in vector
                    integer = "";
                    counter++;
                }
            }

            // For the very last integer
            // If integer has not been reset to ""
            if (integer.size() > 0) {
                int num = stoi(integer);  // Convert string to integer
                vectorOfNums.push_back(num);  // Store integer in vector
                counter++;
            }
        }
        loadedFile.close();
        cout << counter << " integers loaded" << endl;
    }
}

int howToSort() {
    int response = 0;
    do {
        cout << "How would you like to sort the data?" << endl;
        cout << "1. Least to Greatest" << endl;
        cout << "2. Greatest to Least" << endl;
        cin >> response;
    } while (response < 1 || response > 2);

    return response;
}

void sorting(int choice, vector<int>& vectorOfNums) {
    if (choice == 1) {
        // Sort least to greatest
        sort(vectorOfNums.begin(), vectorOfNums.end());
    } else if (choice == 2) {
        // Sort greatest to least
        sort(vectorOfNums.begin(), vectorOfNums.end(), greater<int>());
    }
}

void writingToFile(const vector<int>& vectorOfNums) {
    ofstream csvFile("sorted_data.csv");

    if (csvFile.is_open()) {
        // Writing each integer to the file
        for (vector<int>::const_iterator it = vectorOfNums.begin(); it != vectorOfNums.end(); ++it) {
            csvFile << *it;
            if (next(it) != vectorOfNums.end()) {
                csvFile << ", ";
            }
        }

        cout << "Numbers written to the file successfully." << endl;
        csvFile.close();
    } else {
        cout << "Unable to open the file." << endl;
    }
}

double median(const vector<int>& vectorOfNums) {
    int midIndex = vectorOfNums.size() / 2;

    if (vectorOfNums.size() % 2 == 0) {
        // Even integer of elements
        return double((vectorOfNums.at(midIndex - 1) + vectorOfNums.at(midIndex)) / 2.0);
    } else {
        // Odd integer of elements
        return double(vectorOfNums.at(midIndex));
    }
}

int sum(const vector<int>& vectorOfNums) {
    int sum = 0;

    for (unsigned int i = 0; i < vectorOfNums.size(); i++) {
        sum += vectorOfNums.at(i);
    }
    return sum;
}

void displayInfo(const vector<int>& vectorOfNums) {
    int sumValue = 0;
    map<int, int> quantityOfEachNum;

    sumValue = sum(vectorOfNums);
    cout << endl;

    // Label
    cout << "Sorted Values:" << endl;

    for (vector<int>::const_iterator it = vectorOfNums.begin(); it != vectorOfNums.end(); ++it) {
        cout << *it;
        if (next(it) != vectorOfNums.end()) {
            cout << ", ";
        }
    }
    cout << endl << endl;

    // Bar chart
    cout << "Bar Chart:" << endl;
    for (unsigned int i = 0; i < vectorOfNums.size(); i++) {
        int frequency = count(vectorOfNums.begin(), vectorOfNums.end(), vectorOfNums.at(i));
        quantityOfEachNum[vectorOfNums.at(i)] = frequency;
    }

    int maxFrequency = 0;
    for (map<int, int>::iterator it = quantityOfEachNum.begin(); it != quantityOfEachNum.end(); ++it) {
        maxFrequency = max(maxFrequency, it->second);
    }

    for (map<int, int>::iterator it = quantityOfEachNum.begin(); it != quantityOfEachNum.end(); ++it) {
        cout << setw(2) << it->first << ": ";
        for (int j = 0; j < it->second; j++) {
            cout << "*";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Statisics:" << endl;
    cout << "Mean: " << double(sumValue) / double(vectorOfNums.size()) << endl;
    cout << "Median: " << median(vectorOfNums) << endl;

    vector<int> integersWithMaxFrequency;
    for (map<int, int>::iterator it = quantityOfEachNum.begin(); it != quantityOfEachNum.end(); ++it) {
        if (it->second > maxFrequency) {
            maxFrequency = it->second;
            integersWithMaxFrequency.clear();
            integersWithMaxFrequency.push_back(it->first);
        } else if (it->second == maxFrequency) {
            integersWithMaxFrequency.push_back(it->first);
        }
    }

    // Mode
    // Check for no mode (if all integers have the same frequency)
    if (integersWithMaxFrequency.size() == quantityOfEachNum.size()) {
        cout << "No Mode (all integers have a common frequency of " << maxFrequency << ")" << endl;
    } else if (integersWithMaxFrequency.size() == 1) {
        cout << "Mode: " << integersWithMaxFrequency.at(0) << " (with a frequency of " << maxFrequency << ")" << endl;
    } else {
        cout << "Modes: ";
        for (unsigned int i = 0; i < integersWithMaxFrequency.size(); i++) {
            cout << integersWithMaxFrequency.at(i);
            if (i < integersWithMaxFrequency.size() - 1) {
                cout << ", ";
            }
        }
        cout << " (with a frequency of " << maxFrequency << ")" << endl;
    }
    cout << endl;


    // Other info
    cout << "Additional Information:" << endl;
    cout << "Count: " << vectorOfNums.size() << endl;
    cout << "Sum: " << sumValue << endl;

    // Smallest and largest values
    int smallest = numeric_limits<int>::max(); // Initialize with largest possible value
    int largest = numeric_limits<int>::min(); // Initialize with smallest possible value

    for (unsigned int i = 0; i < vectorOfNums.size(); i++) {
        if (vectorOfNums[i] < smallest) {
            smallest = vectorOfNums[i];
        }
        if (vectorOfNums[i] > largest) {
            largest = vectorOfNums[i];
        }
    }

    cout << "Smallest integer: " << smallest << endl;
    cout << "Greatest integer: " << largest << endl;
    cout << "Range: " << (largest - smallest) << endl;
}

void writingToTxt(const vector<int>& vectorOfNums) {
    // Create a new file with the specified name in the current directory
    ofstream outfile("summary.txt");

    // Check if the file was successfully opened
    if (outfile.is_open()) {
        int sumValue = 0;
        map<int, int> quantityOfEachNum;

        sumValue = sum(vectorOfNums);
        outfile << endl;

        // Label
        outfile << "Sorted Values:" << endl;

        for (vector<int>::const_iterator it = vectorOfNums.begin(); it != vectorOfNums.end(); ++it) {
            outfile << *it;
            if (next(it) != vectorOfNums.end()) {
                outfile << ", ";
            }
        }
        outfile << endl << endl;

        // Bar chart
        outfile << "Bar Chart:" << endl;
        for (unsigned int i = 0; i < vectorOfNums.size(); i++) {
            int frequency = count(vectorOfNums.begin(), vectorOfNums.end(), vectorOfNums.at(i));
            quantityOfEachNum[vectorOfNums.at(i)] = frequency;
        }

        int maxFrequency = 0;
        for (map<int, int>::iterator it = quantityOfEachNum.begin(); it != quantityOfEachNum.end(); ++it) {
            maxFrequency = max(maxFrequency, it->second);
        }

        for (map<int, int>::iterator it = quantityOfEachNum.begin(); it != quantityOfEachNum.end(); ++it) {
            outfile << setw(2) << it->first << ": ";
            for (int j = 0; j < it->second; j++) {
                outfile << "*";
            }
            outfile << endl;
        }
        outfile << endl;

        outfile << "Statisics:" << endl;
        outfile << "Mean: " << double(sumValue) / double(vectorOfNums.size()) << endl;
        outfile << "Median: " << median(vectorOfNums) << endl;

        vector<int> integersWithMaxFrequency;
        for (map<int, int>::iterator it = quantityOfEachNum.begin(); it != quantityOfEachNum.end(); ++it) {
            if (it->second > maxFrequency) {
                maxFrequency = it->second;
                integersWithMaxFrequency.clear();
                integersWithMaxFrequency.push_back(it->first);
            } else if (it->second == maxFrequency) {
                integersWithMaxFrequency.push_back(it->first);
            }
        }

        // Mode
        // Check for no mode (if all integers have the same frequency)
        if (integersWithMaxFrequency.size() == quantityOfEachNum.size()) {
            outfile << "No Mode (all integers have a common frequency of " << maxFrequency << ")" << endl;
        } else if (integersWithMaxFrequency.size() == 1) {
            outfile << "Mode: " << integersWithMaxFrequency.at(0) << " (with a frequency of " << maxFrequency << ")" << endl;
        } else {
            outfile << "Modes: ";
            for (unsigned int i = 0; i < integersWithMaxFrequency.size(); i++) {
                outfile << integersWithMaxFrequency.at(i);
                if (i < integersWithMaxFrequency.size() - 1) {
                    outfile << ", ";
                }
            }
            outfile << " (with a frequency of " << maxFrequency << ")" << endl;
        }
        outfile << endl;


        // Other info
        outfile << "Additional Information:" << endl;
        outfile << "Count: " << vectorOfNums.size() << endl;
        outfile << "Sum: " << sumValue << endl;

        // Smallest and largest values
        int smallest = numeric_limits<int>::max(); // Initialize with largest possible value
        int largest = numeric_limits<int>::min(); // Initialize with smallest possible value

        for (unsigned int i = 0; i < vectorOfNums.size(); i++) {
            if (vectorOfNums[i] < smallest) {
                smallest = vectorOfNums[i];
            }
            if (vectorOfNums[i] > largest) {
                largest = vectorOfNums[i];
            }
        }

        outfile << "Smallest integer: " << smallest << endl;
        outfile << "Greatest integer: " << largest << endl;
        outfile << "Range: " << (largest - smallest) << endl;

        outfile.close();
    } else {
        cout << "Invalid - Could not output to an export file." << endl;
    }

}

int main () {
    vector<int> integers;  // Vector to store integers
    loadFile(integers);
    sorting(howToSort(), integers);
    displayInfo(integers);
    writingToFile(integers);
    writingToTxt(integers);
    return 0;
}

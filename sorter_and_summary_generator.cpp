/******************************************************************************
** File:    sorter_and_summary_generator.cpp
** Project: CSV Sorter and Summary Generator
** Author:  Hikaru Belzer
** Date:    7/22/2023
**
** This file reads a CSV file containing integers and prompts the user to select
** a sorting method. It creates a file called summary.txt containing the sorted
** data, a visualization displaying the frequency of each integer, statistics,
** and generic information including the sum, range, count, minimum value, and
** maximum value. It also creates a new CSV file called sorted_data.csv that
** contains the sorted integers according to the user’s choice.
**
** To compile the code: g++ -Wall sorter_and_summary_generator.cpp
** To run the code: ./sorter_and_summary_generator
**
******************************************************************************/

#include "sorter_and_summary_generator.h"

//-----------------------------------------------------------------------------
// Name: loadFile
// Description: Attempts to open the file that the user types. If the file name
// is not found in the directory, the program returns a 0. If the file name
// is found, the program returns a 1 and proceeds.
// PreCondition: A vector of integers has been created in main and is passed in by reference
// PostCondition: Returns 0 if the file is invalid. If the file is valid, the program opens it,
// adds the data to the vector, and returns 1
//-----------------------------------------------------------------------------
int loadFile(vector<int>& vectorOfNums) {
    string fileName = EMPTY_STRING; // The file name is empty be default
    int counter = 0; // Initialize the counter at 0
    string line = EMPTY_STRING; // Used when storing the line
    
    // Prompt the user to type in their CSV file name. Provide a test file as a sample
    cout << "Type the name of the file you would like to open: (type 'test' for sample)" << endl;
    cin >> fileName;
    if (fileName == "test") {
        fileName = "data.csv";
    }

    ifstream loadedFile(fileName);
    // Check if the file can be opened
    if (!loadedFile.is_open()) {
        cout << "Invalid file - Could not open" << endl;
        return 0;

    } else {
        // If the file successfully opened, proceed
        cout << "Opening " << fileName << endl;

        while (getline(loadedFile, line)) {
            string integer = EMPTY_STRING; // Store each integer

            // For all the integers except for the last
            for (unsigned int i = 0; i < line.size(); i++) {
                // If the character is not a comma, concatenate it
                if (line.at(i) != ',') {
                    integer += line.at(i);

                } else {
                    int num = stoi(integer);  // Convert string to integer

                    // Store integer in vector
                    vectorOfNums.push_back(num);  
                    integer = EMPTY_STRING; // Reset integer to empty
                    counter++;
                }
            }

            // For the very last integer
            // If integer has not been reset to ""
            if (integer.size() > 0) {
                int num = stoi(integer);  // Convert string to integer

                // Store integer in vector
                vectorOfNums.push_back(num);  
                counter++;
            }
        }
        loadedFile.close();
        cout << endl << counter << " integers loaded" << endl;
        return 1;
    }

    // Return a default value as a precaution
    return 0;
}


//-----------------------------------------------------------------------------
// Name: howToSort
// Description: Prompts the user whether they want to sort the data from least to
// greatest or greatest to least
// PreCondition: A file has been successfully loaded. There are no parameters.
// PostCondition: Returns 1 or 2 depending on the user's response
//-----------------------------------------------------------------------------
int howToSort() {
    int response = 0; // Used for storing the user's reponse. Initialize it to 0.

    do {
        cout << "How would you like to sort the data?" << endl;
        cout << "1. Least to Greatest" << endl;
        cout << "2. Greatest to Least" << endl;
        cin >> response;

        // If the user types in letters or other invalid characters, clear their entry
        if (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
        }
    } while (response < 1 || response > 2);

    return response;
}


//-----------------------------------------------------------------------------
// Name: sorting
// Description: Sorts the vector according to the user's choice (least to greatest
// or greatest to least)
// PreCondition: The user chose a sorting method and the vector is passed by reference
// PostCondition: Sorts the vector (the original is updated because it was passed by reference)
//-----------------------------------------------------------------------------
void sorting(int choice, vector<int>& vectorOfNums) {
    if (choice == 1) {
        // Sort least to greatest
        sort(vectorOfNums.begin(), vectorOfNums.end());
    } else if (choice == 2) {
        // Sort greatest to least
        sort(vectorOfNums.begin(), vectorOfNums.end(), greater<int>());
    }
}


//-----------------------------------------------------------------------------
// Name: writingToFile
// Description: Creates a file called sorted_data.csv with the newly sorted data
// PreCondition: The vector is passed by reference
// PostCondition: sorted_data.csv is added to the user's directory with the sorted data
//-----------------------------------------------------------------------------
void writingToFile(const vector<int>& vectorOfNums) {
    ofstream csvFile("sorted_data.csv");

    if (csvFile.is_open()) {

        // Writing each integer to the file
        for (vector<int>::const_iterator it = vectorOfNums.begin(); it != vectorOfNums.end(); ++it) {
            csvFile << *it;
            // If there are still integers left, add a comma
            if (next(it) != vectorOfNums.end()) {
                csvFile << ", ";
            }
        }

        // Tell the user their file was created
        cout << "Sorted integers successfully written to the file sorted_data.csv" << endl;
        csvFile.close();

    } else {
        cout << "Unable to open the file." << endl;
    }
}


//-----------------------------------------------------------------------------
// Name: median
// Description: Calculates the median of the data.
// PreCondition: The vector is passed by reference. The displayInfo fuction calls this.
// PostCondition: Returns the median value.
//-----------------------------------------------------------------------------
double median(const vector<int>& vectorOfNums) {
    int midIndex = vectorOfNums.size() / 2; // Find the middle index

    if (vectorOfNums.size() % 2 == 0) {
        // Even integer of elements
        return double((vectorOfNums.at(midIndex - 1) + vectorOfNums.at(midIndex)) / 2.0);
    } else {
        // Odd integer of elements
        return double(vectorOfNums.at(midIndex));
    }
}


//-----------------------------------------------------------------------------
// Name: sum
// Description: Calculates the sum of the data.
// PreCondition: The vector is passed by reference. The displayInfo fuction calls this.
// PostCondition: Returns the sum.
//-----------------------------------------------------------------------------
int sum(const vector<int>& vectorOfNums) {
    int sum = 0; // Initialize the sum to 0

    // Iterate thtough the vector and add all of its integers
    for (unsigned int i = 0; i < vectorOfNums.size(); i++) {
        sum += vectorOfNums.at(i);
    }

    return sum;
}


//-----------------------------------------------------------------------------
// Name: displayInfo
// Description: Prints the sorted values, data visualization, statistics, and additional
// information to the user's screen
// PreCondition: The vector is passed by reference. The vector has already been sorted
// PostCondition: Prints all information and writes to a new summary.txt file but does not
// return anything
//-----------------------------------------------------------------------------
void displayInfo(const vector<int>& vectorOfNums) {
    int sumValue = sum(vectorOfNums); // Call the sum function to store the sum
    map<int, int> quantityOfEachNum; // Create a map
    cout << endl;

    // Print the sorted values
    cout << "Sorted Values:" << endl;

    // Use an iterator, and print a comma if there are more integers
    for (vector<int>::const_iterator it = vectorOfNums.begin(); it != vectorOfNums.end(); ++it) {
        cout << *it;
        if (next(it) != vectorOfNums.end()) {
            cout << ", ";
        }
    }
    cout << endl << endl;

    // Print the data visualization
    cout << "Data Visualization:" << endl;
    for (unsigned int i = 0; i < vectorOfNums.size(); i++) {
        int frequency = count(vectorOfNums.begin(), vectorOfNums.end(), vectorOfNums.at(i)); // Store the frequency
        quantityOfEachNum[vectorOfNums.at(i)] = frequency; // Edit the map
    }

    int maxFrequency = 0; // Initialize the maximum frequency to 0
    for (map<int, int>::iterator it = quantityOfEachNum.begin(); it != quantityOfEachNum.end(); ++it) {
        // Update the value
        maxFrequency = max(maxFrequency, it->second);
    }

    for (map<int, int>::iterator it = quantityOfEachNum.begin(); it != quantityOfEachNum.end(); ++it) {
        // Set the width to an arbitrary value like 5
        cout << setw(WIDTH) << it->first << ": ";

        // Print the correct number of asterisks according to the frequency
        for (int j = 0; j < it->second; j++) {
            cout << "*";
        }
        cout << endl;
    }
    cout << endl;

    // Print the measures of central tendancy
    cout << "Statisics:" << endl;
    // Calculate the mean here
    cout << "Mean: " << double(sumValue) / double(vectorOfNums.size()) << endl;
    // Use the median function to print the median
    cout << "Median: " << median(vectorOfNums) << endl;

    vector<int> integersWithMaxFrequency; // Create a new vector to save the integers that have the greatest frequency
    for (map<int, int>::iterator it = quantityOfEachNum.begin(); it != quantityOfEachNum.end(); ++it) {
        if (it->second > maxFrequency) {
            // Reassign maxFrequency
            maxFrequency = it->second;

            // Clear the vector and add a new element
            integersWithMaxFrequency.clear();
            integersWithMaxFrequency.push_back(it->first);

        } else if (it->second == maxFrequency) {
            // Otherwise, just add an element
            integersWithMaxFrequency.push_back(it->first);
        }
    }

    // Mode
    // Check for no mode (if all integers have the same frequency)
    if (integersWithMaxFrequency.size() == quantityOfEachNum.size()) {
        cout << "No Mode (all integers have a common frequency of " << maxFrequency << ")" << endl;

    // If there is only one integer with the greatest frequency, then only show that
    } else if (integersWithMaxFrequency.size() == 1) {
        cout << "Mode: " << integersWithMaxFrequency.at(0) << " (with a frequency of " << maxFrequency << ")" << endl;

    // If there are multiple modes, print it from the vector
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

    // Use a loop to find the smallest and greatest integers
    for (unsigned int i = 0; i < vectorOfNums.size(); i++) {
        if (vectorOfNums[i] < smallest) {
            smallest = vectorOfNums[i];
        }
        if (vectorOfNums[i] > largest) {
            largest = vectorOfNums[i];
        }
    }

    // Display the remaining information here
    cout << "Minimum: " << smallest << endl;
    cout << "Maximum: " << largest << endl;
    cout << "Range: " << (largest - smallest) << endl;
    cout << endl;
}


//-----------------------------------------------------------------------------
// Name: writingToTxt
// Description: Writes the same information that was printed to the screen to summary.txt
// PreCondition: The vector is passed by reference. The information was already printed
// to the user's screen
// PostCondition: Puts all of the summary information into summary.txt
//-----------------------------------------------------------------------------
void writingToTxt(const vector<int>& vectorOfNums) {
    // Create a new file with the specified name in the current directory
    ofstream outfile("summary.txt");

    // Check if the file was successfully opened
    if (outfile.is_open()) {
        int sumValue = sum(vectorOfNums); // Call the sum function to store the sum
        map<int, int> quantityOfEachNum; // Create a map
        outfile << endl;

        // Print the sorted values
        outfile << "Sorted Values:" << endl;

        // Use an iterator, and print a comma if there are more integers
        for (vector<int>::const_iterator it = vectorOfNums.begin(); it != vectorOfNums.end(); ++it) {
            outfile << *it;
            if (next(it) != vectorOfNums.end()) {
                outfile << ", ";
            }
        }
        outfile << endl << endl;

        // Print the data visualization
        outfile << "Data Visualization:" << endl;
        for (unsigned int i = 0; i < vectorOfNums.size(); i++) {
            int frequency = count(vectorOfNums.begin(), vectorOfNums.end(), vectorOfNums.at(i)); // Store the frequency
            quantityOfEachNum[vectorOfNums.at(i)] = frequency; // Edit the map
        }

        int maxFrequency = 0; // Initialize the maximum frequency to 0
        for (map<int, int>::iterator it = quantityOfEachNum.begin(); it != quantityOfEachNum.end(); ++it) {
            // Update the value
            maxFrequency = max(maxFrequency, it->second);
        }

        for (map<int, int>::iterator it = quantityOfEachNum.begin(); it != quantityOfEachNum.end(); ++it) {
            // Set the width to an arbitrary value like 5
            outfile << setw(WIDTH) << it->first << ": ";

            // Print the correct number of asterisks according to the frequency
            for (int j = 0; j < it->second; j++) {
                outfile << "*";
            }
            outfile << endl;
        }
        outfile << endl;

        // Print the measures of central tendancy
        outfile << "Statisics:" << endl;
        // Calculate the mean here
        outfile << "Mean: " << double(sumValue) / double(vectorOfNums.size()) << endl;
        // Use the median function to print the median
        outfile << "Median: " << median(vectorOfNums) << endl;

        vector<int> integersWithMaxFrequency; // Create a new vector to save the integers that have the greatest frequency
        for (map<int, int>::iterator it = quantityOfEachNum.begin(); it != quantityOfEachNum.end(); ++it) {
            if (it->second > maxFrequency) {
                // Reassign maxFrequency
                maxFrequency = it->second;

                // Clear the vector and add a new element
                integersWithMaxFrequency.clear();
                integersWithMaxFrequency.push_back(it->first);

            } else if (it->second == maxFrequency) {
                // Otherwise, just add an element
                integersWithMaxFrequency.push_back(it->first);
            }
        }

        // Mode
        // Check for no mode (if all integers have the same frequency)
        if (integersWithMaxFrequency.size() == quantityOfEachNum.size()) {
            outfile << "No Mode (all integers have a common frequency of " << maxFrequency << ")" << endl;

        // If there is only one integer with the greatest frequency, then only show that
        } else if (integersWithMaxFrequency.size() == 1) {
            outfile << "Mode: " << integersWithMaxFrequency.at(0) << " (with a frequency of " << maxFrequency << ")" << endl;

        // If there are multiple modes, print it from the vector
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

        // Use a loop to find the smallest and greatest integers
        for (unsigned int i = 0; i < vectorOfNums.size(); i++) {
            if (vectorOfNums[i] < smallest) {
                smallest = vectorOfNums[i];
            }
            if (vectorOfNums[i] > largest) {
                largest = vectorOfNums[i];
            }
        }

        // Display the remaining information here
        outfile << "Minimum: " << smallest << endl;
        outfile << "Maximum: " << largest << endl;
        outfile << "Range: " << (largest - smallest) << endl;
        outfile << endl;

        outfile.close();
    } else {
        cout << "Invalid - Could not output to an export file." << endl;
    }

}

int main () {
    vector<int> integers;  // Vector to store integers
    int result = loadFile(integers); // Save either 1 or 0 from calling the loadFile function
    
    // Only proceed if a file was successfully opened
    if (result == 1) {
        // Call these functions in this order
        sorting(howToSort(), integers);
        displayInfo(integers);
        writingToFile(integers);
        writingToTxt(integers);
    }
    
    return 0;
}

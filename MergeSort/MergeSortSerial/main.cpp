// MergeSortSerial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>

#include "fileHandling.h"
#include "sort.h"
#include "tbb/tick_count.h"

using namespace std;
using namespace tbb;

int main()
{
	// all the possible chars
	const char alphanum[] = "0123456789"
							"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
							"abcdefghijklmnopqrstuvwxyz";

    #pragma region Setting up the unsorted strings
	// vector that will hold all the randomized strings
	// for which the sorting will be done
	vector<string> initialUnsortedStrings;

	string firstTest = "";
	for (int i = 0; i < 10; i++) {
		firstTest.append(string(1, alphanum[rand() % (sizeof(alphanum) - 1)]));
	}
	firstTest.append("\0");

	string secondTest = "";
	for (int i = 0; i < 100; i++) {
		secondTest.append(string(1, alphanum[rand() % (sizeof(alphanum) - 1)]));
	}
	secondTest.append("\0");

	string thirdTest = "";
	for (int i = 0; i < 1000; i++) {
		thirdTest.append(string(1, alphanum[rand() % (sizeof(alphanum) - 1)]));
	}
	thirdTest.append("\0");

	string fourthTest = "";
	for (int i = 0; i < 10000; i++) {
		fourthTest.append(string(1, alphanum[rand() % (sizeof(alphanum) - 1)]));
	}
	fourthTest.append("\0");

	string fifthTest = "";
	for (int i = 0; i < 100000; i++) {
		fifthTest.append(string(1, alphanum[rand() % (sizeof(alphanum) - 1)]));
	}
	fifthTest.append("\0");

	string sixthTest = "";
	for (int i = 0; i < 1000000; i++) {
		sixthTest.append(string(1, alphanum[rand() % (sizeof(alphanum) - 1)]));
	}
	sixthTest.append("\0");

	initialUnsortedStrings.push_back(firstTest);
	initialUnsortedStrings.push_back(secondTest);
	initialUnsortedStrings.push_back(thirdTest);
	initialUnsortedStrings.push_back(fourthTest);
	initialUnsortedStrings.push_back(fifthTest);
	initialUnsortedStrings.push_back(sixthTest);
    #pragma endregion

	#pragma region Create file that holds unsorted strings
	fstream initialUnsortedFile;
	initialUnsortedFile.open("..//Data//unsorted.txt", ios::out | ios::trunc);

	for (vector<string>::iterator it = initialUnsortedStrings.begin(); it != initialUnsortedStrings.end(); it++) {
		string str = *it;
		initialUnsortedFile << *it << endl;
	}

	initialUnsortedFile.close();
	#pragma endregion

	#pragma region Read the file with unsorted strings and fill a container
	vector<string> unsortedStrings;

	fstream unsortedFile;
	unsortedFile.open("..//Data//unsorted.txt", ios::in);

	string line;
	while (getline(unsortedFile, line)) {
		unsortedStrings.push_back(line);
	}

	unsortedFile.close();
	#pragma endregion

	#pragma region Sort unsorted strings and write results to file
	fstream sortedFile;
	sortedFile.open("..//Data//sorted.txt", ios::out | ios::trunc);
	sortedFile << "******************** SERIAL MERGE SORT *******************" << endl << endl;

	for (vector<string>::iterator it = unsortedStrings.begin(); it != unsortedStrings.end(); it++) {
		string str = *it;

		tick_count start = tick_count::now();
		MergeSort(&str);
		tick_count end = tick_count::now();
		double res = (end - start).seconds() * 1000;

		sortedFile << "Array size: " << strlen(str.c_str()) << endl;
		sortedFile << "Sort execution time: " << res << "ms" << endl;
		sortedFile << "Sorted array: " << str << endl << endl;
	}
	sortedFile << "************************************************************" << endl << endl;

	sortedFile.close();
	#pragma endregion
}
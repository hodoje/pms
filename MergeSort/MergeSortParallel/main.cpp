// MergeSortParallel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>

#include "mergeSortTask.h"
#include "tbb/tick_count.h"

using namespace std;

int main()
{
	cout << "Running parallel merge sort over random unsorted arrays..." << endl;

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
	sortedFile.open("..//Data//sorted.txt", ios::app);
	sortedFile << "******************** PARALLEL MERGE SORT TESTING *******************" << endl << endl;

	for (vector<string>::iterator it = unsortedStrings.begin(); it != unsortedStrings.end(); it++) {
		string str = *it;

		tick_count start = tick_count::now();
		MergeSortTask& task = *new(task::allocate_root())MergeSortTask(&str);
		task::spawn_root_and_wait(task);
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
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
	// all the possible chars
	const char alphanum[] = "0123456789"
							"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
							"abcdefghijklmnopqrstuvwxyz";

	// vector that will hold all the randomized strings
	// for which the sorting will be done
	vector<string> stringList;

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

	stringList.push_back(firstTest);
	stringList.push_back(secondTest);
	stringList.push_back(thirdTest);
	stringList.push_back(fourthTest);
	stringList.push_back(fifthTest);
	stringList.push_back(sixthTest);

	fstream startingFile;
	startingFile.open("..//Data//unsorted.txt", ios::out | ios::trunc);

	for (vector<string>::iterator it = stringList.begin(); it != stringList.end(); it++) {
		string str = *it;
		startingFile << *it << endl;
	}

	startingFile.close();

	cout << "---------- PARALLEL MERGE SORT TESTING ----------" << endl;
	//string arr = "ACB531792";
	//for (int i = 0; i < 1000000; i++) {
	//	arr.append("h");
	//}
	//arr.append("\0");
	//cout << endl << "Unsorted array: " << arr << endl;
	//cout << "--------------------------------------------------" << endl;

	/*tick_count start = tick_count::now();
	MergeSortTask& task = *new(task::allocate_root())MergeSortTask(&arr);
	task::spawn_root_and_wait(task);
	tick_count end = tick_count::now();

	double res = (end - start).seconds() * 1000;
	cout << endl << "Sorted array: " << arr << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "---------- EXECUTION TIME ----------" << endl;
	cout << endl << "Time: " << res << "ms" << endl;*/
}
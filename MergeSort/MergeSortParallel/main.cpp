// MergeSortParallel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "mergeSortTask.h"
#include "tbb/tick_count.h"

using namespace std;

int main()
{
	cout << "---------- PARALLEL MERGE SORT TESTING ----------" << endl;
	string arr = "ACB531792";
	for (int i = 0; i < 1000000; i++) {
		arr.append("h");
	}
	arr.append("\0");
	cout << endl << "Unsorted array: " << arr << endl;
	cout << "--------------------------------------------------" << endl;

	tick_count start = tick_count::now();
	MergeSortTask& task = *new(task::allocate_root())MergeSortTask(&arr);
	task::spawn_root_and_wait(task);
	tick_count end = tick_count::now();

	double res = (end - start).seconds() * 1000;
	cout << endl << "Sorted array: " << arr << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "---------- EXECUTION TIME ----------" << endl;
	cout << endl << "Time: " << res << "ms" << endl;
}
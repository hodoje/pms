// MergeSortSerial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <ostream>

#include "fileHandling.h"
#include "sort.h"

using namespace std;

int main()
{
    cout << "Hello World!\n"; 
	string arr = "531792\0";
	cout << endl << "Unsorted array: " << arr << endl;
	MergeSort(&arr);
	cout << endl << "Sorted array: " << arr << endl;
}
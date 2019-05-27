#pragma once

#include <string>
#include "tbb\task.h"

using namespace std;
using namespace tbb;

class MergeSortTask : public task {
	public:
		string* arrayToSort;

		MergeSortTask(string* arrayToSort);
		~MergeSortTask();

		void merge(string leftArr, string rightArr, string* resultArr);
		void serialMergeSort(string* arrayToSort);
		task* execute();
};
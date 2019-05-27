#pragma once

#include <string>
#include "tbb\task.h"
#include "tbb\task_group.h"

using namespace std;
using namespace tbb;

void Merge(string leftArr, string rightArr, string* resultArr);
void MergeSort(string* arrayToSort);
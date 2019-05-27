#include "pch.h"
#include "mergeSortTask.h"

#define CUTOFF 512

MergeSortTask::MergeSortTask(string* unsortedArray) {
	arrayToSort = unsortedArray;
}

MergeSortTask::~MergeSortTask() {

}

void MergeSortTask::merge(string leftArr, string rightArr, string* resultArr) {
	// get the size of left array
	size_t nL = strlen(leftArr.c_str());
	// get the size of right array
	size_t nR = strlen(rightArr.c_str());
	// i - used for tracking the currently smallest unpicked element in left array
	// j - used for tracking the currently smallest unpicked element in right array
	// k - used for tracking the current element position in resulting array that needs to be filled
	int i = 0;
	int j = 0;
	int k = 0;

	// here we fill the resulting array alternately while comparing the currently unpicked elements from left and right array
	// this while loop breaks when one of the arrays are exhausted
	while (i < nL && j < nR) {
		if (leftArr[i] <= rightArr[j]) {
			(*resultArr)[k] = leftArr[i];
			i++;
		}
		else {
			(*resultArr)[k] = rightArr[j];
			j++;
		}
		k++;
	}

	// here we check if the left array is not exhausted and if not, fill the resulting array with the rest of elements from left
	while (i < nL) {
		(*resultArr)[k] = leftArr[i];
		i++;
		k++;
	}

	// here we check if the right array is not exhausted and if not, fill the resulting array with the rest of elements from right
	while (j < nR) {
		(*resultArr)[k] = rightArr[j];
		j++;
		k++;
	}
}

void MergeSortTask::serialMergeSort(string * arrayToSort)
{
	size_t nA = strlen((*arrayToSort).c_str());

	if (nA == 1) {
		return;
	}

	size_t middle = nA / 2;

	string leftArray = string(middle, ' ');
	size_t leftArraySize = middle;
	leftArray[leftArraySize] = '\0';

	string rightArray = string(nA - middle, ' ');
	size_t rightArraySize = nA - middle;
	rightArray[rightArraySize] = '\0';

	for (size_t i = 0; i <= leftArraySize - 1; i++) {
		leftArray[i] = (*arrayToSort)[i];
	}

	for (size_t i = middle; i <= nA - 1; i++) {
		rightArray[i - middle] = (*arrayToSort)[i];
	}
	
	serialMergeSort(&leftArray);
	serialMergeSort(&rightArray);

	merge(leftArray, rightArray, &(*arrayToSort));
}

// Actually the MergeSort method
task* MergeSortTask::execute() {
	// get the size of the complete unsortedArray
	size_t nA = strlen((*arrayToSort).c_str());

	// when an array is less then size of the cut off, switch to serial merge sort
	if (nA < CUTOFF) {
		serialMergeSort(arrayToSort);
		return NULL;
	}
	else {
		// if number of elements in an array is 1, the array is already sorted and we go back
		if (nA == 1) {
			return NULL;
		}

		// if number of elements of an array is larger than 1, there is another breakdown of the array to be done
		size_t middle = nA / 2;

		// allocate memory for left array
		// NOTE: although we specify the size of memory to be allocated, there still will be some memory ahead of allocated memory
		// that is why we set up the null terminator manually at the end
		// ANOTHER NOTE: creating string like this creates the string on the stack instead on the heap with new char[middle]
		// this means the string will be automatically deleted after function finishes executing
		string leftArray = string(middle, ' ');
		size_t leftArraySize = middle;
		leftArray[leftArraySize] = '\0';

		// allocate memory for left array
		// NOTE: same note from above
		string rightArray = string(nA - middle, ' ');
		size_t rightArraySize = nA - middle;
		rightArray[rightArraySize] = '\0';

		// copy elements of the left half of the unsorted array to left array
		for (size_t i = 0; i <= leftArraySize - 1; i++) {
			leftArray[i] = (*arrayToSort)[i];
		}

		// copy elements of the right half of the unsorted array to right array
		for (size_t i = middle; i <= nA - 1; i++) {
			rightArray[i - middle] = (*arrayToSort)[i];
		}

		// define tasks for each subarray
		MergeSortTask& leftTask = *new(allocate_child())MergeSortTask(&leftArray);
		MergeSortTask& rightTask = *new(allocate_child())MergeSortTask(&rightArray);

		// spawn tasks and wait for them to finish
		// obavezno pre spawn-ovanja bilo kog potomka. Broj 3 predstavlja 2 zadatka
		// potomka i dodatni implicitno uveden zadatak za potrebe
		// metode spawn_and_wait_for_all.
		set_ref_count(3);
		spawn(leftTask);
		spawn_and_wait_for_all(rightTask);

		merge(leftArray, rightArray, &(*arrayToSort));

		return NULL;
	}
}

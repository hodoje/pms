#include "pch.h"
#include "sort.h"

void Merge(string leftArr, string rightArr, string* resultArr) {
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

void MergeSort(string* arrayToSort) {
	// get the size of the complete unsortedArray
	size_t nA = strlen((*arrayToSort).c_str());

	// if number of elements in an array is 1, the array is already sorted and we go back
	if (nA == 1) {
		return;
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
	for (int i = 0; i <= leftArraySize - 1; i++) {
		leftArray[i] = (*arrayToSort)[i];
	}

	// copy elements of the right half of the unsorted array to right array
	for (int i = middle; i <= nA - 1; i++) {
		rightArray[i - middle] = (*arrayToSort)[i];
	}

	// THE ONLY DIFFERENCE FROM SERIAL VERSION
	// recursive call for subarrays but now in tasks
	// task group contains a list tasks that are executing and it's possible to wait for all of them
	task_group group;
	// this expression as the argument of "run" method is a lambda expression, just a syntax that acts as an anonymous function
	group.run([&] {MergeSort(&leftArray); });
	group.run([&] {MergeSort(&rightArray); });
	group.wait();

	//// after sorts return, merge the two arrays in one
	//// this does not improve performance at all, in different cases it acts either slightly faster or slightly slower
	//// would recommend staying with Merge that is not in a task since it's more consistent in execution time
	//group.run([&] {Merge(leftArray, rightArray, &(*arrayToSort)); });
	//group.wait();
	Merge(leftArray, rightArray, &(*arrayToSort));
}
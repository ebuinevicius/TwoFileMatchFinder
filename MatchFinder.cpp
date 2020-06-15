#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <array>
#include <cstring>

using namespace std;

void MergeInts(int arr[], int low, int high, int mid); // Combines sorted values
void MergeSortInts(int *arr, int low, int high); // Splits array into two halves
void MergeStrings(string arr[], int low, int high, int mid);
void MergeSortStrings(string *arr, int low, int high);
string* readStrings(string f1, int &size);
int * readInts(string f1, int &size);

// function to combine values in order from two halves (subarrays from low, mid and mid+1, high)
void MergeInts(int arr[], int low, int high, int mid) {
    int left[mid-low+1]; 
    int right[high-mid];
 
    // copy data from array into left and right halves
    for (int i = 0; i < mid-low+1; i++) {
        left[i] = arr[low+i];
    }
    for (int j = 0; j < high-mid; j++) {
        right[j] = arr[mid+1+j];
    }

    int i = 0; // increment value for left half of array
    int j = 0; // increment value for right half of array
    int k = low; // intial index of new array
    while (i < mid-low+1 && j < high-mid) { // add values from left and right arrays in order into a
        if (left[i] <= right[j]) { // Left value goes first
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < mid-low+1) { // copy remaining elements in case of odd division
        arr[k] = left[i]; 
        i++;
        k++;
    }
    while (j < high-mid) {
        arr[k] = right[j];
        j++;
        k++;
    }
    
}
// function for splitting arrays in half recursively until only one value
void MergeSortInts(int *arr, int low, int high) {
    int mid;
    if (low < high) { // stop when equal or crossed
        mid = (low+high)/2;
        MergeSortInts(arr, low, mid); // call recursively on left half until you reach one value
        MergeSortInts(arr, mid+1, high); // call revursively on right half until you reach one value

        MergeInts(arr, low, high, mid);
    }
}

void MergeSortStrings(string arr[], int low, int high) {
    int mid;
    if (low < high) { // stop when equal or crossed
        mid = (low+high)/2;
        MergeSortStrings(arr, low, mid); // call recursively on left half
        MergeSortStrings(arr, mid+1, high); // recursive call on right half

        MergeStrings(arr, low, high, mid); // 
    }
}

void MergeStrings(string arr[], int low, int high, int mid) {
    string left[mid-low+1];
    string right[high-mid];
 
    // copy data from original array into  left and right halves
    for (int i = 0; i < mid-low+1; i++) {
        left[i] = arr[low+i];
    }
    for (int j = 0; j < high-mid; j++) {
        right[j] = arr[mid+1+j];
    }
    int i = 0;
    int j = 0;
    int k = low; // intial index
    while (i < mid-low+1 && j < high-mid) { // copy data from halves into new array in order
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < mid-low+1) { // copy remaining elements
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < high-mid) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

// function to read strings from file
string* readStrings(string f1, int &size) {
    ifstream in1;
    in1.open(f1);
    if (!in1.is_open()) {
        cout << "Could not open file " << f1 << endl;
    }
    string currString;
    int count1 = 0;
    while (!in1.eof()) { // count number of strings in file
        in1 >> currString;
        if (!in1.fail()) {
            count1++;
        }
    }
    in1.clear();
    in1.close();
    in1.open(f1); // reopen for reading
    string *array = new string[count1];
    size = count1;
    for (int i = 0; i < count1; i++) { // add  strings into array from file
        in1 >> array[i];
    }
    return array;
}

// function to read in an array of its from a file
int* readInts(string f1, int &size) {
    ifstream in1;
    in1.open(f1);
    if (!in1.is_open()) {
        cout << "Could not open file " << f1 << endl;
    }
    int currNum;
    int count1 = 0;
    while (!in1.eof()) { // count number of ints in file 1
        in1 >> currNum;
        if (!in1.fail()) {
            count1++;
        }
    }

    in1.clear();
    in1.close();
    in1.open(f1); // reopen file for reading
    int *array = new int[count1]; // array to hold ints
    for (int i = 0; i < count1; i++) { // store ints from file into array
        in1 >> array[i];
    }
    size = count1;
    return array;
}


int main(int argc, char** argv) {
    string argv1 = argv[1];
    string argv2 = argv[2];
    string argv3 = argv[3];
    if (argv1 == "i") { // read integers
        int size1 = 0;
        int *array1 = readInts(argv2, size1);
        int size2 = 0;
        int *array2 = readInts(argv3, size2);
        MergeSortInts(array1, 0, size1-1); // sort both arrays by themselves
        MergeSortInts(array2, 0, size2-1);
        for (int i = 0; i < size1; i++) { 
            for (int j = i+1; j < size1; j++) {
                if (array1[i] == array1[j]) {
                    i++; // skip duplicate values
                }
            }
            if (find(array2, array2+size2, array1[i]) != array2+size2) { // element found in both
                cout << array1[i] << endl; // output unique values that appear in both arrays
            }
        }
    }
    else if (argv1 == "s") { // must read strings
        int size1 = 0;
        int size2 = 0;
        string *array1 = readStrings(argv2, size1); // first file
        string *array2 = readStrings(argv3, size2); // second file
        MergeSortStrings(array1, 0, size1-1); // sort both arrays by themselves
        MergeSortStrings(array2, 0, size2-1);
        for (int i = 0; i < size1; i++) {
            for (int j = i+1; j < size1; j++) {
                if (array1[i] == array1[j]) {
                    i++; // skip duplicate values
                    
                }
            }
            if (find(array2, array2+size2, array1[i]) != array2+size2) { // element found in both
                cout << array1[i] << endl; // output unique values that appear in both arrays
            }
        }
    }
    return 0;

}
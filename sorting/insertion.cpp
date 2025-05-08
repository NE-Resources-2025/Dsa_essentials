#include <iostream>

using namespace std;

// Insertion sort function
template <typename T>
void insertionSort(T arr[], int n) {
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;

        // arranging in sorted arr
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Utility function to print an array
template <typename T>
void printArray(T arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// // Main function to demonstrate insertion sort
// int main() {
//    int arr[] = {64, 25, 12, 22, 11};
//    int n = sizeof(arr) / sizeof(arr[0]);

//    cout << "Original array: ";
//    printArray(arr, n);

//    // Perform insertion sort
//    insertionSort(arr, n);

//    cout << "Sorted array: ";
//    printArray(arr, n);

//    return 0;
// }
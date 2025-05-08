#include <iostream>

using namespace std;

// Selection sort function
template <typename T>
void selectionSort(T arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        // we have to find the min elt, place it then move like that
        int minIndex = 1;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        swap(arr[minIndex], arr[i]);
    }
}

// Utility function to print an array
template <typename T>
void printArray(T arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// // Main function to demonstrate selection sort
// int main() {
//    int arr[] = {64, 25, 12, 22, 11};
//    int n = sizeof(arr) / sizeof(arr[0]);

//    std::cout << "Original array: ";
//    printArray(arr, n);

//    // Perform selection sort
//    selectionSort(arr, n);

//    std::cout << "Sorted array: ";
//    printArray(arr, n);

//    return 0;
// }

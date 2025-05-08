#include <iostream>

using namespace std;

// Bubble sort function
template <typename T>
void bubbleSort(T arr[], int n) {
    for (int i = 0; i < n - 1; ++i)
    { // loop thru the array
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j)
        { // since after i, others are sorted
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
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

// // Main function to demonstrate bubble sort
// int main() {
//    int arr[] = {64, 25, 12, 22, 11};
//    int n = sizeof(arr) / sizeof(arr[0]);

//    std::cout << "Original array: ";
//    printArray(arr, n);

//    // Perform bubble sort
//    bubbleSort(arr, n);

//    std::cout << "Sorted array: ";
//    printArray(arr, n);

//    return 0;
// }

#include <iostream>

using namespace std;

// Binary search function (iterative implementation)
template <typename T>
int binarySearch(T arr[], int left, int right, T key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) {
            return mid;
        }

        // If key greater, ignore left half
        if (arr[mid] < key)
        {
            left = mid + 1;
        }
        // If key smaller, ignore right half
        else
        {
            right = mid - 1;
        }
    }
    return -1; //if key not found
}

// // Main function to demonstrate binary search
// int main() {
//    int arr[] = {2, 3, 4, 10, 40};
//    int n = sizeof(arr) / sizeof(arr[0]);
//    int key = 10;

//    int result = binarySearch(arr, 0, n - 1, key);
//    if (result != -1) {
//        cout << "Element found at index " << result << endl;
//    } else {
//        cout << "Element not found in array" << endl;
//    }

//    return 0;
// }

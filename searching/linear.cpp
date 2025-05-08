#include <iostream>

using namespace std;

// Linear search function
template <typename T>
int linearSearch(T arr[], int n, T key) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1; //if key not found
}

// // Driver func
// int main() {
//        int arr[] = {2, 3, 4, 10, 40};
//        int n = sizeof(arr) / sizeof(arr[0]);
//        int key = 4;

//        int result = linearSearch(arr, n, key);
//        if (result != -1) {
//         cout << "Element found at index " << result << endl;
//         } else {
//         cout << "Element not found in array" << endl;
//         }
// }
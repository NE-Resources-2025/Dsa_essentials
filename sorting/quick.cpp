#include <iostream>

// Utility function to swap two elements
template <typename T>
void swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

// Partition function for quick sort
template <typename T>
int partition(T arr[], int low, int high)
{
    T pivot = arr[high]; // Pivot (last element)
    int i = low - 1;     // Index of smaller element

    for (int j = low; j < high; ++j)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            ++i; // Increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick sort function
template <typename T>
void quickSort(T arr[], int low, int high)
{
    if (low < high)
    {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partition(arr, low, high);

        // Recursively sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Utility function to print an array
template <typename T>
void printArray(T arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// // Main function to demonstrate quick sort
// int main() {
//    int arr[] = {10, 7, 8, 9, 1, 5};
//    int n = sizeof(arr) / sizeof(arr[0]);

//    std::cout << "Original array: ";
//    printArray(arr, n);

//    // Perform quick sort
//    quickSort(arr, 0, n - 1);

//    std::cout << "Sorted array: ";
//    printArray(arr, n);

//    return 0;
// }

// Hande Köksal Section-1 22401938 HW2

#include <iostream>
#include <chrono>
#include <cmath>
using namespace std;

void createSortedArray(int* arr, int N);

void mergeSort(int* arr, int N, int first, int last);
void merge(int* arr, int N, int first, int mid, int last);

void targetBiggerThanLast(int*arr, int N, int K);
void targetSmallerThanFirst(int* arr, int K);
void targetInBetween(int* arr, int left, int N, int K, int target);

void linearSearch(int* arr, int N, int K, int target);
void binarySearch(int* arr, int N, int K, int target);
void jumpSearch(int* arr, int N, int K, int target);

int main() {
    srand(time(0));

    // 10 N values
    int* N = new int[10];
    const int SIZE_N = 10;

    N[0] = 8; // 2^3
    N[1] = 16; // 2^4
    N[2] = 100; // 10^2
    N[3] = 128; // 2^7
    N[4] = 1000; // 10^3
    N[5] = 1024; // 2^10
    N[6] = 8192; // 2^13
    N[7] = 10000; // 10^4
    N[8] = 65536; // 2^16
    N[9] = 1000000; // 10^6

    // Randomly creating 10 int arrays
    int** randomArrays = new int*[SIZE_N];

    for (int i = 0; i < SIZE_N; i++) {
        int* arr = new int[N[i]];
        createSortedArray(arr, N[i]);
        randomArrays[i] = arr;
    }

    // 10 target values for 10 ranges
    int* targets = new int[SIZE_N];
    for (int i = 0; i < SIZE_N; i++) {
        targets[i] = rand() % (10 * N[i] + 1);
    }

    // Search algorithms for 10 N and 4 K values 
    
    // Linear Search
    for (int i = 0; i < SIZE_N; i++) {
        for (int j = 0; j < 4; j++) {
            if (j == 0) {
                linearSearch(randomArrays[i], N[i], 1, targets[i]);
            }
            else if (j == 1) {
                linearSearch(randomArrays[i], N[i], N[i]/2, targets[i]);
            }
            else if (j == 2) {
                linearSearch(randomArrays[i], N[i], N[i]/4, targets[i]);
            }
            else {
                linearSearch(randomArrays[i], N[i], N[i]/8, targets[i]);
            }
        }
    }


    // Binary Search
    for (int i = 0; i < SIZE_N; i++) {
        for (int j = 0; j < 4; j++) {
            if (j == 0) {
                binarySearch(randomArrays[i], N[i], 1, targets[i]);
            }
            else if (j == 1) {
                binarySearch(randomArrays[i], N[i], N[i]/2, targets[i]);
            }
            else if (j == 2) {
                binarySearch(randomArrays[i], N[i], N[i]/4, targets[i]);
            }
            else {
                binarySearch(randomArrays[i], N[i], N[i]/8, targets[i]);
            }
        }
    }

    // Jump Search
    for (int i = 0; i < SIZE_N; i++) {
        for (int j = 0; j < 4; j++) {
            if (j == 0) {
                jumpSearch(randomArrays[i], N[i], 1, targets[i]);
            }
            else if (j == 1) {
                jumpSearch(randomArrays[i], N[i], N[i]/2, targets[i]);
            }
            else if (j == 2) {
                jumpSearch(randomArrays[i], N[i], N[i]/4, targets[i]);
            }
            else {
                jumpSearch(randomArrays[i], N[i], N[i]/8, targets[i]);
            }
        }
    }


    // Delete[] all dynamically allocated arrays
    delete[] N;
    for (int i = 0; i < SIZE_N; i++) {
        delete[] randomArrays[i];
    }
    delete[] randomArrays;
    delete[] targets;

}

void createSortedArray(int* arr, int N) {
    if (N <= 0) {
        return;
    }

    bool* used = new bool[10*N]();

    for (int i = 0; i < N; i++) {
        int number;
        do {
            number = rand() % (10 * N + 1);
        } while (used[number]);  // Retry if number is not unique, was used

        used[number] = true;
        arr[i] = number;
    }
    delete[] used;

    // Sort
    mergeSort(arr, N, 0, N-1);
    
}

// Merge Sort from the slides
void mergeSort(int* arr, int N, int first, int last) {
    if (first < last) {
        int mid = (first + last)/2; // Index of midpoint
        mergeSort(arr, N, first, mid);
        mergeSort(arr, N, mid+1, last);

        // Merge the two halves
        merge(arr, N, first, mid, last);
    }

}

void merge(int* arr, int N, int first, int mid, int last) {
    int* temp = new int[N]; // Temporary array

    int first1 = first; // Beginning of first subarray
    int last1 = mid; // End of first subarray
    int first2 = mid + 1; // Beginning of second subarray
    int last2 = last; // End of second subarray
    int index = first1; // Next available location in tempArray

    for ( ; (first1 <= last1) && (first2 <= last2); ++index) {
        if (arr[first1] < arr[first2]) {
            temp[index] = arr[first1];
            ++first1;
        }
        else {
            temp[index] = arr[first2];
            ++first2;
        }
    } 

    // Finish off the first subarray, if necessary
    for (; first1 <= last1; ++first1, ++index) {
        temp[index] = arr[first1];
    }
    // Finish off the second subarray, if necessary
    for (; first2 <= last2; ++first2, ++index) {
        temp[index] = arr[first2];
    }
    // Copy the result back into the original array
    for (index = first; index <= last; ++index) {
        arr[index] = temp[index];
    }

    delete[] temp;
    
}

void targetBiggerThanLast(int* arr, int N, int K) {
    for (int j = N-K; j < N; j++) {
        cout << arr[j];
        if (j < N-1) {
            cout << ", ";
        }
    }
    cout << endl;
    cout << endl;
}

void targetSmallerThanFirst(int* arr, int K) {
    for (int j = 0; j < K; j++) {
            cout << arr[j];
            if (j < K-1) {
                cout << ", ";
            }
        }
    cout << endl;
    cout << endl;
}

void targetInBetween(int* arr, int left, int N, int K, int target) {
    int* nearest = new int[K]; // Nearest K elements array
    int count = 0;

    // left = Closest left index
    int right = left+1; // Closest right index

    while (count < K) {
        // If both left and right elements are in bounds
        if (left >= 0 && right < N) {
            // Looking at the distances of left and right elements seperately
            // We will update only one of them at a time
            int distLeft = abs(arr[left] - target);
            int distRight = abs(arr[right] - target);

            // Additionally, if the distances are the same,
            // we will get the smaller element,
            // which will always be on the left side because the array is sorted
            if (distLeft <= distRight) {
                nearest[count] = arr[left];
                count++;
                // Left index gets decremented
                left--;
            }
            else if (distRight < distLeft) {
                nearest[count] = arr[right];
                count++;
                // Right index gets incremented
                right++;
            }
        }
        // If only left elements are in bounds
        else if (left >= 0) {
            nearest[count] = arr[left];
            count++;
            left--;
        }
        // If only right elements are in bounds
        else if (right < N) {
            nearest[count] = arr[right];
            count++;
            right++;
        }
        // If both of them are out of bounds
        else {
            break;
        }
    }

    cout << "Nearest " << K << " sheep from " << target << ": ";
    for (int j = 0; j < K; j++) {
        cout << nearest[j];
        if (j < K-1) cout << ", ";
    }
    cout << endl;
    cout << endl;
    
    delete[] nearest;
    return;
}

void linearSearch(int*arr, int N, int K, int target) {
    cout << "--------------------------------------------" << endl;
    cout << "LINEAR SEARCH N = " << N << " K = " << K << endl;
    //Declare necessary variables
    std::chrono::time_point< std::chrono::system_clock > startTime;
    std::chrono::duration< double, milli > elapsedTime;
    //Store the starting time
    startTime = std::chrono::system_clock::now();
    //Code block O(N)
    for (int i = 0; i < N; i++) {
        // If target's ID is found
        if (arr[i] == target) {
            cout << target << " is alive at index " << i << endl;
            cout << endl;
            break;
        }

        // If target's ID is bigger than the last ID
        if (i == N-1 && target > arr[i]) {
            cout << "Nearest " << K << " sheep from " << target << ": ";
            targetBiggerThanLast(arr, N, K);
            break;
        }

        // If target's ID is smaller than the first ID
        else if (i == 0 && target < arr[i]) {
            cout << "Nearest " << K << " sheep from " << target << ": ";
            targetSmallerThanFirst(arr, K);
            break;
        }

        // If target's ID falls between the other ID's
        else if (i+1 < N && arr[i] < target && arr[i+1] > target) {
            targetInBetween(arr, i, N, K, target);
            break;
        }
    }

    //Compute the number of seconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took " << elapsedTime.count() << " milliseconds." << endl;
    cout << "--------------------------------------------" << endl;
    cout << endl;

}

void binarySearch(int* arr, int N, int K, int target) {
    cout << "--------------------------------------------" << endl;
    cout << "BINARY SEARCH N = " << N << " K = " << K << endl;
    //Declare necessary variables
    std::chrono::time_point< std::chrono::system_clock > startTime;
    std::chrono::duration< double, milli > elapsedTime;
    //Store the starting time
    startTime = std::chrono::system_clock::now();
    //Code block O(logN)
    int low = 0, high = N - 1;
    while ( low <= high ) {
        int mid = (low + high) / 2;
        if ( arr[ mid ] < target ) {
            low = mid + 1;
        }
        else if ( arr[ mid ] > target ) {
            high = mid - 1;
        }
        else {
            cout << target << " is alive at index " << mid << endl;
            cout << endl;
            //Compute the number of seconds that passed since the starting time
            elapsedTime = std::chrono::system_clock::now() -
            startTime;
            cout << "Execution took " << elapsedTime.count() << " milliseconds." << endl;
            return;
        }
    }

    // If target's ID is bigger than the last ID
    if (low >= N) {
        cout << "Nearest " << K << " sheep from " << target << ": ";
        targetBiggerThanLast(arr, N, K);
    }

    // If target's ID is smaller than the last ID
    else if (high < 0) {
        cout << "Nearest " << K << " sheep from " << target << ": ";
        targetSmallerThanFirst(arr, K);
    }

    // If target's ID falls between the other ID's
    else {
        // Here, parameter left will get high as its value
        // Because binary search couldn't find the target,
        // high is currently the index that is right before target
        targetInBetween(arr, high, N, K, target);
    }

    //Compute the number of seconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took " << elapsedTime.count() << " milliseconds." << endl;
    cout << "--------------------------------------------" << endl;
    cout << endl;

}

void jumpSearch(int* arr, int N, int K, int target) {
    cout << "--------------------------------------------" << endl;
    cout << "JUMP SEARCH N = " << N << " K = " << K << endl;
    //Declare necessary variables
    std::chrono::time_point< std::chrono::system_clock > startTime;
    std::chrono::duration< double, milli > elapsedTime;
    //Store the starting time
    startTime = std::chrono::system_clock::now();
    //Code block O(N^½)
    int jump = sqrt(N);
    int index = 0;
    while (index < N && arr[index] < target) {
        index += jump;
    }

    // If target's ID is bigger than the last ID
    if (index >= N) {
        cout << "Nearest " << K << " sheep from " << target << ": ";
        targetBiggerThanLast(arr, N, K);
    }

    // If target's ID is smaller than the last ID
    else if (target < arr[0]) {
        cout << "Nearest " << K << " sheep from " << target << ": ";
        targetSmallerThanFirst(arr, K);
    }

    // If target's ID falls between the other ID's
    else {
        int left = max(0, index - jump);
        int right = min(index, N - 1);

        for (int i = left; i < right; i++) {
            if (arr[i] == target) {
                cout << target << " is alive at index" << i << endl;
                cout << endl;
                //Compute the number of seconds that passed since the starting time
                elapsedTime = std::chrono::system_clock::now() -
                startTime;
                cout << "Execution took " << elapsedTime.count() << " milliseconds." << endl;
                return;
            }
            if (i + 1 < N && arr[i] < target && arr[i+1] > target) {
                left = i;
                break;
            }
        }
        targetInBetween(arr, left, N, K, target);
    }


    //Compute the number of seconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took " << elapsedTime.count() << " milliseconds." << endl;
    cout << "--------------------------------------------" << endl;
    cout << endl;

}
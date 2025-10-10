#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std;

void siftDown(vector<int>& heap, int n, int i) {

    int largest = i;
    int subRight = i*2 + 1;
    int subLeft = i*2 + 2;

    if (subLeft < n and heap[largest] < heap[subLeft]) largest = subLeft;
    if (subRight < n and heap[largest] < heap[subRight]) largest = subRight;

    if (largest != i) {
        swap(heap[largest], heap[i]);
        siftDown(heap, n, largest);
    }
}

void heapSort(vector<int>& heap) {

    int n = heap.size();

    for (int i = n / 2 - 1; i >= 0; i--) siftDown(heap, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(heap[0], heap[i]);
        siftDown(heap, i, 0);
    }
}

bool isSorted(vector<int>& arr) {

    for (int i = 1; i < arr.size() - 1; i++ ) {
        if (arr[i] < arr[i-1]) return false;
    }
    return true;
}

int main() {
    for (int i = 1; i < 10; i++) {
        string filename = "arr" + to_string(i) + ".txt";
        ifstream file(filename);
        vector<int> arr;
        int num;

        while (file >> num) arr.push_back(num);
        file.close();

        auto start = chrono::steady_clock::now();
        heapSort(arr);
        auto end = chrono::steady_clock::now();

        chrono::duration<double> duration = end-start;

        if (isSorted(arr)) {
            cout << filename << " is sorted\n";
            cout << duration.count() << "s\n\n";
        }
        else cout << filename << " is not sorted\n\n";
    }
    return 0;
}
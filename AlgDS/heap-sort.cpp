#include <iostream>
#include <vector>
#include <algorithm>

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

    vector<int> heap = {7,5,4,1,9,2,8,3,6};
    
    heapSort(heap);

    if (isSorted(heap)) cout << "array is sorted\n";
    else cout << "array is not sorted";

    for (int i = 0; i < heap.size(); i++) cout << heap[i] << " ";

    return 0;
}

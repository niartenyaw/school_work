#include "pqueue-heap.h"
#include <iostream>
using namespace std;

const static int START = 10;

HeapPQueue::HeapPQueue() {
    heap = new string[START];
    totalSize = START;
    logSize = 0;
}

HeapPQueue::~HeapPQueue() {
    delete [] heap;
}

string HeapPQueue::peek() const {
	return heap[0];
}

string HeapPQueue::extractMin() {
	string returner = heap[0];
    heapify(heap, logSize);
    logSize--;
    return returner;
}

void HeapPQueue::enqueue(const string& elem) {
    if(logSize == totalSize){ // Resizes the array
        string *newHeap = new string[totalSize*2];
        for(int i = 0; i < logSize; i++) {
            newHeap[i] = heap[i];
        }
        delete [] heap;
        heap = newHeap;
        totalSize *=2;
    }
    heap[logSize] = elem;
    logSize++;
    bubbleUp(heap, logSize-1);
}

HeapPQueue *HeapPQueue::merge(HeapPQueue *one, HeapPQueue *two) {
	HeapPQueue *newHeap = new HeapPQueue();
    string *newArray = new string[one->totalSize + two->totalSize];
    newHeap->heap = newArray;
    for(int i = 0; i < one->logSize; i++){
        newHeap->logSize++;
        newArray[i] = one->heap[i];
    }
    for(int i = 0; i < two->logSize; i++){
        newHeap->logSize++;
        newArray[i + one->logSize] = two->heap[i];
    }
    newHeap->heapify(newHeap->heap, newHeap->logSize);
    
    delete one;
    delete two;
    return newHeap;
}

bool HeapPQueue::bubbleUp(string *array, int index){
    int parentIndex = (index + 1) / 2 - 1;
    if(index == 0){
        return false;
    }
    if(array[index] > array[parentIndex]){
        return false;
    }
    else{
        string temp = array[index];
        array[index] = array[parentIndex];
        array[parentIndex] = temp;
        bubbleUp(array, parentIndex);
        return true;
    }
}

void HeapPQueue::heapify(string *array, int size){
    bool change = false;
    for(int i = size - 1; i > 0; i--){
        if(bubbleUp(array, i)) change = true;
    }
    cout << change << endl;
    if(change){
        heapify(array, size);
    }
}

void HeapPQueue::heapify(HeapPQueue *one){
    /*bool change = false;
    for(int i = one->logSize - 1; i > 0; i--){
        if(one->bubbleUp(i)) change = true;
    }
    if(change){
        one->heapify(one);
    }*/
}





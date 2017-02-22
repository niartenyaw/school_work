#include "pqueue-vector.h"
using namespace std;

VectorPQueue::VectorPQueue() {}
VectorPQueue::~VectorPQueue() {} // Made from the Vector which has a destructor in place

string VectorPQueue::peek() const {
    return queue.get(0);
}

string VectorPQueue::extractMin() {
	string min = queue.get(0);
    int index = 0;
    for(int i = 0; i < queue.size(); i++){
        if(queue[i] < min){
            min = queue[i];
            index = i;
        }
    }
    queue.remove(index);
    logSize--;
	return min;
}

void VectorPQueue::enqueue(const string& elem) {
    queue.add(elem);
    logSize++;
}

VectorPQueue *VectorPQueue::merge(VectorPQueue *one, VectorPQueue *two) {
	VectorPQueue *newVector = new VectorPQueue();
    
    for(int i = 0; i < one->queue.size(); i++){
        newVector->queue.add(one->queue.get(i));
        newVector->logSize++;
    }
    for(int i = 0; i < two->queue.size(); i++){
        newVector->queue.add(two->queue.get(i));
        newVector->logSize++;
    }
	return newVector;
}

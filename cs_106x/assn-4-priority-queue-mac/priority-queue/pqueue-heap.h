#ifndef _binary_heap_pqueue_
#define _binary_heap_pqueue_

#include "pqueue.h"
#include <string>

class HeapPQueue : public PQueue {
public:
	HeapPQueue();
	~HeapPQueue();
	
	static HeapPQueue *merge(HeapPQueue *one, HeapPQueue *two);
	
	void enqueue(const std::string& elem);
    std::string extractMin();
    std::string peek() const;
    
private:
    std::string *heap;
    int totalSize;
    
    bool bubbleUp(std::string *array, int index);
    void heapify(std::string *array, int size);
    void heapify(HeapPQueue *one);
};

#endif
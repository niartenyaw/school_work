#ifndef _binomial_heap_pqueue_
#define _binomial_heap_pqueue_

#include "pqueue.h"
#include <string>
#include "vector.h"

class BinomialHeapPQueue : public PQueue {
public:
	BinomialHeapPQueue();
	~BinomialHeapPQueue();
	
	static BinomialHeapPQueue *merge(BinomialHeapPQueue *one, BinomialHeapPQueue *two);
	
	void enqueue(const std::string& elem);
    std::string extractMin();
    std::string peek() const;
	
private:
    struct node {
        std::string elem;
        Vector<node *> children;
    };
    
    Vector<node *> queue; // Sorted by their order (index)
    
    void add(Vector<node *>& vector, node *tree, int order);
};

#endif

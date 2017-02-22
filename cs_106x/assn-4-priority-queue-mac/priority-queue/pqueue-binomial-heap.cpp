#include "pqueue-binomial-heap.h"
using namespace std;

BinomialHeapPQueue::BinomialHeapPQueue() {}

BinomialHeapPQueue::~BinomialHeapPQueue() {}

string BinomialHeapPQueue::peek() const {
    string returner = queue.get(0)->elem;
    for(int i = 1; i < queue.size(); i++){
        if(queue.get(i)->elem < returner){
            returner = queue.get(i)->elem;
        }
    }
    return returner;
}

string BinomialHeapPQueue::extractMin() {
    int index = 0;
    string returner = queue.get(0)->elem;
    for(int i = 1; i < queue.size(); i++){
        if(queue.get(i)->elem < returner){
            returner = queue.get(i)->elem;
            index = i;
        }
    }
    if(queue[index]->children.isEmpty()){
        queue[index] = NULL;
    }
    else{
        Vector<node *> temp;
        for(int i = 0; i < queue[index]->children.size(); i++){
            temp[i] = queue[index]->children[i];
        }
        queue[index] = NULL;
        for(int i = 0; i < temp.size(); i++){
            add(queue, temp[i], i);
        }
    }
    logSize--;
	return returner;
}

void BinomialHeapPQueue::enqueue(const string& elem) {
    node *tree = new node;
    tree->elem = elem;
    add(queue, tree, 0);
    logSize++;
}

BinomialHeapPQueue *BinomialHeapPQueue::merge(BinomialHeapPQueue *one, BinomialHeapPQueue *two) {
	// placeholder so method compiles..
	// replace with your own implementation
	return new BinomialHeapPQueue();
}

void BinomialHeapPQueue::add(Vector<node *>& vector, node *tree, int order){
    if(queue.size() == order){
        queue.add(tree);
        return;
    }
    if(queue[order] == NULL){
        queue[order] = tree;
        return;
    }
    if(queue[order]->elem < tree->elem){
        node *temp = queue[order];
        temp->children.add(tree);
        add(temp->children, tree, order);
        queue[order] = NULL;
        add(vector, temp, order++);
    }
}


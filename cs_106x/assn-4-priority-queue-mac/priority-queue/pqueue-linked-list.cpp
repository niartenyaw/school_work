#include "pqueue-linked-list.h"
#include <iostream>
using namespace std;

LinkedListPQueue::LinkedListPQueue() {
    head = new cell;
    size = 0;
}

LinkedListPQueue::~LinkedListPQueue() {
    for(cell *curr = head; curr != NULL; head = head->next){
        cell *next = curr->next;
        delete curr;
        curr = next;
    }
}

string LinkedListPQueue::peek() const {
	return head->cellString;
}

string LinkedListPQueue::extractMin() {
    cell *temp = head->next;
    string returner = head->cellString;
    delete head;
    head = temp;
    if(head != NULL){
        head->prev = NULL;
    }
    size--;
    logSize--;
	return returner;
}

void LinkedListPQueue::enqueue(const string& elem) {
    if(size == 0){
        head->cellString = elem;
        size++;
        logSize++;
        return;
    }
    cell *adder = new cell;
    adder->cellString = elem;
    cell *curr = head;
    while(true){
        if(adder->cellString < curr->cellString){
            cell *post = curr;
            cell *pre = curr->prev;
            
            if(pre != NULL){
                pre->next = adder;
                adder->prev = pre;
            }
            adder->next = post;
            post->prev = adder;
            size++;
            logSize++;
            return;
        }
        if(curr->next == NULL){
            curr->next = adder;
            size++;
            logSize++;
            return;
        }
        curr = curr->next;
    }
}

LinkedListPQueue *LinkedListPQueue::merge(LinkedListPQueue *one, LinkedListPQueue *two) {
	LinkedListPQueue *beginning;
    cell *curr;
    cell *next1 = one->head;
    cell *next2 = two->head;
    bool oneUsed;
    if(one->head->cellString < two->head->cellString){ // Determines which PQueue to start with.
        curr = one->head;
        beginning = one;
        next1 = next1->next;
        oneUsed = true;
    }
    else{
        curr = two->head;
        beginning = two;
        next2 = next2->next;
        oneUsed = false;
    }
    beginning->logSize = 1;
    while(true){
        if(next1->cellString < next2->cellString){
            curr->next = next1;
            next1->prev = curr;
            curr = next1;
            next1 = next1->next;
        }
        else{
            curr->next = next2;
            next2->prev = curr;
            curr = next2;
            next2 = next2->next;
        }
        beginning->logSize++;
        
        if(next1 == NULL){ // Checks if one of the lists has been exhausted
            curr->next = next2;
            next2->prev = curr;
            curr = next2;
            while(curr != NULL){ // Makes sure logSize is correct.
                beginning->logSize++;
                curr = curr->next;
            }
            return beginning;
        }
        if(next2 == NULL){
            curr->next = next1;
            next1->prev = curr;
            curr = next1;
            while(curr != NULL){
                beginning->logSize++;
                curr = curr->next;
            }
            return beginning;
        }
    }
}


/**
 * File: pqueue-impl.h
 * Original implementation by eroberts
 * Last modified on Sat Nov 03 16:33:00 PST 2012 by jcain
 * -------------------
 * This file provides a Vector-based implementation of the
 * pqueue.h interface.
 */

/**
 * Implementation notes: PQueue constuctor and destructor
 * ------------------------------------------------------
 * All the work for the constructor and destructor is done by the
 * Vector class.
 */

template <typename Type>
PQueue<Type>::PQueue() {}

template <typename Type>
PQueue<Type>::~PQueue() {}

/**
 * Implementation notes: size, isEmpty, clear
 * ------------------------------------------
 * These implementations simply forward the request to the
 * underlying Vector object.
 */

template <typename Type>
int PQueue<Type>::size() const {
    return entries.size();
}

template <typename Type>
bool PQueue<Type>::isEmpty() const {
    return entries.isEmpty();
}

/**
 * Implementation notes: enqueue
 * -----------------------------
 * This function finds where to insert a new element into the
 * queue and then calls insertAt to put it there.  Because
 * items are removed from the end of the queue, the highest
 * priority elements must be stored at the end of the queue.
 * Moreover, to ensure that elements obey the first-in/first-out
 * discipline when they have the same priority, the function must
 * insert each new element before any with the same priority.
 * Keep in mind that the base type of the vector is pqEntryT,
 * which contains both the element and the priority.
 */

template <typename Type>
void PQueue<Type>::enqueue(const Type& elem, double priority) {
    int pos = 0;
    while (pos < entries.size() && entries[pos].priority > priority) {
        pos++;
    }
    entry ent = {elem, priority};
    entries.insert(pos, ent);
}

/**
 * Implementation notes: extractMin, peek
 * --------------------------------------
 * These functions must check for an empty queue and report an
 * error if there are no entries.
 */

template <typename Type>
Type PQueue<Type>::extractMin() {
    if (isEmpty()) error("extractMin: Attempting to extractMin from an empty queue.");
	int lastIndex = entries.size() - 1;
	Type result = entries[lastIndex].elem;
	entries.remove(lastIndex);
    return result;
}

template <typename Type>
const Type& PQueue<Type>::peek() const {
    if (isEmpty()) error("peek: Attempting to peek at an empty queue.");
    return entries[entries.size() - 1].elem;
}


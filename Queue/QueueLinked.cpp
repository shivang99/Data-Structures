//Name: Shivang Trivedi
//Date: March 5, 2019
//Lab: 7 - take home
#include "QueueLinked.h"

template <typename DataType>
QueueLinked<DataType>::QueueNode::QueueNode(const DataType& nodeData, QueueNode* nextPtr)
{
	//set the items
	dataItem = nodeData;
	next = nextPtr;
}

template <typename DataType>
QueueLinked<DataType>::QueueLinked(int maxNumber)
{
	//initialize all variables
	maxNumber = QueueLinked<DataType>::MAX_QUEUE_SIZE;
	front = NULL;
	back = NULL;
}

template <typename DataType>
QueueLinked<DataType>::QueueLinked(const QueueLinked& other)
{
	//set other to this
	QueueNode *otherPtr = other.front;
	front = other.front;
	back = other.back;
	while (otherPtr != 0) {
		enqueue(other->dataItem);
		otherPtr = otherPtr->next;
	}
}

template <typename DataType>
QueueLinked<DataType>& QueueLinked<DataType>::operator=(const QueueLinked& other)
{
	//overload operator=
	QueueNode* otherPtr = other.front;
	front = new QueueNode;
	front = otherPtr->dataItem;
	front->next = NULL;
	QueueNode* thisPtr = front;
	otherPtr = otherPtr->next;
	while (otherPtr != NULL)
	{
		QueueNode* newNode = new QueueNode(otherPtr->dataItem, NULL);
		thisPtr->next = newNode;
		thisPtr = newNode;
		back = newNode;
		otherPtr = otherPtr->next;
	}
}
	
template <typename DataType>
QueueLinked<DataType>::~QueueLinked()
{
	//clear space in memory
	QueueNode *x;
	//delete each node until it equals to 0
	while (front != NULL) {
		x = front;
		front = front->next;
		delete x;
	}
}

template <typename DataType>
void QueueLinked<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
{
	//insert data into the queue
	if (isFull()) {
		throw logic_error("List is full\n");
	}
	QueueNode* newNode = new QueueNode(newDataItem, 0);
	newNode->next = NULL;
	//if queue is empty, set the front and back to the new node and next pointer of back to NULL
	if(front == NULL) {
		front = back = newNode;
		back->next = NULL;
	}
	//if queue is not empty, add node to the back
	else {
		back->next = newNode;
		back = newNode;
		back->next = NULL;
	}




}

template <typename DataType>
DataType QueueLinked<DataType>::dequeue() throw (logic_error)
{
	if (isEmpty()) {
		throw logic_error("List is empty\n");
	}
	else {
		DataType temp = front->dataItem;
		QueueNode *x = front;
		//if only one node, set front and back to NULL
		if (front == back) {
		front = back = NULL;
		}
		//if more than one node, set front to the next node
		else {
			front = front->next;
		}
		//delete the front by an x pointer that points to front
		delete x;
		return temp;
	}
}

template <typename DataType>
void QueueLinked<DataType>::clear()
{
	QueueNode *x;
	//delete each node until it equals to 0
	while (front != NULL) {
		x = front;
		front = front->next;
		delete x;
	}
}

template <typename DataType>
bool QueueLinked<DataType>::isEmpty() const
{
	//when front is NULL no nodes are enqueued
	return (front == NULL);
}

template <typename DataType>
bool QueueLinked<DataType>::isFull() const
{
	//one of the ways to implement this function
	return false;
}

template <typename DataType>
void QueueLinked<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
{
	//not using
}

template <typename DataType>
DataType QueueLinked<DataType>::getRear() throw (logic_error)
{
	//not using
	DataType temp;
	return temp;
}

template <typename DataType>
int QueueLinked<DataType>::getLength() const
{
	//set up a counter, a temp node, treverse through the list and add to the counter until end of queue
	int count = 0;
	QueueNode *temp;
	temp = front;
	while (temp != NULL) {
		count++;
		temp = temp->next;
	}
	return count;
}

template <typename DataType>
void QueueLinked<DataType>::showStructure() const
{
    QueueNode *p;   // Iterates through the queue

    if ( isEmpty() )
	cout << "Empty queue" << endl;
    else
    {
	cout << "Front\t";
	for ( p = front ; p != 0 ; p = p->next )
	{
	    if( p == front ) 
	    {
		cout << '[' << p->dataItem << "] ";
	    }
	    else
	    {
		cout << p->dataItem << " ";
	    }
	}
	cout << "\trear" << endl;
    }
}
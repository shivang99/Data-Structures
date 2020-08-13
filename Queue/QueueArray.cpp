
#include "QueueArray.h"

template <typename DataType>
QueueArray<DataType>::QueueArray(int maxNumber)
{
	//initialize all variables and allocate memory for dataItems
	maxSize = maxNumber;
	front = -1;
	back = -1;
	dataItems = new DataType[maxSize];
}

template <typename DataType>
QueueArray<DataType>::QueueArray(const QueueArray& other)
{
	//set other maxSize to this
	maxSize = other.maxSize;
	front = other.front;
	back = other.back;
	dataItems = new DataType[maxSize];
	
	for (int x = 0; x < maxSize; x++) {
		dataItems[x] = other.dataItems[x];
	}
}

template <typename DataType>
QueueArray<DataType>& QueueArray<DataType>::operator=(const QueueArray& other)
{

	//check if this maxSize is less than other to have enough space for data
	if (other.maxSize > maxSize) {
		delete[]dataItems;
		dataItems = new DataType[other.maxSize];
	}
	//deep copy from the other to this dataItems
	for (int x = 0; x < maxSize; x++) {
		dataItems[x] = other.dataItems[x];
	}
	//return this
	return *this;
}

template <typename DataType>
QueueArray<DataType>::~QueueArray()
{
	//delete the array
	delete[]dataItems;
}


template <typename DataType>
void QueueArray<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
{
	if (isEmpty()) {
		front = 0;
	}
	else if (isFull()) {
		throw logic_error("The list is full\n");
	}
		//add the dataItem at the back
		back = (++back) % maxSize;
		dataItems[back] = newDataItem;

}

template <typename DataType>
DataType QueueArray<DataType>::dequeue() throw (logic_error)
{
	if (isEmpty()) {
		throw logic_error("The is empty\n");
	}
	DataType temp = dataItems[front];
	if (front == back) {
		front = -1;
		back = -1;
	}
	else {
		front = (front + 1) % maxSize;
	}
	return temp;
	
}

template <typename DataType>
void QueueArray<DataType>::clear()
{
	front = -1;
	back = -1;
}

template <typename DataType>
bool QueueArray<DataType>::isEmpty() const
{
	return (front==-1);
}

template <typename DataType>
bool QueueArray<DataType>::isFull() const
{
	return ((back + 1) % maxSize == front);
}

template <typename DataType>
void QueueArray<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
{

}

template <typename DataType>
DataType QueueArray<DataType>::getRear() throw (logic_error)
{
	DataType temp;
	return temp;
}

template <typename DataType>
int QueueArray<DataType>::getLength() const
{
	return -1;
}

//--------------------------------------------------------------------

template <typename DataType>
void QueueArray<DataType>::showStructure() const 
// Array implementation. Outputs the data items in a queue. If the
// queue is empty, outputs "Empty queue". This operation is intended
// for testing and debugging purposes only.

{
    int j;   // Loop counter

    if ( front == -1 )
       cout << "Empty queue" << endl;
    else
    {
       cout << "Front = " << front << "  Back = " << back << endl;
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       if ( back >= front )
          for ( j = 0 ; j < maxSize ; j++ )
              if ( ( j >= front ) && ( j <= back ) )
                 cout << dataItems[j] << "\t";
              else
                 cout << " \t";
       else
          for ( j = 0 ; j < maxSize ; j++ )
              if ( ( j >= front ) || ( j <= back ) )
                 cout << dataItems[j] << "\t";
              else
                 cout << " \t";
       cout << endl;
    }
}
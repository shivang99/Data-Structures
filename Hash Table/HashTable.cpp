
#include "HashTable.h"

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(int initTableSize)
{
	tableSize = initTableSize;
	dataTable = new BSTree<DataType, KeyType>[tableSize];

}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(const HashTable& other)
{
	
	tableSize = other.tableSize;
	copyTable(other);

}

template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>& HashTable<DataType, KeyType>::operator=(const HashTable& other)
{
	if (this != other) {
		clear();
		tableSize = other.tableSize;
		dataTable = new BSTree<DataType, KeyType>[tableSize];
		copyTable(other);
	}

	return *this;

}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::~HashTable()
{
	clear();

}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem)
{
	int insertAt;
	insertAt = newDataItem.hash(newDataItem.getKey()) % tableSize;
	dataTable[insertAt].insert(newDataItem);
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::remove(const KeyType& deleteKey)
{
	DataType temp;
	int delAt = temp.hash(deleteKey) % tableSize;

	return(dataTable[delAt].remove(deleteKey));
	
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& returnItem) const
{
	int foundAt;
	foundAt = returnItem.hash(searchKey) % tableSize;

	return (dataTable[foundAt].retrieve(searchKey, returnItem));
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::clear()
{
	for (int x = 0; x < tableSize; x++) {
		dataTable[x].clear();
	}
	
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::isEmpty() const
{
	bool emp = true;

	for (int x = 0; x < tableSize; x++) {
		if (!dataTable[x].isEmpty()) {
			emp = false;
		}
	}

	return emp;
}


template <typename DataType, typename KeyType>
double HashTable<DataType, KeyType>::standardDeviation() const
{

	double sum = 0, average = 0, num = 0, count = 0;
	for (int x = 0; x < tableSize; x++) {
		sum += dataTable[x].getCount();
	}
	average = sum / tableSize;
	sum = 0;
	for (int x = 0; x < tableSize; x++) {
		count = dataTable[x].getCount();
		num = pow((count - average), 2);
		sum += num;
	}
	num = sum / (tableSize - 1);

	return (sqrt(num));
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::copyTable(const HashTable& source)
{

	for (int x = 0; x < tableSize; x++) {
		dataTable[x] = source[x];
	}
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::showStructure() const {
	for (int i = 0; i < tableSize; ++i) {
		cout << i << ": ";
		dataTable[i].writeKeys();
		cout << endl;
	}
}
#include "ListLinked.h"
#include "iostream"
//Name: Shivang Trivedi
//Date: Jan 30, 2019
template<typename DataType>
inline List<DataType>::List(int ignored)
{
	//initialize to null
	head = NULL;
	cursor = NULL;
}

template<typename DataType>
List<DataType>::List(const List & other)
{
	//create a new listnode type and set it to others 
	ListNode *otherPtr = other.head;
	ListNode *holdCursor = 0;
	//while the other is not zero, insert the new item
	while (otherPtr != 0) {
		insert(other->dataItem);
		if (otherPtr == other.cursor)
			holdCursor = cursor;
		otherPtr = otherPtr->next;
	}
	//update cursor
	cursor = holdCursor;
}

template<typename DataType>
List<DataType>& List<DataType>::operator=(const List & other)
{
	//if they are not the same then copy it
	if (this != other) {
		ListNode *otherPtr = other.head;
		ListNode *holdCursor = 0;
		//while other pointer is not zero, copy each cursor from other
		while (otherPtr != 0) {
			insert(other->dataItem);
			if (otherPtr == other.cursor)
				holdCursor = cursor;
			otherPtr = otherPtr->next;
		}
		//update cursor
		cursor = holdCursor;
	}
	return *this;
}


template<typename DataType>
List<DataType>::~List()
{
	//set cursor to head
	cursor = head;
	ListNode *x;
	//delete each node until it equals to 0
	while (cursor != 0) {
		x = cursor;
		cursor = cursor->next;
		delete x;
	}

}

template<typename DataType>
void List<DataType>::insert(const DataType & newDataItem) throw(logic_error)
{
	//if the list is empty, set the head to newDataItem
	if (head == NULL) {
		head = new ListNode(newDataItem, 0);
		cursor = head;
	}
	else {
		//insert a new node
		ListNode *temp;
		temp = new ListNode(newDataItem, 0);
		if (cursor->next == 0) {
			cursor->next = temp;
			//update cursor
			cursor = cursor->next;
		}
		else {
			//if the cursor is in the middle of the list, add temp in the middle after the cursor
			temp->next = cursor->next;
			cursor->next = temp;
			cursor = temp;
		}
		
	}
}

template<typename DataType>
void List<DataType>::remove() throw(logic_error)
{
	ListNode *p, *q;
	if (head == NULL) {
		throw logic_error("List is empty\n");
	}
	else {
		//if cursor at the beginning, set p to head and change head and cursor to the next node and delete p
		if (cursor == head) {
			p = head; 
			head = cursor->next;
			cursor = cursor->next;
			delete p;
		}
		/*if the cursor is at the end, set p to cursor and cursor to head and go through 
		the list and set q to cursor and point q to NULL */
		else if (cursor->next == 0) {
			p = cursor;
			cursor = head;
			while (cursor->next != p) {
				cursor = cursor->next;
			}
			q = cursor;
			q->next = NULL;
			delete p;
			cursor = head;
		}
		/*if the cursor is somewhere in the middle of the list, set p to cursor and cursor to head
		go through the list until it reaches the node before p, set q to that and set q pointer to p ponter
		and cursor to p pointer.*/
		else {
			p = cursor;
			cursor = head;
			while (cursor->next != p) {
				cursor = cursor->next;
			}
			q = cursor;
			q->next = p->next;
			cursor = p->next;
			delete p;
		}
	}
}

template<typename DataType>
void List<DataType>::replace(const DataType & newDataItem) throw(logic_error)
{
	//check if the list is empty or not
	if (head == NULL) {
		throw logic_error("List is empty\n");
	}
	else {
		//replace current item with new item
		cursor->dataItem = newDataItem;
	}
}

template<typename DataType>
void List<DataType>::clear()
{
	//set cursor to head
	cursor = head;
	ListNode *x;
	//delete each node until it equals to 0
	while (cursor != 0) {
		x = cursor;
		cursor = cursor->next;
		delete x;
	}
	//reset variables
	head = NULL;
	cursor = NULL;
}

template<typename DataType>
bool List<DataType>::isEmpty() const
{
	//if head is null it returns true, else false
	if (head == NULL) {
		return true;
	}
	else {
		return false;
	}
}

template<typename DataType>
bool List<DataType>::isFull() const
{
	return false;
}

template<typename DataType>
void List<DataType>::gotoBeginning() throw(logic_error)
{
	//check if the list is empty
	if (head == NULL) {
		throw logic_error("List is empty\n");
	}
	else{
		//set the cursor to the first node
		cursor = head;
	}
}

template<typename DataType>
void List<DataType>::gotoEnd() throw(logic_error)
{
	//check if the list is empty
	if (head == NULL) {
		throw logic_error("List is empty\n");
	}
	else {
		//keep updating the cursor until it reaches the last node
		while (cursor->next != 0) {
			cursor = cursor->next;
		}
	}
}

template<typename DataType>
bool List<DataType>::gotoNext() throw(logic_error)
{
	//throw error if list if empty
	if (head == NULL) {
		throw logic_error("List is empty\n");
	}
	//check if this is the last node in the list
	else if (cursor->next == 0) {
		return false;
	}
	else {
		//move cursor to the next node
		cursor = cursor->next;
		return true;
	}
}

template<typename DataType>
bool List<DataType>::gotoPrior() throw(logic_error)
{
	//check if the list is empty
	if (head == NULL) {
		throw logic_error("List is empty\n");
	}
	//check if the cursor is pointing to the first node
	else if(cursor == head)
		return false;
	else {
		//create a temp variable and set that to head and go through the list until the next node is temp
		ListNode *temp = cursor;
		cursor = head;
		while (cursor->next!= temp) {
			cursor = cursor->next;
		}
	}

}

template<typename DataType>
void List<DataType>::moveToBeginning() throw(logic_error)
{
	//if list is empty, throw logic error
	if (isEmpty())
		throw logic_error("list is empty\n");
	else {
		/*add current cursor data item to the new node, set the next pointer to head 
		and set head to temp and remove current cursor and set cursor to head*/
		ListNode *temp = new ListNode(cursor->dataItem, 0);
		temp->next = head;
		head = temp;
		remove();
		cursor = head;
	}
}

template<typename DataType>
void List<DataType>::insertBefore(const DataType & newDataItem) throw(logic_error)
{
	if (isFull())
		throw logic_error("List is full\n");
	else {
		//sets the cursor to the beginning
		gotoPrior();
		//if the cursor is at the head
		if (cursor == head) {
			//add data item to the new node, set the next pointer to head and set head to temp and cursor to head
			ListNode *temp = new ListNode(newDataItem, 0);
			temp->next = head;
			head = temp;
			cursor = head;
		}
		else {
			insert(newDataItem);
		}
	}
}



template<typename DataType>
DataType List<DataType>::getCursor() const throw(logic_error)
{
	//check if the list is empty
	if (head == NULL) {
		throw logic_error("List is empty\n");
	}
	//return the dataItem at cursor
	else {
		return cursor->dataItem;
	}
}

template<typename DataType>
inline List<DataType>::ListNode::ListNode(const DataType & nodeData, ListNode * nextPtr)
{
	//set nodeData to dataItem and nextPtr to next
	dataItem = nodeData;
	next = nextPtr;
}
template <typename DataType>
void List<DataType>::showStructure() const

// Outputs the items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.

{
	if (isEmpty())
	{
		cout << "Empty list" << endl;
	}
	else
	{
		if (isEmpty())
		{
			cout << "Empty list" << endl;
		}
		else
		{
			for (ListNode* temp = head; temp != 0; temp = temp->next) {
				if (temp == cursor) {
					cout << "[";
				}

				// Assumes that dataItem can be printed via << because
				// is is either primitive or operator<< is overloaded.
				cout << temp->dataItem;

				if (temp == cursor) {
					cout << "]";
				}
				cout << " ";
			}
			cout << endl;
		}
	}
}
template<typename DataType>
void List<DataType>::removeElement(int val)
{
	cursor = head;
	while (cursor != NULL) {
		int num = cursor->dataItem;
		if (num == val) {
			ListNode *p, *q;
			//if cursor at the beginning, set p to head and change head and cursor to the next node and delete p
			if (cursor == head) {
				p = head;
				head = cursor->next;
				cursor = cursor->next;
				delete p;
			}
			/*if the cursor is at the end, set p to cursor and cursor to head and go through
			the list and set q to cursor and point q to NULL */
			else if (cursor->next == 0) {
				p = cursor;
				cursor = head;
				while (cursor->next != p) {
					cursor = cursor->next;
				}
				q = cursor;
				q->next = NULL;
				delete p;
				cursor = cursor->next;
			}
			/*if the cursor is somewhere in the middle of the list, set p to cursor and cursor to head
			go through the list until it reaches the node before p, set q to that and set q pointer to p ponter
			and cursor to p pointer.*/
			else {
				p = cursor;
				cursor = head;
				while (cursor->next != p) {
					cursor = cursor->next;
				}
				q = cursor;
				q->next = p->next;
				cursor = p->next;
				delete p;
			}
		}
		else {
			cursor = cursor->next;
		}
	}

}

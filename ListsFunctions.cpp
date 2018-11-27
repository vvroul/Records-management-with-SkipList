#include <iostream>
#include "GeneralList.h"

using namespace std;


GeneralList::GeneralList()		
{
	header = NULL;
	cout << "GeneralList initialized successfully!" << endl << endl;		
}



GeneralList::~GeneralList()
{
	cout << "Processing general list completed." << endl;
}



ListNode* GeneralList::getNode() 
{
	return header;
}



void GeneralList::PrintData()
{
	ListNode* node = new ListNode();
	node = header;
	int counter = 1;
	while (node->getNext() != NULL)
	{
		cout << "Item " << counter << " in list : " << node->getKey() << " with times : " << node->getTimes() << endl;
		node = node->getNext();
		++counter;
	}

	cout << "Item " << counter << " in list : " << node->getKey() << endl;
}



int GeneralList::Exists(int item)
{
    ListNode* node = header;
    
    while (node != NULL) 
    {
        if(node->getKey() == item)
        {
            return 1;
        }
        node = node->getNext();
    }
    return 0;
}



ListNode* GeneralList::Search(int item)
{
    ListNode* node = header;
    
    while (node != NULL) 
    {
        if(node->getKey() == item)
        {
            return node;
        }
        node = node->getNext();
    }
    return NULL;
}



void GeneralList::Insert(int newItem)
{

	ListNode* node = new ListNode();

	if (Exists(newItem) == 1)
	{
		node = Search(newItem);
		int theTimes = node->getTimes();
		node->setTimes(++theTimes);
		return;
	}
	else
	{
		node->setKey(newItem);
		node->setTimes(1);
		node->setNext(NULL);

		if (header == NULL)
	    {
			header = node;
	    }
		else
		{
			ListNode* tail = header;
			while (tail->getNext() != NULL)
			{
				tail = tail->getNext();
			}
			tail->setNext(node);
		}
		//cout << "Item inserted : " << newItem << endl;
	}
}
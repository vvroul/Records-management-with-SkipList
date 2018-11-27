#include <iostream>
#include "HashTable.h"
#include "Declars.h"

using namespace std;

extern "C"
{
    #include <stdlib.h>
}



HashTable::HashTable()
{
	hashArray = new HashList*[hashSize];
	for (int i = 0; i < hashSize; ++i)
	{
	    hashArray[i] = NULL;
	}

	cout << "Hash table initialized successfully!" << endl;
}



HashTable::HashTable(int hashSize)
{
    this->hashSize = hashSize;
    hashArray = new HashList*[hashSize];
    for (int i = 0; i < hashSize; ++i)
    {
        hashArray[i] = NULL;
    }

    cout << "Hash table initialized successfully!" << endl;
}



HashTable::~HashTable() 
{
    for (int i = 0; i < hashSize; i++)
    {
	    if (hashArray[i] != NULL) 
		{
	   		HashList *prev = NULL;
	      	HashList *list = hashArray[i];
	      	while (list != NULL) 
	      	{
	        	prev = list;
	           	list = list->getNext();
	           	delete prev;
	      	}
		}
	}

    std::cout << "Processing hash hashArray completed." << std::endl;
}



Record* HashTable::GetRecord(int key) 
{
    int hashValue = HashFunction(key);
    if (hashArray[hashValue] == NULL)
    {
    	return NULL;
    }
    else 
    {
		HashList *list = hashArray[hashValue];
		while ((list != NULL) && (list->getKey() != key))
      	{
	    	list = list->getNext();
      	}
		if (list != NULL)
      	{
            //cout << "The record: " << list->getRecord()->lastname << endl;
	   		return list->getRecord();
      	}
		else
        {
	    	return NULL;
        }
    }
}



float HashTable::FindAverageGPA(int key) 
{
    int hashValue = HashFunction(key);
    float theGPA, sumGPA;
    int count = 0;
    if (hashArray[hashValue] == NULL)
    {
        return 0.0f;
    }
    else 
    {
        HashList *list = hashArray[hashValue];
        while (list != NULL)
        {
            if (list->getKey() == key)
            {
                //cout << "The record : " << list->getRecord()->gpa << endl;
                sumGPA = sumGPA + list->getRecord()->gpa;
                ++count;
            }
            list = list->getNext();
        }
    }

    theGPA = sumGPA / count;
    return theGPA;
}



HashList* HashTable::FindK(int key) 
{
    int hashValue = HashFunction(key);
    if (hashArray[hashValue] == NULL)
    {
        return NULL;
    }
    else 
    {
        HashList* list = hashArray[hashValue];
        while (list != NULL)
        {
            if (list->getKey() == key)
            {
                return list;
            }
            list = list->getNext();
        }
    }
}



HashList* getTail(HashList* current)
{
    while ((current != NULL) && (current->getNext() != NULL))
    {
        current = current->getNext();
    }
    return current;
}



void HashTable::QuickSortGPA(HashList** head_ref)
{

    HashList *head1, *head2, *pivot, *tail;

    if((*head_ref == NULL) || ((*head_ref)->getNext() == NULL)) 
    {
    	return;
    }

    pivot = partitionGPA(*head_ref, &head1, &head2);
    QuickSortGPA(&head1);
    QuickSortGPA(&head2);

    if(head1 != NULL)
    {
	    tail = getTail(head1);
	    tail->setNext(pivot);
    }
    pivot->setNext(head2);

    if (head1 == NULL)
    {
    	*head_ref = pivot;
    }
    else
    {
    	*head_ref = head1;
    }
}



HashList* partitionGPA(HashList* head, HashList** head1_ref, HashList** head2_ref)
{
    HashList* temp1 = head;
    HashList* temp2 = head;
    HashList* pivot = head;
    HashList* t;

    while(temp2->getNext() != NULL)
    {
    	if(temp2->getNext()->getRecord()->gpa > pivot->getRecord()->gpa)
    	{
    		if(temp1 == temp2)
    		{
    			temp1 = temp1->getNext();
    			temp2 = temp2->getNext();
    		}
    		else
    		{
	    		t = temp1->getNext();
	    		temp1->setNext(temp2->getNext());
	    		temp2->setNext(temp2->getNext()->getNext());
	    		temp1 = temp1->getNext();
	    		temp1->setNext(t);
	    	}
    	}
    	else
        {
    		temp2 = temp2->getNext();
        }
    }

    *head2_ref = temp1->getNext();
    temp1->setNext(NULL);
    *head1_ref = head->getNext();

    return pivot;
}



void HashTable::PutRecord(int key, Record* newRecord) 
{
	int hashValue = HashFunction(key);
	HashList* prev = NULL;
    HashList* list = hashArray[hashValue];

    while (list != NULL)
    {
        prev = list;
        list = list->getNext();
    }
    if (list == NULL)
    {
        list = new HashList(key, newRecord);

        if (prev == NULL)
        {
            hashArray[hashValue] = list;
        }
        else
        {
            prev->setNext(list);
        }
    }
    else
    {
        list->setRecord(newRecord);
    }

    //cout << "Item inserted in hash table with hash : " << hashValue <<endl;
}



void HashTable::Remove(int key) 
{
    int hashValue = HashFunction(key);
    if (hashArray[hashValue] != NULL) 
    {
    	HashList *prev = NULL;
        HashList *list = hashArray[hashValue];
        while ((list->getNext() != NULL) && (list->getKey() != key)) 
        {
        	prev = list;
            list = list->getNext();
        }
        if (list->getKey() == key) 
        {
        	if (prev == NULL) 
            {
            	HashList *next= list->getNext();
                delete list;
                hashArray[hashValue] = next;
            } 
            else 
            {
            	HashList *_next = list->getNext();
                delete list;
            	prev->setNext(_next);
            }
        }
    }
}



int HashTable::HashFunction(int key)
{
    return key % hashSize;
}


HashList** HashTable::getArray()
{
    return hashArray;
}


void HashTable::setArray(HashList** hashArray)
{
    this->hashArray = hashArray;
}


HashList* HashTable::getList()
{
    return *hashArray;
}


void HashTable::setList(HashList* table)
{
    *hashArray = table;
}
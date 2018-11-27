#include <iostream>
#include "SkipList.h"
#include "Declars.h"

using namespace std;

extern "C"
{
    #include <stdio.h>
    #include <stdlib.h>
}



SkipList::SkipList()
{
	/*
		Skip list initialization
	*/
	header = new Node();
	terminatingNode = new Node();
	terminatingNode->setKey(MaxValue);

	//Header and Terminating nodes have MaxLevel forward pointers
	header->setForward(new Node*[MaxNumOfPointers]);
	terminatingNode->setForward(new Node*[MaxNumOfPointers]);

	//All forward pointers of terminating node, point to NULL
	for (int i = 0; i < MaxNumOfPointers; ++i)
	{
		terminatingNode->getForward()[i] = NULL;	
	}

	//At start, header node pointers, point to terminating node
	for (int i = 0; i < MaxNumOfPointers; ++i)
	{
		header->getForward()[i] = terminatingNode;
	}

	cout << "Skip list initialized successfully!" << endl;
}



SkipList::SkipList(const SkipList& list)
{
    /*cout << "Copy constructor allocating" << endl;
    header = new Node();
    terminatingNode = new Node();
    terminatingNode->key = MaxValue;
    header->forward = new Node*[MaxNumOfPointers];
    terminatingNode->forward = new Node*[MaxNumOfPointers];

    for (int i = 0; i < MaxNumOfPointers; ++i)
    {
    	terminatingNode->forward[i] = NULL;	
    }

    for (int i = 0; i < MaxNumOfPointers; ++i)
    {
    	header->forward[i] = terminatingNode;
    }

    Node* x = new Node();
    x = list.header;
 
    for (int i = 0; i < MaxNumOfPointers; ++i)
    {
    	while(x->getForward()[i]->getKey() != MaxValue)
    	{
    		header->forward[i] = x->getForward()[i];
    		x = x->getForward()[i];
    	}

    	if (x->getForward()[i]->getKey() == MaxValue)
    	{
    		break;
    	}
    }*/
}



SkipList::~SkipList()
{

	/*Node* x = new Node();
	x = header;
	
	for (int i = 0; i < MaxNumOfPointers; ++i)
	{
		while(x->getForward()[i]->getKey() != MaxValue)
		{
			x = x->getForward()[i];
			Node* y = x;
			x = x->getForward()[i];
			delete y;

			if (x->getForward()[i] == NULL)
			{
				break;
			}
		}
	}*/

	delete header;
	delete terminatingNode;
	std::cout << "Processing skip list completed." << std::endl;
}



Record* SkipList::Search(int searchKey)
{
	Node* x = new Node();
	x = header;
	for (int i = MaxNumOfPointers-1; i >= 0; --i)
	{
		while(x->getForward()[i]->getKey() < searchKey)
		{
			x = x->getForward()[i];
		}
	}
	x = x->getForward()[0];
	if (x->getKey() == searchKey)
	{
		//cout << "KEY FOUND IN Search : " << x->getKey() << endl;
		//cout << "STUDENT ID FOUND IN Search : " << x->getRecord()->studid << endl;
		return x->getRecord();
	}
	else
	{
		return NULL;
	}
}



Record* SkipList::SearchByGPA(float searchKey)
{
	Node* x = new Node;
	x = header;

	for (int i = 0; i < MaxNumOfPointers; ++i)
	{
		while(x->getForward()[i]->getKey() != MaxValue)
		{
			if (x->getForward()[i]->getRecord()->gpa == searchKey)
			{
				return x->getForward()[i]->getRecord();
			}
			x = x->getForward()[i];
		}

		if (x->getForward()[i]->getKey() == MaxValue)
		{
			break;
		}
	}
	return NULL;
}



float SkipList::SearchBetweenGPA(int key1, int key2)
{
	Node* x = new Node;
	x = header;
	float theGPA, sumGPA;
	int count = 0;
	for (int i = 0; i < MaxNumOfPointers; ++i)
	{
		while(x->getForward()[i]->getKey() != MaxValue)
		{
			if ((x->getForward()[i]->getKey() >= key1) && (x->getForward()[i]->getKey() <= key2))
			{
				//cout << "Printing in SearchBetween " << x->getForward()[i]->getKey() << " && ";
				//cout << "Printing in SearchBetween " << x->getForward()[i]->getRecord()->lastname << " && " << x->getForward()[i]->getRecord()->gpa << endl;
				sumGPA = sumGPA + x->getForward()[i]->getRecord()->gpa;
				++count;
			}
			x = x->getForward()[i];
		}

		if (x->getForward()[i]->getKey() == MaxValue)
		{
			break;
		}
	}

	theGPA = sumGPA / (float)count;
	return theGPA;
}



int SkipList::Insert(int searchKey, Record* newRecord)
{
	Node** update = new Node*[MaxNumOfPointers];
	Node* x = new Node;
	x = header;
	for (int i = MaxNumOfPointers-1; i >= 0; --i)
	{
		while(x->getForward()[i]->getKey() < searchKey)
		{
			x = x->getForward()[i];
		}
		update[i] = x;
	}
	x = x->getForward()[0];
	
	if (x->getKey() == searchKey)
	{
		x->setRecord(newRecord);
		//cout << "Key inserted to existing node" << endl;
		return 1;
	}
	else
	{
		int level = (int)((double)rand() / ((double)RAND_MAX + 1) * MaxNumOfPointers+1);
		//cout << "Level : " << level << endl;
		x = MakeNode(level, searchKey, newRecord);
		
		for (int i = 0; i < level; ++i)
		{
			x->getForward()[i] = update[i]->getForward()[i];
			update[i]->getForward()[i] = x;
		}	
		//cout << "Key inserted to new node" << endl;
		return 0;
	}

}



Node* SkipList::MakeNode(int lvl, int newKey, Record* newRecord)
{
	/*
		Creation of a new Node
	*/
	Node* node = new Node;
	node->setKey(newKey);
	node->setRecord(newRecord);
	node->setForward(new Node*[MaxNumOfPointers]); 

	for (int i = 0; i < lvl; ++i)
	{
		node->getForward()[i] = terminatingNode;
	}

	for (int i = lvl; i < MaxNumOfPointers; ++i)
	{
		node->getForward()[i] = NULL;
	}

	return node;
}



void SkipList::Print()
{
	Node* x = new Node;
	x = header;

	for (int i = 0; i < MaxNumOfPointers; ++i)
	{
		while(x->getForward()[i]->getKey() != MaxValue)
		{
			cout << "Printing... " << x->getForward()[i]->getKey() << " && ";
			cout << "Printing... " << x->getForward()[i]->getRecord()->lastname << endl;
			x = x->getForward()[i];
		}

		if (x->getForward()[i]->getKey() == MaxValue)
		{
			break;
		}
	}
}



Node* SkipList::getNode() 
{
	return header;
}



Node* getTail(Node* current)
{
    while ((current != NULL) && (current->getNext() != NULL))
    {
        current = current->getNext();
    }
    return current;
}



void SkipList::QuickSortGPA(Node** head_ref)
{

    Node *head1, *head2, *pivot, *tail;

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



Node* partitionGPA(Node* head, Node** head1_ref, Node** head2_ref)
{
    Node* temp1 = head;
    Node* temp2 = head;
    Node* pivot = head;
    Node* t;

    while((temp2->getNext() != NULL) && (temp2->getNext()->getRecord() != NULL))
    {
    	if(temp2->getNext()->getRecord()->gpa < pivot->getRecord()->gpa)
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



void SkipList::QuickSortCourses(Node** head_ref)
{
    Node *head1, *head2, *pivot, *tail;

    if((*head_ref == NULL) || ((*head_ref)->getNext() == NULL)) 
    {
    	return;
    }

    pivot = partitionCourses(*head_ref, &head1, &head2);
    QuickSortCourses(&head1);
    QuickSortCourses(&head2);

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



Node* partitionCourses(Node* head, Node** head1_ref, Node** head2_ref)
{
    Node* temp1 = head;
    Node* temp2 = head;
    Node* pivot = head;
    Node* t;

    while((temp2->getNext() != NULL) && (temp2->getNext()->getRecord() != NULL))
    {
    	if(temp2->getNext()->getRecord()->numofcourses > pivot->getRecord()->numofcourses)
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



Record* SkipList::Delete(int searchKey)
{
	Node** update = new Node*[MaxNumOfPointers];
	Node* x = new Node;
	Node* z = new Node;
	x = header;
	for (int i = MaxNumOfPointers-1; i >= 0; --i)
	{
		while(x->getForward()[i]->getKey() < searchKey)
		{
			x = x->getForward()[i];
		}
		update[i] = x;
	}
	x = x->getForward()[0];
	if (x->getKey() == searchKey)
	{
		for (int i = 0; i < MaxNumOfPointers; ++i)
		{
			if (update[i]->getForward()[i] != x)
			{
				break;
			}
			update[i]->getForward()[i] = x->getForward()[i];
		}
		z = x;
		delete x;
		return z->getRecord();
	}
	else
	{
		return NULL;
	}
}
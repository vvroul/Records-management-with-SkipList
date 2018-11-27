#ifndef SKIP_LIST
#define SKIP_LIST

#include "Record.h"
#include "Node.h"

#define MaxNumOfPointers 3
#define MaxValue 999999

class SkipList
{
	public : 

		SkipList();
		SkipList(const SkipList& list);  
		~SkipList();

		int Insert(int searchKey, Record* newRecord);
		float SearchBetweenGPA(int key1, int key2);
		void Print();
		void QuickSortGPA(Node** head_ref);
		void QuickSortCourses(Node** head_ref);
		Node* MakeNode(int lvl, int key, Record* record);
		Node* getNode();
		Record* Search(int key);
		Record* Delete(int searchKey);
		Record* SearchByGPA(float key);
		

	private :
		Node* header;
		Node* terminatingNode;	
};


#endif
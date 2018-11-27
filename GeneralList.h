#ifndef GENERAL_LIST
#define GENERAL_LIST

#include "ListNode.h"

class GeneralList
{
	public:
		GeneralList();
		~GeneralList();
		int Exists(int item);
		void PrintData();
		void Insert(int item);
		ListNode* Search(int item);
		ListNode* getNode();
	

	private:
		ListNode* header;
};


#endif // !GENERAL_LIST
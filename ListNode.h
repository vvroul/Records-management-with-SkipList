#ifndef LIST_NODE_H
#define LIST_NODE_H

class ListNode
{
	public:
		ListNode();
		~ListNode();
		int getKey();
		int getTimes();
		void setNext(ListNode* next);
		void setKey(int key);
		void setTimes(int times);
		ListNode* getNext();
		

	private:
		int key;
		int times;
		ListNode* next;
};

#endif // LIST_NODE_H
#include <iostream>
#include "ListNode.h"


ListNode::ListNode()
{
	//cout << "ListNode created successfully!" << endl;
}


ListNode::~ListNode()
{
	//cout << "ListNode deleted." << endl;
}


ListNode* ListNode::getNext()
{
	return next;
}


void ListNode::setNext(ListNode* next)
{
	this->next = next;
}


int ListNode::getKey()
{
	return key;
}


void ListNode::setKey(int key)
{
	this->key = key;
}


int ListNode::getTimes()
{
	return times;
}


void ListNode::setTimes(int times)
{
	this->times = times;
}	
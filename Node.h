#ifndef NODE
#define NODE

class Node
 {
 	public:
 		Node()
 		{
 			
 		}
 		
 		~Node()
 		{

 		}

 		Node** getForward()
 		{
 			return forward;
 		}
 		
 		void setForward(Node** next)
 		{
 			forward = next;
 		}

 		Node* getNext()
 		{
 			return forward[0];
 		}
 		
 		void setNext(Node* next)
 		{
 			forward[0] = next;
 		}

 		int getKey()
 		{
 			return key;
 		}

 		void setKey(int key)
 		{
 			this->key = key;
 		}

		Record* getRecord() 
		{
	    	return record;
		}
	
		void setRecord(Record* myRecord) 
		{
	    	record = myRecord;
		}
 	

	private : 
 		int key;
 		Record *record;
 		Node** forward;
 }; 


#endif
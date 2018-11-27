#ifndef HASH_LIST
#define HASH_LIST

#include "Record.h"

class HashList 
{
	public:

        HashList()
        {
            //
        }

		HashList(int newKey, Record* newRecord) 
	    {
	    	key = newKey;
            record = newRecord;
	        next = NULL;
	    }

        ~HashList()
        {
            //
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
 
      	HashList* getNext() 
      	{
            return next;
      	}
 
      	void setNext(HashList* next) 
      	{
      		this->next = next;
      	}


	private:
        int key;
	    Record* record;
	    HashList* next;
};


#endif
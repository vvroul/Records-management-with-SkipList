#ifndef HASH_TABLE
#define HASH_TABLE

#include "HashList.h"
//#define hashSize 20

class HashTable
{
    
    public :
        HashTable();
        HashTable(int hashSize);
        ~HashTable();
        int HashFunction(int key);
        float FindAverageGPA(int key);
        void PutRecord(int key, Record* newRecord);
        void Remove(int key);
        void QuickSortGPA(HashList** head);
        void setList(HashList* table);
        void setArray(HashList** hashArray);
        HashList* FindK(int key); 
      	HashList* getList();
        HashList** getArray();
        Record* GetRecord(int key);        


    private :
        int hashSize;
        HashList** hashArray;
};

#endif
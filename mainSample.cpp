#include <iostream>
#include <fstream>
#include "SkipList.h"
#include "Record.h"
#include "HashTable.h"
#include "Declars.h"
#include "GeneralList.h"

using namespace std;


extern "C"
{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
}

int main(int argc, char **argv)
{

	ifstream read1;
	int hashEntries;

	if (argc > 1) 
	{
		for (int i = 1; i < argc; i++) 
		{
			if (strcmp(argv[i], "-l") == 0) 
			{
				read1.open(argv[i+1]);		//input file is next on argv
				if (read1 == NULL)
				{
					cout << "You've given a wrong input file. " << endl;
					exit(1);
				}
				else
				{
					cout << "File : " << argv[i+1] << " opened successfully!" << endl;
				}
				++i;
			}
			else if (strcmp(argv[i], "-b") == 0) 
			{
				hashEntries = atoi(argv[i+1]);		//hash size is next on argv
				cout << "Max entries for hash table : " << hashEntries << endl;
				++i;
			}
			else if (strcmp(argv[i], "-c") == 0) 
			{
				cout << "No config-file is being used. " << endl;
				exit(1);
			}
			else 
			{
				cout << "You've given wrong input" << endl;
				exit(1);
			}
		}
	}
	else
	{
		cout << "------>  Suggested input: $./stucs –l <input file> –b <hashentries>" << endl;
		exit(1);
	}

	
	cout << "Welcome to student management!" << endl;
	
	srand(time(NULL));
	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout.precision(2);
	
	SkipList* skipList = new SkipList();
	SkipList* tempSkipList = new SkipList();
	HashTable* hashTable = new HashTable(hashEntries);
	GeneralList* genList = new GeneralList();

	char instr[3];
	int k;
	int sumofstudents = 0;
	read1 >> instr;
	
	do 
	{
		while (strcmp(instr, "i") == 0)
		{
			//cout << "------------->  Inserting" << endl;
			Record *newRecord = new Record();

			read1 >> newRecord->studid;
			cout << newRecord->studid << " ";
			read1 >> newRecord->lastname;
			cout << newRecord->lastname << " ";
			read1 >> newRecord->firstname;
			cout << newRecord->firstname << " ";
			read1 >> newRecord->gpa;
			cout << newRecord->gpa << " ";
			read1 >> newRecord->numofcourses;
			cout << newRecord->numofcourses << " ";
			read1 >> newRecord->deprt;
			cout << newRecord->deprt << " ";
			read1 >> newRecord->postcode;
			cout << newRecord->postcode << endl;
			
			//Inserting information to the needed structs
			skipList->Insert(newRecord->studid, newRecord);
			tempSkipList->Insert(newRecord->studid, newRecord);
			hashTable->PutRecord(newRecord->postcode, newRecord);
			genList->Insert(newRecord->postcode);
			
			++sumofstudents;
			read1 >> instr;
			newRecord = NULL;
			//cout << "********************************** " << endl << endl;
		}

		while (strcmp(instr, "q") == 0)
		{
			//cout << "-------------> Searching" << endl;
			Record* theRecord = new Record();
			Record* newRecord = new Record();
			cout << instr << " ";
			read1 >> newRecord->studid;
			cout << newRecord->studid << endl;
			theRecord = skipList->Search(newRecord->studid);

			if (theRecord != NULL)
			{
				cout << theRecord->studid << " ";
				cout << theRecord->lastname << " ";
				cout << theRecord->firstname << " ";
				cout << theRecord->gpa << " ";
				cout << theRecord->numofcourses << " ";
				cout << theRecord->deprt << " ";
				cout << theRecord->postcode << endl;
			}
			else
			{
				cout << "not found" << endl;
			}
			
			read1 >> instr;
			theRecord = NULL;
			newRecord = NULL;
			//cout << "********************************** " << endl << endl;
		}

		while (strcmp(instr, "m") == 0)
		{
			//cout << "-------------> Searching for modification" << endl;
			Record* myRecord = new Record();
			Record* theRecord = new Record();
			cout << instr << " ";
			read1 >> myRecord->studid;
			cout << myRecord->studid << " ";
			read1 >> myRecord->gpa;
			cout << myRecord->gpa << " ";
			read1 >> myRecord->numofcourses;
			cout << myRecord->numofcourses << endl;
			
			theRecord = skipList->Search(myRecord->studid);

			if (theRecord != NULL)
			{
				theRecord->gpa = myRecord->gpa;
				theRecord->numofcourses = myRecord->numofcourses;
				//cout << "-------------> Modified" << endl;
				cout << theRecord->studid << " ";
				cout << theRecord->lastname << " ";
				cout << theRecord->firstname << " ";
				cout << theRecord->gpa << " ";
				cout << theRecord->numofcourses << " ";
				cout << theRecord->deprt << " ";
				cout << theRecord->postcode << endl;
			}
			else
			{
				cout << "not found" << endl;
			}

			read1 >> instr;
			myRecord = NULL;
			theRecord = NULL;
			//cout << "********************************** " << endl << endl;
		}

		while (strcmp(instr, "d") == 0)
		{
			//cout << "-------------> Searching for deletion" << endl;
			Record* myRecord = new Record();
			cout << instr << " ";
			read1 >> myRecord->studid;
			cout << myRecord->studid << endl;
			Record* delRecord = skipList->Delete(myRecord->studid);
			if (delRecord != NULL)
			{
				cout << "Deleted" << endl;
				cout << delRecord->studid << " ";
				cout << delRecord->lastname << " ";
				cout << delRecord->firstname << " ";
				cout << delRecord->gpa << " ";
				cout << delRecord->numofcourses << " ";
				cout << delRecord->deprt << " ";
				cout << delRecord->postcode << endl;
			}
			else
			{
				cout << "not found" << endl;
			}
			read1 >> instr;
			myRecord = NULL;
			delRecord = NULL;
			//cout << "********************************** " << endl << endl;
		}

		while (strcmp(instr, "ra") == 0)
		{
			//cout << "-------------> Computing average between values" << endl;
			Record* myRecord = new Record();
			Record* myRecord2 = new Record();
			float theGPA;
			cout << instr << " ";
			read1 >> myRecord->studid;
			cout << myRecord->studid << " ";
			read1 >> myRecord2->studid;
			cout << myRecord2->studid << endl;
			
			theGPA = skipList->SearchBetweenGPA(myRecord->studid, myRecord2->studid);
			cout << theGPA << endl;
			read1 >> instr;
			myRecord = NULL;
			myRecord2 = NULL;
			//cout << "********************************** " << endl << endl;
		}

		while (strcmp(instr, "a") == 0)
		{
			//cout << "-------------> AVRG GPA FROM POSTCODE" << endl;
			Record* myRecord = new Record();
			cout << instr << " "; 
			float theGPA;
			read1 >> myRecord->postcode;
			cout << myRecord->postcode << endl;
			theGPA = hashTable->FindAverageGPA(myRecord->postcode);
			cout <<  theGPA << endl;
			read1 >> instr;
			myRecord = NULL;
			//cout << "********************************** " << endl << endl;
		}

		while (strcmp(instr, "ta") == 0)
		{
			//cout << "-------------> TOP K GPA FROM POSTCODE" << endl;
			Record* myRecord = new Record();
			HashList* myHashList = new HashList();
			int counter = 0;
			cout << instr << " ";
			read1 >> k;
			cout << k << " ";
			read1 >> myRecord->postcode;
			cout <<  myRecord->postcode << endl;
			
			myHashList = hashTable->FindK(myRecord->postcode);
			hashTable->QuickSortGPA(&myHashList);
			
			while (counter != k)
			{
			    //cout << "The record IN MAIN :::  : " << myHashList->getRecord()->gpa << endl;
				cout << myHashList->getRecord()->studid << " ";
				cout << myHashList->getRecord()->lastname << " ";
				cout << myHashList->getRecord()->firstname << " ";
				cout << myHashList->getRecord()->gpa << " ";
				cout << myHashList->getRecord()->numofcourses << " ";
				cout << myHashList->getRecord()->deprt << " ";
				cout << myHashList->getRecord()->postcode << endl;

			    ++counter;
			    myHashList = myHashList->getNext();

			    if (myHashList == NULL)
			    {
			    	break;
			    }
			}
			myRecord = NULL;
			delete myHashList;
			read1 >> instr;
			//cout << "********************************** " << endl << endl;
		}

		while (strcmp(instr, "b") == 0)
		{

			//cout << "-------------> BOTTOM K GPA FROM ALL" << endl;
			Record* myRecord = new Record();
			int counter = 0;
			cout << instr << " ";
			read1 >> k;
			cout << k << endl;
			
			tempSkipList->QuickSortGPA(tempSkipList->getNode()->getForward());
			Node* x = new Node;
			x = tempSkipList->getNode();
			while (counter != k)
			{
				myRecord = x->getForward()[0]->getRecord();

				if (myRecord != NULL)
				{
					cout << myRecord->studid << " ";
					cout << myRecord->lastname << " ";
					cout << myRecord->firstname << " ";
					cout << myRecord->gpa << " ";
					cout << myRecord->numofcourses << " ";
					cout << myRecord->deprt << " ";
					cout << myRecord->postcode << endl;
				}
				//cout << "The BOTTOM gpa IN MAIN :::  : " << x->forward[0]->getRecord()->gpa << endl;
				++counter;
				if (x->getForward()[0]->getKey() == MaxValue)
				{
					break;
				}
				x = x->getForward()[0];	
			}
			read1 >> instr;
			myRecord = NULL;
			x = NULL;
			//cout << "********************************** " << endl << endl;
		}

		while (strcmp(instr, "ct") == 0)
		{
			//cout << "-------------> SUM OF CT FROM SAME POSTCODE" << endl;
			cout << instr << " ";
			HashList* myHashList = new HashList();
			int counter = 0;
			int sumofcourses = 0;
			Record* myRecord = new Record();
			read1 >> myRecord->postcode;
			cout <<  myRecord->postcode << " ";
			read1 >> myRecord->deprt;
			cout <<  myRecord->deprt << endl;
			
			myHashList = hashTable->FindK(myRecord->postcode);
			while (myHashList != NULL)
			{
				if (strcmp(myHashList->getRecord()->deprt, myRecord->deprt) == 0)
				{
					
					cout << myHashList->getRecord()->studid << " ";
					cout << myHashList->getRecord()->lastname << " ";
					cout << myHashList->getRecord()->firstname << " ";
					cout << myHashList->getRecord()->gpa << " ";
					cout << myHashList->getRecord()->numofcourses << " ";
					cout << myHashList->getRecord()->deprt << " ";
					cout << myHashList->getRecord()->postcode << endl;

					++counter;
					sumofcourses += myHashList->getRecord()->numofcourses;
				}
				myHashList = myHashList->getNext();
			}
			if (counter == 0)
			{
				cout << "not found" << endl;
			}
			else
			{
				cout <<  sumofcourses << endl;
			}
			myRecord = NULL;
			delete myHashList;
			read1 >> instr;
			//cout << "********************************** " << endl << endl;
		}

		while (strcmp(instr, "f") == 0)
		{
			//cout << "-------------> MAXIMUM COURSES AND FGPA > GPA" << endl;
			Record* myRecord = new Record();
			Record* theRecord = new Record();
			int counter = 0;
			int maximumCourses = -1;
			cout << instr << " ";
			read1 >> myRecord->gpa;
			cout <<  myRecord->gpa << endl;
			
			tempSkipList->QuickSortCourses(tempSkipList->getNode()->getForward());
			Node* x = new Node;
			x = tempSkipList->getNode();
			while (x->getForward()[0]->getKey() != MaxValue)
			{
				theRecord = x->getForward()[0]->getRecord();

				if ((theRecord != NULL) && (theRecord->gpa > myRecord->gpa) && (theRecord->numofcourses >= maximumCourses))
				{
					cout << theRecord->studid << " ";
					cout << theRecord->lastname << " ";
					cout << theRecord->firstname << " ";
					cout << theRecord->gpa << " ";
					cout << theRecord->numofcourses << " ";
					cout << theRecord->deprt << " ";
					cout << theRecord->postcode << " ";
					maximumCourses = theRecord->numofcourses;
				}

				//cout << "The BOTTOM gpa IN MAIN :::  : " << x->forward[0]->getRecord()->gpa << endl;
				//++counter;
				x = x->getForward()[0];	
			}
			read1 >> instr;
			myRecord = NULL;
			theRecord = NULL;
			//cout << "********************************** " << endl << endl;
		}

		while (strcmp(instr, "p") == 0)
		{
			//cout << "-------------> PERCENTAGE POSTCODE" << endl;
			Record* myRecord = new Record();
			HashList* myHashList = new HashList();
			int counter = 0;
			double percentage;
			cout << instr << " ";
			read1 >> myRecord->postcode;
			cout <<  myRecord->postcode << endl;
			
			myHashList = hashTable->FindK(myRecord->postcode);
			while (myHashList != NULL)
			{
			    //cout << "THe recoo for PERCENTAGE POSTCODE :::  : " << myHashList->getRecord()->lastname << endl;
			    myHashList = myHashList->getNext();
			    ++counter;
			}
			percentage =  (double)counter / (double)sumofstudents;
			//cout << "Number who live in postcode : " << counter << endl;
			//cout << "Sum of all students : " << sumofstudents << endl;
			cout << percentage << endl;
			myRecord = NULL;
			myHashList = NULL;
			delete myHashList;
			read1 >> instr;
			//cout << "********************************** " << endl << endl;
		}

		while (strcmp(instr, "pe") == 0)
		{
			//cout << "------------->POSTCODES AND MANY OTHER STUFF" << endl;
			cout << instr << endl;
			int counter;
			double percentage;
			//genList->PrintData();
			ListNode* node = new ListNode();
			node = genList->getNode();
			while (node->getNext() != NULL)
			{
				percentage = (double)node->getTimes() / (double)sumofstudents;
				cout << node->getKey()  << " " <<  percentage << endl;
				node = node->getNext();
				//++counter;
			}
			percentage = (double)node->getTimes() / (double)sumofstudents;
			cout << node->getKey()  << " " <<  percentage << endl;
			read1 >> instr;
			//cout << "********************************** " << endl << endl;
		}
	
	}while (instr[0] != 'e');
	cout << "e" << endl << endl;

	//skipList->Print();

	cout << "Input file reached the end." << endl;

	read1.close();
	delete skipList;
	delete hashTable;
	delete genList;
	return 0;
}
#ifndef RECORD
#define RECORD

extern "C"
{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
}

class Record
{
	public:
		Record()
		{

		}
		~Record()
		{

		}

		int studid;
		char lastname[20];
		char firstname[20];
		float gpa;
		int numofcourses;
		char deprt[5];
		int postcode;
};

#endif
#ifndef DECLARS
#define DECLARS

#include "Node.h"
#include "Record.h"
#include "HashList.h"

Node* partitionGPA(Node* head, Node** head1_ref, Node** head2_ref);
Node* partitionCourses(Node* head, Node** head1_ref, Node** head2_ref);
Node* MakeNode(int lvl, int key, Record* record);
Node* getTail(Node* current);
HashList* partitionGPA(HashList* head, HashList** head1_ref, HashList** head2_ref);
HashList* getTail(HashList* current);


#endif
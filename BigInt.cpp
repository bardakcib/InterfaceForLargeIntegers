#include <iostream>
#include <fstream>
#include "BigInt.h"

using namespace std;
BigInt::BigInt ()
{
	head = NULL;
	tail=NULL;
}


void BigInt::addtoEnd (int n)
{
	node *ptr = new node();
	ptr->number=n;
    if(head==NULL){
		head = ptr;
		tail=ptr;
		ptr->next=NULL;
		ptr->prev=NULL;
	}
	else{
	tail->next=ptr;
	ptr->prev=tail;
	tail=ptr;
	}
}	

void BigInt::printList (ofstream&out)
{
	node * ptr = head;
    while (ptr != NULL) 
	{
		out << ptr ->number;
		ptr = ptr->next;
	}
	cout << endl;
}

void BigInt::debug(){
	node * ptr = head;
    while (ptr != NULL) 
	{
		cout << ptr ->number;
		ptr = ptr->next;
	}
	cout << endl;

}

void BigInt::addToBeginning (int n)
{
	node *ptr = new node();
    ptr->number=n;
    if(head==NULL){
		head = ptr;
		tail=ptr;
		ptr->next=NULL;
		ptr->prev=NULL;
	}
	else{

	ptr->next=head;
	head->prev=ptr;
	ptr->prev=NULL;
	head=ptr;
	}
}

node* & BigInt::getTail(){
	return tail;
}


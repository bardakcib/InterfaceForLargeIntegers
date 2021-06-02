#ifndef _BIGINT_H
#define _BIGINT_H
struct node {
	int number;
	node *next; 
	node *prev;


	node::node ()
	{
		next=nullptr;
		prev=nullptr;
	}
};

class BigInt 
{
private:
	node * head;
	node *tail;

public:
	BigInt (); //constructor		
	void printList(std::ofstream&); //Printing the bigInt to the output file
	void debug(); //printing bigInt to the console for debug purposes
	void addtoEnd(int n); //adding digit to the end of the number
	void addToBeginning(int n); //adding digit to the beginning of the number
	node* & getTail(); //returning last node of the number 
};

#endif

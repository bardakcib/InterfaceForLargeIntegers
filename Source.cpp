#include <iostream>
#include <string>
#include <fstream>
#include"BigInt.h"
#include <vector>
#include<stack>

using namespace std;

stack<BigInt> operands;
stack<char> operators;

//Create a bigInt object from the given strng
BigInt createBigInt(string number){
	BigInt bigInt;
	for(int i=0;i<number.length();i++){
		int temp= (int)number.at(i) - 48;
		bigInt.addtoEnd(temp);
	}

	return bigInt;
}

//delete the memory of the bigInt
void freeBigInt(BigInt&temp){

	node *t1=temp.getTail();

	while(t1!=NULL){
		node* deleted=t1;
		t1=t1->prev;
		delete deleted;
	}
}

//update the op1 bigInt by adding two numbers and equaling the resul to the op1 and releasing op2
void updateBigInt(BigInt&op1,BigInt&op2){

	BigInt result;

	node *temp1=op1.getTail();
	node *temp2=op2.getTail();
	int remainder=0;

	while(temp1!=NULL && temp2!=NULL){
		int sum= temp1->number+temp2->number;
		sum+=remainder;
		result.addToBeginning(sum%10);
		remainder=sum/10;
		temp1=temp1->prev;
		temp2=temp2->prev;
	}

	if(temp1!=NULL){
		while(temp1!=NULL){
			int sum=temp1->number+remainder;
			result.addToBeginning(sum%10);
			remainder=sum/10;
			temp1=temp1->prev;
		}
	}
	else if(temp2!=NULL){
		while(temp2!=NULL){
			int mult=temp2->number+remainder;
			result.addToBeginning(mult%10);
			remainder=mult/10;
			temp2=temp2->prev;
		}

	}
	else if(remainder!=0){
		result.addToBeginning(remainder);
	}
	op1=result;
	freeBigInt(op2);

}

//Multiply given two big int and push the result to the operands stack
void multiplyBigInt(BigInt&operand1,BigInt&operand2){


	BigInt result;

	node *temp1=operand1.getTail();
	node *temp2=operand2.getTail();
	int remainder=0;
	int count=0;
	while(temp2!=NULL){
		temp1=operand1.getTail();
		BigInt temp;
		
		while(temp1!=NULL){
			int mult=temp2->number*temp1->number+remainder;
			remainder=mult/10;
			temp.addToBeginning(mult%10);
			temp1=temp1->prev;
		}
		if(remainder!=0){
			temp.addToBeginning(remainder);
			remainder--;
		}
		if(temp2==operand2.getTail())
			result=temp;
		else{
			for(int i=count; i>0;i--)
				temp.addtoEnd(0);
			updateBigInt(result,temp);
		}
		
		temp2=temp2->prev;
		count++;
	}


	operands.push(result);
	freeBigInt(operand1);
	freeBigInt(operand2);

}

//add two operands and push the result to the operand stack
void addBigInt(BigInt&op1,BigInt&op2){

	BigInt result;

	node *temp1=op1.getTail();
	node *temp2=op2.getTail();
	int remainder=0;

	while(temp1!=NULL && temp2!=NULL){
		int sum= temp1->number+temp2->number;
		sum+=remainder;
		result.addToBeginning(sum%10);
		remainder=sum/10;
		temp1=temp1->prev;
		temp2=temp2->prev;
	}

	if(temp1!=NULL){
		while(temp1!=NULL){
			int sum=temp1->number+remainder;
			result.addToBeginning(sum%10);
			remainder=sum/10;
			temp1=temp1->prev;
		}
	}
	else if(temp2!=NULL){
		while(temp2!=NULL){
			int mult=temp2->number+remainder;
			result.addToBeginning(mult%10);
			remainder=mult/10;
			temp2=temp2->prev;
		}

	}
	else if(remainder!=0){
		result.addToBeginning(remainder);
	}

	
	operands.push(result);
	freeBigInt(op1);
	freeBigInt(op2);

}

//subtracttwo operands and add the result to the operand stack
void substractBigInt(BigInt&op1,BigInt&op2){
	BigInt result;

	node *temp1=op1.getTail();
	node *temp2=op2.getTail();
	int extra=0;

	while(temp1!=NULL && temp2!=NULL){
		if(extra>0)
		{
			if(temp2->number==0){
				temp2->number=9;
			}
			else{
				temp2->number--;
				extra=0;
			}

		}
		if(temp2->number<temp1->number){

			extra=1;
			int diff=temp2->number+10-temp1->number;
			
			result.addToBeginning(diff);
		}
		else{

			int diff=temp2->number-temp1->number;
			
			result.addToBeginning(diff);

		}
		temp1=temp1->prev;
		temp2=temp2->prev;
	}

	if(temp1!=NULL){
		while(temp1!=NULL){
			int diff;
			if(extra>0){
				if(temp1->number==0){
					temp1->number=9;

				}
				else{
					temp1->number--;
					extra=0;
				}
				diff=temp1->number;
			}
			else{
				diff=temp1->number-extra;
			}
		
			result.addToBeginning(diff);
			temp1=temp1->prev;
		}
	}
	else if(temp2!=NULL){
		while(temp2!=NULL){
			int diff;
			if(extra>0){
				if(temp2->number==0){
					temp2->number=9;

				}
				else{
					temp2->number--;
					extra=0;
				}
				diff=temp2->number;
			}
			else{
				diff=temp2->number-extra;
			}
			result.addToBeginning(diff);
			temp2=temp2->prev;
		}

	}

	
	operands.push(result);
	freeBigInt(op1);
	freeBigInt(op2);

}

//which operation to do by op char
void makeOperation(BigInt&operand1,BigInt&operand2,char op){
	switch (op)
	{
	case '*':
		multiplyBigInt(operand1,operand2);
		break;
	case '+':
		addBigInt(operand1,operand2);
		break;
	case '-':
		substractBigInt(operand1,operand2);
		break;
	default:
		break;
	}


}

//print the result to the output file
void outputResult(BigInt&result){
	ofstream output;
	output.open("output.txt");

	result.printList(output);
}

//read file and calculate result
void calculate(ifstream&input){
	string text;
	while(input>>text){

		if(text!="+" && text!="-" && text!="*"){ //if the text is number
			BigInt number=createBigInt(text); //create an bigInt object
			operands.push(number);  //push it to the operand stack
		}
		else{//if the text is an operator
		 //While the operator stack is not empty and the precedence of the top of the stack is same or greater than the text
			while(!operators.empty() && ((operators.top()=='*')||(operators.top()=='-'&&text!="*")||(operators.top()=='+'&&text!="*"))){
				//pop two operands and an operator and do the operation
				char op=operators.top();
				operators.pop();
				BigInt operand1=operands.top();
				operands.pop();
				BigInt operand2=operands.top();
				operands.pop();
				makeOperation(operand1,operand2,op);

			}
			//push the operator to the operators stack
			operators.push(text[0]);

		}
	}

	//while operators stack is not empty
	while (!operators.empty())
	{
		//pop two operands and an operator and do the operation
		char op=operators.top();
		operators.pop();
		BigInt operand1=operands.top();
		operands.pop();
		BigInt operand2=operands.top();
		operands.pop();
		makeOperation(operand1,operand2,op);
	}

	//write the result to the file
	outputResult(operands.top());
}

int main(){
	string fileName="input.txt";

	ifstream input;
	input.open(fileName);

	if(!input.fail()){

		calculate(input);
	}
}

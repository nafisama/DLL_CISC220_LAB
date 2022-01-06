
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;


	DLL::DLL(){  // constructor - initializes an empty list
		last = NULL;
		first = NULL;
		numTasks = 0;
		tothrs = 0;
		totmin = 0;
	}
	DLL::DLL(string t, int p, int h, int m){  // constructor, initializes a list with one new node with data x
		DNode *n = new DNode (t,p,h,m);
		first = n;
		last = n;
		numTasks=1;
		tothrs = h;
		totmin = m;
	}
	/***************************************************************************************************/
	/*Part 1																																		*/
	/***************************************************************************************************/
	void DLL::push(string n, int p, int h, int m) {  
    // does what you'd think, with a caveat that if the
	//priority isn't 3, it will move the task up to the end of the set of tasks with that priority.
	//In other words, if the priority is 1, it will traverse the list in reverse order until it finds a
	//task with a priority of 1, and insert the new task between the last task with a priority of
	//1 and the first task with a priority of 2
	//it also updates the total time of the list

		DNode *newNode= new DNode(n,p,h,m);

		DNode *tmp=last;

		if(last==NULL && first==NULL){
			//cout<<"empty list case" <<endl;

			first=newNode;
			last=newNode;
			newNode->next=NULL;
			newNode->prev=NULL;

		}else if(p>=3){
			//Add to the end
			//cout<<"p>=3 case" <<endl;

			last->next=newNode;
			newNode->prev=last;
			last=newNode;
			newNode->next=NULL;

		}else{
			//adding elements in between
			//cout<<"middle elements case"<<endl;

			while(tmp != NULL && tmp->task->priority > p){
				//cout<<"within while loop" <<endl;
				tmp=tmp->prev;

			}

			if(tmp==NULL){

				cout << "tmp, i.e last  is NULL" <<endl;

			}else{
				//cout<<"in the else case where tmp is not NULL" <<endl;

				DNode *nextP= tmp->next;
				if(nextP==NULL){  //when the curr node will be added to the end1
					tmp->next=newNode;
					newNode->prev=tmp;
					newNode->next=NULL;
				}else{
					newNode->prev=tmp;
					newNode->next=nextP;
					tmp->next=newNode;
					nextP->prev=newNode;
				}

			}


		}



		tothrs += h;
		totmin +=m;


	}

	Task *DLL::pop() { 
	//does what you'd think - make sure to update the total time of the list.
	//Note -this isn’t all that necessary for this particular project, but I 
	//kinda had to make you write pop because it’s //fundamental to so much of 
	//linked list data type uses (e.g., stack, undo).
				DNode *tmp = last;

		        last = last->prev;
		        last->next = NULL;

				int h= last->task->hr;
				int m= last->task->min;
		        numTasks--;
		        tothrs -= h;
		        totmin -= m;
		        return tmp->task;

	}

	void DLL::printList() {
		//prints out the entire list, along with the total time necessary to complete all tasks 
		//on the list

		DNode *tmp = first;
		while(tmp != NULL){
		      tmp->task->printTask();
		     //print time too
		     tmp = tmp->next;
		}


	}

	void DLL::printList(int p) {
		//print out only all the tasks with a priority of p, along with the total time necessary
		//to complete the tasks with a priority of p
		//Don't hardcode

		DNode *tmp=first;
		while(tmp!=NULL){
			if(tmp->task->priority == p ){
				tmp->task->printTask();
				tothrs += tmp->task->hr;
				totmin += tmp->task->min;
			}
			tmp=tmp->next;
		}

		cout <<endl;




	}

	void DLL::moveUp(int t) {
		// moves task with number tn up one in the list.
	    //If it is at the beginning of the list,
        //it will be moved to the end of the list.
		// NOTE: if this moves a task up before a task with a higher priority (1 is
		// higher priority than 2 - I know the wording is a bit weird), then this
		// changes the priority of the task being moved to that higher priority

		DNode *tmp=first;

		if(t == first->task->tasknum){


			first->prev=last;
			last->next=first;
			last=first;
			first=first->next;
			first->prev=NULL;
			last->next=NULL;

		}else{
			while(tmp != NULL){
				 if(tmp->task->tasknum == t){  //at 4

					DNode *belNode= tmp->next; //address of the task to be moved    - 5
					DNode *mov= tmp; //address to be moved down    -4
					DNode *down=tmp->prev; // address of previous node  -  3
					DNode *upNode=tmp->prev->prev; // address of the node below task  - 2

					if(upNode ==NULL){
						//for 2 elem

						first->next=belNode;
						tmp->next->prev=first;
						tmp->next=first;
						tmp->prev=NULL;
						first=tmp;

					}else if(belNode==NULL){
						//last element
						tmp->prev->prev->next=last;
						tmp->prev->prev=last;
						tmp->next=down;
						last=down;
						tmp->prev=upNode;
						last->next=NULL;

					}else{


					tmp->prev->prev->next=mov;  // 2 pointing to 4
					tmp->next->prev=down;  // 5's prev pointing to 3

					tmp->prev->next=belNode;    //3 next is towards 5
					tmp->prev->prev=mov;       // 3 prev is towards 4

					tmp->prev= upNode; // 4 prev pointing to 2
					tmp->next= down;  //4 next pointing to 3

					}

				 }

				tmp=tmp->next;
			}

		}


	}

	void DLL::listDuration(int *th, int *tm,int tp) {
		// gets the list duration in hours and minutes (passed
		//in as pointers) of a particular priority (so the total time
		//needed to complete all tasks with priority of p)
		// I had you pass in the parameters as pointers for practice.


		DNode *tmp=first;
				while(tmp != NULL){
					if(tmp->task->priority==tp){
						*th +=tmp->task->hr;
						*tm +=tmp->task->min;
					}
					tmp=tmp->next;
				}

	}
	
	
	void DLL::moveDown(int tn) {
		//moves task with task number tn down one in the list.
		//If it is at the end of the list, it will move to
		//beginning of the list.
		//NOTE: if this moves a task after a task with a lower priority (again, 3 is
		//a lower priority than 2) then this changes the priority of the task being
		//moved.

		DNode *tmp=first;

		if(tmp!=NULL && tn== last->task->tasknum){
			first->prev=last;
			last->next=first;

			first=first->prev;  // update last value as first value
			last=last->prev;	// update 2nd last value as last

			first->prev=NULL;
			last->next=NULL;

		}else{
			while(tmp != NULL){

				 if(tmp->task->tasknum == tn){  //4
					 DNode *mov=tmp;          // address of the node to be moved  - 4
					 DNode *above=tmp->prev;  // address of the node above curr   - 3
					 DNode *below=tmp->next;  // address of node beloww curr      - 5
					 DNode *botEnd=tmp->next->next; //address of end node in the set- 6

					 if(above==NULL){
						 //first element
						 tmp->next->next->prev=first;
						 tmp->next->next= first;
						 first->prev=below;
						 first->next=botEnd;
						 first=below;
						 first->prev=NULL;

					 }else if(botEnd==NULL){
						 //2nd last elem
						 tmp->prev->next=below;      //  3 pointing to 5
						 tmp->next->prev=above;		 // 5 pointing to 3
						 tmp->next->next=mov;			// 5 pointing to 4

						 tmp->next=NULL;              // 4 pointing to 6
						 tmp->prev=below;				// 4 pointing to 5
						 last=tmp;

					 }else{


					 tmp->prev->next=below;      //  3 pointing to 5
					 tmp->next->prev=above;		 // 5 pointing to 3

					 tmp->next->next->prev= mov;	// 6 pointing to 4
					 tmp->next->next=mov;			// 5 pointing to 4

					 tmp->next=botEnd;              // 4 pointing to 6
					 tmp->prev=below;				// 4 pointing to 5
					 }

				 }


				tmp=tmp->next;
			}

		}




	}

	int DLL::remove(int tn) {
		//removes a task (based on its number) and updates the total time of the list
		//Make sure you link the next to the previous and the previous to the next.  The 
		//biggest catch with this method is making sure you test to make sure the node 
		//after and/or the node before the node you’re deleting aren’t NULL (i.e., you’re 
		//not deleting the first or last node in the list)

		DNode *tmp=first;
		int succ=0;
		while(tmp!=NULL){


			if( tn == first->task->tasknum){
				//deleting first node
				//cout << "within removing first node" <<endl;
				if(first->next!=NULL){
				first=first->next;
				first->prev=NULL;
				}else{
					first=NULL;
					cout<< "list empty, WOHOO!!! " <<endl;
				}
				return 1;

			}else if(tn==last->task->tasknum){
				//deleting last node
				last=last->prev;
				last->next=NULL;

				return 1;
			}else{
            	//	cout << "within else case before if " << tn << "    "<<tmp->task->tasknum <<endl;

				if(tmp->task->tasknum == tn){

				//cout<< "\n within if of else \m" <<endl;
				DNode *nex=tmp->next; //address of next node
				DNode *pre= tmp->prev; //address of previous node
				tmp->next->prev=pre; // next node's prev is pointing to previous node
				tmp->prev->next=nex;  // previous node's next is pointing towards the next node

				tmp=NULL;
				return 1;
				}

			}

			tmp=tmp->next;
		}


		return succ;
	}

	void DLL::changePriority(int tn, int newp) {
		//changes the priority of the task.  This method also moves the task to the end 
		//of the set of tasks with 
		//that priority.  In other words, if you have the following:
		/*
		task1, 1, 2:20
		task2, 1, 3:20
		task3, 1, 1:15
		task4, 2, 3:10
		task5, 2, 1:10
		task6, 3, 3:15
		task7, 3, 2:54

		And you change task6’s priority to 1, the resulting list should be:
		task1, 1, 2:20
		task2, 1, 3:20
		task3, 1, 1:15
		task6, 1, 3:15
		task4, 2, 3:10
		task5, 2, 1:10
		task7, 3, 2:54
		*/
		DNode *tmp1=first;
		DNode *tn1;
		if(tmp1!=NULL && tn==first->task->tasknum){
			first->task->priority=newp;
			tn1=first;

			first=first->next;
			first->prev=NULL;

		}else if(tmp1!= NULL && tn == last->task->tasknum){

			last->task->priority=newp;
			tn1=last;

			last=last->prev;
			last->next=NULL;

		}else{
			while(tmp1 != NULL){

				if(tmp1->task->tasknum ==tn){
					tmp1->task->priority=newp;
					tn1 = tmp1;

					tmp1->prev->next= tmp1->next;
					tmp1->next->prev=tmp1->prev;

					break;
				}else{
					tmp1=tmp1->next;
				}

			}
		}
		//pushing it under new priority

		DNode *tmp= last;
		while(tmp!=NULL && tmp->task->priority > newp){
				tmp=tmp->prev;
		}
		DNode *nextP= tmp->next;

		if(tmp==NULL){
			//when adding as first node
			first->prev=tn1;
			tn1->next=first;
			first=tn1;
			first->prev=NULL;
		}else if(nextP==NULL){
			//when adding as last node
			tn1->prev =tmp;
			tmp->next=tn1;
			tn1->next=NULL;
			last=tn1;
		}else{
			//middle nodes
			tn1->prev =tmp;
			tn1->next=nextP;
			tmp->next=tn1;
			nextP->prev=tn1;
		}

	}

	DLL::~DLL(){
		DNode *tmp = first;
		DNode *tmp2 = first->next;
		while (tmp != NULL) {
			delete tmp;
			tmp = tmp2;
			if (tmp != NULL) {
				tmp2 = tmp2->next;
			}
		}
		first = NULL;
		last = NULL;
		numTasks = 0;
		tothrs = 0;
		totmin = 0;
	}

	/******************Optional Helper Methods********************************/
	void DLL::addTime(int h, int m) {
	}

	void DLL::removeTime(int h, int m) {
	}
	/********************End of Optional Helper Methods ********************/

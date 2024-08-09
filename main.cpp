#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include <ctime>

using namespace std;

struct ListNode{
	int val;
	ListNode* next;
	ListNode(): val(0), next(nullptr) {}
	ListNode(int x): val(x), next(nullptr) {}
	ListNode(int x, ListNode* next): val(x), next(next) {}
};

class Solution{
public:
	vector<int> nodesBetweenCriticalPoints(ListNode* head){
		ListNode* prev=head;
		head=head->next;
		int i=1, mindit=INT_MAX, prev_i=INT_MIN, first_i= -1;
		while(head->next!=nullptr){
			if((prev->val<head->val && head->val>head->next->val) || 
			   (prev->val>head->val && head->val<head->next->val)){
				if(prev_i != INT_MIN){
					mindit=min(mindit, i - prev_i);
				}
				if(first_i==-1){
					first_i=i;
				}
				prev_i=i;
			}
			prev=head;
			head=head->next;
			i++;
		}
		if(mindit=INT_MAX){
			return{-1,-1};
		}
		return {mindit, prev_i - first_i};
	}
/*
Input: head = [5,3,1,2,5,1,2]
Output: [1,3]
*/
};

class SolutionOne{
public:
	ListNode* swapNodes(ListNode* head, int k){
		vector<int> ele;
		int n=0;
		ListNode* temp=head;
		while(temp!=nullptr){
			ele.push_back(temp->val);
			n++;
			temp=temp->next;
		}
		swap(ele[k-1], ele[n-k]);
		temp=head;
		int i=0;
		while(temp!=nullptr){
			temp->val=ele[i];
			temp=temp->next;
			i++;
		}
		return head;
	}
/*
Input: head = [1,2,3,4,5], k = 2
Output: [1,4,3,2,5]
*/
};

class SolutionTwo{
public:
	vector<ListNode*> v;
	vector<ListNode*> splitListToParts(ListNode* head, int k){
		int sz=0; ListNode* temp=head; ListNode* temphead=head;
		for(ListNode* cur=head; cur; cur=cur->next) sz++;
		int split=0; int ctr=0; ListNode* cur=head; //hasta ahora van tres punteros
	    while(sz){
	    	split=ctr=ceil((double)sz/(double)k); //la longitud entre k
	    	sz -= split; //la longitud disminuye por la parte dividida
	    	k--; //las k partes tambien
	    	/*
	    	Primera parte: ceil(10 / 3) = 4 nodos
            Segunda parte: ceil(6 / 2) = 3 nodos
            Tercera parte: ceil(3 / 1) = 3 nodos
	    	*/
	    	while(ctr>0){
	    		if(split==ctr){
	    			//los dos punteros apuntan a hud->head
	    			temphead=cur;
	    			temp=cur;
	    		}
	    		ctr--;
	    		if(ctr!=0){ //mientras sea diferente ambospunteros avanzan
	    			cur=cur->next;
	    			temp=temp->next;
	    		}else{
	    			cur=cur->next; //si ctr ya es igual a cero
	    			//cur se mueve al siguiente nodo que sera 
	    			//el comienzo de la nueva lista
	    			temp->next=nullptr; //temp corta la lista
	    			v.push_back(temphead); //se agrega el temphead al vector
	    		}
	    	}
	    }
	    if(k!=0){
	    	while(k--){
	    		ListNode* extra=nullptr;
	    		v.push_back(extra);
	    	}
	    }
	    return v;
	}
};

class SolutionThree{
private:
	ListNode* head;
	int size=0;
	int len(ListNode* head){
		int n=0;
		while(head!=nullptr){
			n++;
			head=head->next;
		}
		return n;
	}
public:
	SolutionThree(ListNode* head){
		this->head=head;
		size=len(head);
	}
	int getRandom(){
		int move=rand()%size;
		ListNode* mover=head;
		while(move){
			mover=mover->next;
			move--;
		}
		return mover->val;
	}
/*
Input
["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
[[[1, 2, 3]], [], [], [], [], []]
Output
[null, 1, 3, 2, 2, 3]
*/
};

class SolutionFour{
private:
	pair<int, ListNode*> func(ListNode* head){
		int a=head->val*2;
		if(head->next){
			pair<int, ListNode*> next_result=func(head->next);
			a += next_result.first;
		}
		head->val=a%10;
		return {a/10, head}; //solo se guarda el ultimo digito al ser
		//divido por 10
	}
public:
	ListNode* doubleIt(ListNode* head){
		pair<int, ListNode*> result=func(head);
		if(result.first!=0){
			ListNode* new_hand=new ListNode(result.first);
			new_hand->next=result.second;
		}
		return result.second;
	}
/*
Input: head = [1,8,9]
Output: [3,7,8]
*/
};

ListNode* createdLinkedList(vector<int> nodes){
	ListNode* head=new ListNode(0);
	ListNode* temp=head;
	for(int node: nodes){
		temp->next=new ListNode(node);
		temp=temp->next;
	}
	return head->next; //despues de head sigue temp
}

void printVectorInt(vector<int> input){
	for(int i=0; i<input.size(); i++){
		cout<<input[i];
	}
	cout<<endl;
}

void printList(ListNode* root){
	while(root!=nullptr){
		cout<<root->val<<"->";
		root=root->next;
	}
}

int main(){

	Solution solutioni;
	vector<int> input={5,3,1,2,5,1,2};
	ListNode* inputOne=createdLinkedList(input);
	vector<int> output=solutioni.nodesBetweenCriticalPoints(inputOne);
	cout<<"Original First LinkedList: "<<endl;
	printVectorInt(output);
	cout<<endl;

	SolutionOne solution1;
	vector<int> inputInput={1,2,3,4,5};
	int k=2;
	ListNode* inputTwo=createdLinkedList(inputInput);
	ListNode* outputOne=solution1.swapNodes(inputTwo, k);
	cout<<"Original LinkedList: "<<endl;
	printList(inputTwo);
	cout<<endl;
	cout<<endl;
	cout<<"output LinkedList: "<<endl;
	printList(outputOne);
	cout<<endl;
	cout<<endl;

	vector<int> inputsss={1,2,3};
	ListNode* input2=createdLinkedList(inputsss);
	srand(time(nullptr));
	SolutionThree solution(input2); //de esta forma se invoca las instancias
	cout<<"Original LinkedList: "<<endl;
	printList(input2);
	cout<<endl;
	cout<<"Funcion Random: "<<endl;
	cout<<solution.getRandom()<<endl;
	cout<<solution.getRandom()<<endl;
	cout<<solution.getRandom()<<endl;
	cout<<solution.getRandom()<<endl;
	cout<<solution.getRandom()<<endl;

	return 0;
}
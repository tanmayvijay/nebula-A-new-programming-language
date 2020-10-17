// Circular Doubly Linked List

#ifndef CDLL
#define CDLL

#include<iostream>
using namespace std;

template<class T>
class CDLLNode{
	T data;
	CDLLNode<T> *next = nullptr;
	CDLLNode<T> *prev = nullptr;
	
	public:
		CDLLNode(T& data, CDLLNode<T>* prev=nullptr, CDLLNode<T>* next=nullptr){
			this->data = data;
			this->next = next;
			this->prev = prev;
		}
		
		void add_next(CDLLNode* new_node){
			if (this->next){
				new_node->next = this->next;
				if (new_node->next)
					new_node->next->prev = new_node;
				
				new_node->prev = this;
				this->next = new_node;
				
			}else{
				this->next = new_node;
				new_node->prev = this;
			}
		}
		
		void add_prev(CDLLNode* new_node){
			if (this->prev){
				new_node->prev = this->prev;
				if (new_node->prev)
					new_node->prev->next = new_node;
				
				this->prev = new_node;
				new_node->next = this;
			}else{
				this->prev = new_node;
				new_node->next = this;
			}
		}
		
		void set_next(CDLLNode* new_node){
			this->next = new_node;
			if (new_node)
				new_node->prev = this;
		}
		
		void set_prev(CDLLNode* new_node){
			this->prev = new_node;
			if (new_node)
				new_node->next = this;
		}
		
		T get_data(){
			return this->data;
		}
		
		CDLLNode* get_next(){
			return this->next;
		}
		
		CDLLNode* get_prev(){
			return this->prev;
		}
};


template<class T>
class CircularDoublyLinkedList{
	CDLLNode<T> *head = nullptr;
	CDLLNode<T> *tail = nullptr;
	int size = 0;
	public:
		void insert_back(T data){
			this->tail = new CDLLNode<T>(data, this->tail, this->head);
			if (this->tail->get_prev()){
				this->tail->get_prev()->set_next(this->tail);
			} 
			else{
				this->head = this->tail;
				this->tail->set_next(this->tail);
				this->tail->set_prev(this->tail);
			}
			
			this->head->set_prev(this->tail);
			
			this->size ++;
		}
		
		void insert_front(T data){
			this->head = new CDLLNode<T>(data, this->tail, this->head);
			if (this->head->get_next())
				this->head->get_next()->set_prev(this->head);
			else{
				this->tail = this->head;
				this->head->set_next(this->head);
				this->head->set_prev(this->head);
			}
			
			this->tail->set_next(this->head);
			
			this->size ++;
		}
		
		void insert(T data, int n=0){
			if (n > this->size){
				cout << n << " is not a valid index (n should be <= " << this->size <<  ")!" << endl;
				return;
			}
			
			CDLLNode<T> *new_node = new CDLLNode<T>(data);
			
			if (n == 0){
				new_node->add_next(this->head);
				this->head = new_node;
				this->head->set_prev(this->tail);
				
				if (! this->tail) this->tail = this->head;
			} else if (n == this->size){
				new_node->add_prev(this->tail);
				this->tail = new_node;
				this->tail->set_next(this->head);
				
				if (! this->head) this->head = this->tail;
			} else{
				CDLLNode<T> *t = this->head;
				while(--n){
					t = t->get_next();
				}
				t->add_next(new_node);
			}
			
			this->size ++;
		}

		T delete_node(int n=0){
			if (n >= this->size){
				cout << n << " is not a valid index (n should be < " << this->size <<  ")!" << endl;
				throw exception();
			}
			
			T data;
			
			if (n==0){
				CDLLNode<T>* node = head;
				head = head->get_next();
				if (head)
					head->set_prev(this->tail);
				else
					tail = head;
				
				data = node->get_data();
				delete node;
			}else if (n == this->size - 1){
				CDLLNode<T>* node = tail;
				tail = tail->get_prev();
				if (tail)
					tail->set_next(this->head);
				else
					head = tail;
				
				data = node->get_data();
				delete node;
			} else{
				CDLLNode<T>* t = this->head;
				while(--n){
					t = t->get_next();
				}
				CDLLNode<T>* node = t->get_next();
				CDLLNode<T>* next_node = node->get_next();
				t->set_next(next_node);
				// next_node->set_prev(t);
				data = node->get_data();
				delete node;
			}

			this->size --;
			
			return data;
		}
		
		CDLLNode<T>* get_node(int n=0){
			if (n >= this->size){
				cout << n << " is not a valid index (n should be < " << this->size <<  ")!" << endl;
				throw exception();
			}
			
			CDLLNode<T>* t = head;
			
			while(n--){
				t = t->get_next();
			}
			
			return t;
		}

		int get_size(){
			return this->size;
		}
		
		CDLLNode<T>* get_head(){
			return this->head;
		}
		
		CDLLNode<T>* get_tail(){
			return this->tail;
		}
		
		void print_list(){
			CDLLNode<T> *t = this->head;
			do{
				cout << t->get_data() << " ";
				t = t->get_next();
			}while(t != this->head);
			
			cout << endl;
		}
};


int main(){
	CircularDoublyLinkedList<int> cdll;

	for(int i=0; i<30; i++){
		cout << "List: ";
		cdll.insert_back(i);
		cdll.print_list();
		cout << cdll.get_size() << endl;
	}
	
	cdll.print_list();
	
	cdll.insert(100, 0);
	cdll.print_list();
	cout << cdll.get_size() << endl;

	cdll.insert(100, cdll.get_size());
	cdll.print_list();
	cout << cdll.get_size() << endl;

	cdll.insert(100, cdll.get_size()-1);
	cdll.print_list();
	cout << cdll.get_size() << endl;
	
	cdll.insert(100, 20);
	cdll.print_list();
	cout << cdll.get_size() << endl;
	
	cdll.delete_node(cdll.get_size()-1);
	cdll.print_list();

	cout << endl << cdll.get_node(28)->get_data();
	
	
	
}

#endif

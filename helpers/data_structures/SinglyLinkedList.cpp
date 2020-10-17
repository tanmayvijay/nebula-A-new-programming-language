#include<iostream>
using namespace std;

template<class T>
class SLLNode{
	T data;
	SLLNode<T> *next = nullptr;
	
	public:
		SLLNode(T& data, SLLNode<T>* next){
			this->data = data;
			this->next = next;
		}
		
		void add_next(SLLNode* new_node){
			if (this->next){
				new_node->next = this->next;
				this->next = new_node;
			}else{
				this->next = new_node;
			}
		}
		
		void set_next(SLLNode* new_node){
			this->next = new_node;
		}
		
		T get_data(){
			return this->data;
		}
		
		SLLNode* get_next(){
			return this->next;
		}
		
		
};


template<class T>
class SinglyLinkedList{
	SLLNode<T> *head = nullptr;
	int size = 0;
	public:
		void insert_back(T data){
			if (! this->head){
				this->head = new SLLNode<T>(data, nullptr);
				this->size ++;
			}else{
				SLLNode<T> *t = head;
				while(t->get_next()){
					t = t->get_next();
				}
				t->add_next( new SLLNode<T>(data, nullptr) );
				this->size ++;
			}
		}
		
		void insert_front(T data){
			SLLNode<T>* new_node = new SLLNode<T>(data, this->head);
			this->head = new_node;
			this->size ++;
		}
		
		void insert(T data, int n){
			if (n > this->size){
				cout << n << " is not a valid index (n should be <= " << this->size <<  ")!" << endl;
				return;
			}
			
			SLLNode<T> *new_node = new SLLNode<T>(data, nullptr);
			
			if (n == 0){
				new_node->add_next(this->head);
				this->head = new_node;
			}else{
				SLLNode<T> *t = this->head;
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
				SLLNode<T>* node = head;
				head = head->get_next();
				data = node->get_data();
				delete node;
			}else{
				SLLNode<T>* t = this->head;
				while(--n){
					t = t->get_next();
				}
				SLLNode<T>* node = t->get_next();
				SLLNode<T>* next_node = node->get_next();
				t->set_next(next_node);
				data = node->get_data();
				delete node;
			}

			this->size --;
			
			return data;
		}
		
		SLLNode<T>* get_node(int n=0){
			if (n >= this->size){
				cout << n << " is not a valid index (n should be < " << this->size <<  ")!" << endl;
				throw exception();
			}
			
			SLLNode<T>* t = head;
			
			while(n--){
				t = t->get_next();
			}
			
			return t;
		}
		
		int get_size(){
			return this->size;
		}
		
		SLLNode<T>* get_head(){
			return this->head;
		}
		
		void print_list(){
			SLLNode<T> *t = this->head;
			while(t != NULL){
				cout << t->get_data() << " ";
				t = t->get_next();
			}
			cout << endl;
		}
};


//int main(){
//	SinglyLinkedList<int> sll;
//
//	for(int i=0; i<30; i++){
//		sll.insert_back(i);
//	}
//	
//	sll.print_list();
//	
//	sll.delete_node(15);
//	sll.print_list();
//	
//	cout << endl << sll.get_node(28)->get_data();
//	
//	
//	
//}

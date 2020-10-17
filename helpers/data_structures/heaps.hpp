#ifndef HEAP
#define HEAP

#include<iostream>
#include<vector>
#include<exception>
using namespace std;

template<class T>
class Heap{
	vector<T> data;
	bool type; // false = min_heap, true = max_heap
	
	bool compare(T& a, T& b){
		if (type){ // max_heap
			return a >= b;
		}else{ // min_heap
			return a <= b;
		}
	}
	public:
		const static bool MINHEAP = false;
		const static bool MAXHEAP = true;
		
		Heap() {
			this->type = Heap<T>::MINHEAP;
		}
		
		Heap(bool type) : type(type) {
		}
		
		Heap(vector<T>& data, bool type=Heap<T>::MINHEAP) : type(type){
			this->data = data;
		}
		
		void heapify(){
			int n = data.size();
			for (int e=n-1; e>=0; e--){
				int i = e;
				while(true){
					int ch = 2*i+1;
					if (ch >= n) break;
					if (ch+1 < n && compare(data[ch+1], data[ch])) ch += 1;
					
					if (compare(data[i], data[ch])) break;
					
					int temp = data[ch];
					data[ch] = data[i];
					data[i] = temp;
					
					i = ch;
				}
			}
		}
		
		
		void insert(T& val){
			data.push_back(val);
			int i = data.size()-1;
			
			while(true){
				int par = (i-1)/2;
				if (par >= 0 && compare(data[i], data[par]) && i != par){
					int temp = data[par];
					data[par] = data[i];
					data[i] = temp;
					i = par;
				}else break;
			}
		}

		T get_top(){
			if (data.size()) return data[0];
			cout << "Empty Heap!\n";
			throw exception();
		}
		
		T erase_top(int n = -1){
			if (data.empty()){
				cout << "Empty Heap!\n";
				throw exception();
			}
			
			int top = data[0];
			
			if (n <= 0 || n > data.size()) n = data.size();
			
			data[0] = data[n-1];
			data.erase(data.begin()+n-1);
			n--;
			
			
			int i=0;
			while(true){
				int ch = 2*i+1;
				if (ch >= n) break;
				if (ch+1 < n && compare(data[ch+1], data[ch])) ch += 1;
				
				if (compare(data[i], data[ch])) break;
				
				int temp = data[i];
				data[i] = data[ch];
				data[ch] = temp;
				
				i = ch;
			}
			
			return top;			
		}

		void heap_sort(){
			int n = data.size();
			while(n--){
				int top = erase_top(n+1);
				data.push_back(top);
			}
		}
		
		void print_heap(){
			cout << (type ? "MAX" : "MIN") << " Heap: ";
			for (int x: data) cout << x << " ";
			cout << endl << "Size: " << data.size() << endl << endl;
		}
};

#endif

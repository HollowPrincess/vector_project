#include <new>
using namespace std;

template <class T>
class Allocator{
	public:
	T * pointer;

	T * allocate(int num){ 
		//allocate memory for "num" elements
		void * pointer =0;
		if (num==0)//nothing to do
		else if(((T)(-1)/sizeof(T)<num)||(pointer= ::operator new(num*sizeof(T)))==0){
			throw bad_alloc();//didnt allocate memory	
			//operator new is a pointer to our part of memory
			//CHECK is this right		
		}
		return((T)pointer);
	}

	void deallocate(T * pointer)
    {   
        ::operator delete(pointer);
    }

};

template <class T>
class Vector {
protected:
	int * capacity=100;
	Allocator<T> * myalloc;
	
public:
	T * head_ptr;
	T * tail_ptr;
	T * dead_end_ptr;
	//T * iterator_ptr;
	//constructors: //some of them isnt right

	//empty
	Vector() {
		head_ptr = myalloc.allocate(*capacity);//link on allocator
		tail_ptr = head_ptr;
		dead_end_ptr=head_ptr+*capacity;//the last possible element pointer
		//iterator_ptr = head_ptr;
		//now our vector is empty
	}	

	//copy
	Vector(const Vector& existingVector) {
		if(!*existingVector.head_ptr.empty()){
			this.head_ptr= myalloc.allocate(*existingVector.capacity);
			*this.capacity=*existingVector.capacity
			T * iterator_ptr = existingVector.head_ptr;	
			while (iterator_ptr!=existingVector.tail_ptr){
				this.push_back(*iterator_ptr);
				iterator_ptr++;
			};
			this.tail_ptr = head_ptr+existingVector.size();
			this.dead_end_ptr=head_ptr+*existingVector.capacity;
		}
		else{
			this = new Vector();
		};			
	}

	//move
	Vector(Vector&& existingVector){
		//CHECK IT
		//may be this is not important part
		head_ptr = nullptr;
		tail_ptr = nullptr;
		dead_end_ptr=nullptr;
		//iterator_ptr = nullptr;

		//*head_ptr=*existingVector.head_ptr;
		//*tail_ptr=*existingVector.tail_ptr;
		//*dead_end_ptr=*existingVector.dead_end_ptr;
		//*iterator_ptr=*existingVector.iterator_ptr;

		//create new empty Vector 
		//int numOfIteratorElement=existingVector.iterator_ptr-existingVector.head_ptr;//saving an itereted cell//may be we neednt
			
		//head_ptr = myalloc.allocate(*existingVector.capacity);//this is the same Vector in new memory cells
		//tail_ptr = head_ptr+*existingVector.size();//check//old size
		//dead_end_ptr=head_ptr+*existingVector.capacity;

		//copy elements

		this = new Vector(existingVector);//check constructors//copy

		existingVector.head_ptr=nullptr;
		existingVector.tail_ptr = nullptr;
		existingVector.dead_end_ptr=nullptr;
		existingVector.capacity=nullptr;
		//existingVector.iterator_ptr = nullptr;//protection from destructor 
	}

	//simple methods
	//begin() - return iterator on the first element	
	T * begin() const {
		return this.head_ptr;
	}

	//end() - iterator on the last element
	T * end() const {
		return this.tail_ptr-1;
	}

	//size() -num of elements in the Vector
	int size() const{
		return (this.tail_ptr-this.head_ptr);
	}

	//difficult methods:
	//push_back(T) - add element at the tail
	void puch_back(const T& value){
		if(tail_ptr==dead_end_ptr){			//if we havent any memory
			* capacity=dead_end_ptr-head_ptr;//current capacity
			int currentSize=this.size()+1;
			if (max_size() - * capacity / 2 < * capacity) { 
				//if we can take 1.5*capacity of memory
				* capacity = int(* capacity * 1.5);  
		    };
			if (* capacity < currentSize)  {  
				//if we cant take 1.5*capacity of memory
				* capacity = currentSize;     
			};
			//reallocate with move constructor
			this = Vector(this);	//check is this not empty?//move
		};
		//::new ((void *)tail_ptr) T(value);//add new element to the end
		*tail_ptr=value;//add new element to the tail
		++tail_ptr; // change position of tail_ptr on the last element
	}

	//pop_back() - drop element at the tail
	void puch_back(){				
		T * ptr_toDelete = tail_ptr;
		--tail_ptr; // change position of tail_ptr on the last existing element
		delete ptr_toDelete;//delete element at the tail
	}

	//erase() - delete elements //look cpp 
	//erase one element at position = num_of_pos
	//may be SWAP?
	void erase(int num_of_pos){
		if(!*(this.head_ptr+num_of_pos).empty()){
			T *iterator=this.head_ptr+num_of_pos;
			while(iterator+1<this.tail_ptr){
				*iterator=*(iterator+1);//check it//swap & pop back
				iterator++;
			};
		}


	}
	//swap() elements in vector

	//operators:
	//operator=


	//destructor
	~Vector() {
		head_ptr = nullptr;
		tail_ptr = nullptr;
		//iterator_ptr = nullptr;
		//deallocate and other
	}
};

//swap() vectors

int main() {
	//check all methods
	return 0;
}
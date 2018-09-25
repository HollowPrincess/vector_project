#include <new>
using namespace std;

template <class T>
class Allocator{
	public:
	T * pointer;

	T * allocate(int num){ 
		//allocate memory for "num" elements
		void * pointer =0;
		if(((T)(-1)/sizeof(T)<num)||(pointer= ::operator new(num*sizeof(T)))==0){
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
	int * capacity=1000;
	Allocator<T> * myalloc;
	
public:
	T * head_ptr;
	T * tail_ptr;
	T * dead_end_ptr;
	T * iterator_ptr;
	//constructors:

	//empty
	Vector() {
		head_ptr = myalloc.allocate(*capacity);//link on allocator
		tail_ptr = head_ptr;//now it is empty
		dead_end_ptr=head_ptr+*capacity;//the last possible element pointer
		iterator_ptr = head_ptr;//now our vector is empty
	}

	//copy
	Vector(const Vector& existingVector) {
		if(!*existingVector.head_ptr.empty()){
			head_ptr= new T(*existingVector.head_ptr);
		}
		else{
			head_ptr=nullptr;
		};

		if(!*existingVector.tail_ptr.empty()){
			tail_ptr= new T(*existingVector.tail_ptr);
		}
		else{
			tail_ptr=nullptr;
		};

		if((!*existingVector.dead_end_ptr.empty())&&(!*existingVector.head_ptr.empty())){
			dead_end_ptr=head_ptr+*capacity;
		}
		else{
			dead_end_ptr=nullptr;
		};

		iterator_ptr = head_ptr;
	}

	//move
	Vector(Vector&& existingVector){
		//CHECK IT
		//may be this is not important part
		head_ptr = nullptr;
		tail_ptr = nullptr;
		dead_end_ptr=nullptr;
		iterator_ptr = nullptr;

		*head_ptr=*existingVector.head_ptr;
		*tail_ptr=*existingVector.tail_ptr;
		*dead_end_ptr=*existingVector.dead_end_ptr;
		*iterator_ptr=*existingVector.iterator_ptr;

		existingVector.head_ptr=nullptr;
		existingVector.tail_ptr = nullptr;
		existingVector.dead_end_ptr=nullptr;
		existingVector.iterator_ptr = nullptr;//protection from destructor 
	}

	//simple methods
	//begin() - return iterator on the first element	
	T * begin() const {
		return this.iterator_ptr = this.head_ptr;
	}

	//end() - iterator on the last element
	T * end() const {
		return this.iterator_ptr = this.tail_ptr;
	}

	//size() -num of elements in the Vector
	int * size() const{
		return (this.last-this.first);
	}

	//difficult methods:
	//push_back(T) - add element at the tail
	void puch_back(T){

	}

	//pop_back(T) - drop element at the tail
	//erase() - delete all elements
	//swap() in vector

	//operators:
	//operator=


	//destructor
	~Vector() {
		head_ptr = nullptr;
		tail_ptr = nullptr;
		iterator_ptr = nullptr;
		//deallocate and other
	}
};

//swap() method for STL classes

int main() {
	//check all methods
	return 0;
}
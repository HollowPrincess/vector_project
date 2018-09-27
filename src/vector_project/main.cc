#include <new>
using namespace std;

template <class T>
class Allocator{
	public:
	//size_t size_type;
        
	T * pointer;

	T * allocate(size_t num){ 
		//allocate memory for "num" elements
		void * pointer =0;
		if (num==0){
			//nothing to do
		}
		else if(((size_t)(-1)/sizeof(T)<num)||(pointer= ::operator new(num*sizeof(T)))==0){
			throw bad_alloc();//didnt allocate memory	
			//operator new is a pointer to our part of memory
			//CHECK is this right		
		}
		return((T)pointer);
	}

	void deallocate()
    {   
        ::operator delete(pointer);
    }

};

template <class T>
class Vector {
//protected:

	
public:
	size_t * capacity=100;
	Allocator<T> * myalloc;
	T * head_ptr;
	T * tail_ptr;
	T * dead_end_ptr;
	//size_t size_type;

	//constructors:
	//empty
	Vector() {
		head_ptr = myalloc->allocate(*capacity);//link on allocator
		tail_ptr = head_ptr;
		dead_end_ptr=head_ptr+*capacity;//the last possible element pointer
	}	

	//copy
	Vector(const Vector<T>& existingVector){
		if(existingVector.head_ptr!=existingVector.tail_ptr){			
			this->head_ptr= myalloc->allocate(*(existingVector.capacity));

			*(this->capacity)=*(existingVector.capacity);
			T * iterator_ptr = existingVector.begin();	
			while (iterator_ptr!=existingVector.tail_ptr){
				this->push_back(*iterator_ptr);
				iterator_ptr++;
			};
			this->tail_ptr = head_ptr+existingVector.size();
			this->dead_end_ptr=head_ptr+*existingVector.capacity;
		}
		else{
			head_ptr = myalloc->allocate(*capacity);//link on allocator
			tail_ptr = head_ptr;
			dead_end_ptr=head_ptr+*capacity;//the last possible element pointer
		};			
	}

	//move
	void move(Vector&& rightVector){
		//CHECK IT
		//may be this is not important part
		head_ptr = nullptr;
		tail_ptr = nullptr;
		dead_end_ptr=nullptr;
		capacity=nullptr;
		myalloc=nullptr;

		head_ptr=rightVector.head_ptr;
		tail_ptr=rightVector.tail_ptr;
		dead_end_ptr=rightVector.dead_end_ptr;
		capacity=rightVector.capacity;
		myalloc=rightVector.myalloc;

		rightVector.head_ptr=nullptr;
		rightVector.tail_ptr = nullptr;
		rightVector.dead_end_ptr=nullptr;
		rightVector.capacity=nullptr;//protection from destructor 
	}


	Vector(Vector&& existingVector){
		//CHECK IT
		//may be this is not important part
		head_ptr = nullptr;
		tail_ptr = nullptr;
		dead_end_ptr=nullptr;
		capacity=nullptr;
		myalloc=nullptr;

		head_ptr=existingVector.head_ptr;
		tail_ptr=existingVector.tail_ptr;
		dead_end_ptr=existingVector.dead_end_ptr;
		capacity=existingVector.capacity;
		myalloc=existingVector.myalloc;

		existingVector.head_ptr=nullptr;
		existingVector.tail_ptr = nullptr;
		existingVector.dead_end_ptr=nullptr;
		existingVector.capacity=nullptr;//protection from destructor 
	}

	//simple methods
	//begin() - return iterator on the first element	
	T * begin() const {
		return this->head_ptr;
	}

	//end() - iterator on the after last element
	T * end() const {
		return this->tail_ptr;
	}

	//size() - num of elements in the Vector
	size_t size() const{
		return (this->tail_ptr-this->head_ptr);
	}

	//difficult methods:
	//push_back(T) - add element at the tail

	void push_back(const T& value){
		if(tail_ptr==dead_end_ptr){			//if we havent any memory
			* capacity=dead_end_ptr-head_ptr;//current capacity
			size_t currentSize=this->size()+1;
			//if (max_size() - * capacity / 2 < * capacity) { 
			if(myalloc.allocate(size_t(1.5* *capacity))!=bad_alloc()){
				//if we can take 1.5*capacity of memory
				* capacity = size_t(* capacity * 1.5);  
		    };
			if (* capacity < currentSize)  {  
				//if we cant take 1.5*capacity of memory
				* capacity = currentSize;     
			};
			//reallocate with move constructor
			this = Vector<T>(this);	//check is this not empty?
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
	void erase(size_t num_of_pos){
		if(!*(this.head_ptr+num_of_pos).empty()){
			T *iterator=this.head_ptr+num_of_pos;
			while(iterator+1<this.tail_ptr){
				*iterator=*(iterator+1);//check it
				iterator++;
			};
			this.push_back();
		}
	}

	void erase(size_t first_num, size_t last_num){
		if(!*(this.head_ptr+first_num).empty()){
			T *iterator=this.head_ptr+first_num;
			while(iterator(last_num-first_num)<this.tail_ptr){
				*iterator=*(iterator+(last_num-first_num));//check it
				iterator++;
			};
			for(size_t i=0; i<(last_num-first_num);i++){
				this.push_back();//check it
			};
		}
	}
	//swap() vectors
	void swap(Vector<T>& rightVector){
		Vector<T> tmp(*this);
		this=move(rightVector);
		rightVector=move(tmp);
	}

	friend void swap(Vector<T> &, Vector<T> &);

	//operators:
	//operator=
	Vector<T>& operator=(const Vector<T> &&rightVector){
		Vector<T> tmp(rightVector);
		this.swap(tmp);
		return *this;
	}

	Vector<T>& operator=(Vector<T> &&rightVector){
		this->swap(rightVector);
		return *this;
	}

	//destructor
	~Vector() {
		delete head_ptr;
		delete tail_ptr;
		delete dead_end_ptr;
		delete capacity;

		myalloc->deallocate();
		delete myalloc;
	}
};

//swap() vectors
void swap(Vector<class T> &leftVector, Vector<class T> &rightVector){
	Vector<class T> tmp(leftVector);
	leftVector=move(rightVector);
	rightVector=move(tmp);
};

int main() {
	//check all methods
	return 0;
}
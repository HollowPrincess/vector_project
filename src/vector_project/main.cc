#include <new>
#include <cstddef>
#include <algorithm>
using namespace std;

template <typename T>
class Vector
{
  protected:
	T *allocator;
  public:
	size_t *size;
	//constructors:

	//empty constructor
	Vector()
	{
		allocator = new T[0];
		*size = 0;
	}

	//copy constructor
	Vector(const Vector<T> &existingVector)
	{
		*this->size = existingVector.sizeOfVector();
		for (size_t counter = 0; counter < *this->size; counter++)
		{
			allocator[counter] = ::forward(existingVector.allocator[counter]);
		}
	}
	//copy constructor with another size
	Vector(const Vector<T> &existingVector, const size_t new_size)
	{
		*this->size = new_size;
		this->allocator = new T[new_size];
		for (size_t counter = 0; counter < min(*existingVector->size,new_size); counter++)
		{
			allocator[counter] = ::forward(existingVector.allocator[counter]);
		}		
		//CHECK
	}
	//move
	/*void move(Vector&& rightVector){
		//CHECK IT
		//may be this is not important part
		head_ptr = nullptr;
		tail_ptr = nullptr;
		dead_end_ptr=nullptr;
		//capacity=nullptr;
		myalloc=nullptr;

		head_ptr=rightVector.head_ptr;
		tail_ptr=rightVector.tail_ptr;
		dead_end_ptr=rightVector.dead_end_ptr;
		capacity=rightVector.capacity;
		myalloc=rightVector.myalloc;

		rightVector.head_ptr=nullptr;
		rightVector.tail_ptr = nullptr;
		rightVector.dead_end_ptr=nullptr;
		rightVector.myalloc=nullptr;
		//rightVector.capacity=nullptr;//protection from destructor 
	}*/
	//MAYBE I NEED IT


//move constructor
	Vector(Vector &&existingVector)
	{
		allocator = nullptr;
		size=nullptr;
		size = existingVector.size;
		allocator = existingVector.allocator;
		existingVector.allocator = nullptr;
		existingVector.size = nullptr;
	}

	//simple methods
	//begin() - return iterator on the first element
	T *begin() const
	{
		return allocator;
	}

	//end() - iterator on the after last element
	T *end() const
	{
		return (allocator+*size);
	}

	//size() - num of elements in the Vector
	size_t sizeOfVector() const
	{
		return (*size);
	}

	//difficult methods:
	//push_back(T) - add element at the tail

	void push_back(const T &value)
	{
		*this->size += 1;
		Vector<T> tmp(this, size);
		//add new element
		*tmp.allocator[*size] = value;
		this.swap(tmp);
		//CHECK is tmp will be deleted
	}

	//pop_back() - drop element at the tail
	void pop_back()
	{
		*this->size -= 1;
		Vector<T> tmp(this, size);
		//CHEK not to copy last element
		this.swap(tmp);
	}

	//erase() - delete elements //look cpp
	//erase one element at position = num_of_pos
	void erase(size_t num_of_pos)
	{
		//move the tail on one position and pop_back
		if (this.sizeOfVector()>=num_of_pos){
			for (size_t counter=num_of_pos;counter<this.sizeOfVector();counter++){
				*this->allocator[counter]=*this->allocator[counter+1];
			}
			this.pop_back();
		}
	}

	void erase(size_t first_num, size_t last_num)
	{
		if(first_num>last_num){
			first_num+=last_num;
			last_num=first_num-last_num;
			first_num=first_num-last_num;
		}
		//move the tail on (last_num-first_num) position and pop_back
		if (this.sizeOfVector()>=last_num){
			for (size_t counter=first_num;counter<this.sizeOfVector();counter++){
				*this->allocator[counter]=*this->allocator[counter+(last_num-first_num)];
			}
			for (size_t counter=first_num;counter<*size;counter++){
				this.pop_back();
			}			
		}
	}
	//swap() vectors
	void swap(Vector<T> &rightVector)
	{
		Vector<T> tmp(*this);
		this = ::move(rightVector);
		rightVector = ::move(tmp); 
	}

	friend void swap(Vector<T> &, Vector<T> &);

	//operators:
	//operator=
	Vector<T> &operator=(const Vector<T> &&rightVector)
	{
		Vector<T> tmp(rightVector);
		this.swap(tmp);
		return *this;
	}

	Vector<T> &operator=(Vector<T> &&rightVector)
	{
		this->swap(rightVector);
		return *this;
	}

	//destructor
	~Vector()
	{
		delete size;
		delete [] allocator;
	}
};

//swap() vectors
template <typename T>
void swap(Vector<T> &leftVector, Vector<T> &rightVector)
{
	leftVector.swap(rightVector);
};

int main()
{
	//check all methods
	return 0;
}
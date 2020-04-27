#pragma once
#include <algorithm>
#include <iterator>

template <typename TElem>

class DynamicVector
{
	private:

		int capacity, size;
		TElem* elems;


	public:

		//default constructor for a DynamicVector
		DynamicVector(int capacity = 10);

		//copy constructor for a DynamicVector
		DynamicVector(const DynamicVector& v);
		
		//destructor for a DynamicVector
		~DynamicVector();

		//assignment operator for a DynamicVector
		DynamicVector& operator=(const DynamicVector& v);

		//adds an element to the current DynamicVector
		void add(TElem e);

		//updates the element e from the position given
		void update(TElem e, int position);

		//deletes the element from the given position
		void deleteByPosition(int position);

		//returns the size;
		int getSize() ;

		//returns the element on a given position
		//the position must be a valid one

		TElem& get(int position) const;

		TElem& operator[](int position);

	private:
		//resizes the current DynamicVector, multiplying its capacity
		void resize();

	public:
		class iterator {
			private:
				TElem* ptr;
		
			public:
				iterator() = default;
				iterator(TElem* pointer) :ptr{ pointer } {}
				TElem operator*();
				bool operator!=(const iterator& it);
				typename iterator operator++();
				typename iterator operator++(int x);
				bool operator==(const iterator& it);
		
		};

	public:
		typename iterator begin();
		typename iterator end();
};

template <class TElem>

inline DynamicVector<TElem>::DynamicVector(int capacity) : size{ 0 }, capacity{ capacity }
{
	elems = new TElem[capacity];
}

template <class TElem>
inline DynamicVector<TElem>::DynamicVector(const DynamicVector& vector)
{
	size = vector.size;
	capacity = vector.capacity;
	elems = new TElem[capacity];
	
	for (int i = 0; i < size; ++i) {
		elems[i] = vector.elems[i];
	}
}

template <class TElem>
inline DynamicVector<TElem>::~DynamicVector() {
	delete[]elems;
}

template <class TElem>
inline void DynamicVector<TElem>::resize() {
	if (size == capacity) { capacity *= 2; }
	TElem* aux = new TElem[capacity];
	for (int i = 0; i < size; ++i) {
		aux[i] = elems[i];
	}
	delete[]elems;
	elems = aux;
}

template <class TElem>
inline void DynamicVector<TElem>::add(TElem e) {
	if (size == capacity) { resize(); }
	elems[size++] = e;
}

template <class TElem>
inline void DynamicVector<TElem>::update(TElem e, int position)
{
	elems[position] = e;
}

template <class TElem>
inline void DynamicVector<TElem>::deleteByPosition(int position) {
	for (int i = position; i < size - 1; ++i) {
		elems[i] = elems[i + 1];
	}
	size--;
}

template <class TElem>
inline TElem& DynamicVector<TElem>::get(int position) const
{
	if (position >= size) {
		throw std::runtime_error("Invalid index!");
	}
	return elems[position];
}

template <class TElem>
inline int DynamicVector<TElem>::getSize() {
	return size;
}

template <class TElem>
inline TElem& DynamicVector<TElem>::operator[](int position) {
	return elems[position];
}

template <class TElem>
inline DynamicVector<TElem>& DynamicVector<TElem>::operator=(const DynamicVector&vector)
{
	if (this == &vector) {
		return *this;
	}
	this->capacity = vector.capacity;
	this->size = vector.size;
	delete[]this->elems;
	this->elems = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = vector.elems[i];
	return *this;
}

template <class TElem>
inline typename DynamicVector<TElem>::iterator DynamicVector<TElem>::begin()
{
	return iterator{ this->elems };
}

template <class TElem>
inline typename DynamicVector<TElem>::iterator DynamicVector<TElem>::end()
{
	return iterator{ elems + size };
}



template <class TElem>
inline TElem DynamicVector<TElem>::iterator::operator*()
{
	return (*this->ptr);
}

template <class TElem>
inline bool DynamicVector<TElem>::iterator::operator!=(const iterator& it)
{
	return this->ptr != it.ptr;
}

template <class TElem>
inline typename DynamicVector<TElem>::iterator DynamicVector<TElem>::iterator::operator++()
{
	this->ptr++;
	return *this;
}

template <class TElem>
inline typename DynamicVector<TElem>::iterator DynamicVector<TElem>::iterator::operator++(int x)
{
	iterator aux{ *this };
	this->ptr++;
	return aux;
}

template<typename TElem>
inline bool DynamicVector<TElem>::iterator::operator==(const iterator& it)
{
	return !(this->ptr != it.ptr);
}

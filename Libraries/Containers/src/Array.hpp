#ifndef ARRAY_HPP
# define ARRAY_HPP

template <typename T>
class ArrayIterator
{
	public:
		ArrayIterator();
		ArrayIterator(T * store_ptr, size_t index = 0);

		bool operator !=(const ArrayIterator<T> & other) const;
		bool operator ==(const ArrayIterator<T> & other) const;
		ArrayIterator & operator ++();
		ArrayIterator   operator ++(int);
		ArrayIterator & operator --();
		ArrayIterator   operator --(int);
		T & operator *() const;
	private:
		T * _ptr;
		size_t _index;
};

template <typename T>
class ArrayReverseIterator
{
	public:
		ArrayReverseIterator();
		ArrayReverseIterator(T * store_ptr, size_t index = 0);

		bool operator !=(const ArrayReverseIterator<T> & other) const;
		bool operator ==(const ArrayReverseIterator<T> & other) const;
		ArrayReverseIterator & operator ++();
		ArrayReverseIterator   operator ++(int);
		ArrayReverseIterator & operator --();
		ArrayReverseIterator   operator --(int);
		T & operator *() const;
	private:
		T * _ptr;
		size_t _index;
};

template <typename T>
class Array
{
	public:
		typedef ArrayIterator<T> iterator;
		typedef ArrayIterator<const T> const_iterator;
		typedef ArrayReverseIterator<T> reverse_iterator;
		typedef ArrayReverseIterator<const T> const_reverse_iterator;

		Array();
		template <size_t MAX_SIZE>
		Array(T (&store)[MAX_SIZE], size_t size = 0);
		Array(size_t max_size);
		~Array();

		template <size_t MAX_SIZE>
		void setBackingStore(T (&store)[MAX_SIZE]);

		T & at(size_t index) const;
		T & operator[](size_t index);
		const T & operator[](size_t index) const;
		T & front();
		T & back();
		T * data();
		const T * data() const;
		
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

		reverse_iterator rbegin();
		reverse_iterator rend();

		const_reverse_iterator rbegin() const;
		const_reverse_iterator rend() const;

		bool empty() const;
		size_t size() const;
		size_t max_size() const;

		void swap(Array & other);
		void fill(const T & value);

	private:
		T * _store;
		size_t _max_size;
		bool _store_is_internal;
};

#include "ArrayDefinitions.hpp"

#endif

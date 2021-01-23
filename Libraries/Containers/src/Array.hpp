#ifndef ARRAY_HPP
# define ARRAY_HPP

template <typename T>
class ArrayIterator
{
	public:
		ArrayIterator(T * store_ptr, size_t index = 0);

		bool operator !=(const ArrayIterator<T> & other) const;
		bool operator ==(const ArrayIterator<T> & other) const;
		ArrayIterator & operator ++();
		T & operator *() const;
	private:
		T * _ptr;
		size_t _index;
};

template <typename T>
class Array
{
	public:
		Array();

		template <size_t MAX_SIZE>
		Array(T (&store)[MAX_SIZE], size_t size = 0);

		Array(size_t max_size);

		~Array();

		template <size_t MAX_SIZE>
		void setBackingStore(T (&store)[MAX_SIZE], size_t size = 0);

		T & at(size_t index);
		T & operator[](size_t index);

		T & front();
		T & back();

		T * data();

		bool empty();
		size_t size();
		size_t max_size();

		void swap(Array & other);
		void fill(const T & value);

	private:
		T * _store;
		size_t _size;
		size_t _max_size;
		bool _store_is_internal;
};

#include "ArrayDefinitions.hpp"

#endif

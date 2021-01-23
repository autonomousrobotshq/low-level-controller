#ifndef ARRAY_ITERATOR_HPP
#define ARRAY_ITERATOR_HPP

template <typename T>
class ArrayIterator
{
	public:
		ArrayIterator(T * store_ptr, size_t index = 0);

		bool operator !=(const VectorIterator<T> & other) const;
		bool operator ==(const VectorIterator<T> & other) const;
		VectorIterator & operator ++();
		T & operator *() const;
	private:
		T * _ptr;
		size_t _index;
};

template <typename T>
ArrayIterator<T>::ArrayIterator(T * store_ptr, size_t index)
	: _ptr(store_ptr)
	, _index(index)
{
}

template <typename T>
bool operator !=(const VectorIterator<T> & other) const
{
	return (other._index != this->_index);
}

template <typename T>
bool operator ==(const VectorIterator<T> & other) const
{
	return (other._index == this->_index);
}

template <typename T>
VectorIterator & operator ++()
{
	_index++;
	return *this;
}

template <typename T>
T & operator *() const
{
	return *(_ptr + _index);
}

#endif

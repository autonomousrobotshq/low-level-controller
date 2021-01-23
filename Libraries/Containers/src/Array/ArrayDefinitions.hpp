#ifndef ARRAY_DEFINITIONS_HPP
#define ARRAY_DEFINITIONS_HPP

/*
 * Array
 */

template <typename T>
Array<T>::Array()
	: _store(NULL)
	, _size(0)
	, _max_size(0)
	, _store_is_internal(false)
{
}

template <typename T>
template <size_t MAX_SIZE>
Array<T>::Array(T (&store)[MAX_SIZE], size_t size)
	: _store(store)
	, _size(size)
	, _max_size(MAX_SIZE)
	, _store_is_internal(false)
{
}

template <typename T>
Array<T>::~Array()
{
	if (_store_is_internal) {
		delete[] _store;
	}
}

template <typename T>
template <size_t MAX_SIZE>                                              
void Array<T>::setBackingStore(T (&store)[MAX_SIZE], size_t size)
{
	_store = store;
	_size = size;
	_max_size = MAX_SIZE;
}

template <typename T>
T & Array<T>::at(size_t index)
{
	return _store[index];
}

template <typename T>
T & Array<T>::operator[](size_t index)
{
	return _store[index];
}

template <typename T>
T & Array<T>::front()
{
	return (_store[0]);
}

template <typename T>
T & Array<T>::back()
{
	return (_size > 0) ? _store[_size - 1] : _store[0];
}

template <typename T>
T * Array<T>::data()
{
	return _store;
}

template <typename T>
bool Array<T>::empty()
{
	return _size == 0;
}

template <typename T>
size_t Array<T>::size()
{
	return _size;
}

template <typename T>
size_t Array<T>::max_size()
{
	return _max_size;
}

template <typename T>
void Array<T>::swap(Array & other)
{
	T * tmp = this->_store;
	this->_store = other.store;
	other.store = tmp;
}

template <typename T>
void Array<T>::fill(const T & value)
{
	for (size_t i = 0; i < _max_size; i++)
		_store[i] = value;
	_size = max_size;
}

/*
 * ArrayIterator
 */

template <typename T>
ArrayIterator<T>::ArrayIterator(T * store_ptr, size_t index)
	: _ptr(store_ptr)
	, _index(index)
{
}

template <typename T>
bool ArrayIterator<T>::operator !=(const ArrayIterator<T> & other) const
{
	return (other._index != this->_index);
}

template <typename T>
bool ArrayIterator<T>::operator ==(const ArrayIterator<T> & other) const
{
	return (other._index == this->_index);
}

template <typename T>
ArrayIterator<T> & ArrayIterator<T>::operator ++()
{
	_index++;
	return *this;
}

template <typename T>
T & ArrayIterator<T>::operator *() const
{
	return *(_ptr + _index);
}

#endif

#ifndef VECTOR_DEFINITIONS_HPP
#define VECTOR_DEFINITIONS_HPP

template <typename T>
template <size_t MAX_SIZE>
Vector<T>::Vector(T (&store)[MAX_SIZE], size_t size = 0)
	: Array<T>(store)
	, _size(size)
{
}

template <typename T>
void Vector<T>::push_back(const T & item)
{
	if (_size < _max_size)
		_store[_size++] = item;
}

template <typename T>
T &Vector<T>::peek_back()
{
	return ((_size > 0) ? _store[_size-1] : _store[0]);
}

template <typename T>
void Vector<T>::pop_back()
{
	if (_size > 0)
		_size--;
}

template <typename T>
void Vector<T>::remove(size_t index)
{
	if (index >= 0 && index < _size)
	{
		memmove(&_store[index], &_store[index + 1], _size - index -1);
		_size--;
	}
}

template <typename T>
T & Vector<T>::back()
{
	return _store[(_size > 0) ? _size-1 : 0];
}



#endif

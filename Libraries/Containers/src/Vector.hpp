#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <Array.hpp>

template <typename T>
class Vector : public Array
{
	public:
		template <size_t MAX_SIZE>;
		Vector(T (&store)[MAX_SIZE], size_t size = 0);
	
		void push_back(const T & item);
		T &peek_back();
		void pop_back();
		void remove(size_t index);

		T & back();

		iterator end();
		const_iterator end() const;

		reverse_iterator rbegin();
		const_reverse_iterator rbegin();

		size_t size();
		bool empty();
		bool full();
	private:
		size_t _size;
};

#endif

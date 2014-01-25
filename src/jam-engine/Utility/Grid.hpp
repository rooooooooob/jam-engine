#ifndef JE_GRID_HPP
#define JE_GRID_HPP

#include <cassert>

namespace je
{

template <typename T>
class Grid
{
public:
	class Iterator
	{
	public:
		Iterator(Grid<T>& owner, int x = 0, int y = 0);

		bool operator==(const Iterator& rhs) const;

		bool operator!=(const Iterator& rhs) const;

		T& operator*() const;

		T* operator->() const;

		Iterator& operator++();

		Iterator operator++(int);

		Iterator& operator--();

		Iterator operator--(int);
	private:
		Grid<T>& owner;
		int x, y;
	};
	class ConstIterator
	{
	public:
		ConstIterator(const Grid<T>& owner, int x = 0, int y = 0);

		bool operator==(const ConstIterator& rhs) const;

		bool operator!=(const ConstIterator& rhs) const;

		const T& operator*() const;

		const T* operator->() const;

		ConstIterator& operator++();

		ConstIterator operator++(int);

		ConstIterator& operator--();

		ConstIterator operator--(int);
	private:
		const Grid<T>& owner;
		int x, y;
	};

	Grid();
	Grid(int width, int height);
	Grid(const Grid<T>& other);
	~Grid();
	Grid& operator=(const Grid<T>& rhs);


	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
	ConstIterator cbegin() const;
	ConstIterator cend() const;

	void resize(int width, int height, const T& defVal = T());
	void clear();

	T& get(int x, int y);
	const T& get(int x, int y) const;

private:
	T *data;
	int width;
	int height;
};

template <typename T>
Grid<T>::Grid()
	:data(nullptr)
	,width(0)
	,height(0)
{
}

template <typename T>
Grid<T>::Grid(int width, int height)
	:data(new T[width * height])
	,width(width)
	,height(height)
{
}

template <typename T>
Grid<T>::Grid(const Grid<T>& other)
	:data(new T[other.width * other.height])
	,width(other.width)
	,height(other.height)
{
	int size = width * height;
	for (int i = 0; i < size; ++i)
	{
		data[i] = other.data[i];
	}
}

template <typename T>
Grid<T>::~Grid()
{
	this->clear();
}

template <typename T>
Grid<T>& Grid<T>::operator=(const Grid<T>& rhs)
{
	if (rhs.width * rhs.height != width * height)
	{
		if (data)
		{
			delete[] data;
		}
		data = new T[rhs.width * rhs.height];
	}
	width = rhs.width;
	height = rhs.height;
	int size = width * height;
	for (int i = 0; i < size; ++i)
	{
		data[i] = rhs.data[i];
	}
}

template <typename T>
typename Grid<T>::Iterator Grid<T>::begin()
{
	return Iterator(*this, 0, 0);
}

template <typename T>
typename Grid<T>::Iterator Grid<T>::end()
{
	return Iterator(*this, 0, height);
}

template <typename T>
typename Grid<T>::ConstIterator Grid<T>::begin() const
{
	return ConstIterator(*this, 0, 0);
}

template <typename T>
typename Grid<T>::ConstIterator Grid<T>::end() const
{
	return ConstIterator(*this, 0, height);
}

template <typename T>
typename Grid<T>::ConstIterator Grid<T>::cbegin() const
{
	return ConstIterator(*this, 0, 0);
}

template <typename T>
typename Grid<T>::ConstIterator Grid<T>::cend() const
{
	return ConstIterator(*this, 0, height);
}

template <typename T>
void Grid<T>::resize(int width, int height, const T& defVal)
{
	assert(width > 0 && height > 0);
	T* oldData = data;
	data = new T[width * height];
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++ x)
		{
			// copy over all old elements then pad grid with defVal
			if (y < this->height && x < this->width)
			{
				data[x + y * width] = oldData[x + y * this->width];
			}
			else
			{
				data[x + y * width] = defVal;
			}
		}
	}
	delete[] oldData;
}

template <typename T>
void Grid<T>::clear()
{
	if (data)
	{
		delete[] data;
	}
	data = nullptr;
	width = 0;
	height = 0;
}

template <typename T>
T& Grid<T>::get(int x, int y)
{
	assert(x < width && x >= 0 && y < height && y >= 0);
	return data[x + width * y];
}

template <typename T>
const T& Grid<T>::get(int x, int y) const
{
	assert(x < width && x >= 0 && y < height && y >= 0);
	return data[x + width * y];
}

/*
	--------------------------------
		ITERATOR IMPLEMENTATION
	--------------------------------
*/
template <typename T>
Grid<T>::Iterator::Iterator(Grid<T>& owner, int x, int y)
	:owner(owner)
	,x(x)
	,y(y)
{
}

template <typename T>
bool Grid<T>::Iterator::operator==(const Iterator& rhs) const
{
	return x == rhs.x && y == rhs.y && &owner == &(rhs.owner);
}

template <typename T>
bool Grid<T>::Iterator::operator!=(const Iterator& rhs) const
{
	return x != rhs.x || y != rhs.y || &owner != &(rhs.owner);
}

template <typename T>
T& Grid<T>::Iterator::operator*() const
{
	assert(x >= 0 && y >= 0 && x < owner.width && y < owner.height);
	return owner.get(x, y);
}

template <typename T>
T* Grid<T>::Iterator::operator->() const
{
	assert(x >= 0 && y >= 0 && x < owner.width && y < owner.height);
	return &owner.get(x, y);
}

template <typename T>
typename Grid<T>::Iterator& Grid<T>::Iterator::operator++()
{
	++x;
	while (x >= owner.width)
	{
		x -= owner.width;
		++y;
	}
	return *this;
}

template <typename T>
typename Grid<T>::Iterator Grid<T>::Iterator::operator++(int)
{
	Iterator ret(*this);
	++x;
	while (x >= owner.width)
	{
		x -= owner.width;
		++y;
	}
	return ret;
}

template <typename T>
typename Grid<T>::Iterator& Grid<T>::Iterator::operator--()
{
	--x;
	while (x < 0)
	{
		x += owner.width;
		--y;
	}
	return *this;
}

template <typename T>
typename Grid<T>::Iterator Grid<T>::Iterator::operator--(int)
{
	Iterator ret(*this);
	--x;
	while (x < 0)
	{
		x += owner.width;
		--y;
	}
	return ret;
}
/*				const iterator					*/
template <typename T>
Grid<T>::ConstIterator::ConstIterator(const Grid<T>& owner, int x, int y)
	:owner(owner)
	,x(x)
	,y(y)
{
}

template <typename T>
bool Grid<T>::ConstIterator::operator==(const ConstIterator& rhs) const
{
	return x == rhs.x && y == rhs.y && &owner == &(rhs.owner);
}

template <typename T>
bool Grid<T>::ConstIterator::operator!=(const ConstIterator& rhs) const
{
	return x != rhs.x || y != rhs.y || &owner != &(rhs.owner);
}

template <typename T>
const T& Grid<T>::ConstIterator::operator*() const
{
	assert(x >= 0 && y >= 0 && x < owner.width && y < owner.height);
	return owner.get(x, y);
}

template <typename T>
const T* Grid<T>::ConstIterator::operator->() const
{
	assert(x >= 0 && y >= 0 && x < owner.width && y < owner.height);
	return &owner.get(x, y);
}

template <typename T>
typename Grid<T>::ConstIterator& Grid<T>::ConstIterator::operator++()
{
	++x;
	while (x >= owner.width)
	{
		x -= owner.width;
		++y;
	}
	return *this;
}

template <typename T>
typename Grid<T>::ConstIterator Grid<T>::ConstIterator::operator++(int)
{
	ConstIterator ret(*this);
	++x;
	while (x >= owner.width)
	{
		x -= owner.width;
		++y;
	}
	return ret;
}

template <typename T>
typename Grid<T>::ConstIterator& Grid<T>::ConstIterator::operator--()
{
	--x;
	while (x < 0)
	{
		x += owner.width;
		--y;
	}
	return *this;
}

template <typename T>
typename Grid<T>::ConstIterator Grid<T>::ConstIterator::operator--(int)
{
	ConstIterator ret(*this);
	--x;
	while (x < 0)
	{
		x += owner.width;
		--y;
	}
	return ret;
}

}

#endif

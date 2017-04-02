#pragma once

#include <exception>
#include <algorithm>
#include<iostream>
#include "implementation/container_interface.hpp"

namespace ava {
	typedef unsigned int uint;

	//! Initial vector capacity for default constuctor.
	const size_t default_capacity = 10;

	//! Array with elements in dynamic memory.
	template <class T>
	class Vector : public ContainerInterface<T> {
	public:
		explicit Vector(const std::size_t capacity = default_capacity);
		explicit Vector(const Vector& that);
		//! Constractor for initializer list in oder to use expressions like this: Vector v = {1, 2, 3}
		Vector(const std::initializer_list<T>& init);
		//! Move constructor
		Vector(Vector&& that);
		//! Fill constructor constucts a container with n elements.
		//! Each element is a copy of value
		//! 
		//! @param value is a value that equals to each element in the created container
		explicit Vector(std::size_t size, const T& value);
		~Vector();
		//! Overloaded assignment operator
		const Vector& operator=(const Vector& that);
		//! Overloaded move assignment operator
		Vector& operator=(Vector&& that);
		//! Overloaded operator returns L-value of an element at pos
		//
		// @param pos is the position of returning element
		T& operator[](const std::size_t pos);
		//! Overloaded equality operator
		//!
		//! @param that is a vector wich is compared to
		bool operator ==(const Vector& that);
		//! Overloaded non-equality operator
		//!
		//! @param that is a vector wich is compared to
		bool operator !=(const Vector& that);
		//! Exchanges the contents of the array with those of other.
		//! Does not cause references to associate with the other array.
		//!
		//! @param that is array to exchange the contents with
		void swap(Vector & that);
		//! Adds a new element at the end of the vector, after its current last element.
		//! The content of val is copied (or moved) to the new element.
		//! This effectively increases the container size by one,
		//! which causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
		//!
		//! @param value is a new value to push in back
		void push_back(T value_to_copy);
		//! Delete last element.
		//! Removes the last element in the vector, effectively reducing the container size by one.
		//! This destroys the removed element.
		void pop_back();
		//! The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
		void insert(std::size_t pos, std::size_t elements_count, const T& value_to_copy);
		//! Resizes the container so that it contains new_size elements.
		//! If new size is smaller than the current container size, the content is reduced to its first new_size elements, removing those beyond (and destroying them).
		//! If new size is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of new_size.
		//! If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
		//! If new size is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
		//! Notice that this function changes the actual content of the container by inserting or erasing elements from it.
		//!
		//! @param new_size is a new size for a vector
		//! @param value_to_copy is a value that will be copied to each new elements in data sotrage if new size is greater than current size
		void resize(std::size_t new_size, T value_to_copy = T());
		//! Requests that the vector capacity be at least enough to contain new_capacity elements.
		//! If new capacity is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to new capacity (or greater).
		//! In all other cases, the function call does not cause a reallocation and the vector capacity is not affected
		//! This function has no effect on the vector size and cannot alter its elements.
		//! 
		//! @param new_capacity is a new capacity for the current vector
		void reserve(std::size_t new_capacity);
		//! Requests the container to reduce its capacity to fit its size.
		//! This may cause a reallocation, but has no effect on the vector size and cannot alter its elements.
		void shrink_to_fit();
		//! Returns capacity of the current vector
		std::size_t capacity() const { return capacity_; }
		//! Assign vector content.
		//! Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
		void assign(std::size_t count, const T& value_to_Copy);
		//! Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
		void clear();
	private:
		std::size_t get_proper_new_capacity(std::size_t new_size);
		const std::size_t CAPACITY_INCREMENT;
		std::size_t capacity_;
	};

	template<>
	class Vector<bool> {
	public:
		Vector();
		explicit Vector(std::size_t capacity_);
		Vector(const Vector<bool>& that);
		Vector(const std::initializer_list<bool>& init_list);
		Vector(Vector<bool>&& that);
		explicit Vector(const std::size_t size, bool val);
		~Vector();
		class BitReference;
		class BitIterator : public std::iterator<std::forward_iterator_tag, BitReference> {
		public:
			BitIterator(std::size_t element_pos, std::size_t bit_pos, uint* data);
			~BitIterator();
			BitReference operator*();
			BitIterator& operator++();
			BitIterator& operator--();
			BitIterator& operator++(int);//postfix
			BitIterator& operator--(int);//postfix
			bool operator==(const BitIterator& that);
			bool operator!= (const BitIterator& that);
		private:
			std::size_t element_pos_, bit_pos_;
			uint* data_;
		};
		//! Overloaded assignment operator
		const Vector<bool>& operator=(const Vector<bool>& that);
		//! Overloaded move assignment operator
		Vector<bool>& operator=(Vector<bool>&& that);
		//! Overloaded operator returns L-value of an element at pos
		//
		// @param pos is the position of returning element
		BitReference operator[](const std::size_t pos);
		//! Overloaded operator returns R-value of an element at pos
		//
		// @param pos is the position of returning element
		bool operator[](const std::size_t pos) const;
		//! Exchanges the contents of the array with those of other.
		//! Does not cause references to associate with the other array.
		//!
		//! @param that is array to exchange the contents with
		void swap(Vector<bool>& that);
		//! Adds a new element at the end of the vector, after its current last element.
		//! The content of val is copied to the new element.
		//! This effectively increases the container size by one,
		//! which causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
		//!
		//! @param value is a new value to push in back
		void push_back(bool val);
		//! Delete last element.
		//! Removes the last element in the vector, effectively reducing the container size by one.
		//! This destroys the removed element.
		void pop_back();
		//! The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
		void insert(std::size_t pos, std::size_t elements_count, bool val);
		//! Resizes the container so that it contains new_size elements.
		//! If new size is smaller than the current container size, the content is reduced to its first new_size elements, removing those beyond.
		//! If new size is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of new_size.
		//! If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
		//! If new size is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
		//! Notice that this function changes the actual content of the container by inserting or erasing elements from it.
		//!
		//! @param new_size is a new size for a vector
		//! @param value_to_copy is a value that will be copied to each new elements in data sotrage if new size is greater than current size
		void resize(std::size_t new_size, bool value_to_copy = false);
		//! Requests that the vector capacity be at least enough to contain new_capacity elements.
		//! If new capacity is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to new capacity (or greater).
		//! In all other cases, the function call does not cause a reallocation and the vector capacity is not affected
		//! This function has no effect on the vector size and cannot alter its elements.
		//! 
		//! @param new_capacity is a new capacity for the current vector
		void reserve(std::size_t new_capacity);
		//! Requests the container to reduce its capacity to fit its size.
		//! This may cause a reallocation, but has no effect on the vector size and cannot alter its elements.
		void shrink_to_fit();
		//! Returns capacity of the current vector
		std::size_t capacity() const { return capacity_; }
		//! Assign vector content.
		//! Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
		void assign(std::size_t count, bool value_to_copy);
		//! Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
		void clear();
		bool at(const std::size_t pos) const;
		bool front() const;
		bool back() const;
		bool empty() const;
		BitIterator begin() const;
		BitIterator end() const;
	private:
		void clear();
		std::size_t get_proper_new_capacity(std::size_t new_size);
		class BitReference {
		public:
			BitReference(std::size_t element_pos, std::size_t bit_pos, uint* data);
			~BitReference();
			bool get_value() const;
			void set_value(bool value);
			const BitReference& operator=(const BitReference& that);
			const BitReference& operator=(bool val);
			bool operator==(bool that);
		private:
			std::size_t element_pos_, bit_pos_;
			uint* data_;
			//bool value_;
		};
		const static std::size_t DEFAULT_ELEMENT_CAPACITY_ = 4;
		const static size_t BITS_PER_ELEMENT_ = 32;
		const static std::size_t DEFAULT_BITS_CAPACITY_ = DEFAULT_ELEMENT_CAPACITY_ * BITS_PER_ELEMENT_;
		const static size_t CAPACITY_MULTIPLY_KOEFF = 2;
		std::size_t capacity_;
		std::size_t size_;
		uint* data_;
	};
}

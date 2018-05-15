#pragma once
#include <cstdint>
#include <cstdlib>
#include <cstdio>

namespace FieaGameEngine {
	//! functor class which can be used to provide  custom implementation for reserve strategy.
	class Incrementor
	{
	public:
		//! Funtion to overload the () operator
	   /*!
	   Overload the () operator so we can call the object as a function.
	   \param size, a unsigned integer which is the current size of the vector
	   \param capacity, a unsigned integer which is the current capacity of the vector
	   \return a unsigned int, which is the new capacity to reserve for the vector
	   */
		uint32_t operator()(uint32_t size, uint32_t capacity) const
		{
			size++;
			return capacity + 5;
		}
	};

	//! class Vector
	/*!
		A Class That implements a Vector using templates. Has an additional Increment function templated type which is defaulted.
		The user can pass in their own incrementor class if they want to do custom implemetation.
	*/
	template <typename T, typename IncrementFunctor = Incrementor>
	class Vector
	{
	public:
		//! Class Iterator
		class Iterator
		{
			friend Vector;	//Declare the SList class as a friend so it can access the private Data
		public:
			//! Default Iterator Constructor
			/*!
				We need a default constructor incase we want to defer the intialization of the iterator.
			*/
			Iterator();
			//! A parameterized constructor.
			/*!
				\Param Index a integer, The index of the data iterator refers to
				\Param owner Const Vector reference, a reference to the Vector that the iterator belongs to.
			*/
			Iterator(uint32_t index, const Vector& owner);
			//! A function overloading the equality operator
			/*!
				We overload the equality operator so we can compare 2 iterators. First it checks if the owners are the same and then
				it checks the data. returns true if its same else returns false.
				\param rhs, const iterator reference to the rhs of the equality operator.
				\return A boolean which is true if the iterators refer to the same data. False otherwise.
			*/
			bool operator==(const Iterator& rhs) const;
			//! A function overloading the inequality operator
			/*!
				We overload the inequality operator so we can compare 2 iterators. Returns the NOT of equality operator.
				\param rhs, const iterator reference to the rhs of the inequality operator.
				\return A boolean which is true if the iterators refer to the Differet Data. False otherwise.
			*/
			bool operator!=(const Iterator& rhs) const;
			//!A function to overload the Pre Increment operator.
			/*!
				We overload the Pre Increment so that we can move the move the iterator to next data. Throws an exception if the
				iterator is already null.
				\return A Iterator reference to the new incremented iterator.
			*/
			Iterator& operator++();
			//!A function to overload the Post Increment operator.
			/*!
				We overload the Post Increment so that we can move the move the iterator to next data. Throws an exception if the
				iterator index is greater than size.
				\return A Iterator that is a copy of the iterator before it was incremented.
			*/
			Iterator operator++(int);
			//!A function to overload the Pre Decrement operator.
			/*!
				We overload the Pre Decrement so that we can move the move the iterator to previous data. Throws an exception if the
				iterator index is already 0
				\return A Iterator reference to the new decremented iterator.
			*/
			Iterator& operator--();
			//!A function to overload the post Decrement operator.
			/*!
				We overload the Post Decrement so that we can move the move the iterator to previous data. Throws an exception if the
				iterator index is already 0
				\return A Iterator that is a copy of the iterator before it was decremented.
			*/
			Iterator operator--(int);
			//!A function to overload the addition operator.
			/*!
				We overload the addition so that we can increment the iterator by a given integer. 
				\return A Iterator with the added index
			*/
			Iterator operator+(uint32_t increment) const;
			//!A function to overload the subtraction operator.
			/*!
				We overload the addition so that we can decrement the iterator by a given integer.
				\return A Iterator with the decremented index
			*/
			Iterator operator-(uint32_t decrement) const;
			//! A function overloading the Dereference operator
			/*!
				We overload the dereference operator to return the value held in the index of the iterator in the list.
				\return A T reference to the value in that index
			*/
			T& operator*();
			//! A const function overloading the Dereference operator
			/*!
				We overload the dereference operator to return the value held in the index of the iterator in the list.
				\return A const T reference to the value in that index
			*/
			const T& operator*() const;

			//Default the copy and the assignment operator
			Iterator(const Iterator& rhs) = default;
			Iterator& operator=(const Iterator& rhs) = default;
		private:
			uint32_t mIndex; /*<!mIndex, an integer that contains the index of the data the iterator refers to. */
			const Vector* mOwner;/*<!mOwner, a const vector reference to the Vector the iterator belongs to*/
		};

		//!parameterized constructor
		/*
			constructor that takes in the initial capacity of the vector. It is defaulted to 3
			\param capacity, an unsigned integer which is the inital capacity of the vector.
		*/
		explicit Vector(uint32_t capacity = 3);
		//! Copy Constructor
		/*!
			Copy Constructor to initalize an Vector object with another. Performs a deep copy.
			\param copyList a const reference to the Vector to intialize it with.
		*/
		Vector(const Vector& rhs);
		//! function overloading the default assignment operator
		/*!
		Overload the default assignment operator so we can perform a deep copy.
		\param copyList a const reference to the Vector on the rhs of the assignment operator.
		*/
		Vector& operator=(const Vector& rhs);
		Vector(Vector&& rhs);
		Vector& operator=(Vector&& rhs);
		//! Function to overload the [] operator
		/*!
			Overload the [] operator to return the value in the index.
			\param index, a const uint32_t reference to the index value whose value we have to return.
			\return a T reference to the item in that index of the vector.
		*/
		T& operator[](const uint32_t& index);
		//! Function to overload the [] operator
		/*!
			Overload the [] operator to return the value in the index.
			\param index, a const uint32_t reference to the index value whose value we have to return.
			\return a T reference to the item in that index of the vector.
		*/
		const T& operator[](const uint32_t& index) const;
		//! function that returns the first data in the vector.
		/*!
			A function that returns a T reference so that the data can be modified by other functions.
			it returns the first data in the vector.
			\return Data in the first node of the vector. It is a T reference.
		*/
		T& Front();
		//! function that returns the first data in the vector.
		/*!
			A const function that returns a const T reference so that it cannot be modified by other functions.
			it returns the first data in the vector.
			\return Data in the first node of the vector. It is a const T reference.
		*/
		const T& Front() const;
		//! function that returns the last data in the vector.
		/*!
			A function that returns a T reference so that it can be modified by other functions.
			it returns the last data in the vector.
			\return Data in the last node of the vector. It is a T reference.
		*/
		T& Back();
		//! function that returns the last data in the vector.
		/*!
			A const function that returns a const T reference so that it cannot be modified by other functions.
			it returns the last data in the vector.
			\return Data in the last node of the vector. It is a const T reference.
		*/
		const T& Back() const; 
		//! function to return the size(number of elements in the list) of the vector.
		/*!
			Function is constant because it doesn't have to change any members.
			\return a unsigned int which is the size of the Vector
		*/
		uint32_t Size() const;
		//! function to return the capacity of the vector.
		/*!
			Function is constant because it doesn't have to change any members.
			\return a unsigned int which is the capacity of the vector
		*/
		uint32_t Capacity() const;
		//! function to check if the vector is empty
		/*!
			Function that checks if the vector is empty. Returns true if it empty, false otherwise.
			\return const bool value, true if vector is empty, false otherwise.
		*/
		bool IsEmpty() const;
		//! function to shrink the array.
		/*
			Shrinks the capacity of the array to its current size. Does not affect the elements
			in the array.
		*/
		void ShrinkToFit();
		//! function to reserve memory with the given capacity for the array.
		/*
			Change the capacity of the array by the given value without affecting the elements already
			present. Capacity cannot be less than the size.
			\param capacity, a unsigned integer which is the new capacity.
			\return a bool which is true if the capacity was changed.
		*/
		bool Reserve(const uint32_t& capacity);
		//! PushBack function, insert the given data at the end of the Vector
		/*!
			\param data, a const reference to the data to be inserted into the Vector.
			\return an Iterator, which points to the data that was just inserted.
		*/
		Iterator PushBack(const T& value);
		//! popBack function that deletes the last data in the vector.
		void PopBack();
		//! Remove function to remove first instance of a given value in the vector.
		/*!
			Takes in the value to be removed from the vector. If the value is not there in the vector 
			returns false, else returns true after removing it.
			\param value a Const T reference to the value that needs to be deleted in that vector.
			\return bool, returns true if the value was deleted, else returns false.
		*/
		bool Remove(const T& value);
		//! Remove function to remove the item in the index of the given iterator.
		/*!
			Takes in the iterator of the value to be removed from the vector. 
			\param value a Const Iterator reference to the iterator to the value that needs to be deleted in that vector.
			\return bool, returns true if the value was deleted, else returns false.
		*/
		bool Remove(const Iterator& it);
		//! Remove function to remove a range of values.
		/*!
			Takes 2 iterators first and last. All the values between the 2 iterator(inclusive)
			are removed from the list.
			\param first, A const reference to the starting iterator in the range.
			\param last, A const reference to the last iterator in the range.
			\return bool, true if the items were removed, false otherwise.
		*/
		bool Remove(const Iterator& first,const Iterator& last);
		//! Clear function
		/*!
			Calls clear function to destruct all the data in the vector.
		*/
		void Clear();
		//! destructor
		~Vector();
		//! Iterator const Begin function
		/*!
			The begin function returns a Iterator that points to the first item in the vector.
			\return A iterator pointing to the first item.
		*/
		Iterator begin() const;
		//! Iterator end function
		/*!
			The end function returns a Iterator with the index of size (1 next to the last element).
			\return A iterator with the indexs next to the last item.
		*/
		Iterator end() const;
		//! Find function to find an item in the Vector
		/*!
			Takes in the value to be found and returns a Iterator that points to that value in the Vector. Returns end(), if the value
			is not there in the vector.
			\Param value a Const T reference to the value that needs to be inserted in that vector.
			\return an Iterator that points to the index the value is in. Returns end() if the value is not there in the vector.
		*/
		Iterator Find(const T& value) const;

		T& At(uint32_t index);
		const T& At(uint32_t index) const;
		void Resize(uint32_t size);

		
	private:
		T* mData;	/*<! A pointer to the memory location where the items in the vector are stored*/
		uint32_t mCapacity; /*<! stores the current capacity of the vector*/
		uint32_t mSize; /*<! Stores the current size of the vector*/
		IncrementFunctor mIncrementCapacity; /*<! functor object*/		
	};

#include "Vector.inl"
}


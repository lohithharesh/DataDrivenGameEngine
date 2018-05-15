#pragma once

namespace FieaGameEngine {
//! class SList
/*! 
	A Class That implements a Singly Linked List using templates.
*/
	template<typename T>
	class SList
	{
		//! Class Node
		/*!
			Node class that holds has the data and a next pointer which points to the next node in the list. It is private 
			and is not visible outside SList class. This helps us hide the actual implementation details.
		*/
		class Node {
		public:
			Node* next;	/*!< next pointer that points to the next node in the list*/
			T data;		/*!< data Variable that stores the data in the list*/
			//! A constructor
			/*!
				A constructor that takes in the data to store and a node to which the next pointer should point to.
				\param Data of type T, the data to store in the list.
				\param nextNode a Node pointer which points to the next node in the list.
			*/
			Node(const T& data, Node* nextNode = nullptr);
		};
		Node* front;/*!< Pointer of type Node that points to the first node in the list*/
		Node* back;/*!< Pointer of type Node that points to the last node in the list*/
		unsigned int size;/*!< A integer member that keeps track of the size of the list*/

	public:
		//! Class Iterator
		class Iterator
		{
			friend SList; //Declare the SList class as a friend so it can access the private constructor
		public:
			//! Default Iterator Constructor
			/*!
				We need a default constructor incase we want to defer the intialization of the iterator.
			*/
			Iterator();
			//! A function overloading the equality operator
			/*!
				We overload the equality operator so we can compare 2 iterators. First it checks if the owners are the same and then
				it checks the nodes. returns true if its same else returns false.
				\param rhs, const iterator reference to the rhs of the equality operator.
				\return A boolean which is true if the iterators refer to the same node. False otherwise.
			*/
			bool operator==(const Iterator& rhs) const;
			//! A function overloading the inequality operator
			/*!
				We overload the inequality operator so we can compare 2 iterators. Returns the NOT of equality operator.
				\param rhs, const iterator reference to the rhs of the inequality operator.
				\return A boolean which is true if the iterators refer to the Differet node. False otherwise.
			*/
			bool operator!=(const Iterator& rhs) const;
			//! A function overloading the Dereference operator
			/*!
				We overload the dereference operator to return the value held in the node of the list. 
				\return A T reference to the value in the node.
			*/
			T& operator*();
			//! A const version of the dereference operator in case it is used in a const function
			/*!
				A const T reference to the value in the node.
			*/
			const T& operator*() const;
			//!A function to overload the Pre Increment operator.
			/*!
				We overload the Pre Increment so that we can move the node to the next node in the list. Throws an exception if the
				iterator is already null. 
				\return A Iterator reference to the new incremented iterator.
			*/
			Iterator& operator++();
			//!A function to overload the Post Increment operator.
			/*!
			We overload the Post Increment so that we can move the node to the next node in the list. Throws an exception if the
			iterator is already null.
			\return A iterator that is the copy of the iterator before incrementing it.
			*/
			Iterator operator++(int);

		private:
			//! A Private parameterized constructor.
			/*!
				The parameterized constructor is declared private as the implementation of the node is private.
				\Param A Node pointer, The node the iterator refers to
				\Param Const SList reference, a reference to the SList that the iterator belongs to.
			*/
			Iterator(Node* node,const SList& mOwner);

			Node * mNode; /*!< Pointer to the iterator refers to.*/
			SList* mOwner;/*!< Pointer to the SList that the iterator belongs to.*/
		};

		//! A Default Constructor
		/*
			A constructor that initalizes the front and back pointers to nullptr and the size to 0.
		*/
		SList();
		//! Copy Constructor
		/*!
			Copy Constructor to initalize an SList object with another. Performs a deep copy.
			\param copyList a const reference to the list to intialize it with. 
		*/
		SList(const SList& copyList);
		//! function overloading the default assignment operator
		/*!
			Overload the default assignment operator so we can perform a deep copy. 
			\param copyList a const reference to the list on the rhs of the assignment operator. 
		*/
		SList& operator=(const SList& copyList);
		SList(SList&& rhs);
		SList& operator=(SList&& rhs);
		//! SList class destructor
		/*!
			Calls clear function to delete the nodes in the list.
		*/
		~SList();
		//! pushFront function, adds the given data to the front of the linked list.
		/*!
			\param data, a const reference to the data to be inserted in the list. 
		*/
		Iterator PushFront(const T& data);
		//! popFront function that deletes the first data in the list.
		void PopFront();
		//! PushBack function, insert the given data at the end of the list
		/*!
			\param data, a const reference to the data to be inserted into the list.
		*/
		Iterator PushBack(const T& data);
		//! function to return the size of the list.
		/*!
			Function is constant because it doesn't have to change any members and also the returned data shouldn't
			be modifialbe, so the return type is also a const int.
			\return a const int which is the size of the list
		*/
		unsigned int Size() const;
		//! function to check if the list is empty
		/*!
			Function that checks if the list is empty. Returns true if it empty, false otherwise.
			\return const bool value, true if list is empty, false otherwise.
		*/
		bool IsEmpty() const;
		//! function to clear the list and reset it.
		/*!
			Deletes all the nodes in the list and sets the front and back pointers to nullptr.
			Also sets the size to 0.
		*/
		void Clear();
		//! function that returns the first data in the list.
		/*!
			A const function that returns a const T reference so that it cannot be modified by other functions.
			it returns the first data in the list.
			\return Data in the first node of the list. It is a const T reference.
		*/
		const T& Front() const;
		//! function that returns the first data in the list.
		/*!
			A function that returns a T reference so that the data can be modified by other functions.
			it returns the first data in the list.
			\return Data in the first node of the list. It is a T reference.
		*/
		T& Front();
		//! function that returns the last data in the list.
		/*!
			A const function that returns a const T reference so that it cannot be modified by other functions.
			it returns the last data in the list.
			\return Data in the last node of the list. It is a const T reference.
		*/
		const T& Back() const;
		//! function that returns the last data in the list.
		/*!
			A function that returns a T reference so that it can be modified by other functions.
			it returns the last data in the list.
			\return Data in the last node of the list. It is a T reference.
		*/
		T& Back();

		//! Iterator const Begin function
		/*!
			The begin function returns a Iterator that points to the first node in the list.
			\return A iterator pointing to the first node.
		*/
		Iterator begin() const;
		//! Iterator end function
		/*!
			The end function returns a Iterator that points to the node next to the last node in the list.
			\return A iterator pointing to the node next to the last node.
		*/

		Iterator end() const;
		//! InsertAfter Function to insert a value after the given iterator
		/*!
			The insert after function takes in an iterator and inserts the value after the node the given iterator is pointing to.
			If the iterator is the end(), then inserts at the back of the list. 
			\param it an Iterator, the iterator which contains the node after which to insert the new value
			\param Value A const T reference to the value that has to be inserted.
		*/
		void InsertAfter(const Iterator& it,const T& value);
		//! Find function to find an item in the list
		/*!
			Takes in the value to be found and returns a Iterator that points to that value in the list. Returns end(), if the value
			is not there in the list.
			\Param value a Const T reference to the value that needs to be inserted in that list.
			\return an Iterator that points to the node the value is in. Returns end() if the value is not there in the list.
		*/
		Iterator Find(const T& value) const;
		//! RemoveAll function to remove all instances of a given value in the list.
		/*!
			Takes in the value to be removed from the list. If the list is empty throws an exception. If the value is not there in the list
			nothing happens.
			\param value a Const T reference to the value that needs to be deleted in that list.
		*/
		void RemoveAll(const T& value);
		//! Remove function to remove first instance of a given value in the list.
		/*!
			Takes in the value to be removed from the list. If the list is empty throws an exception. If the value is not there in the list
			nothing happens.
			\param value a Const T reference to the value that needs to be deleted in that list.
		*/
		void Remove(const T& value);

		void Remove(Iterator& it);

	};



#include "SList.inl"




	


}




#pragma once
#include <cstdio>
#include<cstdint>
#include <string>
#include "SList.h"
#include "Vector.h"
#include "DefaultHash.h"
#include "DefaultEquality.h"

namespace FieaGameEngine
{
	//! class HashMap
	/*!
		A Class That implements a HashMap using templates.
		The user can pass in their own HashFunctor class if they want to do custom hashing and a equality testing class.
	*/
	template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>, typename EqualityFunction = Equality<TKey>>
	class HashMap
	{
	public:
		typedef std::pair<TKey, TData>  PairType;			//typedef for the pairtype, the data to insert in the hashmap
		typedef SList<PairType> ChainType;					//typedef for the chain
		typedef Vector<ChainType> BucketType;				//typedef for the bucket
		typedef typename ChainType::Iterator ChainIterator;	//typedef for the iterator in the chain
		//! Class Iterator
		class Iterator
		{
			friend HashMap;		//Declare the HashMap class as a friend so it can access the private Data
		public:
			//! Default Iterator Constructor
			/*!
				We need a default constructor incase we want to defer the intialization of the iterator.
			*/
			Iterator();
			//!A function to overload the Pre Increment operator.
			/*!
				We overload the Pre Increment so that we can move the move the iterator to next valid entry in the hashmap.
				Throws an exception if the iterator is already at the end.
				\return A Iterator reference to the new incremented iterator.
			*/
			Iterator& operator++();
			//!A function to overload the Pre Increment operator.
			/*!
				We overload the Pre Increment so that we can move the move the iterator to next valid entry in the hashmap.
				Throws an exception if the iterator is already at the end.
				\return A copy of the Iterator before incrementing.
			*/
			Iterator operator++(int);
			//! A function overloading the Dereference operator
			/*!
				We overload the dereference operator to return the value held in the node the iterator refers to.
				\return A PairType reference to the value in that node in the chain
			*/
			PairType& operator*();
			//! A function overloading the Dereference operator
			/*!
				We overload the dereference operator to return the value held in the node the iterator refers to. Const version so that const
				functions and hashmaps can use it.
				\return A PairType reference to the value in that node in the chain
			*/
			const PairType& operator*() const;
			//! A function overloading the Arrow operator
			/*!
				We overload the arrow operator to return a pointer value held in the node the iterator refers to.
				\return A pointer to PairType in that node in the chain
			*/
			PairType* operator->();
			//! A function overloading the Arrow operator
			/*!
				We overload the arrow operator to return a pointer value held in the node the iterator refers to. Const version so that const
				functions and hashmaps can use it.
				\return A pointer to constant PairType in that node in the chain
			*/
			const PairType* operator->() const;
			//! A function overloading the equality operator
			/*!
				We overload the equality operator so we can compare 2 iterators. First it checks if the owners are the same and then
				it checks the size and chainIterator. returns true if its same else returns false.
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

			//Default the copy constructors and the move constructors
			Iterator(Iterator&& rhs) = default;
			Iterator& operator=(Iterator&& rhs) = default;
			Iterator(const Iterator& rhs) = default;
			Iterator& operator=(const Iterator& ths) = default;
			~Iterator() = default;
		private:
			//! A parameterized constructor.
			/*!
				\Param owner Const HashMap reference, a reference to the HashMap that the iterator belongs to.
				\Param chainIterator a chainIterator type, The iterator of the node of the current chain the hashmap data is on.
				\param bucketIndex a unsigned int, which is the index on which the chain is on in the bucket.

			*/
			Iterator(const HashMap& owner, const typename ChainIterator& chainIterator, const uint32_t bucketIndex);
			ChainIterator mChainIterator;/*<!  The iterator of the node of the current chain the hashmap data is on.*/
			uint32_t mBucketIndex;/*<! the index on which the chain is on in the bucket.*/
			const HashMap* mOwner; /*<!	pointer to the HashMap that the iterator belongs to.*/
		};

		//!parameterized constructor
		/*!
			constructor that takes in the bucketsize of the HashMap. It is defaulted to 10
			\param BucketSize, an unsigned integer which is the bucketsize of the vector.
		*/
		explicit HashMap(uint32_t bucketSize = 10);
		//!constructor to create a hashmap with an intializer list
		/*!
			constructor that takes in the intializer list of pairs.
			\param intializer list
		*/
		HashMap(std::initializer_list<PairType> list);
		//!Find function
		/*!
			Looks up the given key in the hashmap and returns an iterator to the node which contains that key.
			Returns end() if the key is not there in the list.
			\param key, a const TKey reference to the key to search for
			\return an iterator to the node in the hashmap which contains the key.
		*/
		Iterator Find(const TKey& key) const;
		//!Insert Function
		/*!
			takes in a key, value pair. Computes the hash for the  key and inserts it at its appropriate location in the hashmap and returns an
			iterator to the new node.
			If the key is already there in the hashmap, returns an iterator to the existing value.
			\param entry, a pairtype reference to the data to be inserted in the hashmap
			\return an iterator, to the existing or newly inserted node.
		*/
		Iterator Insert(const PairType& entry);
		//!Insert Function
		/*!
			takes in a key, value pair. Computes the hash for the  key and inserts it at its appropriate location in the hashmap and returns an
			iterator to the new node. Also takes in a bool and sets it to true if a new entry was made. If not sets it to false.
			If the key is already there in the hashmap, returns an iterator to the existing value.
			\param entry, a pairtype reference to the data to be inserted in the hashmap
			\param wasInserted, a bool reference to the boolean to be set if the data was inserted.
			\return an iterator, to the existing or newly inserted node.
		*/
		Iterator Insert(const PairType& entry, bool& wasInserted);
		//! Function to overload the [] operator
		/*!
			Overload the [] operator to return the data corresponding to the key. If the key is already not there, then creates a new entry with
			the given key and sets the value to its default constructed state. Returns a reference to the data so the user can modify it.
			\param key, a const TKey reference to the key whose value has to be returned.
			\return a TData reference to the data corresponding to the key.
		*/
		TData& operator[](const TKey& key);
		//! Remove function to remove the entry corresponding to the key.
		/*!
			Takes in the value to be removed from the hashmap. If the key is not there in the hash map
			returns false, else returns true after removing it.
			\param value a Const T reference to the key that needs to be deleted from the hashmap.
			\return bool, returns true if the entry was deleted, else returns false.
		*/
		bool Remove(const TKey& key);
		//! Clear function
		/*!
			Calls clear function which clears and deletes all the slist nodes that were inserted. Sets all lists to empty.
		*/
		void Clear();
		//! function to return the size(number of elements in the Hashmap).
		/*!
			Function is constant because it doesn't have to change any members.
			\return a unsigned int which is the number of entries in the hashmap
		*/
		uint32_t Size() const;
		//! ContainsKey function
		/*!
			Function that takes in a ket and checks if the key exists in the hasp map. returns true if it exists, false otherwise.
			\param key, a const TKey reference to the key to search for.
			\return bool, true if the key exists in the hashmap, false otherwise.
		*/
		bool ContainsKey(const TKey& key) const;
		//! const ContainsKey function
		/*!
			Function that takes in a ket and a data reference. checks if the key exists in the hasp map.
			returns true if it exists and sets the data parameter passed to the data corresponding to the key, false otherwise.
			\param key, a const TKey reference to the key to search for.
			\return bool, true if the key exists in the hashmap, false otherwise.
		*/
		bool ContainsKey(const TKey& key, TData& data) const;
		//! At function
		/*!
			Returns the data corresponding to the given key. If the key is not there,throws an exception.
			Returns a reference to the data so the user can modify it.
			\param key, a const TKey reference to the key whose value has to be returned.
			\return a TData reference to the data corresponding to the key.
		*/
		TData& At(const TKey& key);
		//!const At function
		/*!
			Returns the data corresponding to the given key. If the key is not there,throws an exception.
			Returns a const reference to the data so the user cannot modify it.
			\param key, a const TKey reference to the key whose value has to be returned.
			\return a const TData reference to the data corresponding to the key.
		*/
		const TData& At(const TKey& key) const;
		//! Begin function
		/*!
			The begin function returns a Iterator that points to the first valid entry in the hashmap.
			throws an exception if the map is empty.
			\return A iterator pointing to the first entry.
		*/
		Iterator begin() const;
		//! Iterator end function
		/*!
			The end function returns a Iterator with the index of size and the chainIterator set to the end of the last chain in the bucket.
			\return A iterator.
		*/
		Iterator end() const;
		//default the move and copy constructors and assignment operators.
		HashMap(HashMap&& rhs);
		HashMap& operator=(HashMap&& rhs);
		HashMap(const HashMap& rhs) = default;
		HashMap& operator=(const HashMap& rhs) = default;
		~HashMap() = default;
	private:
		//!Find function
		/*!
			Looks up the given key in the hashmap and returns an iterator to the node which contains that key.
			Takes in a uint32_t hash parameter and sets it to the hash that has been calculated for the key so that we don't have to
			recalculate the hash when we r inserting the key.
			Returns end() if the key is not there in the list.
			\param key, a const TKey reference to the key to search for.
			\param hash, a uint32_t reference to the hash variable that has to be set.
			\return an iterator to the node in the hashmap which contains the key.
		*/
		Iterator Find(const TKey& key, uint32_t& hash) const;
		BucketType mBucket;	/*<! Bucket of the hashmap that contains all the chains into the which the keys are hashed to.*/
		HashFunctor mHashFunction; /*<! hashfunctor object*/
		EqualityFunction mEquals;	/*! equality functor object.*/
		uint32_t mSize;	/*<! holds the number of entries in the hashmap*/
	};

	#include "HashMap.inl"
}
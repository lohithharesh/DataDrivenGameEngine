#pragma once
#include "Datum.h"
#include "RTTI.h"
#include "HashMap.h"
namespace FieaGameEngine
{
	//Forward declate the RTTI class
	class RTTI;
	//!Scope class
	class Scope : public RTTI
	{
		//RTTI declarations macro.
		RTTI_DECLARATIONS(Scope, RTTI)
	public:
		//typedef for the pair
		typedef std::pair<std::string, Datum> ScopePairType;
		//Typedef for the iterator in the hashmap
		typedef HashMap<std::string, Datum>::Iterator MapIterator;
		//!Default constructor.
		/*!
			Default constructor that intializes the hashmap and the vector.
			\param size, a unsigned int which is the size of the hashmap. It is defaulted to 10.
		*/
		explicit Scope(uint32_t size = 10U);
		//!Copy Constructor
		/*!
			Copy constructor which performs a deep copy of the vector and hashmap.
		*/
		Scope(const Scope&);
		//!Assignment operator
		/*!
			Overload the default assignment operator so we can perform a deep copy.
		*/
		Scope& operator=(const Scope&);
		//!Move constructor
		/*!
			Overload the move constructor. 
		*/
		Scope(Scope&&);
		Scope& operator=(Scope&&);
		//!Find function
		/*!
			Takes in a string and returns a datum corresponding to the string in the scope.
			returns a nullptr if the string doesn't exist in the current scope.
			\param key, a const string reference to the key.
			\return a pointer to the datum corresponding to the the string.
		*/
		Datum* Find(const std::string& key) const;
		//!Search function
		/*!
			Search for a given key in the scope. If it doesnt exist in the current scope,
			it searches in it's ancestors. Returns the datum corresponding to the key.
			\param key, a const string reference to the key to search for.
			\param, a pointer reference to a scope. Sets it to the scope that contains the string.
			\return, a pointer to the dataum corresponding to the key. Returns nullptr if the key doesn't exist.
		*/
		Datum* Search(const std::string& key, Scope*& foundScope) const;
		//!Search function
		/*!
			Search for a given key in the scope. If it doesnt exist in the current scope,
			it searches in it's ancestors. Returns the datum corresponding to the key.
			\param key, a const string reference to the key to search for.
			\return, a pointer to the dataum corresponding to the key. Returns nullptr if the key doesn't exist.
		*/
		Datum* Search(const std::string& key) const;
		//!Append function
		/*!
			Append function appends a string datum pair to the scope. Takes in a key 
			and creates a new datum entry for that. Returns a reference to that datum.
			If the key already exists, returns a reference to that corresponding datum.
			\param key, a const string reference to the key
			\return a datum reference to the newly created or the already existing datum for the key.
		*/
		Datum& Append(const std::string& key);
		//!AppendScope function
		/*!
			Appends a child scope to the current scope. Takes in a key and creates a new datum of
			scopes corresponding to the key. If the key already exists, then pushes the scope into
			that datum.
			\param key, a const string reference to the key
			\return a scope reference to the newly appended scope
		*/
		Scope& AppendScope(const std::string& key);
		//!Orphan function
		/*!
			Remove the given child scope from the current scope. If the current scope is not the
			parent of the given child, then throws an exception.
			\param child, a scope reference to the child to be removed.
		*/
		std::string Orphan(Scope& child);
		//!Adopt function
		/*!
			Adopt the given child scope into the current scope. Creates a new entry in the scope
			with the given key and the child. if the key already exists, then appends it to that field.
			\param child, a scope reference to the child scope
			\key, a const string reference to the key
		*/
		void Adopt(Scope& child, const std::string& key);
		//!GetParent function
		/*!
			Returns the parent of the current scope.
			\return, Scope pointer to the parent.
		*/
		Scope* GetParent() const;
		//!Operator[] function overloaded for a key
		/*!
			overload the [] oerator so we can use the key to retrive a reference to the datum
			corresponding to the key. Calls append so that it inserts a new key and datum if 
			the given key  doesn't exist.s
			\param key, a const string reference to the key.
			\return a datum reference to the datum corresponding to the key.
		*/

		Datum& operator[](const std::string& key);
		//!Operator[] function overloaded for the index
		/*!
			overload the operator[] so we can use it to retrive a datum from the ordered vector 
			in o(1) time. Throws an exception if the index is out of bounds
			\param index, a unsigned integer which is the index to the datum in the vector.
			\return a datum reference to the datum at the given index.
		*/
		Datum& operator[](uint32_t index);
		//!Operator== 
		/*!
			overload the operator== so we can do our own custom comparison. Compares individual 
			entries in the ordered vector. Doesn't enforce order of inserts. Compares only the datums present.
			\param rhs, a const reference to the rhs of the operator.
			\return, a bool which is true if the scopes are equivalent.
		*/
		bool operator==(const Scope& rhs) const;
		//!Operator!=
		/*!
			overload the operator!= so we can do our own custom comparison. Returns the Boolean
			Not of the operator==().
			\param rhs, a const reference to the rhs of the operator
			\return a bool, which is true if the scopes are different.
		*/
		bool operator!=(const Scope& rhs) const;
		//!FindName function
		/*!
			FindName function that returns the name(key) corresponding to the datum that contains
			the given scope. returns empty string if the scope doesn't exist in the current scope.
			\param value, a const scope reference to the scope to search for.
			\return a string which is the key corresponding to the datum
		*/
		std::string FindName(const Scope& value) const;
		//!Clear function
		/*!
			Clear the scope. Deletes all the child scope it contains and resets the hashmap and the
			ordered vector.
		*/
		void Clear();
		//!Destructor
		virtual ~Scope();
		//!ToString function
		/*!
			returns a string version of the scope.
			\return a string.
		*/
		virtual std::string ToString() const override;
		//!Equals function
		/*!
			Overrides the RTTI implementation so that it can be invoked polymorphically.
			call the operator==().
			\param rhs, a RTTI pointer to be compared with.
			\return a bool which is true if both the scopes are equivalent
		*/
		virtual bool Equals(const RTTI* rhs) const override;
		
	protected:
		const Vector<ScopePairType*>& GetOrderedVector() const;
		virtual Scope* Clone(const Scope& rhs);
		
	private:
		HashMap<std::string, Datum> mTableMap;
		Vector<ScopePairType*> mOrderedVector;
		Scope* mParent;
		std::string FindName(const Scope& value, Datum*& datmRef, uint32_t& index) const;
		Datum& Append(const std::string& key, bool& wasInserted);
		

	};



}
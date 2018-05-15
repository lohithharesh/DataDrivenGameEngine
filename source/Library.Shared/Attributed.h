#pragma once
#include "Scope.h"
#include "AttributedTypeManager.h"

namespace FieaGameEngine
{
	//!Attributed Class
	class Attributed : public Scope
	{
		//!RTTI Declarations
		RTTI_DECLARATIONS(Attributed, Scope)
	public:
	
		//!Copy Constructor
		/*!
			calls copy assignment operator.
			\param a const attributed reference to the rhs of the assignment operator
		*/
		Attributed(const Attributed& rhs);
		//!Move constructor
		/*!
			calls the move assignment operator.
			\param a r-value reference to the rhs of the assignment operator
		*/
		Attributed(Attributed&& rhs);
		//!copy assignment operator
		/*!
			calls the scope's copy assignment operator and sets 'this' after copying data.
			\param a const attributed reference to the rhs of the assignment operator.
			\return a attributed reference to the attribute after copying.
		*/
		Attributed& operator=(const Attributed& rhs);
		//!copy assignment operator
		/*!
			calls the scope's move assignment operator and sets 'this' after moving data.
			\param a const attributed reference to the rhs of the assignment operator.
			\return a attributed reference to the attribute after moving.
		*/
		Attributed& operator=(Attributed&& rhs);
		//!IsAttribute function
		/*!
			checks if the given string is an attribute of the class
			\param a const string reference to the key
			\return a bool, true if the given key is an attribute of the class
		*/
		bool IsAttribute(const std::string& key) const;
		//!IsPrescribed function
		/*!
		checks if the given string is a prescribed attribute of the class
		\param a const string reference to the key
		\return a bool, true if the given key is a prescribed attribute of the class
		*/
		bool IsPrescribed(const std::string& key) const;
		//!IsAuxillary function
		/*!
		checks if the given string is an auxillary attribute of the class
		\param a const string reference to the key
		\return a bool, true if the given key is an auxillary attribute of the class
		*/
		bool IsAuxillary(const std::string& key) const;
		//!AppendAuxillaryAttributed function
		/*!
			takes in a key and returns a datum (a new one is added to the scope if the key doesn't already exist or returns the datum corresponding
			to the key if it already exists). This way we can add attributes to an instance of a class at runtime.
			\param const string reference to the key
			\return a datum reference to the datum that is created/already exists in the scope
		*/
		Datum& AppendAuxillaryAttribute(const std::string& key);
		//!Prescribed function
		/*!
			returns a list of all the prescribed attributes of the class
			\return a vector of strings containing the names of the prescribed attributes in the class
		*/
		const Vector<std::string> Prescribed() const;
		//!Auxillary function
		/*!
			returns a list of all the auxillary attributes of the class
			\return a vector of strings containing the names of the auxillary attributes in the class
		*/
		const Vector<std::string> Auxillary() const;
		//!Attributes function
		/*!
			returns a list of all the attributes of the class
			\return a vector of strings containing the names of the attributes in the class
		*/
		const Vector<std::string> Attributes() const;
		
		//!Attributed destructor
		~Attributed() = default;
		const Vector<ScopePairType*> AuxillaryPairs() const;
	protected:
		Attributed(uint64_t id);
		virtual Scope* Clone(const Scope& rhs) override;
		//!PopulateHashMap function
		/*!
			A helper function which takes in a vector of strings which is a list of names of all the prescribed attributes in  the class
			and adds it to the static hash map.
			\param a const reference to a vector of strings containing the names of the prescribed attributes. 
		*/
		void populate(uint64_t typeId);
		void UpdateSignatures(uint64_t id);
		private:
			uint64_t mTypeId;

	};


}

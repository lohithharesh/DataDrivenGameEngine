#pragma once
#pragma warning (push)
#pragma warning (disable : 4201)
#include "glm\glm.hpp"
#include "glm\gtx\string_cast.hpp"
#pragma warning(pop)
#include "HashMap.h"

namespace FieaGameEngine
{
	class Scope;
	class RTTI;
	//!Enum of datatypes
	/*!
		Enum of all the datatypes that the Datum supports.
	*/
	enum class DatumTypeEnum
	{
		Unknown,
		Integer,
		Float,
		String,
		Vector,
		Matrix,
		RTTI,
		Table,
		NumberOfTypes
	};
	//! class Datum
	/*!
		A Class That implements a Datum.
		Currently supports 6 datatypes. (int, float, vec4, mat4, string, RTTI)
	*/
	class Datum final
	{
	public:
		Datum();
		//! Copy Constructor
		/*!
			Copy Constructor to initalize a Datum object with another. Performs a deep copy.
			\param rhs a const reference to the Datum to intialize it with.
		*/
		Datum(const Datum& rhs);
		Datum(Datum&& rhs);
		//!parameterized constructor - Integer
		/*!
			constructor that takes in a integer and makes the datum a scalar integer type.
			\param rhs, an integer which is the value of the scalar datum.
		*/
		Datum(int32_t rhs);
		//!parameterized constructor - Float
		/*!
			constructor that takes in a float and makes the datum a scalar float type.
			\param rhs, a float which is the value of the scalar datum.
		*/
		Datum(float rhs);
		//!parameterized constructor - Vector
		/*!
			constructor that takes in a vec4 and makes the datum a scalar vec4 type.
			\param rhs, a vec4 which is the value of the scalar datum.
		*/
		Datum(const glm::vec4& rhs);
		//!parameterized constructor - Matrix
		/*!
			constructor that takes in a mat4 and makes the datum a scalar mat4 type.
			\param rhs, a mat4 which is the value of the scalar datum.
		*/
		Datum(const glm::mat4& rhs);
		//!parameterized constructor - String
		/*!
			constructor that takes in a string and makes the datum a scalar string type.
			\param rhs, a string which is the value of the scalar datum.
		*/
		Datum(const std::string& rhs);
		//!parameterized constructor - RTTI
		/*!
			constructor that takes in a RTTI* and makes the datum a scalar RTTI* type.
			\param rhs, a RTTI* which is the value of the scalar datum.
		*/
		Datum(RTTI* rhs);
		//!parameterized constructor - Scope
		/*!
			constructor that takes in a Scope* and makes the datum a scalar RTTI* type.
			\param rhs, a Scope* which is the value of the scalar datum.
		*/
		Datum(Scope* rhs);
		//! function overloading the default assignment operator
		/*!
			Overload the default assignment operator so we can perform a deep copy.
			\param rhs a const reference to the Datum on the rhs of the assignment operator.
		*/
		Datum& operator=(const Datum& rhs);
		Datum& operator=(Datum&& rhs);
		//! function overloading the default assignment operator - Integer
		/*!
			Overload the default assignment operator so we can do scalar assignment to the datum.
			\param rhs an integer value, to which the datum has to be set.
		*/
		Datum& operator=(int32_t rhs);
		//! function overloading the default assignment operator - Float
		/*!
			Overload the default assignment operator so we can do scalar assignment to the datum.
			\param rhs a float value, to which the datum has to be set.
		*/
		Datum& operator=(float rhs);
		//! function overloading the default assignment operator - Vector
		/*!
			Overload the default assignment operator so we can do scalar assignment to the datum.
			\param rhs a vec4 reference, to which the datum has to be set.
		*/
		Datum& operator=(const glm::vec4& rhs);
		//! function overloading the default assignment operator - Matrix
		/*!
			Overload the default assignment operator so we can do scalar assignment to the datum.
			\param rhs a mat4 reference, to which the datum has to be set.
		*/
		Datum& operator=(const glm::mat4& rhs);
		//! function overloading the default assignment operator - String
		/*!
			Overload the default assignment operator so we can do scalar assignment to the datum.
			\param rhs a string reference, to which the datum has to be set.
		*/
		Datum& operator=(const std::string& rhs);
		//! function overloading the default assignment operator - RTTI
		/*!
			Overload the default assignment operator so we can do scalar assignment to the datum.
			\param rhs a RTTI* pointer, to which the datum has to be set.
		*/
		Datum& operator=(RTTI* rhs);
		//! function overloading the default assignment operator - Scope
		/*!
			Overload the default assignment operator so we can do scalar assignment to the datum.
			\param rhs a Scope* pointer, to which the datum has to be set.
		*/
		Datum& operator=(Scope* rhs);
		//!Type function.
		/*!
			Type function which returns the type of the datum
			\return Type, a DatumTypeEnum type which is the type of the datum.
		*/
		DatumTypeEnum Type() const;
		//!SetType function.
		/*!
			SetType function which sets the type of the datum to the given type.
			\param Type, a DatumTypeEnum type which is the type of the datum to be set.
		*/
		void SetType(DatumTypeEnum type);
		//!Size function.
		/*!
			Size function which returns the Size of the datum (number of values in the datum).
			\return a uint32_t which is the size of the datum.
		*/
		uint32_t Size() const;
		//!Resize function.
		/*!
			ReSize function which resizes the datum array to the given size. Elements are deleted if the size is lesser than the current size.
			Capacity is set to the given size.
			\param size, a uint32_t which is the new size of the datum
		*/
		void Resize(uint32_t size);
		//!Clear function.
		/*!
			Clear function clears all the data in the datum and sets the size to 0
		*/
		void Clear();
		
		//!SetStorage Function - Integer
		/*!
			Datum points to data in external storage. cannot modify the size or type of the external data. 
			Can only change the values of the data.
			\param inputArray, an integer array to which the datum has to point to.
			\param size, uint32_t which is the size of the array.
		*/
		void SetStorage(int32_t* inputArray, uint32_t size);
		//!SetStorage Function - Float
		/*!
			Datum points to data in external storage. cannot modify the size or type of the external data.
			Can only change the values of the data.
			\param inputArray, a float array to which the datum has to point to.
			\param size, uint32_t which is the size of the array.
		*/
		void SetStorage(float* inputArray, uint32_t size);
		//!SetStorage Function - Vector
		/*!
			Datum points to data in external storage. cannot modify the size or type of the external data.
			Can only change the values of the data.
			\param inputArray, a vec4 array to which the datum has to point to.
			\param size, uint32_t which is the size of the array.
		*/
		void SetStorage(glm::vec4* inputArray, uint32_t size);
		//!SetStorage Function - Matrix
		/*!
			Datum points to data in external storage. cannot modify the size or type of the external data.
			Can only change the values of the data.
			\param inputArray, a mat4 array to which the datum has to point to.
			\param size, uint32_t which is the size of the array.
		*/
		void SetStorage(glm::mat4* inputArray, uint32_t size);
		//!SetStorage Function - String
		/*!
			Datum points to data in external storage. cannot modify the size or type of the external data.
			Can only change the values of the data.
			\param inputArray, a String array to which the datum has to point to.
			\param size, uint32_t which is the size of the array.
		*/
		void SetStorage(std::string* inputArray, uint32_t size);
		//!SetStorage Function - RTTI
		/*!
			Datum points to data in external storage. cannot modify the size or type of the external data.
			Can only change the values of the data.
			\param inputArray, an array of RTTI pointers to which the datum has to point to.
			\param size, uint32_t which is the size of the array.
		*/
		void SetStorage(RTTI** inputArray, uint32_t size);
		void SetStorage(void* inputArray, uint32_t size);
		//! A function overloading the equality operator
		/*!
			We overload the equality operator so we can compare 2 Datums. Checks if the size is same and then the type of data and each data value.
			\param rhs, const Datum reference to the rhs of the equality operator.
			\return A boolean which is true if the Datums are the same. False otherwise.
		*/
		bool operator==(const Datum& rhs) const;
		//! A function overloading the equality operator - Integer
		/*!
			We overload the equality operator so we can do scalar comparison.
			Checks if the size is 1 and then the type of data and data value.
			\param rhs, integer on the rhs of the assignment operator.
			\return A boolean which is true if the Datum value is the same as the integer. False otherwise.
		*/
		bool operator==(int32_t rhs) const;
		//! A function overloading the equality operator - Float
		/*!
			We overload the equality operator so we can do scalar comparison.
			Checks if the size is 1 and then the type of data and data value.
			\param rhs, float on the rhs of the assignment operator.
			\return A boolean which is true if the Datum value is the same as the float. False otherwise.
		*/
		bool operator==(float rhs) const;
		//! A function overloading the equality operator
		/*!
			We overload the equality operator so we can do scalar comparison.
			Checks if the size is 1 and then the type of data and data value.
			\param rhs, vec4 reference to the rhs of the assignment operator.
			\return A boolean which is true if the Datum value is the same as the mat4. False otherwise.
		*/
		bool operator==(const glm::vec4& rhs) const;
		//! A function overloading the equality operator
		/*!
			We overload the equality operator so we can do scalar comparison.
			Checks if the size is 1 and then the type of data and data value.
			\param rhs, mat4 reference to the rhs of the assignment operator.
			\return A boolean which is true if the Datum value is the same as the mat4. False otherwise.
		*/
		bool operator==(const glm::mat4& rhs) const;
		//! A function overloading the equality operator
		/*!
			We overload the equality operator so we can do scalar comparison.
			Checks if the size is 1 and then the type of data and data value.
			\param rhs, vector reference to the rhs of the assignment operator.
			\return A boolean which is true if the Datum value is the same as the vector. False otherwise.
		*/
		bool operator==(const std::string& rhs) const;
		//! A function overloading the equality operator
		/*!
			We overload the equality operator so we can do scalar comparison.
			Checks if the size is 1 and then the type of data and data value.
			\param rhs, RTTI pointer on the rhs of the assignment operator.
			\return A boolean which is true if the Datum value is the same as the rhs. False otherwise.
		*/
		bool operator==(RTTI* rhs) const;
		//! A function overloading the equality operator
		/*!
			We overload the equality operator so we can do scalar comparison.
			Checks if the size is 1 and then the type of data and data value.
			\param rhs, Scope pointer on the rhs of the assignment operator.
			\return A boolean which is true if the Datum value is the same as the rhs. False otherwise.
		*/
		bool operator==(Scope* rhs) const;
		//! A function overloading the inequality operator
		/*!
			We overload the inequality operator so we can compare 2 Datums. 
			Checks if the size is same and then the type of data and each data value.
			\param rhs, const Datum reference to the rhs of the equality operator.
			\return A boolean which is true if the Datums are different. False otherwise.
		*/
		bool operator!=(const Datum& rhs) const;
		//! A function overloading the inequality operator - Integer
		/*!
			We overload the inequality operator so we can do scalar comparison.
			Checks if the size is 1 and then the type of data and data value.
			\param rhs, Integer on the rhs of the assignment operator.
			\return A boolean which is true if the Datum value is the different from the Integer. False otherwise.
		*/
		bool operator!=(int32_t rhs) const;
		//! A function overloading the inequality operator - float
		/*!
			We overload the inequality operator so we can do scalar comparison.
			Checks if the size is 1 and then the type of data and data value.
			\param rhs, float on the rhs of the assignment operator.
			\return A boolean which is true if the Datum value is the different from the float. False otherwise.
		*/
		bool operator!=(float rhs) const;
		//! A function overloading the in0equality operator - Vector
		/*!
			We overload the inequality operator so we can do scalar comparison.
			Checks if the size is 1 and then the type of data and data value.
			\param rhs, float on the rhs of the assignment operator.
			\return A boolean which is true if the Datum value is the different from the vector. False otherwise.
		*/
		bool operator!=(const glm::vec4& rhs) const;
		//! A function overloading the in0equality operator - Matrix
		/*!
			We overload the inequality operator so we can do scalar comparison.
			Checks if the size is 1 and then the type of data and data value.
			\param rhs, Matrix on the rhs of the assignment operator.
			\return A boolean which is true if the Datum value is the different from the Matrix. False otherwise.
		*/
		bool operator!=(const glm::mat4& rhs) const;
		//! A function overloading the in0equality operator - String
		/*!
			We overload the inequality operator so we can do scalar comparison.
			Checks if the size is 1 and then the type of data and data value.
			\param rhs, string on the rhs of the assignment operator.
			\return A boolean which is true if the Datum value is the different from the string. False otherwise.
		*/
		bool operator!=(const std::string& rhs) const;
		//! A function overloading the in0equality operator - RTTI
		/*!
			We overload the inequality operator so we can do scalar comparison.
			Checks if the size is 1 and then the type of data and data value.
			\param rhs, RTTI pointer on the rhs of the assignment operator.
			\return A boolean which is true if the Datum value is the different from the RTTI pointer. False otherwise.
		*/
		bool operator!=(RTTI* rhs) const;
		//! A function overloading the in0equality operator - Scope
		/*!
			We overload the inequality operator so we can do scalar comparison.
			Checks if the size is 1 and then the type of data and data value.
			\param rhs, Scope pointer on the rhs of the assignment operator.
			\return A boolean which is true if the Datum value is the different from the RTTI pointer. False otherwise.
		*/
		bool operator!=(Scope* rhs) const;
		template<typename T>
		T& Get(uint32_t index = 0);
		//!Get Method - Integer
		/*!
			Returns the integer value at the given index. Index is defaulted to 0 so we can use get for scalar without
			specifying the index.
			\param index, a uint32_t index to the value to be returned.
			\return a int32_t reference to the value at the given index.
		*/
		template<>
		int32_t& Get<int32_t>(uint32_t index);
		//!Get Method - Float
		/*!
			Returns the Float value at the given index. Index is defaulted to 0 so we can use get for scalar without
			specifying the index.
			\param index, a uint32_t index to the value to be returned.
			\return a Float reference to the value at the given index.
		*/
		template<>
		float& Get<float>(uint32_t index);
		//!Get Method - String
		/*!
			Returns the string value at the given index. Index is defaulted to 0 so we can use get for scalar without
			specifying the index.
			\param index, a uint32_t index to the value to be returned.
			\return a string reference to the value at the given index.
		*/
		template<>
		std::string& Get<std::string>(uint32_t index);
		//!Get Method - Vector
		/*!
			Returns the vec4 value at the given index. Index is defaulted to 0 so we can use get for scalar without
			specifying the index.
			\param index, a uint32_t index to the value to be returned.
			\return a vec4 reference to the value at the given index.
		*/
		template<>
		glm::vec4& Get<glm::vec4>(uint32_t index);
		//!Get Method - Matrix
		/*!
			Returns the mat4 value at the given index. Index is defaulted to 0 so we can use get for scalar without
			specifying the index.
			\param index, a uint32_t index to the value to be returned.
			\return a mat4 reference to the value at the given index.
		*/
		template<>
		glm::mat4& Get<glm::mat4>(uint32_t index);
		//!Get Method - RTTI
		/*!
			Returns the RTTI* value at the given index. Index is defaulted to 0 so we can use get for scalar without
			specifying the index.
			\param index, a uint32_t index to the value to be returned.
			\return a RTTI* reference to the value at the given index.
		*/
		template<>
		RTTI*& Get<RTTI*>(uint32_t index);
		//!Get Method - Table
		/*!
			Returns the Scope* value at the given index. Index is defaulted to 0 so we can use get for scalar without
			specifying the index.
			\param index, a uint32_t index to the value to be returned.
			\return a Scope* reference to the value at the given index.
		*/
		template<>
		Scope& Get<Scope>(uint32_t index);

		template<typename T>
		const T& Get(uint32_t index = 0) const;
		//!Const Get Method - Integer
		/*!
			Returns the const reference to the value at the given index. Index is defaulted to 0 so we can use get for scalar without
			specifying the index.
			\param index, a uint32_t index to the value to be returned.
			\return a const integer reference to the value at the given index.
		*/
		template<>
		const int32_t& Get<int32_t>(uint32_t index) const;
		//!Const Get Method - Float
		/*!
			Returns the const reference to the value at the given index. Index is defaulted to 0 so we can use get for scalar without
			specifying the index.
			\param index, a uint32_t index to the value to be returned.
			\return a const float reference to the value at the given index.
		*/
		template<>
		const float& Get<float>(uint32_t index) const;
		//!Const Get Method - String
		/*!
			Returns the const reference to the value at the given index. Index is defaulted to 0 so we can use get for scalar without
			specifying the index.
			\param index, a uint32_t index to the value to be returned.
			\return a const String reference to the value at the given index.
		*/
		template<>
		const std::string& Get<std::string>(uint32_t index) const;
		//!Const Get Method - Vector
		/*!
			Returns the const reference to the value at the given index. Index is defaulted to 0 so we can use get for scalar without
			specifying the index.
			\param index, a uint32_t index to the value to be returned.
			\return a const vec4 reference to the value at the given index.
		*/
		template<>
		const glm::vec4& Get<glm::vec4>(uint32_t index) const;
		//!Const Get Method - Matrix
		/*!
			Returns the const reference to the value at the given index. Index is defaulted to 0 so we can use get for scalar without
			specifying the index.
			\param index, a uint32_t index to the value to be returned.
			\return a const mat4 reference to the value at the given index.
		*/
		template<>
		const glm::mat4& Get<glm::mat4>(uint32_t index) const;
		//!Const Get Method - RTTI
		/*!
			Returns the const reference to the value at the given index. Index is defaulted to 0 so we can use get for scalar without
			specifying the index.
			\param index, a uint32_t index to the value to be returned.
			\return a const RTTI reference to the value at the given index.
		*/
		template<>
		RTTI* const& Get<RTTI*>(uint32_t index) const;
		//!Const Get Method - Table
		/*!
			Returns the const reference to the value at the given index. Index is defaulted to 0 so we can use get for scalar without
			specifying the index.
			\param index, a uint32_t index to the value to be returned.
			\return a const Scope reference to the value at the given index.
		*/
		template<>
		const Scope& Get<Scope>(uint32_t index) const;
		//!Set Method - Integer
		/*!
			Sets the Integer value at the given index. Index is defaulted to 0 so we can use set for scalar without
			specifying the index.
			\param value, a integer to be set at the given index.
			\param index, a uint32_t index to the value to be returned.
		*/
		void Set(int32_t value, uint32_t index = 0);
		//!Set Method - Integer
		/*!
			Sets the float value at the given index. Index is defaulted to 0 so we can use set for scalar without
			specifying the index.
			\param value, a float to be set at the given index.
			\param index, a uint32_t index to the value to be returned.
		*/
		void Set(float value, uint32_t index = 0);
		//!Set Method - String
		/*!
			Sets the String at the given index. Index is defaulted to 0 so we can use set for scalar without
			specifying the index.
			\param value, a const string reference to the string to be set at the given index.
			\param index, a uint32_t index to the value to be returned.
		*/
		void Set(const std::string& value, uint32_t index = 0);
		//!Set Method - Matrix
		/*!
			Sets the Vector value at the given index. Index is defaulted to 0 so we can use set for scalar without
			specifying the index.
			\param value, a const Vector reference to the Vector to be set at the given index.
			\param index, a uint32_t index to the value to be returned.
		*/
		void Set(const glm::vec4& value, uint32_t index = 0);
		//!Set Method - Matrix
		/*!
			Sets the Matrix value at the given index. Index is defaulted to 0 so we can use set for scalar without
			specifying the index.
			\param value, a const matrix reference to the matrix to be set at the given index.
			\param index, a uint32_t index to the value to be returned.
		*/
		void Set(const glm::mat4& value, uint32_t index = 0);
		//!Set Method - RTTI
		/*!
			Sets the RTTI* value at the given index. Index is defaulted to 0 so we can use set for scalar without
			specifying the index.
			\param value, a RTTI pointer to be set at the given index.
			\param index, a uint32_t index to the value to be returned.
		*/
		void Set(RTTI* value, uint32_t index = 0);
		//!Const Get Method - Integer
		/*!
			Returns the const reference to the value at the given index. Index is defaulted to 0 so we can use get for scalar without
			specifying the index.
			\param index, a uint32_t index to the value to be returned.
			\return a const Scope reference to the value at the given index.
		*/
		void Set(Scope* value, uint32_t index = 0);
		//! function to reserve memory with the given capacity for the array.
		/*
			Change the capacity of the array by the given value without affecting the elements already
			present. Capacity cannot be less than the size.
			\param capacity, a unsigned integer which is the new capacity.
			\return a bool which is true if the capacity was changed.
		*/
		bool Reserve(uint32_t capacity);
		
		//! PushBack function, insert the given Integer at the end of the Vector
		/*!
			\param value, a integer to be inserted into the Vector.
		*/
		void PushBack(int32_t value);
		//! PushBack function, insert the given float at the end of the Vector
		/*!
			\param value, a float to be inserted into the Vector.
		*/
		void PushBack(float value);
		//! PushBack function, insert the given string at the end of the Vector
		/*!
			\param value, a const string reference to the string to be inserted into the Vector.
		*/
		void PushBack(const std::string& value);
		//! PushBack function, insert the given vec4 at the end of the Vector
		/*!
			\param value, a const vec4 reference to the string to be inserted into the Vector.
		*/
		void PushBack(const glm::vec4& value);
		//! PushBack function, insert the given mat4 at the end of the Vector
		/*!
			\param value, a const mat4 reference to the string to be inserted into the Vector.
		*/
		void PushBack(const glm::mat4& value);
		//! PushBack function, insert the given RTTI pointer at the end of the Vector
		/*!
			\param value, a RTTI* to be inserted into the Vector.
		*/
		void PushBack(RTTI* value);
		//! PushBack function, insert the given Scope pointer at the end of the Vector
		/*!
			\param value, a Scope* to be inserted into the Vector.
		*/
		void PushBack(Scope* value);
		//! popBack function that deletes the last data in the vector.
		void PopBack();
		//!SetFromString function
		/*!
			sets the value in the datum from the given string. Extracts the data from the string.
			\param stringData, a string which represents the value to be set in the datum.
			\param index, a uint32_t the index at which the given data has to be set.
		*/
		void SetFromString(const std::string& stringData, uint32_t index = 0);
		//!ToString function
		/*!
			
			converts the value at the given index into a string and returns it.
			\param index, the index of the value to be converted.
			\return a string which is obtained from the value at the index.
		*/
		std::string ToString(uint32_t index = 0);

		//!Operator[] Function
		/*!
			Returns a scope reference. Wrote this so it is easier to retrive a scope Reference
			without using the get method.
		*/
		Scope& operator[](std::uint32_t index);
		//!Find functions for all the different types of data.
		uint32_t Find(int32_t value);
		uint32_t Find(float value);
		uint32_t Find(const glm::mat4& value);
		uint32_t Find(const glm::vec4& value);
		uint32_t Find(const std::string& value);
		uint32_t Find(RTTI* value);
		uint32_t Find(Scope* value);
		//Remove data at the given index. 
		void RemoveAtIndex(uint32_t value);
		//Remove functions for all the datatypes.
		void Remove(int32_t value);
		void Remove(float value);
		void Remove(const glm::mat4& value);
		void Remove(const glm::vec4& value);
		void Remove(const std::string& value);
		void Remove(RTTI* value);
		void Remove(Scope* value);
		bool IsInternal();
		//Destructor
		~Datum();
	private:
		union DatumType
		{
			int32_t* i;
			float* f;
			glm::vec4* v;
			glm::mat4* m;
			std::string* s;
			Scope** t;
			RTTI** r;
			void* voidPointer;
		};
		DatumTypeEnum mDatumType;
		DatumType mData;
		uint32_t mSize;
		uint32_t mCapacity;
		bool mIsInternal;
		static size_t typeSizeLookup[static_cast<int>(DatumTypeEnum::NumberOfTypes)];

		//Helper function which does exception tests and contains the code common between all the overloaded constructors.
		void TypeCastConstructorCommonCode(DatumTypeEnum type);
		//A helper function that contains the common code for exception checking done in the setstorage methods.
		void SetStorageCommonCode(DatumTypeEnum type, uint32_t size);
		//A helper function that contains the common code for exception checking done in the set and get methods.
		void SetFunctionExceptionTest(uint32_t index, DatumTypeEnum inputType) const;
		//A helper function that contains the common code for exception checking done in the pushback methods.
		void PushBackCommonCode(DatumTypeEnum type);
	};

	//Defined Get templates in .h file becoz visual studio throws an unresolved external error when this is in the .cpp file.
	template<>
	int32_t& Datum::Get<int32_t>(const uint32_t index)
	{
		SetFunctionExceptionTest(index, DatumTypeEnum::Integer);
		return mData.i[index];
	}

	template<>
	float& Datum::Get<float>(const uint32_t index)
	{
		SetFunctionExceptionTest(index, DatumTypeEnum::Float);
		return mData.f[index];
	}

	template<>
	std::string& Datum::Get<std::string>(const uint32_t index)
	{
		SetFunctionExceptionTest(index, DatumTypeEnum::String);
		return mData.s[index];
	}

	template<>
	glm::vec4& Datum::Get<glm::vec4>(const uint32_t index)
	{
		SetFunctionExceptionTest(index, DatumTypeEnum::Vector);
		return mData.v[index];
	}

	template<>
	glm::mat4& Datum::Get<glm::mat4>(const uint32_t index)
	{
		SetFunctionExceptionTest(index, DatumTypeEnum::Matrix);
		return mData.m[index];
	}

	template<>
	RTTI*& Datum::Get<RTTI*>(const uint32_t index)
	{
		SetFunctionExceptionTest(index, DatumTypeEnum::RTTI);
		return mData.r[index];
	}

	template<>
	Scope& Datum::Get<Scope>(const uint32_t index)
	{
		SetFunctionExceptionTest(index, DatumTypeEnum::Table);
		return *(mData.t[index]);
	}


	template<>
	const int32_t& Datum::Get<int32_t>(const uint32_t index) const
	{
		SetFunctionExceptionTest(index, DatumTypeEnum::Integer);
		return mData.i[index];
	}

	template<>
	const float& Datum::Get<float>(const uint32_t index) const
	{
		SetFunctionExceptionTest(index, DatumTypeEnum::Float);
		return mData.f[index];
	}

	template<>
	const std::string& Datum::Get<std::string>(const uint32_t index) const
	{
		SetFunctionExceptionTest(index, DatumTypeEnum::String);
		return mData.s[index];
	}

	template<>
	const glm::vec4& Datum::Get<glm::vec4>(const uint32_t index) const
	{
		SetFunctionExceptionTest(index, DatumTypeEnum::Vector);
		return mData.v[index];
	}

	template<>
	const glm::mat4& Datum::Get<glm::mat4>(const uint32_t index) const
	{
		SetFunctionExceptionTest(index, DatumTypeEnum::Matrix);
		return mData.m[index];
	}

	template<>
	RTTI* const& Datum::Get<RTTI*>(const uint32_t index) const
	{
		SetFunctionExceptionTest(index, DatumTypeEnum::RTTI);
		return mData.r[index];
	}

	template<>
	const Scope& Datum::Get<Scope>(const uint32_t index) const
	{
		SetFunctionExceptionTest(index, DatumTypeEnum::Table);
		return *(mData.t[index]);
	}
}

//TODO make all scopes as scope references
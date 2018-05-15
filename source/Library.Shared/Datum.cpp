#include "pch.h"
#include <string>
#include "RTTI.h"
#include "Datum.h"
#include "Scope.h"

using namespace FieaGameEngine;
using namespace std;

size_t Datum::typeSizeLookup[static_cast<int>(DatumTypeEnum::NumberOfTypes)] = {0 ,sizeof(int32_t), sizeof(float), sizeof(string),
																				sizeof(glm::vec4), sizeof(glm::mat4), sizeof(RTTI*), sizeof(Scope*)};


Datum::Datum() : mDatumType(DatumTypeEnum::Unknown), mSize(0), mCapacity(0), mIsInternal(true)
{
	mData.voidPointer = nullptr;
}

Datum::Datum(const Datum& rhs) : Datum()
{
	operator=(rhs);
}

Datum::Datum(Datum&& rhs) : mData(std::move(rhs.mData)), mDatumType(rhs.mDatumType), mSize(rhs.mSize), mCapacity(rhs.mCapacity), mIsInternal(rhs.mIsInternal)
{
	rhs.mData.voidPointer = nullptr;
	rhs.mDatumType = DatumTypeEnum::Unknown;
	rhs.mSize = 0;
	rhs.mCapacity = 0;
	rhs.mIsInternal = true;
}

void Datum::TypeCastConstructorCommonCode(DatumTypeEnum type)
{
	mSize = 0;
	mCapacity = 0;
	mDatumType = type;
	mIsInternal = true;
	mData.voidPointer = nullptr;
}

Datum::Datum(const int32_t rhs)
{
	TypeCastConstructorCommonCode(DatumTypeEnum::Integer);
	operator=(rhs);
}

Datum::Datum(const float rhs)
{
	TypeCastConstructorCommonCode(DatumTypeEnum::Float);
	operator=(rhs);
}

Datum::Datum(const std::string& rhs)
{
	TypeCastConstructorCommonCode(DatumTypeEnum::String);
	operator=(rhs);
}

Datum::Datum(const glm::vec4& rhs)
{
	TypeCastConstructorCommonCode(DatumTypeEnum::Vector);
	operator=(rhs);
}

Datum::Datum(const glm::mat4& rhs)
{
	TypeCastConstructorCommonCode(DatumTypeEnum::Matrix);
	operator=(rhs);
}

Datum::Datum(RTTI* rhs)
{
	TypeCastConstructorCommonCode(DatumTypeEnum::RTTI);
	operator=(rhs);
}

Datum::Datum(Scope* rhs)
{
	TypeCastConstructorCommonCode(DatumTypeEnum::Table);
	operator=(rhs);
}

Datum& Datum::operator=(const Datum& rhs)
{
	if (this != &rhs)
	{
		if (mIsInternal == true)
		{
			Clear();
			free(mData.voidPointer);
			mCapacity = 0;
			mData.voidPointer = nullptr;
		}
		mDatumType = rhs.mDatumType;
		mIsInternal = rhs.mIsInternal;
		if (!rhs.mIsInternal)
		{
			mData = rhs.mData;
			mSize = rhs.mSize;
			mCapacity = rhs.mCapacity;
			return *this;
		}
		if (rhs.mDatumType == DatumTypeEnum::Unknown)
		{
			mData.voidPointer = nullptr;
			mSize = rhs.mSize;
			mCapacity = rhs.mCapacity;
			return *this;
		}
		Reserve(rhs.mCapacity);
		if (mDatumType == DatumTypeEnum::String)
		{
			for (uint32_t index = 0; index < rhs.mSize; index++)
			{
				PushBack(rhs.mData.s[index]);
			}
		}
		else
		{
			mSize = rhs.mSize;
			memcpy(mData.voidPointer, rhs.mData.voidPointer, typeSizeLookup[static_cast<int>(mDatumType)] * mSize);
		}
	}
	return *this;
}

Datum& Datum::operator=(Datum&& rhs)
{
	if (this != &rhs)
	{
		if (mIsInternal == true && mDatumType != DatumTypeEnum::Unknown)
		{
			Clear();
			free(mData.voidPointer);
		}
		mData = std::move(rhs.mData);
		mCapacity = rhs.mCapacity;
		mSize = rhs.mSize;
		mIsInternal = rhs.mIsInternal;
		rhs.mData.voidPointer = nullptr;
		rhs.mDatumType = DatumTypeEnum::Unknown;
		rhs.mSize = 0;
		rhs.mCapacity = 0;
		rhs.mIsInternal = true;
	}

	return *this;
}



Datum& Datum::operator=(const int32_t rhs)
{
	if (mSize == 0)
	{
		mDatumType = DatumTypeEnum::Integer;
	}
	if (Reserve(1))
	{
		mSize = 1;
	}
	Set(rhs, 0);
	return *this;
}

Datum& Datum::operator=(const float rhs)
{
	if (mSize == 0)
	{
		mDatumType = DatumTypeEnum::Float;
	}
	if (Reserve(1))
	{
		mSize = 1;
	}
	Set(rhs, 0);
	return *this;
}

Datum& Datum::operator=(const std::string& rhs)
{
	if (mSize == 0)
	{
		mDatumType = DatumTypeEnum::String;
	}
	if (Reserve(1))
	{
		PushBack(rhs);
	}
	else
	{
		Set(rhs, 0);
	}
	return *this;
}

Datum& Datum::operator=(const glm::vec4& rhs)
{
	if (mSize == 0)
	{
		mDatumType = DatumTypeEnum::Vector;
	}
	if (Reserve(1))
	{
		mSize = 1;
	}
	Set(rhs, 0);
	return *this;
}

Datum& Datum::operator=(const glm::mat4& rhs)
{
	if (mSize == 0)
	{
		mDatumType = DatumTypeEnum::Matrix;
	}
	if (Reserve(1))
	{
		mSize = 1;
	}
	Set(rhs, 0);
	return *this;
}

Datum& Datum::operator=(RTTI* rhs)
{
	if (mSize == 0)
	{
		mDatumType = DatumTypeEnum::RTTI;
	}
	if (Reserve(1))
	{
		mSize = 1;
	}
	Set(rhs, 0);
	return *this;
}


Datum& Datum::operator=(Scope* rhs)
{
	assert(rhs != nullptr);
	if (mSize == 0)
	{
		mDatumType = DatumTypeEnum::Table;
	}
	if (Reserve(1))
	{
		mSize = 1;
	}
	Set(rhs, 0);
	return *this;
}

DatumTypeEnum Datum::Type() const
{
	return mDatumType;
}

void Datum::SetType(DatumTypeEnum type)
{
	if (type == DatumTypeEnum::Unknown || (mDatumType != DatumTypeEnum::Unknown && type != mDatumType))
	{
		throw std::exception("type error");
	}
	mDatumType = type;
}

uint32_t Datum::Size()const 
{
	return mSize;
}

bool Datum::Reserve(uint32_t capacity)
{
	if (mDatumType == DatumTypeEnum::Unknown)
	{
		throw std::exception("data type is not set");
	}
	if (mIsInternal == false)
	{
		throw std::exception("Datum uses external storage");
	}
	if (capacity <= mCapacity)
	{
		return false;
	}
	mCapacity = capacity;
	mData.voidPointer = realloc(mData.voidPointer, typeSizeLookup[static_cast<int>(mDatumType)] * mCapacity);
	return mData.voidPointer != nullptr;
}

void Datum::Resize(uint32_t size)
{
	if (mIsInternal == true)
	{
		if (size < mSize)
		{
			for (--mSize; mSize >= size; mSize--)
			{
				PopBack();
			}
		}

		mData.voidPointer = realloc(mData.voidPointer, typeSizeLookup[static_cast<int>(mDatumType)] * size);

		if (mDatumType == DatumTypeEnum::String)
		{
			for (; mSize < size; mSize++)
			{
				new(&mData.s[mSize])string();
			}
		}
		mSize = mCapacity = size;
	}
}

void Datum::Clear()
{
	if (mIsInternal == true)
	{
		if (mDatumType == DatumTypeEnum::String)
		{
			for (uint32_t index = 0; index < mSize; index++)
			{
				mData.s[index].~string();
			}
		}
		mSize = 0;
	}
}

void Datum::SetStorageCommonCode(DatumTypeEnum type, uint32_t size)
{
	if (size == 0)
	{
		throw std::exception("invalid type or size");
	}
	
	if (mDatumType != DatumTypeEnum::Unknown && type != mDatumType)
	{
		throw std::exception("type mismatch");
	}

	if (mIsInternal)
	{
		Clear();
		free(mData.voidPointer);
	}
	mDatumType = type;
	mIsInternal = false;
	mCapacity = size;
	mSize = size;
}

void Datum::SetStorage(int32_t* inputArray, uint32_t size)
{
	SetStorageCommonCode(DatumTypeEnum::Integer, size);
	mData.i = inputArray;
	
}

void Datum::SetStorage(float* inputArray, uint32_t size)
{
	SetStorageCommonCode(DatumTypeEnum::Float, size);
	mData.f = inputArray;
}

void Datum::SetStorage(string* inputArray, uint32_t size)
{
	SetStorageCommonCode(DatumTypeEnum::String, size);
	mData.s = inputArray;
}

void Datum::SetStorage(glm::vec4* inputArray, uint32_t size)
{
	SetStorageCommonCode(DatumTypeEnum::Vector, size);
	mData.v = inputArray;
}

void Datum::SetStorage(glm::mat4* inputArray, uint32_t size)
{
	SetStorageCommonCode(DatumTypeEnum::Matrix, size);
	mData.m = inputArray;
}

void Datum::SetStorage(RTTI** inputArray, uint32_t size)
{
	SetStorageCommonCode(DatumTypeEnum::RTTI, size);
	mData.r = inputArray;
}

void Datum::PushBackCommonCode(DatumTypeEnum type)
{
	if (mIsInternal == false)
	{
		throw std::exception("External storage data cannot be modified");
	}
	if (mDatumType == DatumTypeEnum::Unknown)
	{
		mDatumType = type;
	}
	if (mDatumType != type)
	{
		throw std::exception("Invalid datatype");
	}
	if (mSize == mCapacity)
	{
		Reserve(mCapacity + 1);
	}
}

void Datum::PushBack(const int32_t value)
{
	PushBackCommonCode(DatumTypeEnum::Integer);
	mData.i[mSize++] = value;
}

void Datum::PushBack(const float value)
{
	PushBackCommonCode(DatumTypeEnum::Float);
	mData.f[mSize++] = value;
}

void Datum::PushBack(const std::string& value)
{
	PushBackCommonCode(DatumTypeEnum::String);
	new(&mData.s[mSize++])string(value);
}

void Datum::PushBack(const glm::vec4& value)
{
	PushBackCommonCode(DatumTypeEnum::Vector);
	mData.v[mSize++] = value;
}

void Datum::PushBack(const glm::mat4& value)
{
	PushBackCommonCode(DatumTypeEnum::Matrix);
	mData.m[mSize++] = value;
}

void Datum::PushBack(RTTI* value)
{
	PushBackCommonCode(DatumTypeEnum::RTTI);
	mData.r[mSize++] = value;
}

void Datum::PushBack(Scope* value)
{
	assert(value != nullptr);
	PushBackCommonCode(DatumTypeEnum::Table);
	mData.t[mSize++] = value;
}

void Datum::PopBack()
{
	if (mIsInternal == false)
	{
		throw std::exception("External storage data cannot be modified");
	}
	if (mDatumType == DatumTypeEnum::Unknown)
	{
		throw std::exception("Type is not set");
	}
	if (mSize == 0)
	{
		throw std::exception("Datum is already empty");
	}
	if (mDatumType == DatumTypeEnum::String)
	{
		mData.s[mSize - 1].~string();
	}
	mSize--;
}

void Datum::SetFunctionExceptionTest(uint32_t index, DatumTypeEnum inputType) const
{
	if (mDatumType == DatumTypeEnum::Unknown)
	{
		throw std::exception("type is not set");
	}
	if (mDatumType != inputType)
	{
		throw std::exception("type mismatch");
	}
	if (index >= mSize)
	{
		throw std::exception("invalid index");
	}
}

void Datum::Set(const int32_t value, uint32_t index)
{
	SetFunctionExceptionTest(index, DatumTypeEnum::Integer);
	mData.i[index] = value;
}

void Datum::Set(const float value, uint32_t index)
{
	SetFunctionExceptionTest(index, DatumTypeEnum::Float);
	mData.f[index] = value;
}

void Datum::Set(const std::string& value, uint32_t index)
{
	SetFunctionExceptionTest(index, DatumTypeEnum::String);
	mData.s[index] = value;
}

void Datum::Set(const glm::vec4& value, uint32_t index)
{
	SetFunctionExceptionTest(index, DatumTypeEnum::Vector);
	mData.v[index] = value;
}

void Datum::Set(const glm::mat4& value, uint32_t index)
{
	SetFunctionExceptionTest(index, DatumTypeEnum::Matrix);
	mData.m[index] = value;
}

void Datum::Set(RTTI* value, uint32_t index)
{
	SetFunctionExceptionTest(index, DatumTypeEnum::RTTI);
	mData.r[index] = value;
}

void Datum::Set(Scope* value, uint32_t index)
{
	assert(value != nullptr);
	SetFunctionExceptionTest(index, DatumTypeEnum::Table);
	mData.t[index] = value;
}

bool Datum::operator==(const Datum& rhs) const
{
	if (mDatumType != rhs.mDatumType || mSize != rhs.mSize)
	{
		return false;
	}
	if (mDatumType == DatumTypeEnum::String)
	{
		for (uint32_t index = 0; index < mSize; index++)
		{
			if (mData.s[index] != rhs.mData.s[index])
			{
				return false;
			}
		}
		return true;
	}
	else if (mDatumType == DatumTypeEnum::RTTI || mDatumType == DatumTypeEnum::Table)
	{
		for (uint32_t index = 0; index < mSize; index++)
		{
			if (mData.r[index] == nullptr && rhs.mData.r[index] == nullptr)
			{
				continue;
			}
			if (mData.r[index] == nullptr || rhs.mData.r[index] == nullptr)
			{
				return false;
			}
			if (!mData.r[index]->Equals(rhs.mData.r[index]))
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		if (memcmp(mData.voidPointer, rhs.mData.voidPointer, mCapacity * typeSizeLookup[static_cast<int>(mDatumType)]) == 0)
		{
			return true;
		}
	}
	return false;
}

bool Datum::operator==(const int32_t rhs) const
{
	return (mDatumType == DatumTypeEnum::Integer && mSize == 1 && mData.i[0] == rhs);
}

bool Datum::operator==(const float rhs) const
{
	return (mDatumType == DatumTypeEnum::Float && mSize == 1 && mData.f[0] == rhs);
}

bool Datum::operator==(const std::string& rhs) const
{
	return (mDatumType == DatumTypeEnum::String && mSize == 1 && mData.s[0] == rhs);
}

bool Datum::operator==(const glm::vec4& rhs) const
{
	return (mDatumType == DatumTypeEnum::Vector && mSize == 1 && mData.v[0] == rhs);
}

bool Datum::operator==(const glm::mat4& rhs) const
{
	return (mDatumType == DatumTypeEnum::Matrix && mSize == 1 && mData.m[0] == rhs);
}

bool Datum::operator==(RTTI* rhs) const
{
	if (mDatumType == DatumTypeEnum::RTTI && mSize == 1 && mData.r[0] == nullptr && rhs == nullptr)
	{
		return true;
	}
	if (mDatumType == DatumTypeEnum::RTTI && mSize == 1 && (mData.r[0] == nullptr || rhs == nullptr))
	{
		return false;
	}
	return (mDatumType == DatumTypeEnum::RTTI && mSize == 1 && mData.r[0]->Equals(rhs));
}

bool Datum::operator==(Scope* rhs) const
{
	if (mDatumType == DatumTypeEnum::Table && mSize == 1 && mData.t[0] == nullptr && rhs == nullptr)
	{
		return true;
	}
	if (mDatumType == DatumTypeEnum::Table && mSize == 1 && (mData.t[0] == nullptr || rhs == nullptr))
	{
		return false;
	}
	return (mDatumType == DatumTypeEnum::Table && mSize == 1 && mData.t[0]->Equals(rhs));
}

bool Datum::operator!=(const Datum& rhs) const
{
	return !operator==(rhs);
}

bool Datum::operator!=(const int32_t rhs) const
{
	return !operator==(rhs);
}

bool Datum::operator!=(const float rhs) const
{
	return !operator==(rhs);
}

bool Datum::operator!=(const std::string& rhs) const
{
	return !operator==(rhs);
}

bool Datum::operator!=(const glm::vec4& rhs) const
{
	return !operator==(rhs);
}

bool Datum::operator!=(const glm::mat4& rhs) const
{
	return !operator==(rhs);
}

bool Datum::operator!=(RTTI* rhs) const
{
	return !operator==(rhs);
}

bool Datum::operator!=(Scope* rhs) const
{
	return !operator==(rhs);
}

std::string Datum::ToString(uint32_t index)
{
	if (index >= mSize)
	{
		throw std::exception("index out of bounds");
	}
	switch (mDatumType)
	{
		case DatumTypeEnum::Integer:
		{
			return std::to_string(Get<int32_t>(index));
		}

		case DatumTypeEnum::Float:
		{
			return std::to_string(Get<float>(index));
		}

		case DatumTypeEnum::Vector:
		{
			return glm::to_string(Get<glm::vec4>(index));
		}

		case DatumTypeEnum::Matrix:
		{
			return glm::to_string(Get<glm::mat4>(index));
		}

		case DatumTypeEnum::String:
		{
			return Get<std::string>(index);
		}
		
		case DatumTypeEnum::RTTI:
		{
			RTTI* temp = Get<RTTI*>(index);
			if (temp != nullptr)
			{
				return temp->ToString();
			}
			return "";
		}

		case DatumTypeEnum::Table:
		{
			Scope& temp = Get<Scope>(index);
			if (&temp != nullptr)
			{
				return temp.ToString();
			}
			return "";
		}
		default:
		{
			throw std::exception("type mismatch");
		}
	}
}


void Datum::SetFromString(const std::string& stringData, uint32_t index)
{
	if (mDatumType == DatumTypeEnum::Unknown)
	{
		throw std::exception("Type has not been set yet");
	}

	if (index >= mSize)
	{
		throw std::exception("Index out of bounds");
	}

	switch (mDatumType)
	{
		case DatumTypeEnum::Integer:
		{
			Set(std::stoi(stringData), index);
			break;
		}

		case DatumTypeEnum::Float:
		{
			Set(std::stof(stringData), index);
			break;
		}

		case DatumTypeEnum::Vector:
		{
			glm::vec4 vec;
			sscanf_s(stringData.c_str(), "vec4(%f,%f,%f,%f", &vec[0], &vec[1], &vec[2], &vec[3]);
			Set(vec, index);
			break;
		}

		case DatumTypeEnum::Matrix:
		{
			glm::mat4 mat;
			sscanf_s(stringData.c_str(), "mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))", &mat[0][0], &mat[0][1], &mat[0][2], &mat[0][3],
																     &mat[1][0], &mat[1][1], &mat[1][2], &mat[1][3],
															        &mat[2][0], &mat[2][1], &mat[2][2], &mat[2][3],
																	&mat[3][0], &mat[3][1], &mat[3][2], &mat[3][3]);
			Set(mat, index);
			break;
		}

		case DatumTypeEnum::String:
		{
			Set(stringData, index);
		}
	}
}

Datum::~Datum()
{
	if (mIsInternal == true)
	{
		Clear();
		free(mData.voidPointer);
	}
}

Scope& Datum::operator[](std::uint32_t index)
{
	return Get<Scope>(index);
}

uint32_t Datum::Find(int32_t value)
{
	if (mDatumType != DatumTypeEnum::Integer)
	{
		throw std::exception("type mismatch");
	}
	uint32_t index = 0;
	for ( ; index < mSize; index++)
	{
		if (value == mData.i[index])
		{
			break;
		}
	}
	return index;
}

uint32_t Datum::Find(float value)
{
	if (mDatumType != DatumTypeEnum::Float)
	{
		throw std::exception("type mismatch");
	}
	uint32_t index = 0;
	for (; index < mSize; index++)
	{
		if (value == mData.f[index])
		{
			break;
		}
	}
	return index;
}

uint32_t Datum::Find(const std::string& value)
{
	if (mDatumType != DatumTypeEnum::String)
	{
		throw std::exception("type mismatch");
	}
	uint32_t index = 0;
	for (; index < mSize; index++)
	{
		if (value == mData.s[index])
		{
			break;
		}
	}
	return index;
}

uint32_t Datum::Find(const glm::vec4& value)
{
	if (mDatumType != DatumTypeEnum::Vector)
	{
		throw std::exception("type mismatch");
	}
	uint32_t index = 0;
	for (; index < mSize; index++)
	{
		if (value == mData.v[index])
		{
			break;
		}
	}
	return index;
}

uint32_t Datum::Find(const glm::mat4& value)
{
	if (mDatumType != DatumTypeEnum::Matrix)
	{
		throw std::exception("type mismatch");
	}
	uint32_t index = 0;
	for (; index < mSize; index++)
	{
		if (value == mData.m[index])
		{
			break;
		}
	}
	return index;
}

uint32_t Datum::Find(RTTI* value)
{
	if (mDatumType != DatumTypeEnum::RTTI)
	{
		throw std::exception("type mismatch");
	}
	uint32_t index = 0;
	for (; index < mSize; index++)
	{
		if (value->Equals(mData.r[index]))
		{
			break;
		}
	}
	return index;
}

uint32_t Datum::Find(Scope* value)
{
	assert(value != nullptr);
	if (mDatumType != DatumTypeEnum::Table)
	{
		throw std::exception("type mismatch");
	}
	uint32_t index = 0;
	for (; index < mSize; index++)
	{
		if (value->Equals(mData.t[index]))
		{
			break;
		}
	}
	return index;
}



void Datum::Remove(int32_t value)
{
	if (mIsInternal == false)
	{
		throw std::exception("cannot delete external data value");
	}
	uint32_t index = Find(value);
	if (index != mSize)
	{
		std::memmove(&mData.i[index], &mData.i[index + 1], sizeof(int)*(mSize - index - 1));
		mSize--;
	}
}

void Datum::Remove(float value)
{
	if (mIsInternal == false)
	{
		throw std::exception("cannot delete external data value");
	}
	uint32_t index = Find(value);
	if (index != mSize)
	{
		std::memmove(&mData.f[index], &mData.f[index + 1], sizeof(float)*(mSize - index - 1)); 
		mSize--;
	}
}

void Datum::Remove(const std::string& value)
{
	if (mIsInternal == false)
	{
		throw std::exception("cannot delete external data value");
	}
	uint32_t index = Find(value);
	if (index != mSize)
	{
		mData.s[index].~string();
		std::memmove(&mData.s[index], &mData.s[index + 1], sizeof(string)*(mSize - index - 1));
		mSize--;
	}
}

void Datum::Remove(const glm::vec4& value)
{
	if (mIsInternal == false)
	{
		throw std::exception("cannot delete external data value");
	}
	uint32_t index = Find(value);
	if (index != mSize)
	{
		std::memmove(&mData.v[index], &mData.v[index + 1], sizeof(glm::vec4)*(mSize - index - 1));
		mSize--;
	}
}

void Datum::Remove(const glm::mat4& value)
{
	if (mIsInternal == false)
	{
		throw std::exception("cannot delete external data value");
	}
	uint32_t index = Find(value);
	if (index != mSize)
	{
		std::memmove(&mData.m[index], &mData.m[index + 1], sizeof(glm::mat4)*(mSize - index - 1));
		mSize--;
	}
}

void Datum::Remove(RTTI* value)
{
	if (mIsInternal == false)
	{
		throw std::exception("cannot delete external data value");
	}
	uint32_t index = Find(value);
	if (index != mSize)
	{
		std::memmove(&mData.r[index], &mData.r[index + 1], sizeof(RTTI*)*(mSize - index - 1));
		mSize--;
	}
}

void Datum::Remove(Scope* value)
{
	assert(value != nullptr);
	uint32_t index = Find(value);
	if (index != mSize)
	{
		std::memmove(&mData.t[index], &mData.t[index + 1], sizeof(Scope*)*(mSize - index - 1));
		mSize--;
	}
}

void Datum::RemoveAtIndex(uint32_t index)
{
	if (mIsInternal == false)
	{
		throw std::exception("cannot delete external data value");
	}
	if (index >= mSize)
	{
		throw std::exception("index out of bounds");
	}
	switch (mDatumType)
	{
		case DatumTypeEnum::Integer :
		{
			std::memmove(&mData.i[index], &mData.i[index + 1], sizeof(int)*(mSize - index - 1));
			mSize--;
			break;
		}
		case DatumTypeEnum::Float:
		{
			std::memmove(&mData.f[index], &mData.f[index + 1], sizeof(float)*(mSize - index - 1));
			mSize--;
			break;
		}
		case DatumTypeEnum::String:
		{
			mData.s[index].~string();
			std::memmove(&mData.s[index], &mData.s[index + 1], sizeof(string)*(mSize - index - 1));
			mSize--;
			break;
		}
		case DatumTypeEnum::Matrix:
		{
			std::memmove(&mData.m[index], &mData.m[index + 1], sizeof(glm::mat4)*(mSize - index - 1));
			mSize--;
			break;
		}
		case DatumTypeEnum::Vector:
		{
			std::memmove(&mData.v[index], &mData.v[index + 1], sizeof(glm::vec4)*(mSize - index - 1));
			mSize--;
			break;
		}
		case DatumTypeEnum::RTTI:
		{
			std::memmove(&mData.r[index], &mData.r[index + 1], sizeof(RTTI*)*(mSize - index - 1));
			mSize--;
			break;
		}
		case DatumTypeEnum::Table:
		{
			std::memmove(&mData.t[index], &mData.t[index + 1], sizeof(Scope*)*(mSize - index - 1));
			mSize--;
			break;
		}
		default:
		{
			throw std::exception("unknown datatype");
		}
	}
}

bool Datum::IsInternal()
{
	return mIsInternal;
}

void Datum::SetStorage(void* inputArray, uint32_t size)
{
	if (mIsInternal)
	{
		Clear();
		free(mData.voidPointer);
	}
	mIsInternal = false;
	mCapacity = size;
	mSize = size;
	mData.voidPointer = inputArray;
}
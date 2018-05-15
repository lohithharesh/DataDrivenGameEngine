#include "pch.h"
#include "AttributedFoo.h"

using namespace FieaGameEngine;

RTTI_DEFINITIONS(AttributedFoo);

AttributedFoo::AttributedFoo() : Attributed(AttributedFoo::TypeIdClass())
{

}

AttributedFoo::~AttributedFoo()
{
	Attributed::~Attributed();
}

Vector<Signature> AttributedFoo::Signatures()
{
	Vector<Signature> signatures;
	signatures.PushBack({ "this", DatumTypeEnum::RTTI, 0, 0 });
	signatures.PushBack({ "ExternalIntValue", DatumTypeEnum::Integer, 1, offsetof(AttributedFoo, mIntegerValue) });
	signatures.PushBack({ "ExternalFloatValue", DatumTypeEnum::Float, 1, offsetof(AttributedFoo, mFloatValue) });
	signatures.PushBack({ "ExternalStringValue", DatumTypeEnum::String, 1, offsetof(AttributedFoo, mStringValue) });
	signatures.PushBack({ "ExternalVectorValue", DatumTypeEnum::Vector, 1, offsetof(AttributedFoo, mVectorValue) });
	signatures.PushBack({ "ExternalMatrixValue", DatumTypeEnum::Matrix, 1, offsetof(AttributedFoo, mMatrixValue) });
	signatures.PushBack({ "ExternalRTTIValue", DatumTypeEnum::RTTI, 1, offsetof(AttributedFoo, mRTTIValue) });
	signatures.PushBack({ "ExternalIntArray", DatumTypeEnum::Integer, 5, offsetof(AttributedFoo, mIntegerArray) });
	signatures.PushBack({ "ExternalFloatArray", DatumTypeEnum::Float, 5, offsetof(AttributedFoo, mFloatArray) });
	signatures.PushBack({ "ExternalStringArray", DatumTypeEnum::String, 5, offsetof(AttributedFoo, mStringArray) });
	signatures.PushBack({ "ExternalVectorArray", DatumTypeEnum::Vector, 5, offsetof(AttributedFoo, mVectorArray) });
	signatures.PushBack({ "ExternalMatrixArray", DatumTypeEnum::Matrix, 5, offsetof(AttributedFoo, mMatrixArray) });
	signatures.PushBack({ "ExternalRTTIArray", DatumTypeEnum::RTTI, 5, offsetof(AttributedFoo, mRTTIArray) });
	return signatures;
}

Scope* AttributedFoo::Clone(const Scope& rhs)
{
	return new AttributedFoo(*(rhs.As<AttributedFoo>()));
}
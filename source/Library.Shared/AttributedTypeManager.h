#pragma once
#include "Vector.h"
#include "HashMap.h"
#include "Datum.h"
namespace FieaGameEngine {

	struct Signature
	{
		std::string mName;
		DatumTypeEnum mType;
		uint32_t mSize;
		size_t mOffset;
	};

	class AttributedTypeManager
	{
	public:
		AttributedTypeManager() = default;
		~AttributedTypeManager() = default;
		static void AddAttributes(uint64_t id, const Vector<Signature>& signatures);
		AttributedTypeManager(const AttributedTypeManager& rhs) = delete;
		AttributedTypeManager(AttributedTypeManager&& rhs) = delete;
		AttributedTypeManager& operator=(const AttributedTypeManager& rhs) = delete;
		AttributedTypeManager& operator=(AttributedTypeManager&& rhs) = delete;
		static const Vector<Signature>& GetSignatures(uint64_t id);
	protected:
		static HashMap<uint64_t, Vector<Signature>> mPrescribedAttributes;
	};

#define RegisterType(ClassName)																      \
	AttributedTypeManager::AddAttributes(ClassName::TypeIdClass(), ClassName::Signatures())  ; 
}


#pragma once
#include "Attributed.h"

namespace FieaGameEngine
{
	class AttributedFoo final: public Attributed
	{
		RTTI_DECLARATIONS(AttributedFoo, Attributed)
	public:
		AttributedFoo();
		virtual ~AttributedFoo();
		AttributedFoo(const AttributedFoo& rhs) = default;
		AttributedFoo(AttributedFoo&& rhs) = default;
		AttributedFoo& operator=(const AttributedFoo& rhs) = default;
		AttributedFoo& operator=(AttributedFoo&& rhs) = default;
		int32_t mIntegerValue;
		float mFloatValue;
		std::string mStringValue;
		glm::vec4 mVectorValue;
		glm::mat4 mMatrixValue;
		RTTI* mRTTIValue;
		int32_t mIntegerArray[5];
		float mFloatArray[5];
		std::string mStringArray[5];
		glm::vec4 mVectorArray[5];
		glm::mat4 mMatrixArray[5];
		RTTI* mRTTIArray[5];
		static Vector<Signature> Signatures();
		virtual Scope* Clone(const Scope& rhs) override;
	};

	
	
}


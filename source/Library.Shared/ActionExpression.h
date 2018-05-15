#pragma once
#include "Action.h"
#include "AbstractFactory.h"

namespace FieaGameEngine {
	typedef float(*BinaryOperator)(float, float);
	class ActionExpression : public Action
	{
		RTTI_DECLARATIONS(ActionExpression, Action)
	public:
		ActionExpression();
		~ActionExpression() = default;
		virtual void Update(WorldState& worldState) override;
		//!move and copy constructors
		ActionExpression(const ActionExpression& rhs) = default;
		ActionExpression(ActionExpression&& rhs) = default;
		ActionExpression& operator=(const ActionExpression& rhs) = default;
		ActionExpression& operator=(ActionExpression&& rhs) = default;
		static Vector<Signature> Signatures();
		float RPNCalculator(const std::string& rpnExpression);
		std::string mExpression;
		std::string mDatumToSet;
	private:
		static const HashMap<std::string, BinaryOperator> mOperatorFunctionMap;
	protected:
		virtual Scope* Clone(const Scope& rhs) override;
	};

	ConcreteFactory(ActionExpression, Action)
}

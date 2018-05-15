#include "pch.h"
#include "ActionExpression.h"
#include "WorldState.h"
#include <stack>


using namespace FieaGameEngine;

RTTI_DEFINITIONS(ActionExpression)

inline float AddOperator(float op1, float op2)
{
	return op1 + op2;
}

inline float SubOperator(float op1, float op2)
{
	return op1 - op2;
}

inline float MulOperator(float op1, float op2)
{
	return op1 * op2;
}

inline float DivOperator(float op1, float op2)
{
	return op1 / op2;
}

inline float RemainderOperator(float op1, float op2)
{
	return (float)(static_cast<int>(op1) % static_cast<int>(op2));
}

const HashMap<std::string, BinaryOperator> ActionExpression::mOperatorFunctionMap = { {"+", &AddOperator} , {"-", &SubOperator},{ "*", &MulOperator }, {"/", &DivOperator}, {"%", &RemainderOperator} };

ActionExpression::ActionExpression() : Action(ActionExpression::TypeIdClass())
{
	mDatumToSet = "nullptr";
}

Vector<Signature> ActionExpression::Signatures()
{
	Vector<Signature> signatures = Action::Signatures();
	signatures.PushBack({ "Expression", DatumTypeEnum::String, 1, offsetof(ActionExpression, mExpression) });
	signatures.PushBack({ "DatumToSet", DatumTypeEnum::String, 1, offsetof(ActionExpression, mDatumToSet) });
	return signatures;
}

void ActionExpression::Update(WorldState& worldState)
{
	worldState.mCurrentAction = this;
	if (mDatumToSet != "nullptr")
	{
		Search(mDatumToSet)->Set(RPNCalculator(mExpression), 0);
	}
	worldState.mCurrentAction = nullptr;
}


inline bool isOperator(const std::string & s)
{
	return (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/' || s[0] == '%');
}


float ActionExpression::RPNCalculator(const std::string& rpnExpression)
{
	Vector<std::string> tokens;
	size_t i = 0;
	auto pos = rpnExpression.find(' ');
	while (pos != std::string::npos)
	{
		tokens.PushBack(rpnExpression.substr(i, pos - i));
		i = ++pos;
		pos = rpnExpression.find(' ', pos);

		if (pos == std::string::npos)
		{
			tokens.PushBack(rpnExpression.substr(i, rpnExpression.length()));
		}
	}
	std::stack<float> operandStack;
	for (auto token : tokens)
	{
		if (!isOperator(token))
		{
			Datum* d = Search(token);
			if (d != nullptr)
			{
				operandStack.push(d->Get<float>());
			}
			else
			{
				operandStack.push(stof(token));
			}
		}
		else
		{
			float op2 = operandStack.top();
			operandStack.pop();
			float op1 = operandStack.top();
			operandStack.pop();
			operandStack.push(mOperatorFunctionMap.Find(token)->second(op1, op2));
		}
	}

	return operandStack.top();
}


Scope* ActionExpression::Clone(const Scope& rhs)
{
	return new ActionExpression(*(rhs.As<ActionExpression>()));
}
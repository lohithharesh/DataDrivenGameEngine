#pragma once

#include "AbstractFactory.h"
#include "Entity.h"

namespace FieaGameEngine
{
	enum class BoardSpaceObject
	{
		INVALID,
		IS_WORD,
		BABA_WORD,
		ROCK_WORD,
		FLAG_WORD,
		SKULL_WORD,
		WALL_WORD,
		PUSH_WORD,
		STOP_WORD,
		DIE_WORD,
		WIN_WORD,
		YOU_WORD,
		BABA,
		ROCK,
		FLAG,
		SKULL,
		WALL,
		BUSH,
		MAX
	};

	class GameObject;

	class RuleCheckEntity final : public Entity
	{
		RTTI_DECLARATIONS(RuleCheckEntity, Entity)
	public:
		static const uint32_t BOARD_SIZE{ 20u };

		using Board = std::array<std::array<Vector<GameObject*>, BOARD_SIZE>, BOARD_SIZE>;

		RuleCheckEntity() = default;
		~RuleCheckEntity() = default;

		virtual void Update(WorldState& worldState) override;

		static bool IsWord(BoardSpaceObject bso);

		static bool IsMaterialWord(BoardSpaceObject bso);

		static bool IsAspectWord(BoardSpaceObject bso);
		static Vector<Signature> Signatures();
	private:
		void AssignWord(BoardSpaceObject& bso, uint32_t i, uint32_t j, Board& board, bool material) const;
		void LookForAndApplyRule(uint32_t vary, uint32_t constant, Board& board, bool varyI) const;
		static void ReplaceMaterialWithMaterial(Board& board, BoardSpaceObject original, BoardSpaceObject replaceWith);
		static void ApplyAspectToMaterial(Board& board, BoardSpaceObject material, BoardSpaceObject aspect);

		static BoardSpaceObject GetMaterialFromMaterialWord(BoardSpaceObject word);

		static const std::array<std::pair<BoardSpaceObject, BoardSpaceObject>, 5> MaterialWordToMaterialMap;		
	};

	ConcreteFactory(RuleCheckEntity, Entity)
}
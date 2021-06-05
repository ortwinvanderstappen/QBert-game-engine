#pragma once
#include "RenderComponent.h"
#include "ArenaTile.h"
#include "GameManager.h"
#include "TileMovementComponent.h"
#include "TileRevertCreature.h"

class TileRevertCreature;
class CompletedTilesObserver;
class HealthObserver;
class Coily;
class QBert;

class GameArena : public minigen::RenderComponent
{
public:
	
	GameArena(GameManager* pGameManager, GameManager::GameMode gameMode, GameManager::StageSettings* const stageSettings, int stage);
	~GameArena() override;

	void Initialize() override;
	void InitializeArena();
	void CreateDiscs();

	void Update() override;
	void Render() const override;

	void AddPlayers();
	const std::vector<std::shared_ptr<QBert>>& GetPlayers() const;

	void Restart() const;
	void HandleLevelCompletion() const;
	void ResetStageEntities();
	
	float GetTileSize() const;
	ArenaTile* GetNeighbourTile(ArenaTile* pCurrentTile, TileMovementComponent::MovementType movement);
	ArenaTile* GetTopTile();
	bool IsBottomTileIndex(int index) const;
private:
	enum class EntityType
	{
		coily,
		sam,
		slick
	};
	
	void HandleEnemySpawns();
	void SpawnPlayer(ArenaTile* pTile, bool useController);
	void SpawnCoily();
	void SpawnSlickOrSam(TileRevertCreature::CreatureType type);
	
	int GetTopTileIndex() const;
	int GetBottomLeftTileIndex() const;
	int GetBottomRightTileIndex() const;
	int GetNullTileIndexOnRow(int row, bool isLeft) const;

	GameManager* m_pGameManager;
	GameManager::GameMode m_GameMode;
	GameManager::StageSettings* m_pStageSettings;
	int m_Stage;
	
	float m_TileSize;
	int m_TileCount;
	float m_EnemySpawnTime;
	float m_EnemySpawnTimer;
	
	std::weak_ptr<Coily> m_wpCoily;
	std::weak_ptr<TileRevertCreature> m_wpSam;
	std::weak_ptr<TileRevertCreature> m_wpSlick;

	std::vector<ArenaTile> m_ArenaHexes{};
	std::vector<std::shared_ptr<QBert>> m_spPlayers;
	std::shared_ptr<HealthObserver> m_spHealthObserver;
	std::shared_ptr<CompletedTilesObserver> m_spCompletedTilesObserver;
};

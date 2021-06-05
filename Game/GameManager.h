#pragma once
#include <Component.h>

#include "structs.h"
#include <vector>

class ScoreObserver;

class GameManager : public minigen::Component
{
public:
	enum class GameMode
	{
		Single,
		Duo,
		Versus
	};
	struct Disc
	{
		int row;
		bool isLeft;
	};
	struct StageSettings
	{
		int size;
		int lives;
		bool cyclesColor;
		std::vector<Color3i> activeColors;
		Color3i inactiveColor;
		std::vector<Disc> discs;
	};
	
	GameManager();
	
	void Update() override;
	void Initialize() override;
	void SetGameMode(GameMode gameMode);
	
	void Restart();
	void LoadNextStage();

	int GetScore() const;

	const std::shared_ptr<ScoreObserver>& GetScoreObserver() const;

private:
	void InitializeStageSettings();
	void InitializeStage();
	
	GameMode m_GameMode;
	int m_Stage;
	std::vector<StageSettings> m_Stages;
	std::shared_ptr<ScoreObserver> m_spScoreObserver;
};


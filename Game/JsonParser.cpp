#include "JsonParser.h"

#include <iostream>
#include "JsonReader.h"
#include "rapidjson.h"
#include "filereadstream.h"
#include "stream.h"

void JsonParser::ParseDifficulties(std::vector<GameScene::StageSettings>& stageSettings)
{
	using rapidjson::Value;

	JsonReader jr{};
	rapidjson::Document* jsonDoc = jr.ReadJson("../Data/game_difficulties.json");

	const Value& difficultyObject = (*jsonDoc)["levels"];
	// Loop through each level entry
	for (Value::ConstValueIterator valueIt = difficultyObject.Begin(); valueIt != difficultyObject.End(); ++valueIt)
	{
		// Obtain values
		const Value& levelValue = *valueIt;
		const Value& sizeValue = levelValue["size"];

		const Value& activeColorValue = levelValue["activeColor"];
		const Value& activeColorRValue = activeColorValue["r"];
		const Value& activeColorGValue = activeColorValue["g"];
		const Value& activeColorBValue = activeColorValue["b"];

		const Value& inactiveColorValue = levelValue["inactiveColor"];
		const Value& inactiveColorRValue = inactiveColorValue["r"];
		const Value& inactiveColorGValue = inactiveColorValue["g"];
		const Value& inactiveColorBValue = inactiveColorValue["b"];

		// Create stage entry
		GameScene::StageSettings stage{};

		const Value& discsValue = levelValue["discs"];
		for (Value::ConstValueIterator discProperty = discsValue.Begin(); discProperty != discsValue.End(); ++discProperty)
		{
			const Value& discValue = *discProperty;
			const Value& rowValue = discValue["row"];
			const Value& positionValue = discValue["position"];

			const int row = rowValue.GetInt();
			const int discPosition = positionValue.GetInt();

			switch (discPosition)
			{
			case 1:
			{
				GameScene::Disc disc{};
				disc.row = row;
				disc.isLeft = true;
				stage.discs.push_back(disc);
				break;
			}
			case 2:
			{
				GameScene::Disc disc{};
				disc.row = row;
				disc.isLeft = false;
				stage.discs.push_back(disc);
				break;
			}
			case 3:
			{
				GameScene::Disc discL{};
				discL.row = row;
				discL.isLeft = true;
				GameScene::Disc discR{};
				discR.row = row;
				discR.isLeft = false;
				stage.discs.push_back(discL);
				stage.discs.push_back(discR);
				break;
			}
			}
		}

		// Setup properties
		stage.size = sizeValue.GetInt();
		stage.activeColor = Color3i{ activeColorRValue.GetInt(), activeColorGValue.GetInt(), activeColorBValue.GetInt() };
		stage.inactiveColor = Color3i{ inactiveColorRValue.GetInt(), inactiveColorGValue.GetInt(), inactiveColorBValue.GetInt() };

		// Add to list
		stageSettings.push_back(stage);
	}
}

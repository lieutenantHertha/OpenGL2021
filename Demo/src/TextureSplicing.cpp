#include "TextureSplicing.h"

Vector2 Vector2::operator*(const std::pair<int, int>& symbol)
{
	return { DimensionX * symbol.first, DimensionY * symbol.second };
}

std::vector<Vector2> GenerateViewVectors(int number)
{
	std::vector<float> distanceArray;
	std::vector<std::pair<int, int>> symbolArray = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	std::vector<Vector2> viewVectorArray;

	if (number % 2 == 0)
	{
		float distance = 0.5f;
		while (distance < number / 2)
		{
			distanceArray.push_back(distance);
			distance += 1.0f;
		}
	}
	else
	{
		float distance = 1.0f;
		while (distance < number / 2.0f)
		{
			distanceArray.push_back(distance);
			distance += 1.0f;
		}
	}

	for (unsigned int x = 0; x < distanceArray.size(); x++)
		for (unsigned int y = 0; y < distanceArray.size(); y++)
		{
			for (const auto& symbol : symbolArray)
			{
				Vector2 viewVector = Vector2{ distanceArray[x], distanceArray[y] } *symbol;
				viewVectorArray.push_back(viewVector);
			}
		}

	if (number % 2 != 0)
	{
		for (unsigned int index = 0; index < distanceArray.size(); index++)
		{
			viewVectorArray.push_back(Vector2{ distanceArray[index], 0.0f });
			viewVectorArray.push_back(Vector2{ -distanceArray[index], 0.0f });
			viewVectorArray.push_back(Vector2{ 0.0f,  distanceArray[index] });
			viewVectorArray.push_back(Vector2{ 0.0f, -distanceArray[index] });
		}
		viewVectorArray.push_back(Vector2{ 0.0f, 0.0f });
	}

	return viewVectorArray;
};
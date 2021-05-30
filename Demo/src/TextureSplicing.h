#pragma once
#include <vector>
#include <tuple>

// How many texture repetitions in a single row? These are tools for texture splicing

struct Vector2 {
public:
	float DimensionX;
	float DimensionY;

public:
	Vector2 operator*(const std::pair<int, int>& symbol);
};

std::vector<Vector2> GenerateViewVectors(int number);
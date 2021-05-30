#pragma once
#include "Tests/Test.h"

class TestClearColor : public Test
{
private:
	float m_clearColor[4];
public:
	TestClearColor();
	~TestClearColor();

	void OnRender() override;
	void OnImguiRender() override;
};


#include "Test.h"

TestMenu::TestMenu(Test*& current)
	: m_Current(current)
{
	// Get current testing unit access in the main function for changing current test to be chosen inside the test menu
	// Attaching current test unit in main function to changing various test unit during the runtime.
}

TestMenu::~TestMenu()
{
	delete m_Current;
}

void TestMenu::OnImguiRender()
{
	//Config the components of the test menu
	for (const auto& singleTest : m_Tests)
	{
		if (ImGui::Button(singleTest.first.c_str()))
			m_Current = singleTest.second();
	}
}

void Test::ImGuiBegin(const char* labelName)
{
	// Start the Dear ImGui frame in the rendering while loop
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin(labelName);
}

void Test::ImGuiEnd()
{
	// After configuration of ImGui interface
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	// Rendering ImGui interface
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

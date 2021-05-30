#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "TextureSplicing.h"
#include "Tests/Test.h"
#include "Tests/TestClearColor.h"
#include "Tests/TestVertexBuffer.h"
#include "Tests/TestTexture.h"
#include "Tests/TestTextureSplicing.h"
#include "Tests/Test3DScene.h"
#include "Tests/TestCube3D.h"


int main()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1000, 1000, "Demo", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(3);

	if (glewInit() == GLEW_OK)
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	ImFontConfig config;
	config.OversampleH = 2;
	config.OversampleV = 1;
	config.GlyphExtraSpacing.x = 1.0f;
	ImFont* font = io.Fonts->AddFontFromFileTTF("resource/fonts/Roboto-Regular.ttf", 18.0f, &config);

	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();

	// Setup Platform/Renderer back-end
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));

	{
		Test* current = nullptr;
		TestMenu* testMenu = new TestMenu(current);
		current = testMenu;
		testMenu->LoadTest<TestClearColor>("Clear Color");
		testMenu->LoadTest<TestVertexBuffer>("Vertex Position");
		testMenu->LoadTest<TestTexture>("Logo Exhibition");
		testMenu->LoadTest<TestTextureSplicing>("Texture Splicing");
		testMenu->LoadTest<TestCube>("3D Scene");
		testMenu->LoadTest<TestCube3D>("Test Cube");

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			current->OnUpdate(0.0f);
			current->OnRender();

			/* Poll for and process events */
			glfwPollEvents();

			Test::ImGuiBegin("TEST");
			current->OnImguiRender();
			if (current != testMenu && ImGui::Button("<-"))
			{
				delete current;
				current = testMenu;
			}
			Test::ImGuiEnd();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);
		}
	}

	// Cleanup ImGui components to avoid memory leak kind of problem
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}

#include <glad/glad.h>
#include <GLFW/glfw3.h>
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

#include "game.h"
#include "text_renderer.h"
#include "resource_manager.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const unsigned int WindowWidth = 800;
const unsigned int WindowHeight = 800;

Game CallToCoda(WindowWidth, WindowHeight);

int main(int argc, char* argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, "Call.To.Coda", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}





	// OpenGL Config
	glViewport(0, 0, WindowWidth, WindowHeight);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	//while (menuActive || !glfwWindowShouldClose(window))
	//{
	//	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	//}

	// Start Game


	// deltaTime Variables
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// Frame Rate Variables
	float elapsedTime = 0.0f;
	unsigned int counter = 0;

	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	

	CallToCoda.Init();

	CallToCoda.State = GAME_MENU;

	/*
	while (!glfwWindowShouldClose(window) && (CallToCoda.State == GAME_MENU))
	{

		glfwPollEvents();
	}
	*/
	//CallToCoda.StartMusic();

	while (!glfwWindowShouldClose(window))
	{
		//if (!menuActive)
		//{
			// deltaTime Calculation
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		counter++;
		lastFrame = currentFrame;
		elapsedTime += deltaTime;

		if (elapsedTime >= 1.0f)
		{
			std::string framesPerSecond = std::to_string(counter / elapsedTime);
			std::string milliseconds = std::to_string((counter / elapsedTime) * 1000.0f);
			std::string newTitle = "CallToCoda - " + framesPerSecond + "FPS / " + milliseconds + "ms";
			glfwSetWindowTitle(window, newTitle.c_str());
			counter = 0;
			elapsedTime = 0.0f;
		}

		glfwPollEvents();

		// input
		//CallToCoda.ProcessInput(deltaTime);

		// update game state
		CallToCoda.Update(deltaTime);

		// rendering commands here
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		CallToCoda.Render();


		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		//}
	}

	// delete all resources as loadedd using the resource manager
	ResourceManager::Clear();

	glfwTerminate();
	return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// when a user presses the escape key, we set the WindowShouldClose property to true, closing the application similar to processInput
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if ((key == GLFW_KEY_W || key == GLFW_KEY_UP) && action == GLFW_PRESS)
	{
		CallToCoda.PlayerShoot(); // Player Shoot
	}
	else if ((key == GLFW_KEY_A || key == GLFW_KEY_LEFT) && action == GLFW_PRESS)
	{
		CallToCoda.PlayerDodgeLeft();
	}
	else if ((key == GLFW_KEY_D || key == GLFW_KEY_RIGHT) && action == GLFW_PRESS)
	{
		CallToCoda.PlayerDodgeRight();
	}
	else if ((key == GLFW_KEY_S || key == GLFW_KEY_DOWN) && action == GLFW_PRESS)
	{
		CallToCoda.PlayerShootDiagonal();
	}
	else if ((key == GLFW_KEY_ENTER) && CallToCoda.State != GAME_ACTIVE)
	{
		CallToCoda.StartMusic();
		CallToCoda.State = GAME_ACTIVE;
	}
	else if ((key == GLFW_KEY_Q) && action == GLFW_PRESS)
	{
		CallToCoda.EnemyShootLeft();
	}
	else if ((key == GLFW_KEY_E) && action == GLFW_PRESS)
	{
		CallToCoda.EnemyShootRight();
	}

}

/*
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
*/
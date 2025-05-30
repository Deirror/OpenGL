#include "Engine.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "VertexArray.h"

#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Engine::run(GLFWwindow* window)
{
	// Enable GL Effects
	glfwSwapInterval(1);

	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	// Main Code
	float verts[] =
	{
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,

		960.0f, 0.0f, 0.5,
		1.0f, 0.0f, 0.0f,
		
		480.0f, 540.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, 540.0f, 0.1f,
		0.0f, 0.0f, 1.0f,

		960.0f, 540.0f, -0.5f, 
		0.0f, 0.0f, 1.0f,

		480.0f, 0.0f, -1.0f,
		0.0f, 0.0f, 1.0f,
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		3, 4, 5	
	};

	glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	glm::mat4 mvp = proj * view * model;

	VertexBuffer vb(verts, 6 * sizeof(float) * 6);

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);

	VertexArray va;
	va.AddVertexBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	Shader shader("res/shaders/Basic.shader");
	shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	shader.SetUniformMat4f("u_MVP", mvp);

	Renderer renderer;

	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();
		
		renderer.Draw(va, ib, shader);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
}

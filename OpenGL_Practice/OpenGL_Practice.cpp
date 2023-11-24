﻿#define STB_IMAGE_IMPLEMENTATION

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


const float toRadians = glm::pi<float>() / 180.f;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

GLfloat deltaTime = 0.f;
GLfloat lastTime = 0.f;


// Vertex Shadder
static const char* vShader = "Shaders/shader.vert";

// Fragment Shadder
static const char* fShader = "Shaders/shader.frag";


void CreateObjects() {
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		// x,  y,  z,  u,  v
		-1.f, -1.f, 0.f, 0.f, 0.f,
		0.f, -1.f, 1.f, 0.5f, 0.f,
		1.0f, -1.0f, 0.f, 1.f, 0.f,
		0.f, 1.0f, 0.f, 0.5f, 1.f,
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(obj2);
}

void CreateShaders() {
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(shader1);
}

int main(void) {
	Window* mainWindow = new Window(800, 600);
	mainWindow->Initialise();

	CreateObjects();
	CreateShaders();

	Camera* camera = new Camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f), -90.0f, 0.0f, 5.f, 0.5f);

	Texture* brickTexture = new Texture("Textures/brick.png");
	brickTexture->LoadTexture();
	Texture* dirtTexture = new Texture("Textures/dirt.png");
	dirtTexture->LoadTexture();


	GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0;

	glm::mat4 projection = glm::perspective(45.0f, static_cast<GLfloat>(mainWindow->GetBufferWidth()) / static_cast<GLfloat>(mainWindow->GetBufferHeight()), 0.1f, 100.f);

	// Loop until window closed
	while (!mainWindow->GetShouldClose()) {

		// Calculate delta time for FPS
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime; // Time unit is ms
		lastTime = now;

		// Get + Handle user input events
		glfwPollEvents();

		camera->KeyControl(mainWindow->GetKeys(), deltaTime);
		camera->MouseControl(mainWindow->GetXChange(), mainWindow->GetYChange());

		// Clear window
		glClearColor(0.f, 0.0f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformView = shaderList[0]->GetViewLocation();

		glm::mat4 model(1.f);

		// Translate, Rotate and then Scale
		model = glm::translate(model, glm::vec3(0.f, 0.f, -2.5f));
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.f, 0.f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		// Update model
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		// Update projection
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		// Update view
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->CalculateViewMatrix()));
		brickTexture->UseTexture();
		meshList[0]->RenderMesh();


		model = glm::mat4(1.f);
		// Translate, Rotate and then Scale
		model = glm::translate(model, glm::vec3(0.f, 1.f, -2.5f));
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.f, 0.f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture->UseTexture();
		meshList[1]->RenderMesh();

		glUseProgram(0);

		mainWindow->SwapBuffers();
	}


	//Release heap memory


	for (int i = 0; i < meshList.size(); ++i) {
		delete meshList[i];
		meshList[i] = nullptr;
	}

	for (int i = 0; i < shaderList.size(); ++i) {
		delete shaderList[i];
		shaderList[i] = nullptr;
	}

	delete mainWindow; mainWindow = nullptr;
	delete camera; camera = nullptr;
	delete brickTexture; brickTexture = nullptr;
	delete dirtTexture; dirtTexture = nullptr;

	return 0;
}
#define STB_IMAGE_IMPLEMENTATION

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"
#include "Material.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

#include <spdlog/spdlog.h>

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
static const char* vShader = "../../Shaders/shader.vert";

// Fragment Shadder
static const char* fShader = "../../Shaders/shader.frag";

void CalcAverageNormals(unsigned int* indices, unsigned int indicesCount, GLfloat* vertices, unsigned int vecticesCount, unsigned int vLength, unsigned int normalOffset) {
	for (size_t i = 0; i < indicesCount; i += 3) {
		unsigned int idx0 = indices[i] * vLength;
		unsigned int idx1 = indices[i + 1] * vLength;
		unsigned int idx2 = indices[i + 2] * vLength;

		glm::vec3 v1(vertices[idx1] - vertices[idx0], vertices[idx1 + 1] - vertices[idx0 + 1], vertices[idx1 + 2] - vertices[idx0 + 2]);
		glm::vec3 v2(vertices[idx2] - vertices[idx0], vertices[idx2 + 1] - vertices[idx0 + 1], vertices[idx2 + 2] - vertices[idx0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);


		idx0 += normalOffset;
		idx1 += normalOffset;
		idx2 += normalOffset;

		vertices[idx0] += normal.x; vertices[idx0 + 1] += normal.y; vertices[idx0 + 2] += normal.z;
		vertices[idx1] += normal.x; vertices[idx1 + 1] += normal.y; vertices[idx1 + 2] += normal.z;
		vertices[idx2] += normal.x; vertices[idx2 + 1] += normal.y; vertices[idx2 + 2] += normal.z;

	}

	for (size_t i = 0; i < vecticesCount / vLength; ++i) {
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects() {
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		// x,   y,     z,     u,     v      nx     ny     nz
		-1.f,  -1.f,   -0.6f,   0.f,   0.f,   0.f,   0.f,   0.f,
		 0.f,  -1.f,   1.f,   0.5f,  0.f,   0.f,   0.f,   0.f,
		 1.0f, -1.0f,  -0.6f,   1.f,   0.f,   0.f,   0.f,   0.f,
		 0.f,   1.0f,  0.f,   0.5f,  1.f,   0.f,   0.f,   0.f
	};

	CalcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);
}

void CreateShaders() {
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(shader1);
}

int main(int argc, const char** argv) {
	SPDLOG_INFO("OPENGL program start");
	Window* mainWindow = new Window(1280, 1024);
	mainWindow->Initialise();

	CreateObjects();
	CreateShaders();

	Camera* camera = new Camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f), -90.0f, 0.0f, 5.f, 0.5f);

	Texture* brickTexture = new Texture("../../Textures/brick.png");
	brickTexture->LoadTexture();
	Texture* dirtTexture = new Texture("../../Textures/dirt.png");
	dirtTexture->LoadTexture();

	Light* mainLight = new Light(1.f, 1.f, 1.f, 0.2f, 
								2.f, -1.f, -2.f, 0.3f);

	Material* shinyMaterial = new Material(1.f, 32);
	Material* dullMaterial = new Material(0.3f, 4);

	GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0,
		uniformAmbientIntensity = 0, uniformAmbientColour = 0, uniformDirection = 0, uniformDiffuseIntensity = 0,
		uniformEyePosition = 0, uniformSpecualrIntensity = 0, uniformShininess = 0;

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
		uniformAmbientIntensity = shaderList[0]->GetAmbientIntensityLocation();
		uniformAmbientColour = shaderList[0]->GetAmbientColourLocation();
		uniformDirection = shaderList[0]->GetDirectionLocation();
		uniformDiffuseIntensity = shaderList[0]->GetDiffuseIntensityLocation();
		uniformEyePosition = shaderList[0]->GetEyePositionLocation();
		uniformSpecualrIntensity = shaderList[0]->GetSpecularIntensityLocation();
		uniformShininess = shaderList[0]->GetShininessLocation();


		mainLight->UseLight(uniformAmbientIntensity, uniformAmbientColour,
							uniformDiffuseIntensity, uniformDirection);


		// Update projection
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		// Update view
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->CalculateViewMatrix()));
		// Update Camera
		glUniform3f(uniformEyePosition, camera->GetCameraPosition().x, camera->GetCameraPosition().y, camera->GetCameraPosition().z);

		glm::mat4 model(1.f);
		// Translate, Rotate and then Scale
		model = glm::translate(model, glm::vec3(0.f, 0.f, -2.5f));
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.f, 0.f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		// Update model
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		brickTexture->UseTexture();
		shinyMaterial->UseMaterial(uniformSpecualrIntensity, uniformShininess);
		meshList[0]->RenderMesh();


		model = glm::mat4(1.f);
		// Translate, Rotate and then Scale
		model = glm::translate(model, glm::vec3(0.f, 4.f, -2.5f));
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.f, 0.f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture->UseTexture();
		dullMaterial->UseMaterial(uniformSpecualrIntensity, uniformShininess);
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
	delete mainLight; mainLight = nullptr;
	delete shinyMaterial; shinyMaterial = nullptr;
	delete dullMaterial; dullMaterial = nullptr;
	return 0;
}
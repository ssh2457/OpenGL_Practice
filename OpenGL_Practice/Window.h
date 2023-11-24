#pragma once

#include <cstdio>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	virtual ~Window();

	int Initialise();

	GLint GetBufferWidth() const;
	GLint GetBufferHeight() const;

	bool GetShouldClose();

	void SwapBuffers();

	bool* GetKeys();

	GLfloat GetXChange();
	GLfloat GetYChange();

private:
	GLFWwindow* mainWindow;

	// Window dimensions
	const GLint WIDTH, HEIGHT;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;

	void CreateCallbacks();
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
};
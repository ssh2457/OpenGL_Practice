#include "Window.h"

Window::Window()
	: WIDTH(800)
	, HEIGHT(600)
	, mainWindow(nullptr)
	, bufferWidth(0)
	, bufferHeight(0)
	, lastX(0.f)
	, lastY(0.f)
	, xChange(0.f)
	, yChange(0.f)
	, mouseFirstMoved(true)
{
	for (int i = 0; i < 1024; ++i) {
		keys[i] = false;
	}
}


Window::Window(GLint windowWidth, GLint windowHeight)
	: WIDTH(windowWidth)
	, HEIGHT(windowHeight)
	, mainWindow(nullptr)
	, bufferWidth(0)
	, bufferHeight(0)
	, lastX(0.f)
	, lastY(0.f)
	, xChange(0.f)
	, yChange(0.f)
	, mouseFirstMoved(true)
{
	for (int i = 0; i < 1024; ++i) {
		keys[i] = false;
	}
}

Window::~Window() {
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

int Window::Initialise() {
	// Initialize GLFW
	if (!glfwInit()) {
		printf("GLFW initialization failed!\n");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile = No Backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test window", NULL, NULL);
	if (!mainWindow) {
		printf("GLFW window creation failed!\n");
		glfwTerminate();
		return 1;
	}

	// Get Buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Handle key + Mouse input
	CreateCallbacks();

	// Hide mouse cursor in window
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	// Allow mordern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("GLEW initialization failed!\n");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Depth test
	glEnable(GL_DEPTH_TEST);

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	// Set window user pointer
	glfwSetWindowUserPointer(mainWindow, this);

	return 0;
}

GLint Window::GetBufferWidth() const {
	return bufferWidth;
}

GLint Window::GetBufferHeight() const {
	return bufferHeight;
}

bool Window::GetShouldClose() {
	return glfwWindowShouldClose(mainWindow);
}

void Window::SwapBuffers() {
	glfwSwapBuffers(mainWindow);
}

bool* Window::GetKeys(){
	return keys;
}

GLfloat Window::GetXChange() {
	GLfloat theChange = xChange;
	xChange = 0.f;
	return theChange;
}

GLfloat Window::GetYChange() {
	GLfloat theChange = yChange;
	yChange = 0.f;
	return theChange;
}

void Window::CreateCallbacks() {
	glfwSetKeyCallback(mainWindow, HandleKeys);
	glfwSetCursorPosCallback(mainWindow, HandleMouse);
}


void Window::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (0 <= key && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
			printf("Pressed %d\n", key);
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
			printf("Released %d\n", key);
		}
	}
}

void Window::HandleMouse(GLFWwindow* window, double xPos, double yPos) {
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved) {
		theWindow->lastX = static_cast<GLfloat>(xPos);
		theWindow->lastY = static_cast<GLfloat>(yPos);
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = static_cast<GLfloat>(xPos - theWindow->lastX);
	theWindow->yChange = static_cast<GLfloat>(theWindow->lastY - yPos);

	theWindow->lastX = static_cast<GLfloat>(xPos);
	theWindow->lastY = static_cast<GLfloat>(yPos);

	printf("x: %.6f, y: %.6f\n", theWindow->xChange, theWindow->yChange);
}
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

class Camera {
public:
	Camera() = delete;
	Camera(glm::vec3 startPosition, glm::vec3 startWorldUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	virtual ~Camera();

	void KeyControl(bool* keys, GLfloat deltaTime);
	void MouseControl(GLfloat xChange, GLfloat yChange);
	glm::mat4 CalculateViewMatrix();

	glm::vec3 GetCameraPosition() const;
	glm::vec3 GetCameraDirection() const;

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat movementSpeed;
	GLfloat turnSpeed;

	void Update();
};

#ifndef CAMERA_H
#define CAMERA_H
#include <GLFW\glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera
{
public:
	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : camera_front(glm::vec3(0.0f, 0.0f, -1.0f)), move_speed(SPEED), mouse_sensitivity(SENSITIVITY), fov(ZOOM)
	{
		this->camera_pos = position;
		this->camera_up = up;
		this->yaw = yaw;
		this->pitch = pitch;
		updateCameraVectors();
	}
	void processInput(GLFWwindow* window, float deltaTime);
	void mouse_callback(GLFWwindow* window, float xpos, float ypos);
	void scroll_callback(GLFWwindow* window, float xoffset, float yoffset);
	glm::mat4 get_view();
	float get_fov() const;
	glm::vec3 get_pos() const;
	glm::vec3 get_front() const;
	void lock_plane(bool locked);
private:

	glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 camera_right;
	float camera_speed = 2.5f;
	float pitch = 0, yaw = 0;
	float fov = 45.0f;

	float move_speed, mouse_sensitivity;

	float lastX = 400, lastY = 300;
	bool firstMouse = true;
	bool locked_plane = true;
	void updateCameraVectors() {
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		camera_front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		camera_right = glm::normalize(glm::cross(camera_front, world_up));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		camera_up = glm::normalize(glm::cross(camera_right, camera_front));
	}
};


#endif
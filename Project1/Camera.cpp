#include "Camera.h"

Camera::Camera()
{
}

void Camera::processInput(GLFWwindow* window, float deltaTime)
{
	glm::vec3 camera_front = get_front();
	glm::vec3 myFront = glm::vec3(camera_front.x, 0.0f, camera_front.z);
	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * myFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * myFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(camera_front, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(camera_front, cameraUp)) * cameraSpeed;
}

void Camera::mouse_callback(GLFWwindow* window, float xpos, float ypos)
{
	if (firstMouse) // 这个bool变量初始时是设定为true的
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
}

void Camera::scroll_callback(GLFWwindow* window, float xoffset, float yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

glm::vec3 Camera::get_front() const
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::vec3 front = glm::vec3(0.0f);
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	return front;
}

glm::mat4 Camera::get_view()
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraPos + get_front(), cameraUp);
	return view;
}

float Camera::get_fov() const
{
	return fov;
}

glm::vec3 Camera::get_pos() const
{
	return cameraPos;
}

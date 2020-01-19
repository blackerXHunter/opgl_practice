#include "Camera.h"

void Camera::processInput(GLFWwindow* window, float deltaTime)
{
	glm::vec3 camera_front = get_front();
	glm::vec3 myFront = glm::vec3(0.0);
	if (locked_plane)
	{
		myFront = glm::vec3(camera_front.x, 0.0f, camera_front.z);
	}
	else
	{
		myFront = camera_front;
	}
	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera_pos += cameraSpeed * myFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera_pos -= cameraSpeed * myFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;
	updateCameraVectors();
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

	xoffset *= mouse_sensitivity;
	yoffset *= mouse_sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	updateCameraVectors();
}

void Camera::scroll_callback(GLFWwindow* window, float xoffset, float yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
	updateCameraVectors();
}

glm::vec3 Camera::get_front() const
{
	return camera_front;
}

void Camera::lock_plane(bool locked)
{
	this->locked_plane = locked;
}

glm::mat4 Camera::get_view()
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(camera_pos, camera_pos + get_front(), camera_up);
	return view;
}

float Camera::get_fov() const
{
	return fov;
}

glm::vec3 Camera::get_pos() const
{
	return camera_pos;
}

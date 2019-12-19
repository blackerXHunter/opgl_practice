#ifndef CAMERA_H
#define CAMERA_H
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
public:
	Camera();
	void processInput(GLFWwindow* window, float deltaTime);
	void mouse_callback(GLFWwindow* window, float xpos, float ypos);
	void scroll_callback(GLFWwindow* window, float xoffset, float yoffset);
	glm::mat4 get_view();
	float get_fov();
	glm::vec3 get_pos();

private:

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float camera_speed = 2.5f;
	float pitch = 0, yaw = 0;
	float fov = 45.0f;


	float lastX = 400, lastY = 300;
	bool firstMouse = true;

};


#endif
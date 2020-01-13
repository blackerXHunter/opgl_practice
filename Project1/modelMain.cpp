/***
 * ����  ���������� (MAKE������ʱ��ɾ��ALL_BUILD��Ҳ���Խ�Task-triangle��ΪĬ����������)
 * ����:
 * 1-��ʼ��:   GLFW���ڣ�GLAD��
 * 2-���ݴ���: �����������ݣ����ɲ���VAO&VBO(׼����GPU�н��д���)�����ö�������ָ��(�����Ͼ��Ǹ���OpenGL��δ�������)��
 * 3-��ɫ��:   ���������Ƭ����ɫ����Ȼ������Ϊ��ɫ��������Ⱦʱʹ����ɫ������
 * 4-��Ⱦ:     ��ջ��壬������ʹ����ɫ�����򣬻��������Σ�������������鴥���¼����ͷ���Դ
 */
#include "Global.h"

int main() {

	// ��ʼ��GLFW
	glfwInit();                                                     // ��ʼ��GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // OpenGL�汾Ϊ3.3�����ΰ汾�ž���Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // ʹ�ú���ģʽ(������������)
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // ���ʹ�õ���Mac OS Xϵͳ�����������
	glfwWindowHint(GLFW_RESIZABLE, false);						    // ���ɸı䴰�ڴ�С

	// ��������(���ߡ���������)
	auto window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triangle", nullptr, nullptr);
	if (window == nullptr) {                                        // ������ڴ���ʧ�ܣ����Failed to Create OpenGL Context
		std::cout << "Failed to Create OpenGL Context" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);                                 // �����ڵ�����������Ϊ��ǰ�̵߳���������
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// ��ʼ��GLAD������OpenGL����ָ���ַ�ĺ���
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	Console();

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	//Shader modelShader("shader/model/model_g.vs", "shader/model/model_g.gs", "shader/model/model_g.fs");
	Shader modelShader("shader/model/model_g.vs", "shader/model/model_g.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float points[] = {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // ����
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // ����
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // ����
		-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // ����
	};

	// points vao
	Model ourModel("nanosuit/nanosuit.obj");
	// load textures
	// -------------


	// shader configuration
	// --------------------


	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) {
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		// make sure we clear the framebuffer's content
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// draw models
		// 
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		modelShader.use();
		modelShader.setVec3("viewPos", camera.get_pos());
		modelShader.setFloat("material.shininess", 32);

		modelShader.setVec3("dirLight.direction", -1.0f, -1.0f, -1.0f);
		modelShader.setVec3("dirLight.diffuse", glm::vec3(1.0f));
		modelShader.setVec3("dirLight.ambient", glm::vec3(1.0f));
		modelShader.setVec3("dirLight.specular", glm::vec3(1.0f));


		//for (size_t i = 0; i < (sizeof(pointLightPositions) / sizeof(glm::vec3)); i++)
		//{
		//	std::stringstream ss;
		//	ss << "pointLights[" << i << "].";
		//	std::string frontStr = ss.str();
		//	modelShader.setVec3(frontStr + "position", pointLightPositions[i]);
		//	modelShader.setVec3(frontStr + "ambient", 0.05f, 0.05f, 0.05f);
		//	modelShader.setVec3(frontStr + "diffuse", 0.8f, 0.8f, 0.8f);
		//	modelShader.setVec3(frontStr + "specular", 1.0f, 1.0f, 1.0f);
		//	modelShader.setFloat(frontStr + "constant", 1.0f);
		//	modelShader.setFloat(frontStr + "linear", 0.09);
		//	modelShader.setFloat(frontStr + "quadratic", 0.032);
		//}

		modelShader.setVec3("spotLight.position", camera.get_pos());
		modelShader.setVec3("spotLight.direction", camera.get_front());
		modelShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		modelShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));

		modelShader.setFloat("spotLight.constant", 1.0f);
		modelShader.setFloat("spotLight.linear", 0.09);
		modelShader.setFloat("spotLight.quadratic", 0.032);

		modelShader.setVec3("spotLight.ambient", glm::vec3(1.0f));
		modelShader.setVec3("spotLight.diffuse", glm::vec3(1.0f)); // �����յ�����һЩ�Դ��䳡��
		modelShader.setVec3("spotLight.specular", glm::vec3(1.0f));

		auto projection = glm::perspective(camera.get_fov(), (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
		auto view = camera.get_view();
		modelShader.setMat4("projection", projection);
		modelShader.setMat4("view", view);

		auto model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		modelShader.setMat4("model", model);
		ourModel.Draw(modelShader);


		// �������岢�Ҽ���Ƿ��д����¼�(����������롢����ƶ��ȣ�
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------

	// �������е���Դ����ȷ�˳�����
	glfwTerminate();
	return 0;
}

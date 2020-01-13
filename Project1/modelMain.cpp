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
	//Shader shader("shader/model/model_g.vs", "shader/model/model_g.gs", "shader/model/model_g.fs");
	Shader shader("shader/model/model_g.vs",  "shader/model/model_g.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float points[] = {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // ����
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // ����
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // ����
		-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // ����
	};

	// points vao
	Model model("nanosuit/nanosuit.obj");
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
		// draw scene as normal
		model.Draw(shader);

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

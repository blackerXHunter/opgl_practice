/***
 * 例程  绘制三角形 (MAKE后运行时可删除ALL_BUILD，也可以将Task-triangle设为默认启动工程)
 * 步骤:
 * 1-初始化:   GLFW窗口，GLAD。
 * 2-数据处理: 给定顶点数据，生成并绑定VAO&VBO(准备在GPU中进行处理)，设置顶点属性指针(本质上就是告诉OpenGL如何处理数据)。
 * 3-着色器:   给出顶点和片段着色器，然后链接为着色器程序，渲染时使用着色器程序。
 * 4-渲染:     清空缓冲，绑定纹理，使用着色器程序，绘制三角形，交换缓冲区检查触发事件后释放资源
 */
#include "Global.h"

int main() {

	// 初始化GLFW
	glfwInit();                                                     // 初始化GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // OpenGL版本为3.3，主次版本号均设为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 使用核心模式(无需向后兼容性)
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 如果使用的是Mac OS X系统，需加上这行
	glfwWindowHint(GLFW_RESIZABLE, false);						    // 不可改变窗口大小

	// 创建窗口(宽、高、窗口名称)
	auto window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triangle", nullptr, nullptr);
	if (window == nullptr) {                                        // 如果窗口创建失败，输出Failed to Create OpenGL Context
		std::cout << "Failed to Create OpenGL Context" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);                                 // 将窗口的上下文设置为当前线程的主上下文
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// 初始化GLAD，加载OpenGL函数指针地址的函数
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
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 左上
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // 右上
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 右下
		-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // 左下
	};

	// points vao
	Model ourModel("nanosuit/nanosuit.obj");
	// load textures
	// -------------


	// shader configuration
	// --------------------


	// 渲染循环
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
		modelShader.setVec3("spotLight.diffuse", glm::vec3(1.0f)); // 将光照调暗了一些以搭配场景
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


		// 交换缓冲并且检查是否有触发事件(比如键盘输入、鼠标移动等）
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------

	// 清理所有的资源并正确退出程序
	glfwTerminate();
	return 0;
}

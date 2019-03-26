//#define STB_IMAGE_IMPLEMENTATION
//#include <glad/glad.h>
//#include <GLFW\glfw3.h>
//#include "stb_image.h"
//#include "shader_s.h"
//#include "camera.h"
//#include <iostream>
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//unsigned int loadTexture(const char *path);
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//int main() {
//	// glfw: initialize and configure
//	// ------------------------------
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
//#endif
//														 // glfw window creation
//														 // --------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tian,good!", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// tell GLFW to capture our mouse
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	// glad: load all OpenGL function pointers
//	// ---------------------------------------
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//	glEnable(GL_DEPTH_TEST);
//	glDepthMask(GL_FALSE);
//	Shader ourShader("shader_s.vs", "shader_s.fs");
//	Shader lightShader("lamp.vs", "lamp.fs");
//
//	float vertices[] = {
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
//	};
//	glm::vec3 cubePositions[] = {
//		glm::vec3(0.0f,  0.0f,  0.0f),
//		glm::vec3(2.0f,  5.0f, -15.0f),
//		glm::vec3(-1.5f, -2.2f, -2.5f),
//		glm::vec3(-3.8f, -2.0f, -12.3f),
//		glm::vec3(2.4f, -0.4f, -3.5f),
//		glm::vec3(-1.7f,  3.0f, -7.5f),
//		glm::vec3(1.3f, -2.0f, -2.5f),
//		glm::vec3(1.5f,  2.0f, -2.5f),
//		glm::vec3(1.5f,  0.2f, -1.5f),
//		glm::vec3(-1.3f,  1.0f, -1.5f)
//	};
//	glm::vec3 pointLightPositions[] = {
//		glm::vec3(0.7f,  0.2f,  2.0f),
//		glm::vec3(2.3f, -3.3f, -4.0f),
//		glm::vec3(-4.0f,  2.0f, -12.0f),
//		glm::vec3(0.0f,  0.0f, -3.0f)
//	};
//	unsigned int VBO;
//	unsigned int CubeVAO;
//
//	glGenVertexArrays(1, &CubeVAO);
//	glGenBuffers(1, &VBO);
//	//1绑定数据对象
//	glBindVertexArray(CubeVAO);
//	//2把顶点数据复制到顶点缓冲区
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	//4解析顶点数据，激活顶点属性
//	//位置属性
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// normal attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	//纹理属性
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//
//	unsigned int lightVAO;
//	glGenVertexArrays(1, &lightVAO);
//	glBindVertexArray(lightVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	unsigned int WoodMap = loadTexture("resource/container2.png");
//	unsigned int SpecularMap = loadTexture("resource/container2_specular.png");
//
//	ourShader.use();
//	ourShader.setInt("material.diffuse", 0);
//	ourShader.setInt("material.specular", 1);
//	// render loop
//	// -----------
//
//	while (!glfwWindowShouldClose(window))
//	{
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// input
//		// -----
//		processInput(window);
//
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 projection = glm::mat4(1.0f);
//		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 model = glm::mat4(1.0f);
//
//		ourShader.use();
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, WoodMap);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, SpecularMap);
//
//		ourShader.setMat4("view", view);
//		ourShader.setMat4("projection", projection);
//		ourShader.setMat4("model", model);
//
//		ourShader.setVec3("viewPos", camera.Position);
//		ourShader.setFloat("material.shininess", 32.0f);
//
//		// directional light
//		ourShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
//		ourShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
//		ourShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
//		ourShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//		// point light 1
//		ourShader.setVec3("pointLights[0].position", pointLightPositions[0]);
//		ourShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
//		ourShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
//		ourShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
//		ourShader.setFloat("pointLights[0].constant", 1.0f);
//		ourShader.setFloat("pointLights[0].linear", 0.09);
//		ourShader.setFloat("pointLights[0].quadratic", 0.032);
//		// point light 2
//		ourShader.setVec3("pointLights[1].position", pointLightPositions[1]);
//		ourShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
//		ourShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
//		ourShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
//		ourShader.setFloat("pointLights[1].constant", 1.0f);
//		ourShader.setFloat("pointLights[1].linear", 0.09);
//		ourShader.setFloat("pointLights[1].quadratic", 0.032);
//		// point light 3
//		ourShader.setVec3("pointLights[2].position", pointLightPositions[2]);
//		ourShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
//		ourShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
//		ourShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
//		ourShader.setFloat("pointLights[2].constant", 1.0f);
//		ourShader.setFloat("pointLights[2].linear", 0.09);
//		ourShader.setFloat("pointLights[2].quadratic", 0.032);
//		// point light 4
//		ourShader.setVec3("pointLights[3].position", pointLightPositions[3]);
//		ourShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
//		ourShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
//		ourShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
//		ourShader.setFloat("pointLights[3].constant", 1.0f);
//		ourShader.setFloat("pointLights[3].linear", 0.09);
//		ourShader.setFloat("pointLights[3].quadratic", 0.032);
//		// spotLight
//		ourShader.setVec3("spotLight.position", camera.Position);
//		ourShader.setVec3("spotLight.direction", camera.Front);
//		ourShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
//		ourShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
//		ourShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
//		ourShader.setFloat("spotLight.constant", 1.0f);
//		ourShader.setFloat("spotLight.linear", 0.09);
//		ourShader.setFloat("spotLight.quadratic", 0.032);
//		ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
//		ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
//
//
//		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(CubeVAO);
//		for (unsigned int i = 0; i < 10; i++) {
//			model = glm::mat4(1.0f);
//			model = glm::translate(model, cubePositions[i]);
//			float angle = 20.0f * i;
//			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//
//			ourShader.setMat4("model", model);
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//
//		lightShader.use();
//		lightShader.setMat4("view", view);
//		lightShader.setMat4("projection", projection);
//
//		glBindVertexArray(lightVAO);
//		for (unsigned int i = 0; i < 4; i++)
//		{
//			model = glm::mat4(1.0f);
//			model = glm::translate(model, pointLightPositions[i]);
//			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
//			lightShader.setMat4("model", model);
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glDeleteVertexArrays(1, &CubeVAO);
//	glDeleteVertexArrays(1, &lightVAO);
//	glDeleteBuffers(1, &VBO);
//	// glfw: terminate, clearing all previously alllocated GLFW resources.
//	// ------------------------------------------------------------------
//	glfwTerminate();
//	return 0;
//}
//
//void framebuffer_size_callback(GLFWwindow * window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow * window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//void mouse_callback(GLFWwindow * window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}
//
//unsigned int loadTexture(const char * path)
//{
//	unsigned int texture1;
//	glGenTextures(1, &texture1);
//	// 加载并生成纹理
//	int width, height, nrComponents;
//	stbi_set_flip_vertically_on_load(true);
//	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
//	if (data)
//	{
//		GLenum format;
//		if (nrComponents == 1) {
//			format = GL_RED;
//		}
//		else if (nrComponents == 3) {
//			format = GL_RGB;
//		}
//		else if (nrComponents == 4) {
//			format = GL_RGBA;
//		}
//		glBindTexture(GL_TEXTURE_2D, texture1);
//		// 为当前绑定的纹理对象设置环绕、过滤方式
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//	}
//	stbi_image_free(data);
//	return texture1;
//}

//#version 330 core
//layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec3 aNormal;
//layout(location = 2) in vec2 aTexCoords;
//
//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;
//
//out vec3 Normal;
//out vec3 FragPos;
//out vec2 TexCoords;
//
//void main()
//{
//	FragPos = vec3(model * vec4(aPos, 1.0));
//	gl_Position = projection * view * vec4(FragPos, 1.0);
//	Normal = mat3(transpose(inverse(model))) * aNormal;
//	TexCoords = aTexCoords;
//}


//#version 330 core
//in vec3 Normal;
//in vec3 FragPos;
//in vec2 TexCoords;
//
//out vec4 FragColor;
//uniform vec3 viewPos;
//
//struct Material {
//	sampler2D diffuse;
//	sampler2D specular;
//	float shininess;
//};
//uniform Material material;
//
//struct DirLight {
//	vec3 direction;
//
//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
//};
//uniform DirLight dirLight;
//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
//
//struct PointLight {
//	vec3 position;
//
//	float constant;
//	float linear;
//	float quadratic;
//
//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
//};
//#define NR_POINT_LIGHTS 4
////点光源的数量
//uniform PointLight pointLights[NR_POINT_LIGHTS];
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
//
//struct SpotLight {
//	vec3 position;
//	vec3 direction;
//	float cutOff;
//	float outerCutOff;
//
//	float constant;
//	float linear;
//	float quadratic;
//
//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
//};
//uniform SpotLight spotLight;
//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
//
//void main() {
//	// 属性
//	vec3 norm = normalize(Normal);
//	vec3 viewDir = normalize(viewPos - FragPos);
//
//	// 第一阶段：定向光照
//	vec3 result = CalcDirLight(dirLight, norm, viewDir);
//	// 第二阶段：点光源
//	for (int i = 0; i < NR_POINT_LIGHTS; i++)
//		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
//	// 第三阶段：聚光
//	result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
//
//	FragColor = vec4(result, 1.0);
//}
//
//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
//{
//	vec3 lightDir = normalize(-light.direction);
//	// 漫反射着色
//	float diff = max(dot(normal, lightDir), 0.0);
//	// 镜面光着色
//	vec3 reflectDir = reflect(-lightDir, normal);
//	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//	// 合并结果
//	vec3 ambient = light.ambient  * vec3(texture(material.diffuse, TexCoords));
//	vec3 diffuse = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
//	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
//	return (ambient + diffuse + specular);
//}
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
//{
//	vec3 lightDir = normalize(light.position - fragPos);
//	// 漫反射着色
//	float diff = max(dot(normal, lightDir), 0.0);
//	// 镜面光着色
//	vec3 reflectDir = reflect(-lightDir, normal);
//	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//	// 衰减
//	float distance = length(light.position - fragPos);
//	float attenuation = 1.0 / (light.constant + light.linear * distance +
//		light.quadratic * (distance * distance));
//	// 合并结果
//	vec3 ambient = light.ambient  * vec3(texture(material.diffuse, TexCoords));
//	vec3 diffuse = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
//	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
//	ambient *= attenuation;
//	diffuse *= attenuation;
//	specular *= attenuation;
//	return (ambient + diffuse + specular);
//}
//// calculates the color when using a spot light.
//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
//{
//	vec3 lightDir = normalize(light.position - fragPos);
//	// diffuse shading
//	float diff = max(dot(normal, lightDir), 0.0);
//	// specular shading
//	vec3 reflectDir = reflect(-lightDir, normal);
//	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//	// attenuation
//	float distance = length(light.position - fragPos);
//	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
//	// spotlight intensity
//	float theta = dot(lightDir, normalize(-light.direction));
//	float epsilon = light.cutOff - light.outerCutOff;
//	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
//	// combine results
//	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
//	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
//	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
//	ambient *= attenuation * intensity;
//	diffuse *= attenuation * intensity;
//	specular *= attenuation * intensity;
//	return (ambient + diffuse + specular);
//}
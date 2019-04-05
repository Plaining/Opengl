//#define STB_IMAGE_IMPLEMENTATION
//#define _CRT_SECURE_NO_WARNINGS
//#include <glad/glad.h>
//#include <GLFW\glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "stb_image.h"
//#include "model.h"
//#include "shader_s.h"
//#include "camera.h"
//#include <fstream>
//#include <iostream>
//#include <cstdio>
//#include <cstdlib>
//
//#include <glm/gtx/transform2.hpp>
//const unsigned int SCR_WIDTH = 1280;
//const unsigned int SCR_HEIGHT = 720;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//unsigned int loadTexture(const char *path);
//unsigned int load3DTexture(const char *path, int width, int height, int depth);
//unsigned int load3DTextureByData(char * data, int width, int height, int depth);
//
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//float Image[SCR_WIDTH*SCR_HEIGHT * 4];
//bool firstMouse = true;
//
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//void GenerateVolume(char *Data, int* Dim);//生成体数据
//void GenCube(int x, int y, int z, int side, int density, char *Data, int *Dim);//生成正方体数据
//void GenSphere(int x, int y, int z, int radius, int density, char *Data, int *Dim);//生成球体数据
//void Classify(float* CData, int *Data, int *Dim);//数据分类着色
//
//unsigned int initVol3DTex(const char* filename, int w, int h, int d);
//unsigned int initFace2DTex(int bfTexWidth, int bfTexHeight);
//unsigned int initTFF1DTex(const char* filename);
//
//unsigned int texture3dID;
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
//// glfw window creation
//// --------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "^   V  ^", NULL, NULL);
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
//	glEnable(GL_CULL_FACE);
//
//	Shader shader("shader_s.vs", "shader_s.fs");
//	Shader bkshader("bkshader.vs", "bkshader.fs");
//
//	GLfloat vertices[24] = {
//		0.0, 0.0, 0.0,
//		0.0, 0.0, 1.0,
//		0.0, 1.0, 0.0,
//		0.0, 1.0, 1.0,
//		1.0, 0.0, 0.0,
//		1.0, 0.0, 1.0,
//		1.0, 1.0, 0.0,
//		1.0, 1.0, 1.0
//	};
//	GLuint indices[36] = {
//		1,5,7,
//		7,3,1,
//		0,2,6,
//		6,4,0,
//		0,1,3,
//		3,2,0,
//		7,5,4,
//		4,6,7,
//		2,3,7,
//		7,6,2,
//		1,0,4,
//		4,5,1
//	};
//
//	//int Dim[3] = { 256,256,225};//体数据大小
//	//char *Data = (char *)malloc(sizeof(int)*Dim[0] * Dim[1] * Dim[2]);
//	//GenerateVolume(Data, Dim);
//	//texture3dID = load3DTextureByData(Data, 256, 256,225);
//	texture3dID = initVol3DTex("head256.raw", 256, 256, 225);
//	//load3DTextureByData("head256.raw", 256, 256, 225);
//	unsigned int texture1dID = initTFF1DTex("tff.dat");
//
//	unsigned int cubeVBO;
//	unsigned int CubeVAO;
//	unsigned int CubeEBO;
//	glGenVertexArrays(1, &CubeVAO);
//	glGenBuffers(1, &cubeVBO);
//	glGenBuffers(1, &CubeEBO);
//	//1绑定数据对象
//	glBindVertexArray(CubeVAO);
//	//2把顶点数据复制到顶点缓冲区
//	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeEBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	//4解析顶点数据，激活顶点属性
//	//位置属性
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// normal attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glBindVertexArray(0);
//
//	unsigned int framebuffer;
//	glGenFramebuffers(1, &framebuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//	// create a color attachment texture]
//
//	unsigned int textureColorbuffer;
//	glGenTextures(1, &textureColorbuffer);
//	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
//	glBindTexture(GL_TEXTURE_2D,0);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
//	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
//	unsigned int rbo;
//	glGenRenderbuffers(1, &rbo);
//	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
//																								  // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//
//	// render loop
//	// -----------
//	while (!glfwWindowShouldClose(window))
//	{
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// input
//		// -----
//		processInput(window);
//		glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
//		glEnable(GL_DEPTH_TEST);
//
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//
//		glCullFace(GL_FRONT);
//		
//		bkshader.use();
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 projection = glm::mat4(1.0f);
//		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 model = glm::mat4(1.0f);
//		bkshader.setMat4("projection", projection);
//		bkshader.setMat4("view", view);
//		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
//		bkshader.setMat4("model", model);
//
//		glBindVertexArray(CubeVAO);
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		glDisable(GL_DEPTH_TEST);
//		glClearColor(0.7f, 0.3f, 0.5f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		glCullFace(GL_BACK);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_3D, texture3dID);
//		glActiveTexture(GL_TEXTURE2);
//		glBindTexture(GL_TEXTURE_1D, texture1dID);
//		shader.use();
//		shader.setMat4("projection", projection);
//		shader.setMat4("view", view);
//		shader.setMat4("model", model);
//		
//		shader.setVec2("ScreenSize", glm::vec2(400.0f, 400.0f));
//		shader.setInt("textureColorbuffer", 0);
//		shader.setFloat("StepSize", 0.002f);
//		shader.setInt("texture3dID", 1);
//		shader.setInt("texture1dID", 2);
//
//		glBindVertexArray(CubeVAO);
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glDeleteVertexArrays(1, &CubeVAO);
//	glDeleteBuffers(1, &cubeVBO); 
//	glDeleteFramebuffers(1, &framebuffer);
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
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height, nrComponents;
//	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
//	if (data)
//	{
//		GLenum format;
//		if (nrComponents == 1)
//			format = GL_RED;
//		else if (nrComponents == 3)
//			format = GL_RGB;
//		else if (nrComponents == 4)
//			format = GL_RGBA;
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//
//	return textureID;
//}
//unsigned int load3DTexture(const char * path, int width, int height, int depth)
//{
//
//	FILE *fp;
//	size_t size = width * height * depth;
//	int fwidth, fheight, nrComponents;
//	unsigned char *data = stbi_load(path, &fwidth, &fheight, &nrComponents, 0);
//
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	// bind 3D texture target
//	glBindTexture(GL_TEXTURE_3D, textureID);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
//	// pixel transfer happens here from client to OpenGL server
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, width, height, depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//
//	delete[]data;
//	cout << "volume texture created" << endl;
//	return textureID;
//}
//unsigned int load3DTextureByData(char * data, int width, int height, int depth)
//{
//	unsigned int texture3dID;
//	glGenTextures(1, &texture3dID);
//
//	// bind 3D texture target
//	glBindTexture(GL_TEXTURE_3D, texture3dID);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
//	// pixel transfer happens here from client to OpenGL server
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, width, height, depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//
//	cout << "3D volume texture created" << endl;
//	return texture3dID;
//}
//void GenerateVolume(char * Data, int * Dim)
//{
//	GenCube(0, 0, 0, 200, 100, Data, Dim);//大正方体
//	GenSphere(100, 100, 100, 80, 200, Data, Dim);//球体
//	GenCube(70, 70, 70, 60, 300, Data, Dim);//小正方体
//}
//
//void GenCube(int x, int y, int z, int side, int density, char * Data, int * Dim)
//{
//	int max_x = x + side, max_y = y + side, max_z = z + side;
//	int Dimxy = Dim[0] * Dim[1];
//	for (int k = z; k < max_z; k++)
//	{
//		for (int j = y; j < max_y; j++)
//		{
//			for (int i = x; i < max_x; i++)
//			{
//				Data[k*Dimxy + j*Dim[0] + i] = density;//.raw voxel=k*Dimxy + j*Dim[0] + i
//				//so,Data[voxel]的值在.raw中存储,在这里也就暂时用density定义存的值，全都存为一个值。
//			}
//		}
//	}
//}
//
//void GenSphere(int x, int y, int z, int radius, int density, char * Data, int * Dim)
//{
//	int radius2 = radius*radius;
//	int Dimxy = Dim[0] * Dim[1];
//	for (int k = 0; k < Dim[2]; k++)
//	{
//		for (int j = 0; j < Dim[1]; j++)
//		{
//			for (int i = 0; i < Dim[0]; i++)
//			{
//				if ((i - x)*(i - x) + (j - y)*(j - y) + (k - z)*(k - z) <= radius2)
//				{
//					Data[k*Dimxy + j*Dim[0] + i] = density;//存了一个球形的值
//				}
//			}
//		}
//	}
//}
//
//void Classify(float * CData, int * Data, int * Dim)
//{
//	int *LinePS = Data;
//	float *LinePD = CData;
//	for (int k = 0; k < Dim[2]; k++)
//	{
//		for (int j = 0; j < Dim[1]; j++)
//		{
//			for (int i = 0; i < Dim[0]; i++)
//			{
//				if (LinePS[0] <= 100)//即density的值=100，符合条件，因此这些点的颜色全都设定为（1，1，1，0.005）
//				{
//					//白色
//					LinePD[0] = 1.0;
//					LinePD[1] = 1.0;
//					LinePD[2] = 1.0;
//					LinePD[3] = 0.005;
//				}
//				else if (LinePS[0] <= 200)
//				{
//					//红色
//					LinePD[0] = 1.0;
//					LinePD[1] = 0.0;
//					LinePD[2] = 0.0;
//					LinePD[3] = 0.015;
//				}
//				else
//				{
//					//黄色
//					LinePD[0] = 1.0;
//					LinePD[1] = 1.0;
//					LinePD[2] = 0.0;
//					LinePD[3] = 0.02;
//				}
//				LinePS++;
//				LinePD += 4;
//			}
//		}
//	}
//}
//unsigned initTFF1DTex(const char* filename)
//{
//	//	 read in the user defined data of transfer function
//	ifstream inFile(filename, ifstream::in);
//	if (!inFile)
//	{
//		cerr << "Error openning file: " << filename << endl;
//		exit(EXIT_FAILURE);
//	}
//
//	const int MAX_CNT = 10000;
//	GLubyte *tff = (GLubyte *)calloc(MAX_CNT, sizeof(GLubyte));
//	inFile.read(reinterpret_cast<char *>(tff), MAX_CNT);
//	if (inFile.eof())
//	{
//		size_t bytecnt = inFile.gcount();
//		*(tff + bytecnt) = '\0';
//		cout << "bytecnt " << bytecnt << endl;
//	}
//	else if (inFile.fail())
//	{
//		cout << filename << "read failed " << endl;
//	}
//	else
//	{
//		cout << filename << "is too large" << endl;
//	}
//	unsigned int tff1DTex;
//	glGenTextures(1, &tff1DTex);
//	glBindTexture(GL_TEXTURE_1D, tff1DTex);
//	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA8, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, tff);
//	free(tff);
//	return tff1DTex;
//}
//// init the 2D texture for render backface 'bf' stands for backface
//unsigned int initFace2DTex(int bfTexWidth, int bfTexHeight)
//{
//	unsigned int backFace2DTex;
//	glGenTextures(1, &backFace2DTex);
//	glBindTexture(GL_TEXTURE_2D, backFace2DTex);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, bfTexWidth, bfTexHeight, 0, GL_RGBA, GL_FLOAT, NULL);
//	return backFace2DTex;
//}
//// init 3D texture to store the volume data used fo ray casting
//unsigned int initVol3DTex(const char* filename, int w, int h, int d)
//{
//
//	FILE *fp;
//	size_t size = w * h * d;
//	GLubyte *data = new GLubyte[size];			  // 8bit
//	if (!(fp = fopen(filename, "rb")))
//	{
//		cout << "Error: opening .raw file failed" << endl;
//		exit(EXIT_FAILURE);
//	}
//	else
//	{
//		cout << "OK: open .raw file successed" << endl;
//	}
//	if (fread(data, sizeof(char), size, fp) != size)
//	{
//		cout << "Error: read .raw file failed" << endl;
//		exit(1);
//	}
//	else
//	{
//		cout << "OK: read .raw file successed" << endl;
//	}
//	fclose(fp);
//
//	glGenTextures(1, &texture3dID);
//
//	// bind 3D texture target
//	glBindTexture(GL_TEXTURE_3D, texture3dID);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
//	// pixel transfer happens here from client to OpenGL server
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, w, h, d, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//	delete[]data;
//	cout << "volume texture created" << endl;
//	return texture3dID;
//}

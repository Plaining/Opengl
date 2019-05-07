////生成图像过小
//#define _CRT_SECURE_NO_WARNINGS
//#define GLEW_STATIC
//
//#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glext.h>
//
//#include <fstream>
//#include <iostream>
//#include <cstdio>
//#include <cstdlib>
//#include <glut.h>
//#include <glm/gtx/transform2.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include "camera.h"
//
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//
//#define GL_ERROR() checkForOpenGLError(__FILE__, __LINE__)
//using namespace std;
//using glm::mat4;
//using glm::vec3;
//GLuint g_vao;
//GLuint g_programHandle;
//GLuint g_winWidth = 800;
//GLuint g_winHeight = 800;
//GLint g_angle = 0;
//GLuint g_frameBuffer;
//// transfer function
//GLuint g_tffTexObj;
//GLuint g_bfTexObj;
//GLuint g_texWidth;
//GLuint g_texHeight;
//GLuint g_volTexObj;
//GLuint g_rcVertHandle;
//GLuint g_rcFragHandle;
//GLuint g_bfVertHandle;
//GLuint g_bfFragHandle;
//float g_stepSize = 0.001f;
//
//int checkForOpenGLError(const char* file, int line)
//{
//	//return 1 if an OpenGL error occured, 0 otherwise.
//	GLenum glErr;
//	int retCode = 0;
//
//	glErr = glGetError();
//	while (glErr != GL_NO_ERROR)
//	{
//		cout << "glError in file " << file
//			<< "@line " << line << gluErrorString(glErr) << endl;
//		retCode = 1;
//		exit(EXIT_FAILURE);
//	}
//	return retCode;
//}
//void keyboard(unsigned char key, int x, int y);
//void display(void);
//void initVBO();
//void initShader();
//void initFrameBuffer(GLuint, GLuint, GLuint);
//GLuint initTFF1DTex(const char* filename, GLuint width, GLuint height, GLuint depth);//读取dat文件
//GLuint initFace2DTex(GLuint texWidth, GLuint texHeight);
//GLuint initVol3DTex(const char* filename, GLuint width, GLuint height, GLuint depth);//读取raw文件
//void render(GLenum cullFace);
//void init()
//{
//	g_texWidth = g_winWidth;
//	g_texHeight = g_winHeight;
//	initVBO();
//	initShader();//初始化
//	g_tffTexObj = initTFF1DTex("tff.dat", 256, 256, 225);
//	g_bfTexObj = initFace2DTex(g_texWidth, g_texHeight);
//	g_volTexObj = initVol3DTex("head256.raw", 256, 256, 225);
//	//g_volTexObj = initVol3DTex("baby_face.raw", 152, 368, 94);
//	//g_volTexObj = initVol3DTex("head-128x128x113.den", 128, 128, 113);
//	//g_volTexObj = initVol3DTex("FOOT.RAW", 256, 256, 225);
//	GL_ERROR();
//	initFrameBuffer(g_bfTexObj, g_texWidth, g_texHeight);//初始化帧缓冲
//	GL_ERROR();
//}
//// init the vertex buffer object
//void initVBO()
//{
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
//	GLuint gbo[2];
//	glGenBuffers(2, gbo);
//	GLuint vertexdat = gbo[0];
//	GLuint veridxdat = gbo[1];
//	glBindBuffer(GL_ARRAY_BUFFER, vertexdat);
//	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veridxdat);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), indices, GL_STATIC_DRAW);
//
//	GLuint vao;
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//	glEnableVertexAttribArray(0); // for vertexloc
//	glEnableVertexAttribArray(1); // for vertexcol
//
//	glBindBuffer(GL_ARRAY_BUFFER, vertexdat);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLfloat *)NULL);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLfloat *)NULL);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veridxdat);
//	glBindVertexArray(0);
//	g_vao = vao;
//}
//void drawBox(GLenum glFaces)
//{
//	glEnable(GL_CULL_FACE);
//	glCullFace(glFaces);
//	glBindVertexArray(g_vao);
//	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)NULL);
//	glDisable(GL_CULL_FACE);
//}
//// check the compilation result
//GLboolean compileCheck(GLuint shader)
//{
//	GLint err;
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &err);
//	if (GL_FALSE == err)
//	{
//		GLint logLen;
//		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
//		if (logLen > 0)
//		{
//			char* log = (char *)malloc(logLen);
//			GLsizei written;
//			glGetShaderInfoLog(shader, logLen, &written, log);
//			cerr << "Shader log: " << log << endl;
//			free(log);
//		}
//	}
//	return err;
//}
//// init shader object
//GLuint initShaderObj(const GLchar* srcfile, GLenum shaderType)
//{
//	ifstream inFile(srcfile, ifstream::in);
//	//use assert?
//	if (!inFile)
//	{
//		cerr << "Error openning file: " << srcfile << endl;
//		exit(EXIT_FAILURE);
//	}
//
//	const int MAX_CNT = 10000;
//	GLchar *shaderCode = (GLchar *)calloc(MAX_CNT, sizeof(GLchar));
//	inFile.read(shaderCode, MAX_CNT);
//	if (inFile.eof())
//	{
//		size_t bytecnt = inFile.gcount();
//		*(shaderCode + bytecnt) = '\0';
//	}
//	else if (inFile.fail())
//	{
//		cout << srcfile << "read failed " << endl;
//	}
//	else
//	{
//		cout << srcfile << "is too large" << endl;
//	}
//	//	 create the shader Object
//	GLuint shader = glCreateShader(shaderType);
//	if (0 == shader)
//	{
//		cerr << "Error creating vertex shader." << endl;
//	}
//	//cout << shaderCode << endl;
//	//cout << endl;
//	const GLchar* codeArray[] = { shaderCode };
//	glShaderSource(shader, 1, codeArray, NULL);
//	free(shaderCode);
//
//	//	 compile the shader
//	glCompileShader(shader);
//	if (GL_FALSE == compileCheck(shader))
//	{
//		cerr << "shader compilation failed" << endl;
//	}
//	return shader;
//}
//GLint checkShaderLinkStatus(GLuint pgmHandle)
//{
//	GLint status;
//	glGetProgramiv(pgmHandle, GL_LINK_STATUS, &status);
//	if (GL_FALSE == status)
//	{
//		GLint logLen;
//		glGetProgramiv(pgmHandle, GL_INFO_LOG_LENGTH, &logLen);
//		if (logLen > 0)
//		{
//			GLchar * log = (GLchar *)malloc(logLen);
//			GLsizei written;
//			glGetProgramInfoLog(pgmHandle, logLen, &written, log);
//			cerr << "Program log: " << log << endl;
//		}
//	}
//	return status;
//}
//// link shader program
//GLuint createShaderPgm()
//{
//	GLuint programHandle = glCreateProgram();
//	if (0 == programHandle)
//	{
//		cerr << "Error create shader program" << endl;
//		exit(EXIT_FAILURE);
//	}
//	return programHandle;
//}
//
//GLuint initTFF1DTex(const char* filename, GLuint w, GLuint h, GLuint d)
//{
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
//	size_t bytecnt = 0;
//	if (inFile.eof())
//	{
//		bytecnt = inFile.gcount();
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
//
//	GLuint tff1DTex;
//	glGenTextures(1, &tff1DTex);
//	glBindTexture(GL_TEXTURE_1D, tff1DTex);
//	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA8, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, tff);
//
//	//free(tff);
//	return tff1DTex;
//}
//GLuint initFace2DTex(GLuint bfTexWidth, GLuint bfTexHeight)
//{
//	GLuint backFace2DTex;
//	glGenTextures(1, &backFace2DTex);
//	glBindTexture(GL_TEXTURE_2D, backFace2DTex);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bfTexWidth, bfTexHeight, 0, GL_RGBA, GL_FLOAT, NULL);
//	return backFace2DTex;
//}
//GLuint initVol3DTex(const char* filename, GLuint w, GLuint h, GLuint d)
//{
//
//	FILE *fp;
//	unsigned int size = w * h * d;
//	unsigned char *data = new unsigned char[size];			  // 8bit
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
//	glGenTextures(1, &g_volTexObj);
//	glBindTexture(GL_TEXTURE_3D, g_volTexObj);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	unsigned char* test = new unsigned char[size * 4];
//	
//	for (int k = 0; k < d; k++) {
//		for (int j = 0; j < h; j++) {
//			for (int i = 0; i < w; i++) {
//				unsigned char ndata = (int)data[k * 256 * 256 + j * 256 + i];
//				if (k == 0||k==d-1||j==0||j==h-1||i==0||i==w-1) {
//					test[(k * 256 * 256 + j * 256 + i) * 4] = ndata;
//					test[(k * 256 * 256 + j * 256 + i) * 4 + 1] = ndata;
//					test[(k * 256 * 256 + j * 256 + i) * 4 + 2] = ndata;
//					test[(k * 256 * 256 + j * 256 + i) * 4 + 3] = ndata;
//				}
//				else {
//					unsigned char nx = (data[k * 256 * 256 + j * 256 + i + 1] - data[k * 256 * 256 + j * 256 + i - 1]) / 2;
//					unsigned char ny = (data[k * 256 * 256 + (j + 1) * 256 + i] - data[k * 256 * 256 + (j - 1) * 256 + i]) / 2;
//					unsigned char nz = (data[(k + 1) * 256 * 256 + j * 256 + i] - data[(k - 1) * 256 * 256 + j * 256 + i]) / 2;
//					test[(k * 256 * 256 + j * 256 + i) * 4] = nx;
//					test[(k * 256 * 256 + j * 256 + i) * 4 + 1] = ny;
//					test[(k * 256 * 256 + j * 256 + i) * 4 + 2] = nz;
//					test[(k * 256 * 256 + j * 256 + i) * 4 + 3] = ndata;
//				}
//			}
//		}
//	}
//	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, w, h, d, 0, GL_RGBA, GL_UNSIGNED_BYTE, test);
//	
//	delete[]test;
//	delete[]data;
//	cout << "volume texture created" << endl;
//	return g_volTexObj;
//}
//
//void checkFramebufferStatus()
//{
//	GLenum complete = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//	if (complete != GL_FRAMEBUFFER_COMPLETE)
//	{
//		cout << "framebuffer is not complete" << endl;
//		exit(EXIT_FAILURE);
//	}
//}
//void initFrameBuffer(GLuint texObj, GLuint texWidth, GLuint texHeight)
//{
//	GLuint depthBuffer;
//	glGenRenderbuffers(1, &depthBuffer);
//	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, texWidth, texHeight);
//
//	glGenFramebuffers(1, &g_frameBuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, g_frameBuffer);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texObj, 0);
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
//	checkFramebufferStatus();
//	glEnable(GL_DEPTH_TEST);
//}
//
//void rcSetUinforms()
//{
//	GLint screenSizeLoc = glGetUniformLocation(g_programHandle, "ScreenSize");
//	if (screenSizeLoc >= 0)
//	{
//		glUniform2f(screenSizeLoc, (float)g_winWidth, (float)g_winHeight);
//	}
//	else
//	{
//		/*cout << "ScreenSize"
//			<< "is not bind to the uniform"
//			<< endl;*/
//	}
//	GLint stepSizeLoc = glGetUniformLocation(g_programHandle, "StepSize");
//	GL_ERROR();
//	if (stepSizeLoc >= 0)
//	{
//		glUniform1f(stepSizeLoc, g_stepSize);
//	}
//	else
//	{
//		cout << "StepSize"
//			<< "is not bind to the uniform"
//			<< endl;
//	}
//	GL_ERROR();
//	GLint transferFuncLoc = glGetUniformLocation(g_programHandle, "TransferFunc");
//	if (transferFuncLoc >= 0)
//	{
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_1D, g_tffTexObj);
//		glUniform1i(transferFuncLoc, 0);
//	}
//	else
//	{
//		/*cout << "TransferFunc"
//			<< "is not bind to the uniform"
//			<< endl;*/
//	}
//	GL_ERROR();
//	GLint backFaceLoc = glGetUniformLocation(g_programHandle, "ExitPoints");
//	if (backFaceLoc >= 0)
//	{
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, g_bfTexObj);
//		glUniform1i(backFaceLoc, 1);
//	}
//	else
//	{
//		cout << "ExitPoints"
//			<< "is not bind to the uniform"
//			<< endl;
//	}
//	GL_ERROR();
//	GLint volumeLoc = glGetUniformLocation(g_programHandle, "VolumeTex");
//	if (volumeLoc >= 0)
//	{
//		glActiveTexture(GL_TEXTURE2);
//		glBindTexture(GL_TEXTURE_3D, g_volTexObj);
//		glUniform1i(volumeLoc, 2);
//	}
//	else
//	{
//		cout << "VolumeTex"
//			<< "is not bind to the uniform"
//			<< endl;
//	}
//
//}
//// init the shader object and shader program
//void initShader()
//{
//	//vertex shader object for first pass
//	g_bfVertHandle = initShaderObj("shader/backface.vert", GL_VERTEX_SHADER);
//	//fragment shader object for first pass
//	g_bfFragHandle = initShaderObj("shader/backface.frag", GL_FRAGMENT_SHADER);
//	//vertex shader object for second pass
//	g_rcVertHandle = initShaderObj("shader/raycasting.vert", GL_VERTEX_SHADER);
//	//fragment shader object for second pass
//	g_rcFragHandle = initShaderObj("shader/raycasting.frag", GL_FRAGMENT_SHADER);
//	//create the shader program , use it in an appropriate time
//	g_programHandle = createShaderPgm();
//}
//
//// link the shader objects using the shader program
//void linkShader(GLuint shaderPgm, GLuint newVertHandle, GLuint newFragHandle)
//{
//	const GLsizei maxCount = 2;
//	GLsizei count;
//	GLuint shaders[maxCount];
//	glGetAttachedShaders(shaderPgm, maxCount, &count, shaders);
//	// cout << "get VertHandle: " << shaders[0] << endl;
//	// cout << "get FragHandle: " << shaders[1] << endl;
//	GL_ERROR();
//	for (int i = 0; i < count; i++) {
//		glDetachShader(shaderPgm, shaders[i]);
//	}
//	// Bind index 0 to the shader input variable "VerPos"
//	glBindAttribLocation(shaderPgm, 0, "VerPos");
//	// Bind index 1 to the shader input variable "VerClr"
//	glBindAttribLocation(shaderPgm, 1, "VerClr");
//	GL_ERROR();
//	glAttachShader(shaderPgm, newVertHandle);
//	glAttachShader(shaderPgm, newFragHandle);
//	GL_ERROR();
//	glLinkProgram(shaderPgm);
//	if (GL_FALSE == checkShaderLinkStatus(shaderPgm))
//	{
//		cerr << "Failed to relink shader program!" << endl;
//		exit(EXIT_FAILURE);
//	}
//	GL_ERROR();
//}
//
//void display()
//{
//	//统计时间
//	int gStart = 0;
//	int gEnd = 0;
//	gStart = glutGet(GLUT_ELAPSED_TIME);
//	glEnable(GL_DEPTH_TEST);
//	// test the gl_error
//	GL_ERROR();
//	// render to texture
//	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g_frameBuffer);
//	glViewport(0, 0, g_winWidth, g_winHeight);
//	linkShader(g_programHandle, g_bfVertHandle, g_bfFragHandle);
//	glUseProgram(g_programHandle);
//	// cull front face
//	render(GL_FRONT);
//	glUseProgram(0);
//	GL_ERROR();
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	glViewport(0, 0, g_winWidth, g_winHeight);
//	linkShader(g_programHandle, g_rcVertHandle, g_rcFragHandle);
//	GL_ERROR();
//	glUseProgram(g_programHandle);
//	rcSetUinforms();
//	GL_ERROR();
//	render(GL_BACK);
//	glUseProgram(0);
//	GL_ERROR();
//	glutSwapBuffers();
//	gEnd = glutGet(GLUT_ELAPSED_TIME);
//	int time = gEnd - gStart;
//
//	cout << "time" << time << endl;
//}
//void render(GLenum cullFace)
//{
//	GL_ERROR();
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	//  transform the box
//	glm::mat4 view = camera.GetViewMatrix();
//	//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)g_winWidth / g_winHeight, 0.1f, 400.0f);
//	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)g_winWidth / g_winHeight, 0.1f, 100.0f);
//	glm::mat4 model = glm::mat4(1.0f);
//	//model *= glm::rotate((float)g_angle/50, glm::vec3(0.0f, 1.0f, 0.0f));
//	model *= glm::rotate(80.0f, vec3(1.0f, 0.0f, 0.0f));
//	model *= glm::translate(glm::vec3(-0.5f, -0.5f, -0.5f));
//	glm::mat4 mvp = projection * view * model;
//	GLuint mvpIdx = glGetUniformLocation(g_programHandle, "MVP");
//	if (mvpIdx >= 0)
//	{
//		glUniformMatrix4fv(mvpIdx, 1, GL_FALSE, &mvp[0][0]);
//	}
//	else
//	{
//		cerr << "can't get the MVP" << endl;
//	}
//	GL_ERROR();
//	drawBox(cullFace);
//	GL_ERROR();
//	//glutWireTeapot(0.5);
//}
//void rotateDisplay()
//{
//	g_angle = (g_angle + 1) % 360;
//	glutPostRedisplay();
//}
//void reshape(int w, int h)
//{
//	g_winWidth = w;
//	g_winHeight = h;
//	g_texWidth = w;
//	g_texHeight = h;
//}
//
//void keyboard(unsigned char key, int x, int y)
//{
//	switch (key)
//	{
//	case '\x1B':
//		exit(EXIT_SUCCESS);
//		break;
//	}
//}
//
//void SpecialKey(GLint key, GLint x, GLint y)
//{
//	if (key == GLUT_KEY_UP)
//	{
//		camera.ProcessKeyboard(FORWARD, 0.001);
//	}
//	if (key == GLUT_KEY_LEFT)
//	{
//		camera.ProcessKeyboard(LEFT, 0.001);
//	}
//	if (key == GLUT_KEY_DOWN)
//	{
//		camera.ProcessKeyboard(BACKWARD, 0.001);
//	}
//	if (key == GLUT_KEY_RIGHT)
//	{
//		camera.ProcessKeyboard(RIGHT, 0.001);
//	}
//	display();
//}
//int main(int argc, char** argv)
//{
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//	glutInitWindowSize(800, 800);
//	glutCreateWindow("GLUT Test");
//	GLenum err = glewInit();
//	if (GLEW_OK != err)
//	{
//		/* Problem: glewInit failed, something is seriously wrong. */
//		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
//	}
//
//	glutKeyboardFunc(&keyboard);
//	glutSpecialFunc(&SpecialKey);
//
//	glutDisplayFunc(&display);
//	glutReshapeFunc(&reshape);
//	glutIdleFunc(&rotateDisplay);
//	init();
//	glutMainLoop();
//	return EXIT_SUCCESS;
//}

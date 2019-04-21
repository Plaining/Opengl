//#define _CRT_SECURE_NO_WARNINGS
//#include "stdio.h"
//#include "math.h"
//#include "windows.h"
//
//#include "gl/glut.h"
//
//#define DIAMETER 5  //定义重构核大小
//#define VOLUME_X  256
//#define VOLUME_Y  256
//#define VOLUME_Z  225//256
//#define SCALE_X 1
//#define SCALE_Y 1
//#define SCALE_Z 1
//
//
//void vDrawScene();
//void vResize(GLsizei, GLsizei);
//void vPrintHelp();
//void myinit();
//void readdata();
//void make_buffer_zero();
//void footprint(int diameter);
//void draw_qq(float r, float g, float b);
//
//
//unsigned char data[VOLUME_Z][VOLUME_X][VOLUME_Y];//
//float table[DIAMETER][DIAMETER];//
//
//struct Normal
//{
//	float x;
//	float y;
//	float z;
//};
//struct Buffer
//{
//	float value;
//	struct Normal normal;
//
//} buffer[512][512];
//
//void main(int argc, char **argv)
//{
//
//	GLsizei iWidth = 520.0;
//	GLsizei iHeight = 520.0;
//
//	glutInit(&argc, argv);//GLUT环境初始化
//	glutInitWindowPosition(0, 0);//定义窗口位置
//	glutInitWindowSize(iWidth, iHeight);//定义窗口大小
//	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);//显示模式初始化 
//	glutCreateWindow("Splatting");//显示窗口，窗口标题为splatting
//	glutDisplayFunc(vDrawScene);//注册OpenGL绘图函数
//
//	glutReshapeFunc(vResize);//注册窗口大小改变时的响应函数
//
//	vResize(iWidth, iHeight);// 
//	vPrintHelp();
//	glutMainLoop(); //进入GLUT消息循环，开始执行程序
//}
//
//GLvoid vPrintHelp()
//{
//	printf("Splatting algorithm implemented by Tian Dekun\n\n");
//
//
//}
//void vResize(GLsizei iWidth, GLsizei iHeight)
//{
//	glMatrixMode(GL_PROJECTION);//将当前矩阵转换为指定的矩阵类型
//	glLoadIdentity();//replace the current matrix with the specified matrix
//	glOrtho(0, 520, 0, 520, -520, 0);//正射投影
//
//	glMatrixMode(GL_MODELVIEW);//把变换结果返回视点坐标系 
//	glViewport(0, 0, iWidth, iHeight);//定义视口
//
//}
//
//void vDrawScene()
//{
//	int i, j, k, x, y;
//	float r, g, b, a, density, density_table;
//	double starttime, endtime;
//
//	footprint(DIAMETER);//
//	myinit();//清窗口
//	glEnable(GL_BLEND);//enable or disable server-side GL capabilities
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//specify pixel arithmetic
//	glShadeModel(GL_FLAT);//select flat or smooth shading 
//	readdata();//读数据
//	glPointSize(1);//specify the diameter of rasterized points
//
//	starttime = GetTickCount();
//
//	for (i = VOLUME_X; i>0; i--)
//	{
//		make_buffer_zero();//
//		for (j = 2; j<VOLUME_Z - 2; j++)
//			for (k = 2; k<VOLUME_Y - 2; k++)
//			{
//				density = (float)data[j][k][i];
//
//				for (x = 0; x<DIAMETER; x++)
//					for (y = 0; y<DIAMETER; y++)
//					{
//						density_table = density*table[x][y];
//						buffer[j * 2 - (DIAMETER - 1) / 2 + y][k * 2 - (DIAMETER - 1) / 2 + x].value += density_table;
//					}
//
//
//				// buffer[j*2][k*2].value=density;
//			}
//
//
//		for (x = 0; x<512; x++)
//			for (y = 0; y<512; y++)
//			{
//				if (buffer[x][y].value>300) draw_qq(0.3, 0.9, 0.4);
//				if (buffer[x][y].value>170)
//				{
//					r = (float)(buffer[x][y].value + 50) / 255;
//					g = (float)(buffer[x][y].value + 50) / 255;
//					b = (float)(buffer[x][y].value + 50) / 255;
//					//g=buffer[x][y].value/255;
//					//0 //b=buffer[x][y].value/255;
//					a = 0.99;
//				}
//
//				if (buffer[x][y].value>50 && buffer[x][y].value<170)
//				{
//					r = (float)(buffer[x][y].value + 30) / 255;
//					g = (float)20 / 255;
//					b = (float)20 / 255;
//					a = 0.1;
//				}
//				if (buffer[x][y].value<50)
//				{
//					r = 0;
//					g = 0;
//					b = 0;
//					a = 0;
//				}
//
//				glColor4f(r, g, b, a);
//				glBegin(GL_POINTS);
//				glVertex2f((float)(512 - x), (float)(512 - y));
//				glEnd();
//			}
//		glutSwapBuffers();
//	}
//	//glutSwapBuffers(); 
//	endtime = GetTickCount();
//	printf("%f seconds", (endtime - starttime) / 1000);
//}
//
//
//void make_buffer_zero(void)
//{
//	int x, y;
//	for (x = 0; x<512; x++)
//		for (y = 0; y<512; y++)
//			buffer[x][y].value = 0;
//}
//
//void myinit(void)
//{
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//}
//
//void readdata(void)
//{
//	FILE *fp;
//	//fp = fopen("FOOT.RAW", "rb");
//	fp = fopen("head256.raw","rb");
//	//fseek(fp,0,0);
//	fread(data, VOLUME_Z*VOLUME_X*VOLUME_Y, 1, fp);
//	fclose(fp);
//}
//void draw_qq(float r, float g, float b)
//{
//	glColor4f(r, g, b, 1);
//	glRectf(400, 400, 500, 500);
//}
//
//void footprint(int diameter)
//{
//	float m;
//	int i, j, k, radius;
//	float x, y, z;
//	radius = (diameter - 1) / 2;
//
//	for (i = 0; i<diameter; i++)
//		for (j = 0; j<diameter; j++)
//			table[i][j] = 0;
//
//	for (i = 0; i<diameter; i++)
//		for (j = 0; j<diameter; j++)
//			for (k = 0; k<diameter; k++)
//			{
//
//				x = (float)(i - radius) / radius;
//				y = (float)(j - radius) / radius;
//				z = (float)(k - radius) / radius;
//				if (x*x + y*y + z*z <= 1)
//				{
//					m = 1 - sqrt(x*x + y*y + z*z);
//					table[i][j] += (float)m * 1 / radius;
//				}
//			}
//
//}

//
//#define _CRT_SECURE_NO_WARNINGS
//#include <fstream>
//#include <iostream>
//#include <cstdio>
//#include <cstdlib>
//#include<stdio.h>
//#include<stdlib.h>
//#include<math.h>
//using namespace std;
//
//void main() {
//	FILE *fp;
//	unsigned int size = 256 * 256 * 225;
//	unsigned char *data = new unsigned char[size];			  // 8bit
//	if (!(fp = fopen("head256.raw", "rb")))
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
//	int d = 225;
//	int w = 256;
//	int h = 256;
//	unsigned char* test = new unsigned char[size * 4];
//	for (int k = 0; k < d; k++) {
//		for (int j = 0; j < h; j++) {
//			for (int i = 0; i < w; i++) {
//				unsigned char ndata = data[k * 256 * 256 + j * 256 + i];
//				if (k == 0 || k == d - 1 || j == 0 || j == h - 1 || i == 0 || i == w - 1) {
//					test[(k * 256 * 256 + j * 256 + i) * 4] = ndata;
//					test[(k * 256 * 256 + j * 256 + i) * 4 + 1] = ndata;
//					test[(k * 256 * 256 + j * 256 + i) * 4 + 2] = ndata;
//					test[(k * 256 * 256 + j * 256 + i) * 4 + 3] = ndata;
//				}
//				else {
//					unsigned char nx = ((int)data[k * 256 * 256 + j * 256 + i + 1] - (int)data[k * 256 * 256 + j * 256 + i - 1]) / 2;
//					unsigned char ny = ((int)data[k * 256 * 256 + (j + 1) * 256 + i] - (int)data[k * 256 * 256 + (j - 1) * 256 + i]) / 2;
//					unsigned char nz = ((int)data[(k + 1) * 256 * 256 + j * 256 + i] - (int)data[(k - 1) * 256 * 256 + j * 256 + i]) / 2;
//					test[(k * 256 * 256 + j * 256 + i) * 4] = nx;
//					test[(k * 256 * 256 + j * 256 + i) * 4 + 1] = ny;
//					test[(k * 256 * 256 + j * 256 + i) * 4 + 2] = nz;
//					test[(k * 256 * 256 + j * 256 + i) * 4 + 3] = ndata;
//				}
//			}
//		}
//	}
//	for (int i = 57000; i < 57100; i++) {
//		cout << "data[" << i << "]::" << (int)data[i]<<"[0]::"<<(int)test[i*4]<<"[1]::"<<(int)test[i*4+1]<<"[2]::"<<(int)test[i*4+2]<<"[3]::"<<(int)test[i*4+3]<<endl;
//
//	}
//
//	system("pause");
//	delete[]data;
//}

#include "binaryTest.h"


int  BinaryTest()
{
	int retVal = 0;

	double area;
	double minarea = 100;
	double maxarea = 0;
	Moments mom; // 轮廓矩  
	Mat image, gray, edge, binaryPic, dst;

	namedWindow("originWnd");
	namedWindow("grayWnd");
	namedWindow("blurWnd");
	namedWindow("binaryWnd");

	image = imread("D:\\VSCodeDir\\openCVtest\\x64\\Debug\\11_d.jpg");
	cvtColor(image, gray, COLOR_BGR2GRAY);
	blur(gray, edge, Size(3, 3));   //模糊去噪  
	threshold(edge, binaryPic, 150, 255, THRESH_BINARY);   //二值化处理

	imshow("originWnd", image);
	imshow("grayWnd", gray);
	imshow("blurWnd", edge);
	imshow("binaryWnd", binaryPic);
	waitKey(0);
	float a[20];
	int b[3];
	//printf("%d,%d,%d\n", sizeof(a[0]), sizeof(b[3]), t);
	getchar();
	return(retVal);
}
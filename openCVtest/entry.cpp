#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <stdio.h>  

//#include "binaryTest.h"
//#include "contourTest.h"
//#include "trackBarTest.h"
#include "eolExample.h"

using namespace cv;
using namespace std;

vector<vector<Point> > contours;   //轮廓数组  
vector<Point2d>  centers;    //轮廓质心坐标   
vector<vector<Point> >::iterator itr;  //轮廓迭代器  
vector<Point2d>::iterator  itrc;    //质心坐标迭代器  
vector<vector<Point> > con;    //当前轮廓 

double c[20];

int t = sizeof(c[0]);

int main()
{
	int retVal = 0;
	//retVal=BinaryTest();
	//retVal = contourTest();
	//retVal = trackBarTest();
	retVal = eolExample();
}
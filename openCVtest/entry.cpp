#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <stdio.h>  

//#include "binaryTest.h"
//#include "contourTest.h"
//#include "trackBarTest.h"
#include "eolExample.h"

using namespace cv;
using namespace std;

vector<vector<Point> > contours;   //��������  
vector<Point2d>  centers;    //������������   
vector<vector<Point> >::iterator itr;  //����������  
vector<Point2d>::iterator  itrc;    //�������������  
vector<vector<Point> > con;    //��ǰ���� 

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
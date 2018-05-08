#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;


int contourTest()
{
	int retVal = 0;
	//todo add the src img path
	Mat srcImg = imread("D:\\VSCodeDir\\openCVtest\\x64\\Debug\\11_d.jpg");
	Mat procImg = srcImg.clone();
	Mat backGroundImg(procImg.rows,procImg.cols,CV_8UC3,Scalar::all(0));

	cvtColor(procImg, procImg,CV_BGR2GRAY);

	threshold(procImg, procImg,100,255,CV_THRESH_BINARY);


	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;

	// note proImg is changed.
	findContours(procImg,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);

	drawContours(backGroundImg,contours,-1,Scalar(255,0,128),2,8);

	//get the rect
	vector<Rect> rectArray(contours.size());
	for (int i=0;i<contours.size();i++)
	{
		rectArray[i] = boundingRect(contours[i]);
		rectangle(srcImg,rectArray[i],Scalar(0,255,0),1,8);
		rectangle(procImg,rectArray[i],Scalar(255,0,255),1,8);
	}

	

	imshow("srcImg", srcImg);
	imshow("contours", backGroundImg);
	imshow("procImg", procImg);
	waitKey(0);
	return(retVal);
}
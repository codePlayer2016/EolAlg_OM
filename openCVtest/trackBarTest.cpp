#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;


int colorVal=255;
int binaryMinVal=100;
//todo add the src img path
Mat srcImg ;
Mat procImg;
Mat binaryImg;
Mat backGroundImg;


void onChange(int argc,void *argv)
{

	threshold(procImg, binaryImg, binaryMinVal, 255, CV_THRESH_BINARY);

#if 0
	// note proImg is changed.
	findContours(procImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	drawContours(backGroundImg, contours, -1, Scalar(255, 0, 128), 2, 8);

	//get the rect
	vector<Rect> rectArray(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		rectArray[i] = boundingRect(contours[i]);
		rectangle(srcImg, rectArray[i], Scalar(0, colorVal, 0), 1, 8);
		rectangle(procImg, rectArray[i], Scalar(colorVal, 0, 255), 1, 8);
	}


	imshow("controlWnd", srcImg);

	imshow("srcImg", srcImg);
	imshow("contours", backGroundImg);
	imshow("procImg", procImg);
#endif
	imshow("controlWnd", binaryImg);

}

int trackBarTest()
{
	int retVal = 0;

	//todo add the src img path
	 srcImg = imread("D:\\VSCodeDir\\openCVtest\\x64\\Debug\\11_d.jpg");
	procImg = srcImg.clone();
	Mat _binaryImg(procImg.rows,procImg.cols,CV_8UC3);
	binaryImg = _binaryImg.clone();


	cvtColor(procImg, procImg, CV_BGR2GRAY);

	namedWindow("controlWnd", CV_WINDOW_AUTOSIZE);
	createTrackbar("binaryMinVal", "controlWnd", &binaryMinVal, 255, onChange, 0);
	//createTrackbar("binaryMinVal", "controlWnd", &binaryMinVal, 100, onChange, 0);

	waitKey(0);
	return(retVal);
}

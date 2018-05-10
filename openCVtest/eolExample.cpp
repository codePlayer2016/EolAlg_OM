
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"

void test(IplImage *pSrc)
{
	 IplImage *pDst = pSrc;
}

int eolExample()
{
	int retVal = 0;
	unsigned char *yuvData = (unsigned char *)malloc(704 * 480);
	FILE *fp = fopen("d:/binaryY.yuv","rb");
	
	if (NULL==fp)
	{
		printf("fopen failed\n");
		return -1;
	}
	fread(yuvData,1,704*480,fp);
	IplImage* pFrImg = cvCreateImage(cvSize(704,480),IPL_DEPTH_8U,1);
	cvSetData(pFrImg, yuvData, 704);
	//unsigned char *pFrImg = (unsigned char *)pSrcImg;
	//IplImage *pFrImg = cvLoadImage("D:\\VSCodeDir\\openCVtest\\x64\\Debug\\test.jpg", CV_LOAD_IMAGE_UNCHANGED);
//	IplImage *pFrImg = cvLoadImage("D:\\VSCodeDir\\openCVtest\\x64\\Debug\\11_d.jpg", CV_LOAD_IMAGE_UNCHANGED);
	cvNamedWindow("srcImg");
	cvShowImage("srcImg", pFrImg);

	IplImage *pFrame = cvCreateImage(cvSize(pFrImg->width, pFrImg->height), 8, 1);
	IplImage *pGrayImg = cvCreateImage(cvSize(pFrImg->width, pFrImg->height), IPL_DEPTH_8U, 1);
	IplImage *pBinImg = cvCreateImage(cvSize(pFrImg->width, pFrImg->height), IPL_DEPTH_8U, 1);
	IplImage *temp_img = cvCreateImage(cvSize(pFrImg->width, pFrImg->height), IPL_DEPTH_8U, 1);
	IplImage *temp_img_b = cvCreateImage(cvSize(pFrImg->width, pFrImg->height), IPL_DEPTH_8U, 3);
	IplImage *temp_img_c = cvCreateImage(cvSize(pFrImg->width, pFrImg->height), IPL_DEPTH_8U, 3);

	//cvCvtColor(pFrImg, pGrayImg, CV_BGR2GRAY);


	//cvThreshold(pGrayImg, pBinImg, 100, 255, CV_THRESH_BINARY);
	cvCopy(pFrImg,pBinImg);
	cvNamedWindow("grayImg");
	cvShowImage("grayImg", pBinImg);

	cvNamedWindow("contours");

	CvSeq *contour;
	CvMemStorage *storage = cvCreateMemStorage();
	cvClearMemStorage(storage);



	CvContourScanner scanner = cvStartFindContours(pBinImg, storage, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, cvPoint(0, 0));
	int aera;
	while (contour = cvFindNextContour(scanner))
	{

		//CvRect rect = ((CvContour *)(contour))->rect;
		CvSeq *dst_contour = 0;
		//比较面积大小
		//aera = fabs(cvContourArea(contour));
		CvRect  rect = ((CvContour *)(contour))->rect;
		//if ((2000<aera&&aera<2600 )&&(CV_IS_SEQ_HOLE(contour)))
		if (CV_IS_SEQ_HOLE(contour) && rect.width*rect.height >= 51)
		{
#if 0
			CvRect rect = cvBoundingRect(contour, 0);
			if (0.9 < rect.width*1.0 / rect.height < 1.01)
			{
				cvRectangle(pFrame, cvPoint(rect.x + rect.width, rect.y), cvPoint(rect.x, rect.y + rect.height), CV_RGB(255, 0, 0), 4, 8, 0);

			}
#endif
			int min_approx_level = 2, max_approx_level;

			max_approx_level = 7;


			int approx_level;
			for (approx_level = min_approx_level; approx_level <= max_approx_level; approx_level++)
			{
				dst_contour = cvApproxPoly(contour, sizeof(CvContour), storage,
					CV_POLY_APPROX_DP, (float)approx_level);
				// We call this again on its own output, because sometimes
				// cvApproxPoly() does not simplify as much as it should.
				dst_contour = cvApproxPoly(dst_contour, sizeof(CvContour), storage,
					CV_POLY_APPROX_DP, (float)approx_level);

				if (dst_contour->total == 4)
					break;
			}


			//cvRectangle(pFrame,cvPoint(rect.x,rect.y),cvPoint(rect.x+rect.width,rect.y+rect.height),CV_RGB(255,0,0),1,8,0);
			//cvRectangle(pGrayImg, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height), CV_RGB(255, 200, 0), 2, 8, 0);
			// draw the rect
			CvPoint pt[4];
			if ((dst_contour->total == 4) && cvCheckContourConvexity(dst_contour))
			{
#if 0
				for (int i = 0; i < 4; i++)
				{
					pt[i] = *(CvPoint *)cvGetSeqElem(dst_contour, i);

				}
				cvLine(pFrame, cvPoint(pt[0].x, pt[0].y), cvPoint(pt[1].x, pt[1].y), CV_RGB(255, 0, 0), 1, 8, 0);
				cvLine(pFrame, cvPoint(pt[1].x, pt[1].y), cvPoint(pt[2].x, pt[3].y), CV_RGB(255, 50, 0), 2, 8, 0);
				cvLine(pFrame, cvPoint(pt[2].x, pt[2].y), cvPoint(pt[3].x, pt[3].y), CV_RGB(255, 100, 0), 3, 8, 0);
				cvLine(pFrame, cvPoint(pt[3].x, pt[3].y), cvPoint(pt[0].x, pt[0].y), CV_RGB(255, 150, 0), 4, 8, 0);
				//cvCircle(pFrame, cvPoint(pt[i].x, pt[i].y), 3, CvScalar(255, 0, 255));
				//cvRectangle(pFrame, cvPoint(pt[0].x, pt[0].y), cvPoint(pt[3].x, pt[3].y), CV_RGB(255, 0, 0), 1, 8, 0);
				//cvRectangle(pGrayImg, cvPoint(pt[0].x, pt[0].y), cvPoint(pt[3].x, pt[3].y), CV_RGB(255, 128, 75), 2, 8, 0);
#endif
				CvPoint pt[4];
				double d1, d2, p = cvArcLength(dst_contour, CV_WHOLE_SEQ, 1);
				double area = fabs(cvContourArea(dst_contour, CV_WHOLE_SEQ));
				double dx, dy;
				int i = 0;

				for (i = 0; i < 4; i++)
					pt[i] = *(CvPoint*)cvGetSeqElem(dst_contour, i);

				dx = pt[0].x - pt[2].x;
				dy = pt[0].y - pt[2].y;
				d1 = sqrt(dx*dx + dy*dy);

				dx = pt[1].x - pt[3].x;
				dy = pt[1].y - pt[3].y;
				d2 = sqrt(dx*dx + dy*dy);

				// PHILIPG: Only accept those quadrangles which are more
				// square than rectangular and which are big enough
				double d3, d4;
				dx = pt[0].x - pt[1].x;
				dy = pt[0].y - pt[1].y;
				d3 = sqrt(dx*dx + dy*dy);
				dx = pt[1].x - pt[2].x;
				dy = pt[1].y - pt[2].y;
				d4 = sqrt(dx*dx + dy*dy);
				//!(flags & CV_CALIB_CB_FILTER_QUADS) ||
				//d3*4 > d4 && d4*4 > d3 && d3*d4 < area*1.5 && area > min_size &&
				//d1 >= 0.15 * p && d2 >= 0.15 * p )
				double rect_center[2];
				rect_center[0] = rect.x + (rect.width >> 1);
				rect_center[1] = rect.y + (rect.height >> 1);

				double w_div_h_ceil = 7.0, w_div_h_floor = 0.2;
				if (rect_center[0] < temp_img->width * 0.3 || rect_center[0] > temp_img->width * 0.7)
				{
					w_div_h_ceil *= 0.75;
					w_div_h_floor *= 1.5;
				}

				if ( // d3 / d4 < 6 && 
					rect.height >= 5 && rect.width >= 5 // rectangle edge length selection
					&& rect.width / (double)rect.height < w_div_h_ceil && rect.width / (double)rect.height > w_div_h_floor // rectangle edge ratio selection
					&& rect_center[1] > temp_img->height * 0.25 && rect_center[1] < temp_img->height * 0.9 // rectangle center y direction pos selection
					&& rect_center[0] > temp_img->width * 0.06 && rect_center[0] < temp_img->width * 0.94 // rectangle center x direction pos selection					
					/*|| (corner_config.board_size.height * corner_config.board_size.width == 1)*/
					)
				{
					// src_contour->v_prev表示 同一级别的边缘(不是包含关系)
					CvContour* parent = (CvContour*)(contour->v_prev);
					/*
					CvContourEx* parent = (CvContourEx*)(src_contour->v_prev);
					parent->counter++;
					if (!board || board->counter < parent->counter)
						board = parent;
				*/
					dst_contour->v_prev = (CvSeq*)parent;
					//cvSeqPush(root, &dst_contour);
					for (int i = 0; i < 4; i++)
					{
						pt[i] = *(CvPoint *)cvGetSeqElem(dst_contour, i);

					}

					printf("x=%f,y=%f\n",rect_center[0], rect_center[1]);
					cvLine(temp_img_b, cvPoint(pt[0].x, pt[0].y), cvPoint(pt[1].x, pt[1].y), CV_RGB(255, 0, 0), 1, 8, 0);
					cvLine(temp_img_b, cvPoint(pt[1].x, pt[1].y), cvPoint(pt[2].x, pt[2].y), CV_RGB(0, 255, 0), 1, 8, 0);
					cvLine(temp_img_b, cvPoint(pt[2].x, pt[2].y), cvPoint(pt[3].x, pt[3].y), CV_RGB(0, 0, 255), 1, 8, 0);
					cvLine(temp_img_b, cvPoint(pt[3].x, pt[3].y), cvPoint(pt[0].x, pt[0].y), CV_RGB(150, 150, 150), 1, 8, 0);

					CvPoint2D32f QPts[4];
					int index[4];
					int j = 0;
					// get 4 point.
					for (i = 0; i < 4; i++)
					{
						index[i] = i;
						QPts[i].x = (float)(*(CvPoint*)cvGetSeqElem(dst_contour, i)).x;
						QPts[i].y = (float)(*(CvPoint*)cvGetSeqElem(dst_contour, i)).y;
					}

					// sort the 4 point by y
					for (i = 0; i < 4; i++)
					{
						for (j = i + 1; j < 4; j++)
						{
							if (QPts[i].y > QPts[j].y)
							{
								CvPoint2D32f temp;
								temp = QPts[i];
								QPts[i] = QPts[j];
								QPts[j] = temp;

								int temp_idx;
								temp_idx = index[i];
								index[i] = index[j];
								index[j] = temp_idx;
							}
						}
					}

					// 保证从0点开始，顺时钟排序，（0点的x比1点的小）
					CvPoint2D32f pt_temp[4];
					int k = (QPts[0].x < QPts[1].x) ? index[0] : index[1];
					for (i = 0; i < 4; i++)
					{
						float x = (float)(*(CvPoint*)cvGetSeqElem(dst_contour, k % 4)).x;
						float y = (float)(*(CvPoint*)cvGetSeqElem(dst_contour, k % 4)).y;
						pt_temp[i] = cvPoint2D32f(x, y);

						k++;
					}
					cvLine(temp_img_c, cvPoint(pt_temp[0].x, pt_temp[0].y), cvPoint(pt_temp[1].x, pt_temp[1].y), CV_RGB(255, 0, 0), 1, 8, 0);
					cvLine(temp_img_c, cvPoint(pt_temp[1].x, pt_temp[1].y), cvPoint(pt_temp[2].x, pt_temp[2].y), CV_RGB(0, 255, 0), 1, 8, 0);
					cvLine(temp_img_c, cvPoint(pt_temp[2].x, pt_temp[2].y), cvPoint(pt_temp[3].x, pt_temp[3].y), CV_RGB(0, 0, 255), 1, 8, 0);
					cvLine(temp_img_c, cvPoint(pt_temp[3].x, pt_temp[3].y), cvPoint(pt_temp[0].x, pt_temp[0].y), CV_RGB(150, 150, 150), 1, 8, 0);


				}// end if(rect.width...// position

			}// end if ((dst_contour->total == 4) && cvCheckContourConvexity(dst_contour))
		}// end if hole

	} // end while

	test(pFrame);
	cvEndFindContours(&scanner);
	cvShowImage("contours", temp_img_b);
	cvShowImage("pBinImg", pGrayImg);
	cvShowImage("contours1", temp_img_c);
	// pFrImg->origin=1;  // 这个不需要翻转（实验结果得知）
	cvWaitKey(0);
	free(yuvData);
	return(retVal);

}

#include <iostream>
#include <opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat srcMat = imread("coin.png", 0);
	cv::Mat dstMat, outMat, statsMat, centrMat;
	outMat = cv::Mat::zeros(srcMat.size(), CV_8UC3);

	//二值化
	threshold(srcMat, dstMat, 0, 255, THRESH_OTSU);
	imshow("otsu", dstMat);

	//统计连通域数目
	int nComp = connectedComponentsWithStats(dstMat, outMat, statsMat, centrMat, 8, CV_32S);

	//输出硬币数目
	cout << "the number of coins = " << nComp - 1 << endl;

	for (int i = 0; i < nComp; i++) 
	{
		Rect bndbox;
		bndbox.x = statsMat.at<int>(i, 0);
		bndbox.y = statsMat.at<int>(i, 1);
		bndbox.width = statsMat.at<int>(i, 2);
		bndbox.height = statsMat.at<int>(i, 3);
		rectangle(dstMat, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}
	imshow("output", dstMat);

	waitKey(0);
	return 0;
}

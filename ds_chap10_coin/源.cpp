#include <opencv.hpp>
using namespace cv;
using namespace std;
//int main()
//{
//	Mat src = imread("coin.jpg");
//	Mat gray;
//	cvtColor(src, gray, CV_BGR2GRAY);
//	Mat binary;
//	threshold(gray, binary, 128, 255, THRESH_BINARY | THRESH_OTSU);
//	vector<vector<Point>> contours;
//	vector<Vec4i> hier;
//	vector<vector<Point>> t_contours;
//	findContours(binary.clone(), contours, hier, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
//	for (int i = 0; i < contours.size(); i++)
//	{
//		if (hier[i][3] == -1)
//		{
//			t_contours.push_back(contours[i]);
//		}
//	}
//	
//	sort(t_contours.begin(), t_contours.end(), [](vector<Point> v1, vector<Point> v2) { return contourArea(v1) > contourArea(v2); });
//	for (int i = 0; i < t_contours.size(); i++)
//	{
//		cout << i << endl;
//		Rect rec = boundingRect(t_contours[i]);
//		rectangle(src, rec, Scalar(0, 255, 0), 1, LINE_AA);
//		imshow("src", src);
//		waitKey();
//	}
//	imshow("bin", binary);
//	imshow("src", src);
//	waitKey();
//	
//}

int main()
{
	Mat src = imread("src.bmp",IMREAD_GRAYSCALE);
	int t1 = 0;
	int t2 = 0;
	namedWindow("canny");
	createTrackbar("t1", "canny", &t1, 255);
	createTrackbar("t2", "canny", &t2, 255);
	for (;;)
	{
		Mat canny;
		Canny(src, canny, t1, t2, 3);
		imshow("canny", canny);
		imshow("src", src);
		waitKey(15);
	}
}
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
using namespace std;

string cascade_name = "cascadelbp.xml";
cv::CascadeClassifier cascade;
string window_name = "Dectect Scissor";
long long siz = 300 * 300;
int main(void)
{
	if (!cascade.load(cascade_name))
	{
		cout << "cascadeclassifier build failed" << endl;
		return 0;
	}
	
	cv::VideoCapture cap;
	cap.open(1);
	cv::Mat frame;
	do
	{
		cap >> frame;
	} while (frame.empty());
	auto fsize = frame.rows*frame.cols;
	auto p = sqrt(((double)siz) / fsize);
	cv::Size framesize(round(p*frame.cols), round(p*frame.rows));
	cv::VideoWriter out;
	out.open(
		"test.mp4",
		CV_FOURCC('D', 'I', 'V', 'X'),
		40.0,
		framesize
		);

	while (cap.isOpened())
	{
		
		auto starttime = clock();
		cap >> frame;
	
		if (frame.empty())
		{
			cout << "picture not found" << endl;
			break;
		}
		long long fsize = frame.rows*frame.cols;
		if (fsize >siz)
		{
			cv::Mat tmat;
			cv::resize(frame, tmat, framesize);
			frame = tmat;
		}
		vector<cv::Rect> scissors;
		cv::Mat frame_gray;
		
		cv::cvtColor(frame, frame_gray, CV_BGR2GRAY);
		cascade.detectMultiScale(frame_gray, scissors, 1.1, 3, 0, cv::Size(40, 25));
		auto endtime = clock();
		
		cout << scissors.size() << "scissors found" << endl;
		cout << 1000 * (endtime - starttime) / (double)CLOCKS_PER_SEC << "ms" << endl;
		for (int i = 0; i != scissors.size(); ++i)
		{
			cv::rectangle(frame, scissors[i], cv::Scalar(255, 0, 0), 1, cv::LINE_8, 0);
		}
		cv::imshow(window_name, frame);
		out << frame;
		if (cv::waitKey(5) >= 0) break;
	}
}


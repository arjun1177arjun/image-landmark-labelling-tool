#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

const int points = 5;	// number of landmark points to be marked %%

//global variables
Mat img;
Mat imgLines;;
Mat imgText;;
int step;
int frame = 0;
int exitflag = 0;
int ax[points+1];
int ay[points+1];

void mark(int event, int x, int y, int flags, void* userdata)
{
	if (exitflag == 1)
	{
		return;
	}
	else if (event == EVENT_LBUTTONDOWN)
	{
		step++;
		imgText = Mat::zeros(img.size(), CV_8UC3);;
		putText(imgText, "Point marked = " + to_string(step), Point(10, 20), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(0, 0, 255), 1, 8, false);
		ax[step] = x;
		ay[step] = y;
		circle(imgLines, Point(x, y), 2, Scalar(0, 0, 255), -1, 8, 0);
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		//Undo
		if (step == 0)
			return;
		if (ax[step] == -1 && ay[step] == -1)
			step--;
		circle(imgLines, Point(ax[step], ay[step]), 2, Scalar(0, 0, 0), -1, 8, 0);
		ax[step] = -1;
		ay[step] = -1;
		imgText = Mat::zeros(img.size(), CV_8UC3);;
		putText(imgText, "Point marked = " + to_string(step-1), Point(10, 20), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(0, 0, 255), 1, 8, false);
	}
	if (step == points)
	{
		frame++;
		cout << "Image" << to_string(frame) <<"done"<<endl;
		cout << "Press any key for next image" << endl;
		// generate text file of points                                                                                                                                                                                                                                                                                                                                                   
		ofstream myfile;
		myfile.open("F:\\IDM\\compressed\\implement-Xiong-lip-features\\inputVids\\landmarks-img"+to_string(frame)+".txt");
		myfile << "n_points:  "<<to_string(points)<<" \n";
		myfile << "{ \n";
		for (int i = 1; i <= points;i++)
			myfile <<ax[i]<<" "<<ay[i]<<" \n";
		myfile << "}";
		myfile.close();
		imshow("My Window", img + imgText + imgLines);
		waitKey(15);
		exitflag = 1;
		return;
	}
	imshow("My Window", img + imgText +imgLines);
	waitKey(15);
	return;
}

int main(int argc, char** argv)
{
	VideoCapture cap;
	//Input type-1 giving direct video as input
	cap.open("F:\\IDM\\compressed\\implement-Xiong-lip-features\\inputVids\\a1.mpg");
	//Input type -2 giving folder storing images as input
	/*
	use glob function of opencv
	see theodore's answer here
	http://answers.opencv.org/question/58078/reading-a-sequence-of-files-within-a-folder/
	*/
	if (!cap.isOpened()){ cout << "ERROR" << endl; }
	cap.read(img);
	imgLines = Mat::zeros(img.size(), CV_8UC3);;
	imgText = Mat::zeros(img.size(), CV_8UC3);;
	putText(imgText, "Points marked = 0", Point(10, 20), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(0, 0, 255), 1, 8, false);

	//Create a window
	namedWindow("My Window", CV_WINDOW_AUTOSIZE);

	while (true)
	{
		setMouseCallback("My Window", mark, NULL);
		imshow("My Window", img+imgText +imgLines);
		waitKey(30);
		waitKey(0);
		cap.read(img);
		//new frame inits
		step = 0;
		exitflag = 0;
		imgText = Mat::zeros(img.size(), CV_8UC3);;
		putText(imgText, "Point marked = " + to_string(step), Point(10, 20), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(0, 0, 255), 1, 8, false);
		imgLines = Mat::zeros(img.size(), CV_8UC3);;
	}
	return 0;
}
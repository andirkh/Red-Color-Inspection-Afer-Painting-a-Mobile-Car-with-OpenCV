#include <iostream>
#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

Mat merahhsv;
Scalar minL, maxL;

void CallBackFunc(int event, int x, int y, int flags, void* userdata){
	if(flags == EVENT_FLAG_LBUTTON){
		Vec3b wwww = merahhsv.at<Vec3b>(Point(x,y));
		int phue = wwww[0], psat = wwww[1], pval = wwww[2];
		cout << phue << ", " << psat << ", " << pval << endl;
		
		minL = Scalar(phue-2,psat-10,0);
		maxL = Scalar(phue+2,255,255);
	}
}

int main (int argc, char** argv)
{
	VideoCapture cap(0); //capture video dari web cam
	if ( !cap.isOpened())
	{
		cout << "webcam tidak bisa dibuka" <<endl;
		return -1;
	}
cvNamedWindow("original");
setMouseCallback("original", CallBackFunc, NULL);
	
Mat Merah;
Mat MerahOK;
minL = Scalar(12,45,0);
maxL = Scalar(35,255,255);
Moments Moment;


while (1){
	cap >> Merah;
	cvtColor(Merah, merahhsv, CV_BGR2HSV);
	inRange (merahhsv, minL, maxL, MerahOK);
	Moment = moments(MerahOK,false);
	
	string text = "OK";
	string textf = "REJECT";
	string texte = "  ";
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = 2;
	int thickness = 3;
	int baseline=0;
	Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
	baseline += thickness;

	Point textOrg((Merah.cols - textSize.width)/2, (Merah.rows + textSize.height)/2);
	// draw the box
	rectangle(Merah, cvPoint(200,250), cvPoint(500,400), Scalar(0,0,255));
	// ... and the baseline first
	line(Merah, cvPoint(200,250), cvPoint(500,400), Scalar(0, 0, 255));
	
	//string a = (string)Moment.m00;
	//putText(Merah, a, Point((Merah.cols - textSize.width)/3, (Merah.rows + textSize.height)/3), fontFace, fontScale, Scalar::all(255), thickness, 8);
	if(Moment.m00 > 600000) putText(Merah, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
	if(Moment.m00 > 20000 && Moment.m00 < 600000) putText(Merah, textf, textOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
	if(Moment.m00 < 20000) putText(Merah, texte, textOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
	printf("%f \n",Moment.m00);
	imshow("original" , Merah);
	imshow("hsv", merahhsv);
	imshow("Deteksi Merah", MerahOK);
	
	if (waitKey(30) == 27) break;
}
return 0;
}



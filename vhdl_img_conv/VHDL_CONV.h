#pragma once

#ifdef _DEBUG
//Debugモードの場合
#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\lib\\opencv_core2411d.lib")
#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\lib\\opencv_imgproc2411d.lib")
#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\lib\\opencv_highgui2411d.lib")
#else
//Releaseモードの場合
#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\lib\\opencv_core2411.lib")
#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\lib\\opencv_imgproc2411.lib")
#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\lib\\opencv_highgui2411.lib")
#endif

#include <opencv2\opencv.hpp>
#include <opencv2\core\core_c.h>
#include <opencv\highgui.h>
#include <opencv2\highgui\highgui.hpp>

#include <iostream>
#include <fstream>


class VHDL_CONV
{
public:
	VHDL_CONV(char argv[]);
	~VHDL_CONV();
	void showFile(void);
private:
	cv::Mat mat, outMat, matTemp;
	void init(void);
	std::string windowName = "image";//ウインドウの名前
	std::string filename;
	void imgResize(cv::Mat _mat);
	void fileOutput(void);
	std::string getChannel(int c);
	void fileOutput1dim(void);
};


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
#include<opencv2\core\core_c.h>
#include <opencv\highgui.h>
#include <opencv2\highgui\highgui.hpp>
#include "VHDL_CONV.h"

int main(int argc, char* argv[])
{

	/*char name[] = "test.png";
	VHDL_CONV test(name);
	cv::waitKey();//なにかキーを押されるまで待機*/

	if (argc > 1)//なにかD&Dされたら
	{
		for (int i = 1; i < argc; i++)
		{
			VHDL_CONV test(argv[i]);//ファイルの読み込み
			cv::waitKey();//なにかキーを押されるまで待機
		}
	}
	return 0;
}

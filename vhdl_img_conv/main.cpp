#ifdef _DEBUG
//Debugモードの場合
#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\lib\\opencv_core2411d.lib")
#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\lib\\opencv_imgproc2411d.lib")
#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\lib\\opencv_highgui2411d.lib")
#else
//Releaseモードの場合
/*#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\staticlib\\opencv_core2411.lib")
#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\staticlib\\opencv_imgproc2411.lib")
#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\staticlib\\opencv_highgui2411.lib")
#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\staticlib\\zlib.lib") // ←何故か無いとエラーが出る*/

#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\lib\\opencv_core2411.lib")
#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\lib\\opencv_imgproc2411.lib")
#pragma comment(lib,"C:\\opencv\\opencv-2.4.11\\build\\x64\\vc12\\lib\\opencv_highgui2411.lib")
#endif


//#pragma comment(lib,"comctl32.lib")
//#pragma comment(lib,"vfw32.lib")


/*// バージョン名の取得
#define CV_VERSION_STR CVAUX_STR(CV_MAJOR_VERSION) CVAUX_STR(CV_MINOR_VERSION) CVAUX_STR(CV_SUBMINOR_VERSION)

// libファイル名の最後の部分をReleaseとDebugで分ける
#ifdef _DEBUG
#define CV_EXT_STR "d.lib"
#else
#define CV_EXT_STR ".lib"
#endif

//プロジェクトのプロパティ⇒リンカー⇒全般　の追加のライブラリディレクトリに
// libファイルのあるフォルダ（C:\opencv\build\x86\vc10\libなど）を追加のこと
#pragma comment(lib, "opencv_core"  CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_imgproc"   CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_highgui"   CV_VERSION_STR CV_EXT_STR)

#pragma comment(lib, "zlib" CV_EXT_STR)
#pragma comment(lib, "IlmImf"   CV_EXT_STR)
//#pragma comment(lib, "libjasper"CV_EXT_STR)
#pragma comment(lib, "libjpeg"  CV_EXT_STR)
#pragma comment(lib, "libpng"   CV_EXT_STR)
#pragma comment(lib, "libtiff"  CV_EXT_STR)


#pragma comment(lib, "opencv_calib3d"  CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_contrib"  CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_core"  CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_features2d"  CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_flann"  CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_gpu"  CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_highgui"   CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_imgproc"   CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_legacy"   CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_ml"   CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_nonfree"   CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_objdetect"   CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_ocl"   CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_photo"   CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_stitching"   CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_superres"   CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_ts"   CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_video" CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_videostab" CV_VERSION_STR CV_EXT_STR)

#pragma comment(lib, "zlib" CV_EXT_STR)
#pragma comment(lib, "IlmImf"   CV_EXT_STR)
//#pragma comment(lib, "libjasper"CV_EXT_STR)
#pragma comment(lib, "libjpeg"  CV_EXT_STR)
#pragma comment(lib, "libpng"   CV_EXT_STR)
#pragma comment(lib, "libtiff"  CV_EXT_STR)*/

/*#pragma comment(lib, "opencv_core2411.lib")
#pragma comment(lib, "opencv_imgproc2411.lib")
#pragma comment(lib, "opencv_highgui2411.lib")

#pragma comment(lib, "zlib2411.lib")
#pragma comment(lib, "IlmImf2411.lib")
//#pragma comment(lib, "libjasper"CV_EXT_STR)
#pragma comment(lib, "libjpeg2411.lib")
#pragma comment(lib, "libpng2411.lib")
#pragma comment(lib, "libtiff2411.lib")


#pragma comment(lib, "opencv_calib3d2411.lib")
#pragma comment(lib, "opencv_contrib2411.lib")
#pragma comment(lib, "opencv_core2411.lib")
#pragma comment(lib, "opencv_features2d2411.lib")
#pragma comment(lib, "opencv_flann2411.lib")
#pragma comment(lib, "opencv_gpu2411.lib")
#pragma comment(lib, "opencv_highgui2411.lib")
#pragma comment(lib, "opencv_imgproc2411.lib")
#pragma comment(lib, "opencv_legacy2411.lib")
#pragma comment(lib, "opencv_ml2411.lib")
#pragma comment(lib, "opencv_nonfree2411.lib")
#pragma comment(lib, "opencv_objdetect2411.lib")
#pragma comment(lib, "opencv_ocl2411.lib")
#pragma comment(lib, "opencv_photo2411.lib")
#pragma comment(lib, "opencv_stitching2411.lib")
#pragma comment(lib, "opencv_superres2411.lib")
#pragma comment(lib, "opencv_ts2411.lib")
#pragma comment(lib, "opencv_video2411.lib")
#pragma comment(lib, "opencv_videostab2411.lib")

#pragma comment(lib, "zlib2411.lib")
#pragma comment(lib, "IlmImf2411.lib")
//#pragma comment(lib, "libjasper"CV_EXT_STR)
#pragma comment(lib, "libjpeg2411.lib")
#pragma comment(lib, "libpng2411.lib")
#pragma comment(lib, "libtiff2411.lib")*/



#include <opencv2\opencv.hpp>
#include <opencv2\core\core_c.h>
#include <opencv\highgui.h>
#include <opencv2\highgui\highgui.hpp>
#include "VHDL_CONV.h"
#include <conio.h>

int main(int argc, char* argv[])
{
	if (argc > 1)//なにかD&Dされたら
	{
		for (int i = 1; i < argc; i++)
		{
			VHDL_CONV conv(argv[i]);//ファイルの読み込み
			int c=cv::waitKey();
			if (c == 'v' || c == 'V')
			{
				conv.showFile();
				cv::waitKey();
			}
		}
	}
	return 0;
}

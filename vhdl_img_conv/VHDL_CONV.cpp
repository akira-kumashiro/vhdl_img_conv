#include "VHDL_CONV.h"

VHDL_CONV::VHDL_CONV(char argv[])
{
	mat = cv::imread(argv);//画像の読み込み
	if (mat.data == NULL)//画像の読み込みに失敗したときの処理
	{
		std::cout << "Cannot open this file!" << std::endl;
		return;
	}

	cv::imshow("InMat", mat);//画像の表示

	std::cout << "Set output filename:\n";
	std::cin >> filename;
	std::cout << "Save as \"" + filename + ".vhd\"\n";

	std::cout << "Set image size(dot):\n";
	scanf("%d", &p);

	outMat = cv::Mat::zeros(cv::Size(VGA_WIDTH, VGA_HEIGHT), CV_8UC3);

	imgResize(mat,p);

	cv::imshow("OutMat", outMat);

	fileOutput1dim();

	printf("end\n");
}

VHDL_CONV::~VHDL_CONV()
{
}

void VHDL_CONV::showFile(void)
{
	std::ifstream ifs(filename + ".vhd");
	std::string buf;

	while (ifs && getline(ifs, buf))
	{
		std::cout << buf << std::endl;
	}
}

void VHDL_CONV::imgResize(cv::Mat _mat,int per)//画像サイズを640*480に
{
	cv::Mat temp;

	if (_mat.cols > VGA_WIDTH || _mat.rows > VGA_HEIGHT)
	{
		double scale;
		if (_mat.cols > _mat.rows)
			scale = (double)VGA_WIDTH / _mat.cols;
		else
			scale = (double)VGA_HEIGHT / _mat.rows;
		cv::resize(_mat, temp, cv::Size(), scale, scale);
	}

	int yOffset = (VGA_HEIGHT - temp.rows) / 2;
	int xOffset = (VGA_WIDTH - temp.cols) / 2;

	for (int y = 0; y < temp.rows; y++)
	{
		cv::Vec3b *_mat_ptr = temp.ptr<cv::Vec3b>(y);
		cv::Vec3b *outMat_ptr = outMat.ptr<cv::Vec3b>(y + yOffset);
		for (int x = 0; x < temp.cols; x++)
		{
			for (int c = 0; c < outMat.channels(); c++)
			{
				outMat_ptr[x + xOffset][c] = (int)(_mat_ptr[x][c] / 16) * 16;
			}
		}
	}

	//cv::resize(outMat, outMat, cv::Size(), per / 100.0, per / 100.0,CV_INTER_NN);
	//cv::resize(outMat, outMat, cv::Size(), 100.0 / per, 100.0 / per, CV_INTER_NN);

}

std::string VHDL_CONV::getChannel(int c)
{
	switch (c)
	{
	case 0:return("B");
	case 1:return("G");
	case 2:return("R");
	default:return("\0");
	}
}

void VHDL_CONV::fileOutput1dim(void)//ファイル書き込み
{
	std::ofstream outputfile(filename + ".vhd");
	outputfile << "library ieee;\n	use ieee.std_logic_1164.all;\n	use ieee.std_logic_unsigned.all;\nentity " + filename + " is\n";
	outputfile << "port(\n	Point:in std_logic_vector(19 downto 0);\n	R:out std_logic_vector(3 downto 0);\n	G:out std_logic_vector(3 downto 0);\n	B:out std_logic_vector(3 downto 0)\n);\nend " + filename + ";\n";
	outputfile << "architecture rtl of " + filename + " is\n	begin\n	process(Point)\n		begin\n";

	for (int c = 0; c < outMat.channels(); c++)//RGBチャンネルごとに処理
	{
		for (int i = 0; i < 4; i++)//4bit
		{
			bool writeFileFlag = false;//条件式追加判定フラグ
			bool firstWriteFlag = false;//初めての条件式追加フラグ

			for (int j = c; j < ((outMat.rows - 1)*outMat.step + (outMat.cols - 1)*outMat.elemSize() + c); j += outMat.channels())
			{
				int k;
				bool hitEndOfArrayFlag = false;

				for (k = j; k < ((outMat.rows - 1)*outMat.step + (outMat.cols - 1)*outMat.elemSize() + c); k += outMat.channels())
				{
					if ((int)(outMat.data[k] / std::pow(2, 8.0 - i)) != 1)//bitが立ってる区間を判定
						break;
					else
						outMat.data[k] -= std::pow(2, 8.0 - i);

					if (k == ((outMat.rows - 1)*outMat.step + (outMat.cols - 1)*outMat.elemSize() + c))//画像の末尾を判定
						hitEndOfArrayFlag = true;
				}
				if (k - j)//条件式があるとき
				{
					if (writeFileFlag)
					{
						if (j != c)
						{
							//outputfile << "		elsif";
							outputfile << " or ";
							writeFileFlag = false;
						}
					}

					if (!firstWriteFlag)
						outputfile << "		if(";

					if ((int)((k - j) / outMat.channels()) > 1)//条件式追加
					{
						if (hitEndOfArrayFlag)
						{
							//outputfile << " (Point>=" + std::to_string((j - c) / outMat.channels()) + " and Point<" + std::to_string(VGA_WIDTH * VGA_HEIGHT - 1) + ") then\n			" + getChannel(c) + "(" + std::to_string(outMat.channels() - i) + ")<=\'1\';\n";
							outputfile << "(Point>=" + std::to_string((j - c) / outMat.channels()) + " and Point<" + std::to_string(VGA_WIDTH * VGA_HEIGHT - 1) + ")";
						}
						else
						{
							outputfile << "(Point>=" + std::to_string((j - c) / outMat.channels()) + " and Point<" + std::to_string(( k - c) / outMat.channels()) + ")";
							//outputfile << " (Point>=" + std::to_string((j - c) / outMat.channels()) + " and Point<" + std::to_string(( k - c) / outMat.channels()) + ") then\n			" + getChannel(c) + "(" + std::to_string(outMat.channels() - i) + ")<=\'1\';\n";
						}
					}
					else
					{
						//outputfile << "(Point=" + std::to_string((j - c) / outMat.channels()) + ") then\n			" + getChannel(c) + "(" + std::to_string(outMat.channels() - i) + ")<=\'1\';\n";
						outputfile << "(Point=" + std::to_string((j - c) / outMat.channels()) + ")";
					}
					writeFileFlag = true;
					firstWriteFlag = true;
				}
				j = k;
			}
			if (!writeFileFlag)//条件が1つもないとき
			{
				outputfile << "		" + getChannel(c) + "(" + std::to_string(outMat.channels() - i) + ")<=\'0\';\n";
			}
			else
			{
				outputfile << ") then\n";
				outputfile << "			" + getChannel(c) + "(" + std::to_string(outMat.channels() - i) + ")<=\'1\';\n";
				outputfile << "		else\n			" + getChannel(c) + "(" + std::to_string(outMat.channels() - i) + ")<=\'0\';\n		end if;\n";
			}
		}
	}
	outputfile << "	end process;\nend rtl;";

	outputfile.close();
}

#include "VHDL_CONV.h"



VHDL_CONV::VHDL_CONV(char argv[])
{
	//cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE);//ウインドウの名前をつけて生成
	mat = cv::imread(argv);//画像の読み込み
	if (mat.data == NULL)//画像の読み込みに失敗したときの処理
	{
		std::cout << "Cannot open this file!" << std::endl;
		return;
	}

	cv::imshow(windowName, mat);//画像の表示

	std::cout << "Set output filename:\n";
	std::cin >> filename;
	std::cout << "Save as \"" + filename + ".vhd\"\n";

	outMat = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);

	imgResize(mat);

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

void VHDL_CONV::init(void)
{
	cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE);//ウインドウの名前をつけて生成
}

void VHDL_CONV::imgResize(cv::Mat _mat)
{
	cv::Mat temp;

	if (_mat.cols > 640 || _mat.rows > 480)
	{
		if (_mat.cols > _mat.rows)
		{
			double scale = 640.0 / _mat.cols;
			cv::resize(_mat, temp, cv::Size(), scale, scale);
		}
		else
		{
			double scale = 480.0 / _mat.rows;
			cv::resize(_mat, temp, cv::Size(), scale, scale);
		}
	}

	int yOffset = (480 - temp.rows) / 2;
	int xOffset = (640 - temp.cols) / 2;

	for (int y = 0; y < temp.rows; y++)
	{
		cv::Vec3b *_mat_ptr = temp.ptr<cv::Vec3b>(y);
		cv::Vec3b *outMat_ptr = outMat.ptr<cv::Vec3b>(y + yOffset);
		{
			for (int x = 0; x < temp.cols; x++)
			{
				outMat_ptr[x + xOffset] = _mat_ptr[x];
			}
		}
	}

	for (int y = 0; y < outMat.rows; y++)
	{
		cv::Vec3b *outMat_ptr = outMat.ptr<cv::Vec3b>(y);
		for (int x = 0; x < outMat.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				outMat_ptr[x][c] = (int)(outMat_ptr[x][c] / 16) * 16;
			}
		}
	}
}

void VHDL_CONV::fileOutput(void)
{
	std::string str = std::string("img01");

	std::ofstream outputfile(str + ".vhd");
	outputfile << "library ieee;\n use ieee.std_logic_1164.all;\n use ieee.std_logic_unsigned.all;\n entity " + str + " is\n";
	outputfile << "port(\n H_NUM:in std_logic_vector(10 downto 0);\n V_NUM:in std_logic_vector(10 downto 0);\n R:out std_logic_vector(3 downto 0);\n G:out std_logic_vector(3 downto 0);\n B:out std_logic_vector(3 downto 0));\n end " + str + ";";
	outputfile << "architecture rtl of " + str + " is\n begin\n process(H_NUM, V_NUM)\n begin\n";
	outputfile << "if (H_NUM >= 640 and V_NUM >= 480) then\n R <= \"0000\";\n G <= \"0000\";\n B <= \"0000\";\n";

	for (int y = 0; y < outMat.rows; y++)
	{
		cv::Vec3b *outMat_ptr = outMat.ptr<cv::Vec3b>(y);
		{
			for (int x = 0; x < outMat.cols; x++)
			{
				if (outMat_ptr[x][0] < 16 && outMat_ptr[x][1] < 16 && outMat_ptr[x][2] < 16)
				{
				}
				else
				{
					outputfile << "if(H_NUM=" + std::to_string(x) + " and V_NUM=" + std::to_string(y) + ") then\n";
					for (int i = 0; i < 3; i++)
					{
						switch (i)
						{
						case 0:outputfile << "R<=\""; break;
						case 1:outputfile << "G<=\""; break;
						case 2:outputfile << "B<=\""; break;
						}
						for (int j = 0; j < 4; j++)
						{
							int temp = outMat_ptr[x][2 - i];
							if ((int)(temp / std::pow(2, 8.0 - j)))
							{
								outputfile << "1";
								temp -= std::pow(2, 8.0 - j);
							}
							else
							{
								outputfile << "0";
							}
						}
						outputfile << "\";";
					}
					outputfile << "\n";
				}
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		/*for (int j = i; j < ((outMat.rows - 1)*outMat.step + (outMat.cols - 1)*outMat.elemSize() + i); j+=3)
		{
			if((j-i)

			int k;
			for (k = j; k < ((outMat.rows - 1)*outMat.step + (outMat.cols - 1)*outMat.elemSize() + i); k += 3)
			{
				if (std::abs(outMat.data[j] - outMat.data[k]) >= 16)
				{
					break;
				}
			}
			if (outMat.data[j] < 16)
			{

			}
			else
			{
				if (k)
				{
					outputfile<<"if((H_NUM>="+std::to_string((j-i)/3/480))+" and H_NUM<" + std::to_string((j+k-2*i) / 3 / 480)) +") and "
				}
			}
		}*/
		outputfile << "if(H_NUM>=640 and V_NUM>=480) then\n";
		outputfile << getChannel(i) + "<=\"0000\";\n";




		/*bool sameRowFlag = false;
		int ySameTemp = 0;

		for (int y = 0; y < outMat.rows; y++)
		{
			cv::Vec3b *outMat_ptr = outMat.ptr<cv::Vec3b>(y);
			for (int x = 0; x < outMat.cols; x++)
			{
				if (std::abs(outMat_ptr[x][i] - outMat_ptr[0][i]) >= 16)
				{
					break;
				}
				if (x == outMat.cols - 1)
				{
					sameRowFlag = true;
					ySameTemp = y;
				}
			}
			if(!sameRowFlag)
			for (int x = 0; x < outMat.cols; x++)
			{
				if (outMat_ptr[x][0] < 16 && outMat_ptr[x][1] < 16 && outMat_ptr[x][2] < 16)
				{
				}
				else
				{
					outputfile << "if(H_NUM=" + std::to_string(x) + " and V_NUM=" + std::to_string(y) + ") then\n";
					for (int i = 0; i < 3; i++)
					{
						switch (i)
						{
						case 0:outputfile << "R<=\""; break;
						case 1:outputfile << "G<=\""; break;
						case 2:outputfile << "B<=\""; break;
						}
						for (int j = 0; j < 4; j++)
						{
							int temp = outMat_ptr[x][2 - i];
							if ((int)(temp / std::pow(2, 8.0 - j)))
							{
								outputfile << "1";
								temp -= std::pow(2, 8.0 - j);
							}
							else
							{
								outputfile << "0";
							}
						}
						outputfile << "\";";
					}
					outputfile << "\n";
				}
			}

		}*/
	}

	outputfile << "else\n R <= \"0000\";\n G <= \"0000\";\n B <= \"0000\";\n	end if;\n";
	outputfile << "end process;\n end rtl;";
	/*	if (H_NUM >= 640 and V_NUM >= 480) then
			R <= "0000";
	G <= "0000";
	B <= "0000";
	elsif(H_NUM<320 and V_NUM<240) then
		R <= "1111";
	G <= "0000";
	B <= "0000";
	elsif(H_NUM<640 and V_NUM<240) then
		R <= "0000";
	G <= "1111";
	B <= "0000";
	elsif(H_NUM<320 and V_NUM<480) then
		R <= "0000";
	G <= "0000";
	B <= "1111";
	elsif(H_NUM<640 and V_NUM<480) then
		R <= "1111";
	G <= "1111";
	B <= "0000";*/


	outputfile.close();
}

std::string VHDL_CONV::getChannel(int c)
{
	//std::string str;
	switch (c)
	{
	case 0:return("R");//str = "R"; break;
	case 1:return("G");// str = "G"; break;
	case 2:return("B");// str = "B"; break;
	default:return("\0");
	}
	//return(str);
}

void VHDL_CONV::fileOutput1dim(void)
{
	std::ofstream outputfile(filename + ".vhd");
	outputfile << "library ieee;\n	use ieee.std_logic_1164.all;\n	use ieee.std_logic_unsigned.all;\nentity " + filename + " is\n";
	outputfile << "port(\n	Point:in std_logic_vector(19 downto 0);\n	R:out std_logic_vector(3 downto 0);\n	G:out std_logic_vector(3 downto 0);\n	B:out std_logic_vector(3 downto 0)\n);\nend " + filename + ";\n";
	outputfile << "architecture rtl of " + filename + " is\n	begin\n	process(Point)\n		begin\n";

	for (int c = 0; c < 3; c++)
	{
		for (int i = 0; i < 4; i++)
		{
			bool writeFileFlag = false;
			outputfile << "		if(";
			for (int j = c; j < ((outMat.rows - 1)*outMat.step + (outMat.cols - 1)*outMat.elemSize() + c); j += 3)
			{
				int k;
				bool hitEndOfArrayFlag = false;

				for (k = j; k < ((outMat.rows - 1)*outMat.step + (outMat.cols - 1)*outMat.elemSize() + c); k += 3)
				{
					if ((int)(outMat.data[k] / std::pow(2, 8.0 - i)) != 1)
						break;
					else
						outMat.data[k] -= std::pow(2, 8.0 - i);

					if (k == ((outMat.rows - 1)*outMat.step + (outMat.cols - 1)*outMat.elemSize() + c) - 3)
						hitEndOfArrayFlag = true;

				}
				if (k - j)
				{
					if (j != c && writeFileFlag)
					{
						outputfile << " or ";
						writeFileFlag = false;
					}
					if ((int)((k - j) / 3) > 1)
					{
						if (hitEndOfArrayFlag)
							outputfile << "(Point>=" + std::to_string((j - c) / 3) + " and Point<" + std::to_string(640 * 480 - 1) + ")";
						else
							outputfile << "(Point>=" + std::to_string((j - c) / 3) + " and Point<" + std::to_string((j + k - 2 * c) / 3) + ")";

					}
					else
					{
						outputfile << "(Point=" + std::to_string((j - c) / 3) + ")";
					}
					writeFileFlag = true;
				}
				j = k;
			}
			if (!writeFileFlag)
				outputfile << "\'0\'";

			outputfile << ") then\n";
			outputfile << "			" + getChannel(c) + "(" + std::to_string(3 - i) + ")=\'1\';\n";
			outputfile << "		else\n			" + getChannel(c) + "(" + std::to_string(3 - i) + ")=\'0\';\n		end if;\n";
		}
	}
	outputfile << "	end process;\nend rtl;";

	outputfile.close();
}

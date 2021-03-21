#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    //文件名，编码格式，帧率，分辨率
    VideoWriter video("test.mp4", VideoWriter::fourcc('D', 'I', 'V', 'X'),29.0, Size(1280,720));
	//图片地址
	String img_path = "D:\\CODE\\ComputerNetwork\\Lab1\\VideoToImg\\VideoToImg\\";
	vector<String> img;

	glob(img_path, img, false);
	//获取图片总张数
	size_t count = img.size();
	for (size_t i = 0; i < count; i++)
	{
		stringstream str;
		str << i << ".png";
		Mat image = imread(img_path + str.str());
		//图片不为空
		if (!image.empty())
		{
			//按需调整分辨率
			resize(image, image, Size(1280, 720));
			video << image;
			cout << "正在处理第" << i << "帧" << endl;
		}
	}
	cout << "处理完毕" << endl;
}

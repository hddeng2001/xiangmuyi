#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <String>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;
	//打开视频
	cap.open("D:\\CODE\\ComputerNetwork\\Lab1\\VideoToImg\\test.mp4");
	//是否成功打开视频
	if (!cap.isOpened())
		return 0;
	long totalFrame = cap.get(CAP_PROP_FRAME_COUNT);
	int fps = cap.get(CAP_PROP_FPS);
	cout << "总帧数为：" << totalFrame << "帧率为"<<fps<< endl;

	Mat	frame;
	for(int i=0;i<totalFrame;i++)
	{
		// 通过流操作符把视频转化为一帧帧图片
		cap >> frame;
		if (frame.empty())
			break;
		
		//存储帧
		String str = to_string(i) + ".png";
		imwrite(str.c_str(), frame);
			
		cout << "正在储存第" << i << "帧" << endl;
		//// 新建窗口，0表示可以用鼠标改变窗口大小
		//namedWindow("video", 0);
		////resize窗口大小
		//resizeWindow("video", 500, 500);
		////展示帧
		//imshow("video", frame);
	}
	cout << "输出完毕"<<endl;

	//关闭窗口
	destroyAllWindows();
	return 0;

}
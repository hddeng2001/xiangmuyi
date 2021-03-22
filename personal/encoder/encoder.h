#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

//二维码大小
#define IMG_X 1000
#define IMG_Y 1000
#define anchor_size 30
#define one_block_width 1
#define left_blank 10
//每个二维码最多二进制数量
#define MAX_CHAR ((IMG_X - 2 * left_blank - 2 * anchor_size) * anchor_size + (IMG_Y - 2 * left_blank - 2 * anchor_size) * IMG_X + (IMG_X - 2 * left_blank - anchor_size) * anchor_size)
#pragma once
class QRcode
{
	FILE* input_file;
	char* output_file;
	bool* bin_text;//检查数据是否出错？(FEC)
	char* str;//转化后的数据暂存

public:
	void encode(char* input_file_name,char* output_file_name);
	Mat draw_pure_white(int a,int b);
	Mat bin_to_png(bool* str, int size);
	void draw_anchors(Mat& image);
	bool* char_to_bool(char* a);
};

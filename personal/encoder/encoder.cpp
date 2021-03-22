#include "encoder.h"
void QRcode::encode(char* input_file_name, char* output_file_name)
{
	input_file = fopen(input_file_name, "rb");
	Mat frame;
	char* test_str;
	test_str = new char[MAX_CHAR];
	bool* bin_str;
	while (!input_file)
	{
		fread(test_str, 1, MAX_CHAR, input_file);
		int length = strlen(test_str);
		bin_str = char_to_bool(test_str);
		frame = bin_to_png(bin_str, length);//图片生成
	}
}


Mat QRcode::draw_pure_white(int a,int b)
{
	Mat image(a, b, CV_8UC3, Scalar(255, 255, 255));
	rectangle(image, Point(0, 0), Point(a, b), Scalar(255, 255, 255), FILLED, LINE_8);
	return image;
}

void QRcode::draw_anchors(Mat& image)
{
	//定位点1
	rectangle(image, Point(left_blank, left_blank), Point(anchor_size + left_blank - one_block_width * 2, anchor_size + left_blank - one_block_width * 2), Scalar(0), FILLED, LINE_8);//宁静区域(计入定位点大小)
	rectangle(image, Point(left_blank + one_block_width * 2, left_blank + one_block_width * 2), Point(left_blank + anchor_size - one_block_width * 4, left_blank + anchor_size - one_block_width * 4), Scalar(255), FILLED, LINE_8);
	rectangle(image, Point(left_blank + one_block_width * 4, left_blank + one_block_width * 4), Point(left_blank - one_block_width * 6, left_blank - one_block_width * 6), Scalar(0), FILLED, LINE_8);
	//定位点2
	rectangle(image, Point(IMG_X - anchor_size + left_blank + 2 * one_block_width, left_blank), Point(IMG_X + left_blank, anchor_size + left_blank - one_block_width * 2), Scalar(0), FILLED, LINE_8);//宁静区域
	rectangle(image, Point(IMG_X - anchor_size + left_blank + one_block_width * 4, left_blank + one_block_width * 2), Point(IMG_X + left_blank - one_block_width * 2, left_blank + anchor_size - one_block_width * 4), Scalar(255), FILLED, LINE_8);
	rectangle(image, Point(IMG_X - anchor_size + left_blank + one_block_width * 6, left_blank + one_block_width * 4), Point(IMG_X + left_blank - one_block_width * 4, left_blank + anchor_size - one_block_width * 6), Scalar(0), FILLED, LINE_8);
	//定位点3
	rectangle(image, Point(left_blank, IMG_Y - anchor_size + left_blank + 2 * one_block_width), Point(anchor_size + left_blank - one_block_width * 2, IMG_Y + left_blank), Scalar(0), FILLED, LINE_8);//宁静区域(计入定位点大小)
	rectangle(image, Point(left_blank + one_block_width * 2, IMG_Y - anchor_size + left_blank + 4 * one_block_width), Point(left_blank + anchor_size - one_block_width * 4, IMG_Y + left_blank - one_block_width * 2), Scalar(255), FILLED, LINE_8);
	rectangle(image, Point(left_blank + one_block_width * 4, IMG_Y - anchor_size + left_blank + 6 * one_block_width), Point(left_blank + anchor_size - one_block_width * 6, IMG_Y + left_blank - one_block_width * 4), Scalar(0), FILLED, LINE_8);
}

Mat QRcode::bin_to_png(bool* str, int size)//输入值为二进制字符串和字符串长度
{
	Mat image = draw_pure_white(IMG_X + 2 * left_blank, IMG_Y + 2 * left_blank);
	draw_anchors(image);

	int count = 0;//统计已填充数目
	for (int p = 0; p < anchor_size / one_block_width; p++)//1、2定位点之间的二维码
	{
		for (int q = 0; q < IMG_X / one_block_width - 2 * anchor_size / one_block_width; q++)
		{
			rectangle(image, Point(one_block_width * anchor_size + one_block_width * q + left_blank, 0 + one_block_width * p + left_blank), Point(one_block_width * anchor_size + one_block_width * (q + 1) + left_blank, 0 + one_block_width * (p + 1) + left_blank), Scalar(255 * str[count++]), FILLED, LINE_8);//0为黑，1为白
			if (count >= size)
			{
				str[count] = 0;			//溢出部分用0填充
			}
		}
	}

	for (int p = 0; p < IMG_Y / one_block_width - 2 * anchor_size / one_block_width; p++)//中间部分二维码
	{
		for (int q = 0; q < IMG_X / one_block_width; q++)
		{
			rectangle(image, Point(0 + one_block_width * q + left_blank, one_block_width * anchor_size + one_block_width * p + left_blank), Point(0 + one_block_width * (q + 1) + left_blank, one_block_width * anchor_size + one_block_width * (p + 1) + left_blank), Scalar(255 * str[count++]), FILLED, LINE_8);
			if (count >= size)
			{
				str[count] = 0;
			}
		}
	}
	for (int p = 0; p < anchor_size / one_block_width; p++)//3定位点右边的二维码
	{
		for (int q = 0; q < IMG_X / one_block_width - anchor_size / one_block_width; q++)
		{
			rectangle(image, Point(anchor_size * one_block_width + one_block_width * q + left_blank, IMG_X - anchor_size * one_block_width + one_block_width * p + left_blank), Point(anchor_size * one_block_width + one_block_width * (q + 1) + left_blank, IMG_X - anchor_size * one_block_width + one_block_width * (p + 1) + left_blank), Scalar(255 * str[count++]), FILLED, LINE_8);
			if (count >= size)
			{
				str[count] = 0;
			}
		}

	}
	return image;
}

bool* QRcode::char_to_bool(char* c)
{
	bool* b;
	b = new bool[MAX_CHAR];
	for (int i = 0; i < strlen(c); i++)
	{
		if (c[i] == '0')
			b[i] = false;
		else
			b[i] = true;
	}
	return b;
}
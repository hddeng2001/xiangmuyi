#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include "decode.h"


using namespace cv;
using namespace std;


void DeCode::decode(int argc, char* input_filename)
{
    // Read image
    Mat inputImage;

    ofstream bin("test.txt",ios::ate);//重新开始在txt文件中写数据

    //ofstream bin("test.txt", ios::app);

    //输入图片
    if (argc > 1)
        inputImage = imread(input_filename);
    else
        inputImage = imread("1.png");//需要解码的二维码的地址
    
    int imgcols = inputImage.cols;
    int imgrows = inputImage.rows;
    
//对储存数据的像素点进行处理,黑色代表1,白色代表0

    std::cout << "按行解码后得到的数据:" << endl;

 for (int i = 0; i < imgcols ; i+= one_block_width)
    {

        for (int j = 0; j < imgrows ; j+= one_block_width)
        {
            if (i < anchor_size + left_blank && j < anchor_size + left_blank);
            
            else 
                if(i >= imgcols - anchor_size - left_blank && j < anchor_size + left_blank);
            
                else 
                    if (i < anchor_size + left_blank && j >= imgrows - anchor_size - left_blank);
           
                    else 
                        if (i < left_blank);
           
                        else 
                            if (i >= imgcols - left_blank);
            
                            else 
                                if (j < left_blank);
            
                                else 
                                    if (j >= imgrows - left_blank);
            
                                    else {
                
                                        if (inputImage.at<Vec3b>(i,j)[0] == 0 && inputImage.at<Vec3b>(i,j)[1] == 0 && inputImage.at<Vec3b>(i,j)[2] == 0)
                
                                        {
                    
                                            std::cout << "1";
                                            bin << "1";
                
                                        }
                
                                        else 
                                            if ((inputImage.at<Vec3b>(i,j)[0] == 255 && inputImage.at<Vec3b>(i,j)[1] == 255 && inputImage.at<Vec3b>(i,j)[2] == 255))
                
                                            {
                    
                                                std::cout << "0";
                                                bin << "0";
                
                                            }
            
                                    }
        
        }

        std::cout << endl;
   
 }

    bin.close();

    imshow("处理的图片",inputImage);
    waitKey(0);

    return;

}

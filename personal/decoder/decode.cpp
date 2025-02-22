#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void display(Mat& im, Mat& bbox)
{
    int n = bbox.rows;
    for (int i = 0; i < n; i++)
    {
        line(im, Point2i(bbox.at<float>(i, 0), bbox.at<float>(i, 1)), Point2i(bbox.at<float>((i + 1) % n, 0), bbox.at<float>((i + 1) % n, 1)), Scalar(255, 0, 0), 3);
    }
    imshow("Result", im);
}

int main(int argc, char* argv[])
{
    // Read image
    Mat inputImage;
    if (argc > 1)
        inputImage = imread(argv[1]);
    else
        inputImage = imread("F:/source/2.png");
//初步完成框架的架构,解码部分需进一步考虑
    QRCodeDetector qrDecoder = QRCodeDetector::QRCodeDetector();

    Mat bbox, rectifiedImage;

    std::string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);
    if (data.length() > 0)
    {
        cout << "Decoded Data : " << data << endl;

        display(inputImage, bbox);
        rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
        imshow("Rectified QRCode", rectifiedImage);

        waitKey(0);
    }
    else
        cout << "QR Code not detected" << endl;
}

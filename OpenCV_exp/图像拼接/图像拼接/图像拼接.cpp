#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
#include<string>
using namespace std;
using namespace cv;
//未成功实现
int main(int argc, int **argv)
{
	vector<string> files;
	string floder = "E:/OpenCV_image";
	glob("E:/OpenCV_image", files);
	vector<Mat> images;
	for (int i = 0; i < files.size(); i++) {
		printf("image name is %s\n", files[i].c_str());
		images.push_back(imread(files[i]));
		//imshow(files[i].c_str(), imread(files[i]));
		}
	//设置拼接模式
	Mat result1;
	Stitcher::Mode mode = Stitcher::PANORAMA;
	Ptr<Stitcher> stitcher = Stitcher::create(mode);
	//拼接方式-多通道融合
	auto blenter = detail::Blender::createDefault(detail::Blender::MULTI_BAND);
	stitcher->setBlender(blenter);
	Stitcher::Status status = stitcher->stitch(images, result1);
	if (status != Stitcher::OK)
	{
		cout << "can't stitch image errorInfo:" << int(status) << endl;
		return EXIT_FAILURE;
	}
	imwrite("E:/OpenCV_image/result1.jpg", result1);
	//imshow("拼接图像", result1);
	//waitKey(0);
	return 0;
}


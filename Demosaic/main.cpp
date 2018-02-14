#include "opencv2\opencv.hpp"

#include "utils.h"
#include "demosaic.h"

/*
The main function
*/
int main() {

	std::string path = "D:\\Subjects\\COMP 691 - Computer Vision\\Assignments\\assignment1_sample_images\\";

	std::string pathBW = path + "oldwell_mosaic.png";
	std::string pathOriginal = path + "oldwell.jpg";

	cv::Mat bw = cv::imread(pathBW, CV_LOAD_IMAGE_UNCHANGED);
	cv::Mat original = cv::imread(pathOriginal, CV_LOAD_IMAGE_UNCHANGED);

	if (bw.empty()) {
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	cv::Size size = bw.size();
	cv::Mat colored_bayer, colored_freeman;
	cv::Mat diff_bayer, diff_freeman;
	cv::Mat temp_sum, temp_img, temp_img_filtered;
	cv::Mat mask;

	//////////////////////////////////////		GREEN
	cv::Mat g_channel = cv::Mat::zeros(size, CV_8UC1);
	mask = getMask(size, 'g');

	temp_img = cv::Mat::zeros(size, CV_8UC1);
	bw.copyTo(temp_img, mask);

	float g_kernel_data[] = { 0,1. / 4,0,1. / 4,0,1. / 4,0,1. / 4,0 };
	cv::Mat g_kernel = cv::Mat(cv::Size(3, 3), CV_32F, (g_kernel_data));

	cv::filter2D(temp_img, temp_img_filtered, -1, g_kernel);

	cv::add(temp_img, temp_img_filtered, g_channel);


	////////////////////////////////////////////	BLUE
	cv::Mat b_channel = cv::Mat::zeros(size, CV_8U);
	mask = getMask(size, 'b');

	temp_img = cv::Mat::zeros(size, CV_8U);
	bw.copyTo(temp_img, mask);

	float b_kernel_data1[] = { 1. / 4, 0, 1. / 4,0,0,0,1. / 4,0,1. / 4 };
	cv::Mat b_kernel = cv::Mat(cv::Size(3, 3), CV_32F, (b_kernel_data1));

	// calc B at R
	cv::filter2D(temp_img, temp_img_filtered, -1, b_kernel);

	cv::add(temp_img, temp_img_filtered, temp_sum);

	float b_kernel_data2[] = { 0,1. / 4,0,1. / 4,0,1. / 4,0,1. / 4,0 };
	b_kernel = cv::Mat(cv::Size(3, 3), CV_32F, (b_kernel_data2));

	// calc B at G
	cv::filter2D(temp_sum, temp_img_filtered, -1, b_kernel);

	cv::add(temp_img_filtered, temp_sum, b_channel);


	////////////////////////////////////////////	RED
	cv::Mat r_channel = cv::Mat::zeros(size, CV_8U);
	mask = getMask(size, 'r');

	temp_img = cv::Mat::zeros(size, CV_8U);
	bw.copyTo(temp_img, mask);

	float r_kernel_data1[] = { 1. / 4, 0, 1. / 4,0,0,0,1. / 4,0,1. / 4 };
	cv::Mat r_kernel = cv::Mat(cv::Size(3, 3), CV_32F, (r_kernel_data1));

	// calc R at B
	cv::filter2D(temp_img, temp_img_filtered, -1, r_kernel);

	cv::add(temp_img, temp_img_filtered, temp_sum);

	float r_kernel_data2[] = { 0,1. / 4,0,1. / 4,0,1. / 4,0,1. / 4,0 };
	r_kernel = cv::Mat(cv::Size(3, 3), CV_32F, (r_kernel_data2));

	// calc R at G
	cv::filter2D(temp_sum, temp_img_filtered, -1, r_kernel);

	cv::add(temp_img_filtered, temp_sum, r_channel);

	///////////////////////////////////////////////

	// calc the bayer image
	colored_bayer = demosaic_bayer(b_channel, g_channel, r_channel);
	diff_bayer = calc_diff(original, colored_bayer);


	// calc the freeman image
	colored_freeman = demosaic_freeman(b_channel, g_channel, r_channel);
	diff_freeman = calc_diff(original, colored_freeman);



	cv::imwrite("d:\\colored_bayer.png", colored_bayer);
	cv::imwrite("d:\\colored_freeman.png", colored_freeman);

	cv::imshow("colored bayer", colored_bayer);
	cv::imshow("colored freeman", colored_freeman);
	cv::imshow("diff bayer", diff_bayer);
	cv::imshow("diff freeman", diff_freeman);
	cv::imshow("original", original);
	cv::waitKey();

	return EXIT_SUCCESS;
}
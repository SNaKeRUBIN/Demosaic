#ifndef UTILS_H
#define UTILS_H

#include "opencv2\opencv.hpp"

	cv::Mat calc_diff(const cv::Mat original, const cv::Mat colored);

	cv::Mat getMask(cv::Size size, char channel);

#endif //UTILS_H

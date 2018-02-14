#ifndef DEMOSAIC_H
#define DEMOSAIC_H

#include "opencv2\opencv.hpp"

cv::Mat demosaic_freeman(const cv::Mat b, const cv::Mat g, const cv::Mat r);

cv::Mat demosaic_bayer(const cv::Mat b, const cv::Mat g, const cv::Mat r);


#endif //DEMOSAIC_H

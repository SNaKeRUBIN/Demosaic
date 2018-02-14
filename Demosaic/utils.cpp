#include "utils.h"


/*
Returns the image of the squared differences between the original
and reconstructed values for each pixel, over the three color channels.

@param original The original colored image
@param colored The reconstructed image using demosaicing

@return Returns the image of squared differences
*/
cv::Mat calc_diff(const cv::Mat original, const cv::Mat colored) {

	cv::Mat mat_diff;
	cv::Mat original_new, colored_new;

	original.copyTo(original_new);
	colored.copyTo(colored_new);

	mat_diff = original_new - colored_new;
	mat_diff = mat_diff.mul(mat_diff);

	return mat_diff;
}


/*
Returns the mask appropriate to the channel required.
We follow the RGGB pattern

@param size The size of the mask
@param channel The channel whose respective mask we need

@return Returns the mask
*/
cv::Mat getMask(cv::Size size, char channel) {

	cv::Mat mask = cv::Mat::zeros(size, CV_8UC1);

	for (int x = 0; x < size.width; x++) {
		for (int y = 0; y < size.height; y++) {

			switch (channel) {
			case 'g':
				if (x % 2 != 0 && y % 2 == 0) {
					mask.at<uchar>(y, x) = 1;
				}
				else if (x % 2 == 0 && y % 2 != 0) {
					mask.at<uchar>(y, x) = 1;
				}
				break;

			case 'b':
				if (x % 2 != 0 && y % 2 != 0) {
					mask.at<uchar>(y, x) = 1;
				}
				break;

			case 'r':

				if (x % 2 == 0 && y % 2 == 0) {
					mask.at<uchar>(y, x) = 1;
				}
				break;
			}
		}
	}

	return mask;
}

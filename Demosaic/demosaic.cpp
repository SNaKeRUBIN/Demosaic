#include "demosaic.h"


/*
Returns the demosaiced image using Bill Freeman proposed method.
Since the G channel is sampled at a higher rate than the R and B channels,
one might expect interpolation to work better for G values.
Then it would make sense to use the interpolated G channel to modify the interpolated R and B channels.

@param b The blue channel
@param g The green channel
@param r The red channel

@return Returns the demosaiced image over three channels
*/
cv::Mat demosaic_freeman(const cv::Mat b, const cv::Mat g, const cv::Mat r) {

	cv::Mat colored;
	cv::Mat b_new, g_new, r_new;
	std::vector<cv::Mat> channels;

	b.copyTo(b_new);
	g.copyTo(g_new);
	r.copyTo(r_new);

	b_new.convertTo(b_new, CV_32F);
	g_new.convertTo(g_new, CV_32F);
	r_new.convertTo(r_new, CV_32F);

	b_new = b_new - g_new;
	r_new = r_new - g_new;

	cv::medianBlur(b_new, b_new, 3);
	cv::medianBlur(r_new, r_new, 3);

	b_new = b_new + g_new;
	r_new = r_new + g_new;

	b_new.convertTo(b_new, CV_8U);
	g_new.convertTo(g_new, CV_8U);
	r_new.convertTo(r_new, CV_8U);

	channels.push_back(b_new);
	channels.push_back(g_new);
	channels.push_back(r_new);

	cv::merge(channels, colored);

	return colored;
}

/*
Returns the demosaiced image using Bayer proposed method.

@param b The blue channel
@param g The green channel
@param r The red channel

@return Returns the demosaiced image over three channels
*/
cv::Mat demosaic_bayer(const cv::Mat b, const cv::Mat g, const cv::Mat r) {

	cv::Mat colored;
	cv::Mat b_new, g_new, r_new;
	std::vector<cv::Mat> channels;

	b.copyTo(b_new);
	g.copyTo(g_new);
	r.copyTo(r_new);

	channels.push_back(b_new);
	channels.push_back(g_new);
	channels.push_back(r_new);

	cv::merge(channels, colored);

	return colored;
}
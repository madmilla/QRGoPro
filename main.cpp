#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <zbar.h>  
#include <iostream>  

/**
 * Author: L. Veenendaal
 * Test code for using a GoPro Hero 3 to read QR codes.
 */
 
int main()
{	// To use this connect with the camera over wifi and check what the ipaddres is of the gateway or router.
	// Use that ip here.
	cv::VideoCapture cap( "http://10.5.5.9:8080/live/amba.m3u8" );
	cv::namedWindow( "GoPro" ); // Test feed.
	cv::Mat frame;
	cv::Mat grey;

	if(!cap.isOpened()){  // If we can open it kill it.
		std::cout << "Cannot open live feed of GoPro!" << std::endl;
		return -1;
	}

	//zBar can be used to detect barcodes.
	zbar::ImageScanner scanner;   
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);   
	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeigth = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	std::cout << "FS: " << dWidth << " x " << dHeigth << std::endl;
	cv::namedWindow("Barcode", CV_WINDOW_AUTOSIZE);

	do {
		cap >> frame;
		cv::imshow( "GoPro", frame );
		bool bSucces = cap.read(frame);
		if(!bSucces){
			std::cout << "Frame unreadable of were going to ignore it." << std::endl; 
		}
		cvtColor(frame,grey,CV_BGR2GRAY);
		int width = frame.cols;
		int height = frame.rows;
		uchar *raw = (uchar *)grey.data;

		//Wrap image data
		zbar::Image image(width, height, "Y800", raw, width * height);
		// scan for those fancy barcodes
		int n = scanner.scan(image);
		// Take out the results

		// If the scanner finds something so it on the barcade feed.
		for(zbar::Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol){
			std::vector<cv::Point> vp;
			std::cout << "Decoded " << symbol->get_type_name() << " symbol " << symbol->get_data() << '" ' << std::endl;
			int n = symbol->get_location_size();
			for(int i=0;i<n;i++){
				vp.push_back(cv::Point(symbol->get_location_x(i),symbol->get_location_y(i)));
			}
			cv::RotatedRect r = minAreaRect(vp);
			cv::Point2f pts[4];
			r.points(pts);
			for(int i=0;i<4;i++){
				line(frame,pts[i], pts[(i+1)%4], cv::Scalar(255,0,0),3);
			}
		}
		cv::imshow( "Barcode", frame );

	} while ( cv::waitKey( 30 ) < 0 );
 
return 0;

} 
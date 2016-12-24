#include <cv.h>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>

using namespace cv;

int main( int argc, char** argv )
{
    if( argc != 2 )
    {
        printf( " No image data \n " );
        return -1;
    }
    char* imageName = argv[1];

    Mat image;
    image = imread( imageName, 1 );

    if( !image.data )
    {
        printf( " No image data \n " );
        return -1;
    }

    Mat hsv_image;
    cvtColor( image, hsv_image, CV_BGR2HSV );

    //cout << image << endl;
    //convert back here to call imwrite and imshow
    cvtColor(hsv_image, hsv_image, CV_HSV2BGR);

    imwrite( "./ti1_HSV_Image.jpg", hsv_image );

    namedWindow( imageName, CV_WINDOW_AUTOSIZE );
    namedWindow( "HSV image", CV_WINDOW_AUTOSIZE );

    imshow( imageName, image );
    imshow( "HSV image", hsv_image );


    waitKey(0);

    return 0;
}

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;


int main( int argc, char* argv[])
{

    if (argc < 3)
    {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    Mat I, J;
    if( argc == 4 && !strcmp(argv[3],"G") )
        I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    else
        I = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    if (!I.data)
    {
        cout << "The image" << argv[1] << " could not be loaded." << endl;
        return -1;
    }

    int cycleWith = 0; // convert our input string to number - C++ style
    stringstream s;
    s << argv[2];
    s >> cycleWith;
    if (!s || !cycleWith)
    {
        cout << "Invalid number entered for dividing. " << endl;
        return -1;
    }

    uchar hue_table[256];
    for (int i = 0; i < 256; ++i)
    {
        if (i<180) {
            hue_table[i] = (uchar)((cycleWith * i) % 180);
        }
        else {
            hue_table[i] = (uchar)(0);
        }
    }

    Mat lookUpTable(1, 256, CV_8UC3);
    uchar* p = lookUpTable.data;
    for( int i = 0; i < 256; ++i)
    {
        p[3*i] = hue_table[i];
        p[3*i+1] = i;
        p[3*i+2] = i;
    }

    Mat hsv_image, LUT_hsv_image;

    cvtColor( I, hsv_image, CV_BGR2HSV );

    LUT(hsv_image, lookUpTable, LUT_hsv_image);

    cvtColor(LUT_hsv_image, J, CV_HSV2BGR);

    imwrite( "./ti1_hue_cycle_Image.jpg", J );

    namedWindow( "Original", CV_WINDOW_AUTOSIZE );
    namedWindow( "Hue Cycled", CV_WINDOW_AUTOSIZE );

    imshow( "Original", I );
    imshow( "Hue Cycled", J );

    waitKey(0);

    return 0;
}

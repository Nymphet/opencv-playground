#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;


int main( int argc, char* argv[])
{

    if (argc < 5)
    {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    Mat I, J;
    // if( argc == 4 && !strcmp(argv[3],"G") )
    //     I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    // else
    I = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    if (!I.data)
    {
        cout << "The image" << argv[1] << " could not be loaded." << endl;
        return -1;
    }

    int cycleHueWith = 0; // convert our input string to number - C++ style
    int cycleSaturationWith = 0;
    int cycleValueWith = 0;
    stringstream h,s,v;
    h << argv[2];
    h >> cycleHueWith;
    s << argv[3];
    s >> cycleSaturationWith;
    v << argv[4];
    v >> cycleValueWith;
    if (!s || !v || !h || !cycleHueWith || !cycleSaturationWith || !cycleValueWith)
    {
        cout << "Invalid number entered for dividing. " << endl;
        return -1;
    }

    uchar hue_table[256];
    for (int i = 0; i < 256; ++i)
    {
        if (i<180) {
            hue_table[i] = (uchar)((cycleHueWith * i) % 180);
        }
        else {
            hue_table[i] = (uchar)(0);
        }
    }

    uchar saturation_table[256];
    for (int i = 0; i < 256; ++i)
    {
            saturation_table[i] = (uchar)((cycleSaturationWith * i) % 256);
    }

    uchar value_table[256];
    for (int i = 0; i < 256; ++i)
    {
            value_table[i] = (uchar)((cycleValueWith * i) % 256);
    }

    Mat lookUpTable(1, 256, CV_8UC3);
    uchar* p = lookUpTable.data;
    for( int i = 0; i < 256; ++i)
    {
        p[3*i] = hue_table[i];
        p[3*i+1] = saturation_table[i];
        p[3*i+2] = value_table[i];
    }

    Mat hsv_image, LUT_hsv_image;

    cvtColor( I, hsv_image, CV_BGR2HSV );

    LUT(hsv_image, lookUpTable, LUT_hsv_image);

    cvtColor(LUT_hsv_image, J, CV_HSV2BGR);

    imwrite( "./cycle_Image.jpg", J );

    namedWindow( "Original", CV_WINDOW_AUTOSIZE );
    namedWindow( "Cycled", CV_WINDOW_AUTOSIZE );

    imshow( "Original", I );
    imshow( "Cycled", J );

    waitKey(0);

    return 0;
}

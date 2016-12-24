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

    int cycleBlueWith = 0; // convert our input string to number - C++ style
    int cycleGreenWith = 0;
    int cycleRedWith = 0;
    stringstream h,s,v;
    h << argv[2];
    h >> cycleBlueWith;
    s << argv[3];
    s >> cycleGreenWith;
    v << argv[4];
    v >> cycleRedWith;
    if (!s || !v || !h || !cycleBlueWith || !cycleGreenWith || !cycleRedWith)
    {
        cout << "Invalid number entered for dividing. " << endl;
        return -1;
    }

    uchar blue_table[256];
    for (int i = 0; i < 256; ++i)
    {
            blue_table[i] = (uchar)((cycleBlueWith * i) % 256);
    }

    uchar green_table[256];
    for (int i = 0; i < 256; ++i)
    {
            green_table[i] = (uchar)((cycleGreenWith * i) % 256);
    }

    uchar red_table[256];
    for (int i = 0; i < 256; ++i)
    {
            red_table[i] = (uchar)((cycleRedWith * i) % 256);
    }

    Mat lookUpTable(1, 256, CV_8UC3);
    uchar* p = lookUpTable.data;
    for( int i = 0; i < 256; ++i)
    {
        p[3*i] = blue_table[i];
        p[3*i+1] = green_table[i];
        p[3*i+2] = red_table[i];
    }


    LUT(I, lookUpTable, J);

    imwrite( "./BGR_cycle_Image.jpg", J );

    namedWindow( "Original", CV_WINDOW_AUTOSIZE );
    namedWindow( "Cycled", CV_WINDOW_AUTOSIZE );

    imshow( "Original", I );
    imshow( "Cycled", J );

    waitKey(0);

    return 0;
}

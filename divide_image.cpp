#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

static void help()
{
    cout
        << "\n--------------------------------------------------------------------------" << endl
        << "This program shows how to scan image objects in OpenCV (cv::Mat). As use case"
        << " we take an input image and divide the native color palette (255) with the "  << endl
        << "input. Shows C operator[] method, iterators and at function for on-the-fly item address calculation."<< endl
        << "Usage:"                                                                       << endl
        << "./howToScanImages imageNameToUse divideWith [G]"                              << endl
        << "if you add a G parameter the image is processed in gray scale"                << endl
        << "--------------------------------------------------------------------------"   << endl
        << endl;
}



int main( int argc, char* argv[])
{
    help();
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

    uchar table[256];
    for (int i = 0; i < 256; ++i)
       table[i] = (uchar)(cycleWith * (i/cycleWith));

    const int times = 100;

    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.data;
    for( int i = 0; i < 256; ++i)
        p[i] = table[i];

    LUT(I, lookUpTable, J);

    imwrite( "./ti1_divide_Image.jpg", J );

    namedWindow( "Original", CV_WINDOW_AUTOSIZE );
    namedWindow( "divide image", CV_WINDOW_AUTOSIZE );

    imshow( "Original", I );
    imshow( "divide image", J );

    waitKey(0);

    return 0;
}

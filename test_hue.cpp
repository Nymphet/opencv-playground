#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

int main( int argc, char* argv[])
{
    // int hue_value = 0;
    // stringstream arg1;
    // arg1 << argv[1];
    // arg1 >> hue_value;
    //
    //
    //
    // Mat M(100, 100, CV_8UC3, Scalar(hue_value, 255, 255));
    // //randu(M, Scalar::all(0), Scalar::all(255));
    // //cout << "M = " << endl << " " << M << endl << endl;
    // cvtColor(M, M, CV_HSV2BGR);
    //
    // namedWindow( "Test Image", CV_WINDOW_AUTOSIZE );
    // imshow( "Test Image", M );
    // waitKey(0);

    Mat M(1, 256, CV_8UC3);
    // cout << "M = " << endl << " " <<format( M, "python") << endl << endl;
    uchar hue_table[256];
    for (int i = 0; i < 256; ++i)
    {
        if (i<180) {
            hue_table[i] = (uchar)((3 * i) % 180);
        }
        else {
            hue_table[i] = (uchar)(0);
        }
    }
    uchar* p = M.data;
    for( int i = 0; i < 256; ++i)
    {
        p[3*i] = hue_table[i];
        p[3*i+1] = i;
        p[3*i+2] = i;
    }
    cout << "M = " << endl << " " <<format( M, "python") << endl << endl;

    return 0;
}

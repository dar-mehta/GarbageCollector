#include <iostream>
/*
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv/cv.h>
#include <ctime>
#include <math.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
*/

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d.hpp>


#define TURNRIGHT A
#define TURNLEFT B
#define DRIVE C
#define DRIVESTOP D
#define INCH E
#define COLLECT F
#define TESTFUNCTION G

using namespace cv;
using namespace std;


vector<Point> detectObjects(Mat& input, Mat& output, Mat& output2)
{
    Mat img = input;
    Mat img_gray;
    Mat canny;
    Mat open;
    int reduce = 6;
    Rect cropdim(0, img.rows/reduce - 1, img.cols, (reduce-1)*img.rows/reduce);
    //Hough Transform
    img = img(cropdim);
    int fil_size = 3;
    int open_size = 40;
    int low_thresh = 10;
    int rat = 6;
    int morph_size = 2;
    Mat element = getStructuringElement( MORPH_RECT, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
    cvtColor(img, img_gray, CV_BGR2GRAY);
    GaussianBlur(img_gray, img_gray, Size(fil_size, fil_size), 0 ,0);
    Canny(img_gray, canny, 150,500,3);

    Mat og = canny;

    vector< vector<Point> > contours;
    findContours(canny, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);


    Rect rekt;
    Point center;
    int rad;
    Mat mt = Mat::zeros(canny.rows, canny.cols, CV_8UC1);
    for (int i = 0; i < contours.size(); i++) {
        rekt = boundingRect(contours[i]);
        rad = (rekt.width + rekt.height)/2;
        if (rad > 25) {
            center = Point((rekt.x + (rekt.width / 2)), (rekt.y + (rekt.height / 2)));
            circle(mt, center, rad, Scalar(255,0,0), -5, 8, 0);
            circle(mt, center, rad, Scalar(255,0,0), 8, 8, 0);
            circle(canny, center, rad, Scalar(255,0,0), 1, 8, 0);
        }
    }

    vector< vector<Point> > contours2;
    findContours(mt, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    vector< Point > objects (contours2.size());

    output2 = mt;

    int cnt = 0;
    for (int i = 0; i < contours2.size(); i++) {
        rekt = boundingRect(contours2[i]);
        rad = (rekt.width + rekt.height)/2;
        if (rad > 100) {
            center = Point((rekt.x + (rekt.width / 2)), (rekt.y + (rekt.height / 2)));
            objects[cnt] = center;
            cnt ++;
            circle(img, center, 5, Scalar(0,0,0 ), -5, 8, 0);
        }
        /*
         center = Point((rekt.x + (rekt.width / 2)),rekt.y + (rekt.height / 2));
         rad = (rekt.width + rekt.height)/2;
         cout << rekt << "  /  " << center << endl;
         circle(mt, center, rad, Scalar(255,0,0), 5, 8, 0);
         */
    }

    for (int i = 0; i < objects.size(); i++) {
        if (objects[i].x == 0 && objects[i].y ==0) {
            objects[i].x = 99999;
            objects[i].y = 99999;
        }
    }

    // CV_FILLED fills the connected components found
    output = img;
    //imshow ("dst", dst);
    return objects;
}

Point lowest(vector<Point>& center) {
    Point small = Point(99999,99999);
    for (int i = 0; i < center.size(); i++) {
        if (center[i].y < small.y) {
            small = center[i];

        }
    }
    return small;
}

int main(int argc, char *argv[])
{
    VideoCapture cap(-1);     // get 'any' cam
    Mat frame, out, out2;
    char num;
    vector<Point> obj, point_set;
    Point target, prev_point;
    int point_counter = 0;
    while( cap.isOpened() )   // check if we succeeded
    {
        if ( ! cap.read(frame) )
            break;
        obj = detectObjects(frame, out, out2);

        if (point_counter == 50){
            Point dest = lowest(point_set);
            cout << dest << endl;
            if (abs(dest.x - prev_point.x) < 20){
                if (dest.x >= 2*out.cols/3){
                    cout << "Turn left" << endl;
                } else if (dest.x <= out.cols/3) {
                    cout << "Turn right" << endl;
                } else {
                    cout << "Go straight" << endl;
                }
            }
            prev_point = dest;
            point_set.clear();
            point_counter = 0;
        } else {
            point_set.push_back(lowest(obj));
        }
        point_counter++;
        imshow("lalala",frame);
        imshow("afafaf",out2);
        int k = waitKey(100);
    }
    /*
    Mat in = imread("img/test1.jpg");
    Mat out;
    detectObjects(in, out);
    imshow("out", out);
    waitKey(0);
    return 0;
    */
}

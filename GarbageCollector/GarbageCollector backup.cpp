//
//  main.cpp
//  GarbageCollector
//
//  Created by Dar Mehta on 2016-03-19.
//  Copyright © 2016 Dar Mehta. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

using namespace std;
using namespace cv;

vector<Mat> trainImg;
int trainImg_counter = 0;

void findKeypointsAndDescriptors (Mat, Mat, vector<KeyPoint> &, Mat &, vector<KeyPoint> &, Mat &);
bool wasteMatched (Mat, vector<KeyPoint> &, Mat &, vector<KeyPoint> &, Mat &);

int main(int argc, const char * argv[]) {
    
    Mat robotSrc = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    
    for (int i = 2; i < argc; i++) {
        trainImg.push_back(imread(argv[i]));
    }
    
    vector<KeyPoint> srcKeypoints, trainKeypoints;
    Mat srcDescriptors, trainDescriptors;
    vector<DMatch> matches;
    vector<Point2f> objMatchedPoints, sceneMatchedPoints;
    
    bool waste_classified = false;
    
    while (trainImg_counter < trainImg.size()){
        findKeypointsAndDescriptors(robotSrc, trainImg.at(trainImg_counter), srcKeypoints, srcDescriptors, trainKeypoints, trainDescriptors);
        if (wasteMatched(robotSrc, srcKeypoints, srcDescriptors, trainKeypoints, trainDescriptors))
            cout << "Comparing to Image " << trainImg_counter + 1 << ": Waste Matched" << endl;
        else
            cout << "Comparing to Image " << trainImg_counter + 1 << ": Waste NOT Matched" << endl;
        
        /*Mat img_matches;
        drawMatches( robotSrc, srcKeypoints, trainImg.at(trainImg_counter), trainKeypoints,
                    goodMatches, img_matches, Scalar::all(-1), Scalar::all(-1),
                    vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
        
        imshow(to_string(trainImg_counter), img_matches);*/
        
        //waitKey();
        trainImg_counter++;
    }
    //waitKey();
}

void findKeypointsAndDescriptors (Mat imgO, Mat imgS, vector<KeyPoint> &oK, Mat &oD, vector<KeyPoint> &sK, Mat &sD){
    
    const int minHessian = 1500;
    Ptr<xfeatures2d::SURF> detectorAndExtractor = xfeatures2d::SURF::create(minHessian);
    
    detectorAndExtractor->detectAndCompute(imgO, noArray(), oK, oD);
    detectorAndExtractor->detectAndCompute(imgS, noArray(), sK, sD);
}

bool wasteMatched (Mat robotSrc, vector<KeyPoint> &oK, Mat &oD, vector<KeyPoint> &sK, Mat &sD){
    
    const float lowe_ratio = 0.60;
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("FlannBased");
    vector<Point2f> srcMatched, trainMatched;
    vector<DMatch> goodMatches, matches;
    matcher->match(oD, sD, matches);
    
    for (int i = 0; i < matches.size(); i++){
        if (matches[i].distance < lowe_ratio * matches[i+1].distance){
            goodMatches.push_back(matches[i]);
        }
    }
    
    if (goodMatches.size() > 7){
    for (int i = 0; i < goodMatches.size(); i++){
        srcMatched.push_back(oK[goodMatches[i].queryIdx].pt);
        trainMatched.push_back(sK[goodMatches[i].trainIdx].pt);
    }
    
    Mat homoMat = findHomography(srcMatched, trainMatched, CV_RANSAC);
        
    std::vector< Point2f > src_corners(4);
    src_corners[0] = cvPoint(0,0); src_corners[1] = cvPoint( robotSrc.cols, 0 );
    src_corners[2] = cvPoint( robotSrc.cols, robotSrc.rows ); src_corners[3] = cvPoint( 0, robotSrc.rows );
    std::vector< Point2f > train_corners(4);
    
    perspectiveTransform( src_corners, train_corners, homoMat);
    
    
    line( robotSrc, train_corners[0] , train_corners[1], Scalar(255,255,255), 2 );
    line( robotSrc, train_corners[1] , train_corners[2], Scalar(255,255,255), 2 );
    line( robotSrc, train_corners[2] , train_corners[3], Scalar(255,255,255), 2 );
    line( robotSrc, train_corners[3] , train_corners[0] , Scalar(255,255,255), 2 );
    
    imshow("test", robotSrc);
    waitKey();
    }
     /*Mat img_matches;
     drawMatches( robotSrc, oK, trainImg.at(trainImg_counter), sK,
     goodMatches, img_matches, Scalar::all(-1), Scalar::all(-1),
     vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
     
     imshow("test", img_matches);*/
    
    //cout << "# of matches: " << goodMatches.size() << endl;
    return goodMatches.size() > 5;
}
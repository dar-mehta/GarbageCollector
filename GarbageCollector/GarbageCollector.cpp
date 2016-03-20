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

const float LOWE_RATIO = 0.45;
vector<Mat> img_train;
int train_counter = 0;

void findKeypointsAndDescriptors (Mat, Mat, vector<KeyPoint> &, Mat &, vector<KeyPoint> &, Mat &);
bool wasteMatched (Mat, Mat, vector<KeyPoint> &, Mat &, vector<KeyPoint> &, Mat &);

int main(int argc, const char * argv[]) {
    
    Mat img_robot = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    
    for (int i = 2; i < argc; i++) {
        img_train.push_back(imread(argv[i]));
    }
    
    vector<KeyPoint> obj_train_keys, scene_robot_keys;
    Mat obj_descriptors, scene_descriptors;
    vector<DMatch> matches;
    vector<Point2f> objMatchedPoints, sceneMatchedPoints;
    
    bool waste_classified = false;
    
    while (!waste_classified && train_counter < img_train.size()){
        findKeypointsAndDescriptors(img_train.at(train_counter), img_robot, obj_train_keys, obj_descriptors, scene_robot_keys, scene_descriptors);
        if (wasteMatched(img_train.at(train_counter), img_robot, obj_train_keys, obj_descriptors, scene_robot_keys, scene_descriptors)){
            //cout << "Comparing to Image " << train_counter + 1 << ": Waste Matched" << endl;
            waste_classified = true;
        }else{
            //cout << "Comparing to Image " << train_counter + 1 << ": Waste NOT Matched" << endl;
        }
        /*Mat img_matches;
        drawMatches( robotSrc, srcKeypoints, trainImg.at(trainImg_counter), trainKeypoints,
                    goodMatches, img_matches, Scalar::all(-1), Scalar::all(-1),
                    vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
        
        imshow(to_string(trainImg_counter), img_matches);*/
        
        //waitKey();
        
        train_counter++;
    }
    if (train_counter < 12)
        cout << "Detected Juice Box; Recycle" << endl;
    else if (train_counter < 19)
        cout << "Detected Coke Wrapper; Garbage" << endl;
    else
        cout << "Detected Water Bottle; Recycle" << endl;
    //waitKey();
}

void findKeypointsAndDescriptors (Mat img_object, Mat img_scene, vector<KeyPoint> &obj_keys, Mat &obj_des, vector<KeyPoint> &scene_keys, Mat &scene_des){
    
    const int minHessian = 400;
    Ptr<xfeatures2d::SIFT> detectorAndExtractor = xfeatures2d::SIFT::create(minHessian);
    
    detectorAndExtractor->detectAndCompute(img_object, noArray(), obj_keys, obj_des);
    detectorAndExtractor->detectAndCompute(img_scene, noArray(), scene_keys, scene_des);
}

bool wasteMatched (Mat img_object, Mat img_scene, vector<KeyPoint> &obj_keys, Mat &obj_des, vector<KeyPoint> &scene_keys, Mat &scene_des){
    
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("FlannBased");
    vector<DMatch> goodMatches, matches;
    matcher->match(obj_des, scene_des, matches);
    
    for (int i = 0; i < matches.size(); i++){
        if (matches[i].distance < LOWE_RATIO * matches[i+1].distance){
            goodMatches.push_back(matches[i]);
        }
    }
    
    /*Mat img_matches;
    drawMatches( img_object, obj_keys, img_scene, scene_keys,
                goodMatches, img_matches, Scalar::all(-1), Scalar::all(-1),
                vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    
    vector<Point2f> obj_matched, scene_matched;
        for (int i = 0; i < goodMatches.size(); i++){
            obj_matched.push_back(obj_keys[goodMatches[i].queryIdx].pt);
            scene_matched.push_back(scene_keys[goodMatches[i].trainIdx].pt);
        }
    
        Mat homoMat = findHomography(obj_matched, scene_matched, CV_RANSAC);
        
        std::vector<Point2f> obj_corners(4);
        obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( img_object.cols, 0 );
        obj_corners[2] = cvPoint( img_object.cols, img_object.rows ); obj_corners[3] = cvPoint( 0, img_object.rows );
        std::vector<Point2f> scene_corners(4);
        
        perspectiveTransform( obj_corners, scene_corners, homoMat);
        
        //-- Draw lines between the corners (the mapped object in the scene - image_2 )
        line( img_matches, scene_corners[0] + Point2f( img_object.cols, 0), scene_corners[1] + Point2f( img_object.cols, 0), Scalar(0, 255, 0), 4 );
        line( img_matches, scene_corners[1] + Point2f( img_object.cols, 0), scene_corners[2] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
        line( img_matches, scene_corners[2] + Point2f( img_object.cols, 0), scene_corners[3] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
        line( img_matches, scene_corners[3] + Point2f( img_object.cols, 0), scene_corners[0] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
        
        imshow( "Good Matches & Object detection", img_matches );
        waitKey();*/
     /*Mat img_matches;
     drawMatches( robotSrc, oK, trainImg.at(trainImg_counter), sK,
     goodMatches, img_matches, Scalar::all(-1), Scalar::all(-1),
     vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
     
     imshow("test", img_matches);*/
    
    //cout << "# of matches: " << goodMatches.size() << endl;
    return goodMatches.size() > 2;
}
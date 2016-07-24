# GarbageCollector - RoboHacks
By Can Cui, Stephen Jia, Dar Mehta, Wesley Yue, and Nikhil Keswani

## Project Description
We built a small Rover-like robot that could patrol streets and collect litter. Additionally, it would be able to sort garbage and recycling appropriately.

A laptop would be mounted on the rover which ran a program that uses OpenCV to handle object detection. The laptop would communicate serially through a USB cable to an Arduino board which controlled the motors.

#### Object Detection
The OpenCV Image Processing Library was used to detect objects on the ground. A webcam connected to the laptop would feed image frames into the program; contour detection would then be applied on the image producing a binary image. However, because the contour lines were often discontinuous and difficult to process, we overlayed positive circles on every point of the contour lines thereby producing a blob that represents the object. By finding the center of the blob we would find the location of
the object in the frame of the image.

#### Object Classification
OpenCV was also used to perform image classification to determine whether an object belonged in recycling or garbage. Using reference images, the Object Detection module would crop a detected object from the feed frame, which would then be compared to numerous reference images to determine its identity. 

#### Results
Unfortunately this project was perhaps a little bit too ambitious for a 24 hour hackathon. All the modules were completed but we did not have enough time to integrate them properly. Each module can be found in the following locations:
### Object Detection
main.cpp (in fact this program can be compiled and run from the command line; it will show the center points of objects on a flat, fairly uniform surface from a webcam feed)
### Object Classification 
GarbageCollector folder
### Motor Control and Serial Communication
GarbageCollectorControl folder

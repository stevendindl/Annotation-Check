#include "annotationCheck.h"
#include <iostream>

// using namespace cv;

int main(int argc, char** argv) {
    // Read the image file
    cv::Mat image = cv::imread("/home/steven-dindl/Pictures/profile-pic-ms.jpg");

    // Check for failure
    if (image.empty()) 
    {
    std::cout << "Could not open or find the image" << std::endl;
    std::cin.get(); //wait for any key press
    return -1;
    }

    std::string windowName = "Chunky Cheese"; //Name of the window

    cv::namedWindow(windowName); // Create a window

    imshow(windowName, image); // Show our image inside the created window.

    cv::waitKey(0); // Wait for any keystroke in the window

    cv::destroyWindow(windowName); //destroy the created window

    return 0;
}
#include "../annotationCheck.h"

// using namespace cv;

int main(int argc, char** argv) {

    // Create a JSON object
    nlohmann::json j;
    j["name"] = "Chunky Cheese";
    j["age"] = 5;
    j["isCool"] = true;
    j["hobbies"] = {"eating", "playing", "sleeping"};
    j["address"]["street"] = "123 Cheese Lane";

    printf("Hello World!\n");
    // Print the JSON object
    std::cout << "JSON object:" << std::endl;
    j.dump(4); // Pretty print with an indent of 4 spaces


    std::cout << j.dump(4) << std::endl;


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

    cv::imshow(windowName, image); // Show our image inside the created window.

    cv::waitKey(0); // Wait for any keystroke in the window

    cv::destroyWindow(windowName); //destroy the created window

    return 0;
}
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

fs::path const OUTPUT_DIR = "Ano-Frm"; // Base output directory for extracted frames

/**
 * Extracts frames from a video at a specified FPS and saves them as images in the specified subfolder.
 * 
 * @param videoPath The path to the input video file.
 * @param outputSubDir The subfolder within the output directory where frames will be saved.
 * @param fps The number of frames per second to extract.
 */
void extractFrames(const std::string& videoPath, const std::string& outputSubDir, int fps) {
    // Open the video file
    cv::VideoCapture capture(videoPath);
    if (!capture.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return;
    }

    // Retrieve video properties
    int videoFps = static_cast<int>(capture.get(cv::CAP_PROP_FPS)); // Frames per second of the video
    int frameCount = static_cast<int>(capture.get(cv::CAP_PROP_FRAME_COUNT)); // Total number of frames in the video
    int frameInterval = videoFps / fps; // Interval between frames to extract

    if (frameInterval <= 0) {
        std::cerr << "Error: Specified FPS is greater than the video's FPS." << std::endl;
        return;
    }

    std::cout << "Extracting frames every " << frameInterval << " frames..." << std::endl;

    // Create the output subfolder if it doesn't exist
    fs::path outputDirPath(outputSubDir);
    if (!fs::exists(outputDirPath)) {
        fs::create_directories(outputDirPath);
    }

    // Loop through the video and extract frames
    int frameIndex = 0;
    int extractedFrameCount = 0;
    cv::Mat frame;
    while (capture.read(frame)) {
        // Save the frame if it matches the interval
        if (frameIndex % frameInterval == 0) {
            std::string outputFileName = outputSubDir + "/frame_" + std::to_string(extractedFrameCount) + ".jpg";
            cv::imwrite(outputFileName, frame); // Save the frame as an image
            extractedFrameCount++;
        }
        frameIndex++;
    }

    std::cout << "Extraction complete. Total frames extracted: " << extractedFrameCount << std::endl;

    // Release the video capture object
    capture.release();
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <video_path> <fps> <subfolder_name>" << std::endl;
        return 1;
    }

    std::string videoPath = argv[1];
    int fps = std::stoi(argv[2]);
    std::string subfolderName = argv[3];

    // Construct the full output subfolder path
    fs::path outputSubDir = fs::path(OUTPUT_DIR) / subfolderName;

    // Check if the subfolder already exists
    if (fs::exists(outputSubDir)) {
        std::cerr << "Warning: Subfolder \"" << subfolderName << "\" already exists in the output directory." << std::endl;
        std::cerr << "Do you want to overwrite it? (yes/no): ";
        std::string response;
        std::cin >> response;

        if (response != "yes") {
            std::cerr << "Operation canceled. No frames were extracted." << std::endl;
            return 1;
        }

        // Clear the existing subfolder
        std::cout << "Overwriting existing subfolder..." << std::endl;
        fs::remove_all(outputSubDir);
        fs::create_directories(outputSubDir);
    } else {
        // Create the subfolder if it doesn't exist
        fs::create_directories(outputSubDir);
    }

    // Extract frames from the video
    extractFrames(videoPath, outputSubDir.string(), fps);

    return 0;
}
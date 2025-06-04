#ifndef FINISHED_ANNOTATION_H
#define FINISHED_ANNOTATION_H

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

class OutputData {
    private:
        int frame_count;
        int object_count;
        
    
    public:
        OutputData(int frame_count, int object_count) : frame_count(frame_count), object_count(object_count) {}
        OutputData() : frame_count(0), object_count(0) {} // Default constructor initializes to 0
        
        // Getters
        int getFrameCount() const { return frame_count; }
        int getObjectCount() const { return object_count; }
        // int getVideoFps() const { return video_fps; }
    
        // Incrementers
        void incrementFrameCount() { frame_count++; }
        void incrementObjectCount() { object_count++; }
        
        // Reset function
        void reset() {
            frame_count = 0;
            object_count = 0;
        }
};

struct FileNameComparator {
    bool operator()(const std::string& a, const std::string& b) const {

    }
};

class AnnoChecker {
private:
    // Input & Output directory paths
    fs::path annotation_dir_path; // Path to the folder that is being checked
    fs::path output_dir_path; 

    // Files/directories for input directory
    std::vector<fs::path> annotation_dir_path_files; // Path to the folder that is being checked
    std::priority_queue<fs::path, std::vector<fs::path>, std::greater<fs::path>> annotation_images_paths;

    // Important known info
    std::string image_extension; // Image file extension


    // Files/directories for ouput directory
    std::string log_file = "log.txt"; // Log file for errors
    std::string video_file = "output-video.mp4"; // Output video file
    std::string complied_images_dir = "complied_images"; // Folder for compiled images

    /*
     Complilation input parameters
        Users should be able to set these parameters each time they want to run a new check
        but they should also be able to have default settings, even for the advanced params
    */

    // Complination input parameters
    bool compile_video = true; // Compile images and create video 
    bool create_check_log = true; // Create a log file for errors
    bool create_metrics_log = true; // Create a log file for metrics

    // Advanced complination input parameters 
    int video_fps = 4; // Frames per second for output video
    bool save_video = true; // Save video to output directory
    bool save_images = false; // Save images to output directory


    // Data for output 
    OutputData output_data; // Will be used for video compilation and logging

public:
    // Constructor
    AnnoChecker() = default; // Default constructor

    // Constructor with annotation directory path
    AnnoChecker(fs::path annotation_dir_path) : annotation_dir_path(annotation_dir_path) {
        // Check if the input directory is valid
        if(!validInputDirectory(annotation_dir_path)) {
            std::cerr << "Invalid input directory: " << annotation_dir_path << std::endl;
            throw std::invalid_argument("Invalid input directory");
        }
    }

    bool validInputDirectory(fs::path annotation_dir_path) {
        if(!std::filesystem::is_directory(annotation_dir_path)) {
            return false;
        }
        return true;
    }

    // Setters
    void setCompileVideo(bool compile_video) { this->compile_video = compile_video; }
    void setCreateCheckLog(bool create_check_log) { this->create_check_log = create_check_log; }
    void setCreateMetricsLog(bool create_metrics_log) { this->create_metrics_log = create_metrics_log; }
    void setVideoFps(int video_fps) { this->video_fps = video_fps; }
    void setSaveVideo(bool save_video) { this->save_video = save_video; }
    void setSaveImages(bool save_images) { this->save_images = save_images; }
    void setOutputDirPath(fs::path output_dir_path) { this->output_dir_path = output_dir_path; }
    void setImageExtention(std::string image_extension) { this->image_extension = image_extension; }

    // Mutators
    void addImagePath(fs::path image_path) {
        annotation_images_paths.push(image_path);
    }

    // Getters
    fs::path getAnnotationDirPath() const { return annotation_dir_path; }
    fs::path getOutputDirPath() const { return output_dir_path; }
    auto getAnnotationImagesPaths() const { return annotation_images_paths; }
    std::string getImageExtension() { return image_extension; }

    std::vector<fs::path> getImagePaths() const {
        if(!this->annotation_dir_path.empty()) {
            return {this->annotation_dir_path};
        }
        std::vector<fs::path> imagePaths;
        for (const auto& entry : fs::directory_iterator(annotation_dir_path)) {
            if (fs::is_regular_file(entry.path()) && isImageFile(entry.path())) {
                imagePaths.push_back(entry.path());
            }
        }
        return imagePaths;
    }

    // Check if the path is a valid image file
    bool isImageFile(const fs::path filePath) const {
        std::string extension = filePath.extension().string();
        return (extension == ".jpg" || extension == ".jpeg" || extension == ".png" || 
                extension == ".gif" || extension == ".bmp" || extension == ".tiff" || 
                extension == ".webp");
    }

    // Functions implemented in annotationCheck.cc
    void handleJsonFile(const fs::path& jsonFilePath, AnnoChecker& ac);

};



#endif // FINISHED_ANNOTATION_H
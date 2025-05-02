#ifndef FINISHED_ANNOTATION_H
#define FINISHED_ANNOTATION_H

#include <iostream>
#include <filesystem>
#include <string>
#include <opencv2/opencv.hpp> 

class OutputData {
    private:
        int frame_count;
        int object_count;
        int video_fps = 4; // Frames per second for output video
    
    public:
        OutputData(int frame_count, int object_count) : frame_count(frame_count), object_count(object_count) {}
        OutputData() : frame_count(0), object_count(0) {} // Default constructor initializes to 0
        
        // Getters
        int getFrameCount() const { return frame_count; }
        int getObjectCount() const { return object_count; }
        int getVideoFps() const { return video_fps; }
    
        // Incrementers
        void incrementFrameCount() { frame_count++; }
        void incrementObjectCount() { object_count++; }
    
        // Setters
        void setVideoFps(int fps) { video_fps = fps; }
        
        // Reset function
        void reset() {
            frame_count = 0;
            object_count = 0;
        }
    };

class FinishedAnnotation {
private:
    // Input & Output directory paths
    std::filesystem::path annotation_dir_path; // Path to folder w/ png/json files
    std::string annotation_dir_name;
    std::filesystem::path output_dir_path; 

    // Files/directories for ouput directory
    std::string log_file = "log.txt"; // Log file for errors
    std::string video_file = "output-video.mp4"; // Output video file
    std::string complied_images_dir = "complied_images"; // Folder for compiled images

    // Data for output 
    OutputData output_data; // Will be used for video compilation and logging

public:
    // Constructor
    FinishedAnnotation() = default; // Default constructor
    FinishedAnnotation(const std::filesystem::path& annotation_dir_path, const std::string& annotation_dir_name, const std::filesystem::path& output_dir_path)
        : annotation_dir_path(annotation_dir_path), annotation_dir_name(annotation_dir_name), output_dir_path(output_dir_path) {};







};

#endif // FINISHED_ANNOTATION_H
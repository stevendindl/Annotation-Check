// #include <opencv2/opencv.hpp>
// #include <filesystem>
// #include <fstream>
// #include <iostream>
// #include <string>
// #include <vector>
// #include <map>
// #include <nlohmann/json.hpp> // Include nlohmann/json for JSON parsing

// namespace fs = std::filesystem;

// // Paths
// const std::string annotation_folder = "/home/steven-dindl/Documents/Integer-Scripting/Annotation-Tools/example_files";
// const std::string output_folder = "/home/steven-dindl/Documents/Annotation-Videos";
// const std::string log_file_path = output_folder + "/log.txt";

// // Font settings
// const int font_face = cv::FONT_HERSHEY_SIMPLEX;
// const double font_scale = 1.0;
// const int font_thickness = 2;
// const cv::Scalar font_color(0, 255, 0); // Green

// // Function to get a list of files in a folder
// std::vector<fs::path> get_list_of_files(const std::string& folder_path) {
//     std::vector<fs::path> files;
//     for (const auto& entry : fs::directory_iterator(folder_path)) {
//         if (entry.is_regular_file()) {
//             files.push_back(entry.path());
//         }
//     }
//     std::sort(files.begin(), files.end());
//     return files;
// }

// // Function to process images and JSON files
// std::map<std::string, std::string> get_dict_of_files(const std::string& folder_path, std::ofstream& log) {
//     std::vector<fs::path> files = get_list_of_files(folder_path);
//     std::map<std::string, std::string> file_dict;
//     int object_count = 0;
//     std::vector<std::string> prev_labels;

//     for (const auto& file : files) {
//         if (file.extension() == ".png") {
//             cv::Mat image = cv::imread(file.string());
//             if (image.empty()) {
//                 std::cerr << "Could not open or find the image: " << file << std::endl;
//                 continue;
//             }

//             std::string json_name = file.stem().string() + ".json";
//             fs::path json_file = fs::path(folder_path) / json_name;

//             if (fs::exists(json_file)) {
//                 file_dict[file.string()] = json_file.string();

//                 // Parse JSON file
//                 std::ifstream json_stream(json_file);
//                 nlohmann::json data;
//                 json_stream >> data;

//                 std::vector<std::string> current_labels;
//                 for (const auto& shape : data["shapes"]) {
//                     object_count++;
//                     current_labels.push_back(shape["label"]);

//                     auto points = shape["points"];
//                     cv::Point p1(points[0][0], points[0][1]);
//                     cv::Point p2(points[1][0], points[1][1]);

//                     cv::rectangle(image, p1, p2, cv::Scalar(0, 255, 0), 3); // Draw rectangle
//                 }

//                 // Compare labels
//                 if (current_labels < prev_labels) {
//                     log << file.filename() << " - object disappeared\n";
//                 } else if (current_labels > prev_labels) {
//                     log << file.filename() << " - additional object appeared\n";
//                 }
//                 prev_labels = current_labels;

//                 // Add filename text
//                 cv::putText(image, file.filename().string(), cv::Point(10, 50), font_face, font_scale, font_color, font_thickness);

//                 // Save the modified image
//                 std::string output_path = output_folder + "/" + file.filename().string();
//                 cv::imwrite(output_path, image);
//                 std::cout << "Image saved to " << output_path << std::endl;
//             } else {
//                 file_dict[file.string()] = "";
//                 log << file.filename() << " - not annotated\n";

//                 // Add filename text
//                 cv::putText(image, file.filename().string(), cv::Point(10, 50), font_face, font_scale, font_color, font_thickness);

//                 // Save the modified image
//                 std::string output_path = output_folder + "/" + file.filename().string();
//                 cv::imwrite(output_path, image);
//             }
//         }
//     }

//     log << "Total number of objects in folder: " << object_count << "\n";
//     log << "Total number of images in folder: " << file_dict.size() << "\n";
//     log << "Average number of objects per image: " << (file_dict.size() > 0 ? object_count / file_dict.size() : 0) << "\n";

//     return file_dict;
// }

// // Function to compile images into a video
// void compile_images_to_video(const std::string& image_folder, const std::string& output_video_path, int frame_rate) {
//     std::vector<fs::path> image_files = get_list_of_files(image_folder);
//     if (image_files.empty()) {
//         std::cerr << "No images found in the folder." << std::endl;
//         return;
//     }

//     // Get dimensions of the first image
//     cv::Mat first_image = cv::imread(image_files[0].string());
//     int width = first_image.cols;
//     int height = first_image.rows;

//     // Define the codec and create VideoWriter object
//     cv::VideoWriter video_writer(output_video_path, cv::VideoWriter::fourcc('m', 'p', '4', 'v'), frame_rate, cv::Size(width, height));

//     for (const auto& image_file : image_files) {
//         cv::Mat img = cv::imread(image_file.string());
//         if (!img.empty()) {
//             video_writer.write(img);
//         }
//     }

//     video_writer.release();
//     std::cout << "Video saved to " << output_video_path << std::endl;
// }

// int main() {
//     // Create output directory if it doesn't exist
//     fs::create_directories(output_folder);

//     // Open log file
//     std::ofstream log(log_file_path);
//     if (!log.is_open()) {
//         std::cerr << "Failed to open log file: " << log_file_path << std::endl;
//         return -1;
//     }

//     // Process files
//     std::map<std::string, std::string> files_dict = get_dict_of_files(annotation_folder, log);

//     // Compile images into a video
//     std::string output_video_path = output_folder + "/output_video.mp4";
//     compile_images_to_video(output_folder, output_video_path, 3);

//     log.close();
//     return 0;
// }
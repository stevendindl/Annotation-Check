#include "annotationCheck.h"

using json = nlohmann::json;

void AnnoChecker::handleJsonFile(const fs::path& jsonFilePath, AnnoChecker& ac) {
    json j;
    std::ifstream file(jsonFilePath);
    if (file.is_open()) {
        file >> j;
        file.close(); // Close file, alreay copied to json `j`
        std::string imagePath = j["imagePath"];
        j.erase("imageData"); // Remove the "imageData" key for obj parsing (thousands of unnecessary characters)
        printf("JSON length: %ld\n", j.dump().length());
        
        // Get points from all "shapes" in the JSON
        for (int i = 0; i < j["shapes"].size(); i++) {

            // Check if the shape is a rectangle
            const auto& shape = j["shapes"][i]; 
            if(shape["shape_type"] != "rectangle") {
                std::cerr << "Shape type is not rectangle" << std::endl;
                continue;
            }

            // Check if the shape has exactly 2 points
            if(!shape.contains("points")) {
                std::cerr << "Shape does not contain points" << std::endl;
                continue;
            }
            const auto& points = shape["points"];
            if(points.size() != 2) {
                std::cerr << "There is not two cord pairs is not 2 -- [(x1, y1), (x2, y2)]" << std::endl;
                continue;
            }
            if(points[0].size() != 2 || points[1].size() != 2) {
                std::cerr << "Each pair must have exactly 2 coordinates -- (x, y)" << std::endl;
                continue;
            }
            
            double x1 = points[0][0].get<double>();
            double y1 = points[0][1].get<double>();
            double x2 = points[1][0].get<double>();
            double y2 = points[1][1].get<double>();

            std::cout << "image " << jsonFilePath.filename().replace_extension(ac.getImageExtension()) << std::endl;
            std::string imagePath = jsonFilePath.string();

            // attempt draw to image
            

            std::cout << "Label: " << shape["label"] << std::endl;
            std::cout << "Points: (x1: " << x1 << ", y1: " << y1 << "), (x2: " << x2 << ", y2: " << y2 << ")" <<std::endl;
            std::cout << "------------------------" << std::endl;
        }
        std::cout << "Number of objects: " << j["shapes"].size() << std::endl;
    } else {
        std::cerr << "Could not open the file: " << jsonFilePath << std::endl;
    }
}

// void checkAnnotation(const fs::path& annotation_dir_path) {


// }
#include "annotationCheck.h"
#include <fstream>
#include <vector>

using json = nlohmann::json;

int main(int argc, char *argv[])
{
    // Create instance
    if (argc < 2)
    {
        std::cerr << "Input a dir path into the command line" << std::endl;
        std::cerr << "e.g. -> ./bin/run /home/steven-dindl/Documents/Annotation-Check/prototype/misc/example_files" << std::endl;
        return 0;
    }

    fs::path path = argv[1];
    


    AnnoChecker ac = AnnoChecker(path);

    // Annotation Checker
    fs::path dir = ac.getAnnotationDirPath();

    std::cout << dir << std::endl;
    std::cout << "------------------------" << std::endl;

    try {
        for (const fs::directory_entry &fileEntry : fs::directory_iterator(dir)) {
            if(!fs::is_regular_file(fileEntry.status())){
                std::cerr << "File [" << fileEntry.path().filename() << "] is not a regular file. It's likely a dir." << std::endl;
                std::cout << "------------------------" << std::endl;
                continue;
            }
            if(ac.isImageFile(fileEntry.path())) {
                // Add image path to priority queue
                ac.addImagePath(fileEntry.path());

                ac.setImageExtention(fileEntry.path().extension().string()); // prob shouldny update this repeatedly

                // Attempt to get image's related json path 
                fs::path jsonFilePath = fileEntry.path();
                jsonFilePath.replace_extension(".json");

                // Check if json file exists
                if(!fs::exists(jsonFilePath)) {
                    std::cerr << "JSON file does not exist: " << jsonFilePath << std::endl;
                    std::cout << "------------------------" << std::endl;
                    continue;
                } 

                // If json file exists, handle it
                std::cout << "Image file: " << fileEntry.path() << std::endl;
                std::cout << "JSON file: " << jsonFilePath << std::endl;
                ac.handleJsonFile(jsonFilePath, ac);
                std::cout << "------------------------" << std::endl;
            } 
        }
    } catch (fs::filesystem_error &e) { // file err
      std::cerr << e.what() << std::endl;
    }

    // Print priority queue
    std::cout << "Priority queue:" << std::endl;
    auto annotation_images_paths = ac.getAnnotationImagesPaths();
    while (!annotation_images_paths.empty()) {
        std::cout << annotation_images_paths.top().filename() << std::endl;
        annotation_images_paths.pop();
    }

    


    return 0;
}

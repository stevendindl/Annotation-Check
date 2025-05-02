# Annotation Check Project
## Video compiling for labelme
---
## Project Setup (Conan and Cmake)
### External Libraries Management (Conan)
#### Install Conan
Use pip in the cmd (```pip install conan```) or install from the website (**[here](https://conan.io/downloads)**)

#### Detect Your System Profile
Run the command to have Conan detect your system config:
```bash
conan profile detect --force
```
#### Install Dependencies
Run to install the required dependencies:
Install depenides
```bash
conan install . --output-folder=build --build=missing
```

## Creating a Build System (CMake)
#### Install Cmake
- **Windows**:
  Download the [CMake website](https://cmake.org/download/).
- **Linux Ubuntu/Debian**:
  ```sudo apt install cmake```
- **macOS** (with Homebrew):
  ```brew install cmake```
#### Build Instructions
1. **Configure the Build**:
   ```bash
   cmake -S . -B build
   ```

2. **Compile the Project**:
   ```bash
   cmake --build build
   ```

3. **Run the Executable**:
   ```bash
   ./bin/run
   ```
#### Notes
- After the initial build, you only need to re-run the `cmake --build build` command to recompile changes.
- Ensure that all dependencies are installed using Conan before running the build commands.
---
## Project Structure
### Files and Directories
```bash
Annotation-Check/
├── bin/                     # Output dir for executables
│   └── run   
├── build/                   # Build dir
│   ├── CMakeFiles/            # CMake-generated files
│   └── ...   
├── prototype/               # Test Scripts + png/json files                
├── src/                     # Source code dir
│   ├── main.cc                # Main entry point
│   ├── main2.cc                 
│   ├── annotationCheck.h      # Core functionality
│   └── annotationCheck.cpp    # Functions Implementation  
├── CMakeLists.txt           # CMake config for the build
├── conanfile.txt            # Conan config for libraries
└── README.md                # Project documentation
```
## Development Stack
* Python - Prototyping / quick testing of ideas
* C++ - Core project code
  * Libaries used:
    * opencv: Image processing/editing
    * nlohmann_json: Handing json files
* QT - Frontend desktop framework for C++
---
## Misc dev info 
###### (This section will be clean up)
## Output log
* Box disappears (or exits) frame
* Drastic change of box between frame

## Vibration level
* Possible attribute to track, some sort variance between frames, might have to look into this from a stats approach

## Label me
##### X,y cords of shapes (rectange)
* 0,0 is in top left corner
* points are top_left (x1,y1) & bottom_right (x2,y2)
* calulate others by top_right (x2, y1) & bottom_left (x1, y2)

---
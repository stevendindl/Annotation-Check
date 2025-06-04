# Annotation Check Project
##### Video compiling for labelme
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
### Output log
* Box disappears (or exits) frame
* Drastic change of box between frame

### Vibration level
* Possible attribute to track, some sort variance between frames, might have to look into this from a stats approach

### Label me
##### X,y cords of shapes (rectange)
* 0,0 is in top left corner
* points are top_left (x1,y1) & bottom_right (x2,y2)
* calulate others by top_right (x2, y1) & bottom_left (x1, y2)

### Handling json
It can feel needed to throw a for loop in the mix to iterate through and grab points,
but thats really not needed at all.
##### Take a look at this code
```c++
for (const auto points : j["shapes"][0]["points"]) {
  std::cout << points << std::endl;
  // print type
  std::cout << typeid(points).name() << std::endl;
  std::string str = points.dump();
  std::cout << "String points ! " << str << " !" << std::endl;
}

std::cout << " --- or shapes [0] points ---- " << std::endl;
std::cout << j["shapes"][0]["points"] << std::endl;

std::cout << " --- or or shapes [0] points [0] ---- " << std::endl;
std::cout << j["shapes"][0]["points"][0] << std::endl;

std::cout << " --- or or or shapes [0] points [i][j]---- " << std::endl;
std::cout << j["shapes"][0]["points"][0][0] << std::endl;
std::cout << j["shapes"][0]["points"][0][1] << std::endl;
std::cout << j["shapes"][0]["points"][1][0] << std::endl;
std::cout << j["shapes"][0]["points"][1][1] << std::endl;
```
##### and cross reference with this output
```bash
[1249.6288076473243,894.4240691659]
N8nlohmann16json_abi_v3_11_210basic_jsonISt3mapSt6vectorNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEblmdSaNS0_14adl_serializerES3_IhSaIhEEEE
String points ! [1249.6288076473243,894.4240691659] !
[1365.5468429513153,1078.7297357355635]
N8nlohmann16json_abi_v3_11_210basic_jsonISt3mapSt6vectorNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEblmdSaNS0_14adl_serializerES3_IhSaIhEEEE
String points ! [1365.5468429513153,1078.7297357355635] !
 --- or shapes [0] points ---- 
[[1249.6288076473243,894.4240691659],[1365.5468429513153,1078.7297357355635]]
 --- or or shapes [0] points [0] ---- 
[1249.6288076473243,894.4240691659]
 --- or or or shapes [0] points [i][j]---- 
1249.6288076473243
894.4240691659
1365.5468429513153
1078.7297357355635
```
- For each rect object there is two points, which are pairs, you can even 
ensure that you are only grabbing points from rectangles with an edge case. 
If we wanted todo other objects, we would likely opt for seperate edge cases 
regardless.

---
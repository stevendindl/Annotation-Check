from pathlib import Path
import os
import json
from PIL import Image, ImageDraw, ImageFont
import cv2

# import threading
# mutex = threading.Lock()

# file_name = ""

# Home dir path
home = Path.home()

# User output dir setup
documents_path = home / "Documents"
mkdir_path = documents_path / "Annotation-Videos" / "test-vid"
mkdir_path.mkdir(parents=True, exist_ok=True)

# Create log file if it doesn't exist
log_file_path = mkdir_path / "log.txt"

print(f"Log file path: {log_file_path}")   
log = open(log_file_path, "w")

# PNG / JSON folder setup
annotation_folder = "/home/steven-dindl/Documents/Annotation-Check/Ano-Frm/wrst-vid-12:59-B"

print(f"Annotation folder path: {annotation_folder}")

# Load a font and set the size
font_path = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"  # Path to a TTF font file
font = ImageFont.truetype(font_path, size=50)  

def get_list_of_files(folder_path):
    """
    Get a list of all files in the given folder path.
    """
    return sorted([f for f in Path(folder_path).iterdir() if f.is_file()])

def get_dict_of_files(folder_path):
    """
    Get a dictionary of files where the key is the image file and the value is the corresponding JSON file.
    """
    folder_path = Path(folder_path)  # Convert folder_path to a Path object
    files = get_list_of_files(folder_path)
    file_dict = {}
    object_count = 0
    prev_labels = []
    for file in files:
        # Check if the file is a PNG image
        if file.suffix == ".png" or file.suffix == ".jpg":
            # Open the image file
            image = Image.open(annotation_folder / file)
            draw = ImageDraw.Draw(image)

            # Check for corresponding JSON file
            json_name = (file.stem + ".json");
            json_file = folder_path / json_name
            if json_file.exists():
                file_dict[file] = json_file
                with open(json_file, "r") as f:
                    data = json.load(f)
                currentLabels = []
                # Draw rectangles based on the JSON data
                for shape in data["shapes"]:
                    object_count += 1
                    currentLabels.append(shape["label"])
                    points = shape["points"]
                    if len(points) >= 2:  # Ensure at least 2 points for rectangle
                        (x1, y1), (x2, y2) = points[0], points[1]

                        # Convert to float if needed
                        x1, y1 = float(x1), float(y1)
                        x2, y2 = float(x2), float(y2)

                        left = min(x1, x2)
                        right = max(x1, x2)
                        top = min(y1, y2)
                        bottom = max(y1, y2)

                        print(f"Drawing rectangle: ({left}, {top}) to ({right}, {bottom})")

                        draw.rectangle([(left, top), (right, bottom)], outline="#39FF14", width=1)


                # Save the modified image
                draw.text((10, 10), file.name, fill="#39FF14", font=font)
                output_path = mkdir_path / file.name
                image.save(output_path)
                print(f"Image saved to {output_path}")

                # Compare if the current labels are the same as the previous labels
                if currentLabels < prev_labels:
                    log.write(f"{file.name} - object disappeared\n")
                elif currentLabels > prev_labels:
                    log.write(f"{file.name} - additional object appeared\n")
                
                prev_labels = currentLabels
    
            else:
                file_dict[file] = None
                print(f"JSON file not found for {file.name}")
                log.write(f"{file.name} - not annotated \n")
                draw.text((10, 10), file.name, fill="green", font=font)
                output_path = mkdir_path / file.name
                image.save(output_path)
    log.write(f"Total number of objects in folder: {object_count}\n")
    print(f"Length of file_dict: {len(file_dict)}")

    if object_count > 0 and len(file_dict) > 0:
        log.write(f"Average number of objects per image: {object_count / len(file_dict)}\n") 

    log.write(f"Total number of images in folder: {len(file_dict)}\n")
    return file_dict

def compile_images_to_video(image_folder, output_video_path, frame_rate):
    """
    Compile images from the given folder into a video.
    """
    image_files = sorted([f for f in Path(image_folder).iterdir() if f.is_file() and f.suffix in ['.png', '.jpg', '.jpeg']])
    
    if not image_files:
        print("No images found in the folder.")
        return

    # Get the dimensions of the first image
    first_image = cv2.imread(str(image_files[0]))
    height = first_image.shape[0]
    width = first_image.shape[1]

    # Define the codec and create VideoWriter object
    fourcc = cv2.VideoWriter_fourcc(*'mp4v')
    out = cv2.VideoWriter(str(output_video_path), fourcc, frame_rate, (width, height))

    for image_file in image_files:
        img = cv2.imread(str(image_file))
        out.write(img)

    out.release()
    print(f"Video saved to {output_video_path}")

# Print the dict of files
def print_dict_of_files(file_dict):
    """
    Print the dictionary of files.
    """
    for image_file, json_file in file_dict.items():
        print(f"Image: {image_file}, JSON: {json_file}")



files_dict = get_dict_of_files(annotation_folder)
print_dict_of_files(files_dict)

output_video_path = mkdir_path / "output_video.mp4"
compile_images_to_video(mkdir_path, output_video_path, frame_rate=3)

log.close()
# Split video into frames, 2 frames per second
import cv2
import os
import argparse
import time

mkdir = os.makedirs

out_dir = "Anno-Frames"  # Directory to save the frames
mkdir(out_dir, exist_ok=True)

def split_video(video_path, output_dir, fps=30):
    # Create output directory if it doesn't exist

    os.makedirs(output_dir + "/" + "test", exist_ok=True)

    # Open the video file
    cap = cv2.VideoCapture(video_path)

    # Get the original frames per second (fps) of the video
    original_fps = cap.get(cv2.CAP_PROP_FPS)
    frame_interval = int(original_fps / fps)

    frame_count = 0
    while True:
        ret, frame = cap.read()
        if not ret:
            break

        # Save every nth frame
        if frame_count % frame_interval == 0:
            frame_name = os.path.join(output_dir, f"frame_{frame_count}.jpg")
            cv2.imwrite(frame_name, frame)

        frame_count += 1

    cap.release()
    print(f"Extracted {frame_count} frames to {output_dir}")

# ask for video path from user
print("Please enter the path to the video file:")
video_path = input().strip()
if not os.path.exists(video_path):
    print("Video file does not exist.")
    exit(1)

split_video(video_path, out_dir)


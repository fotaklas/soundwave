# Image and Video Transfer via CSV Encoding

## Overview
This project implements an innovative method for transferring images using a CSV-based encoding approach. The concept is to convert image pixel data into structured numerical values, store them in a CSV file, and reconstruct the image on the receiving end. This technique lays the foundation for future real-time video transmission and has significant applications in robotics and constrained network environments.

## Current Features
- **CSV-Based Image Encoding**: Converts an image into a structured CSV format where each pixel is stored as `R|G|B` values.
- **BMP Image Reconstruction**: Reads the CSV file, processes the pixel values, and reconstructs a high-quality BMP image.
- **Scalability for Video**: The structure allows for sequential frame processing, paving the way for real-time video transmission.
- **Error Handling**: Ensures data integrity by validating CSV input and reporting inconsistencies in pixel formatting.
- **Efficient Memory Management**: Uses optimized data structures to handle large image resolutions without excessive memory consumption.

## Future Development Goals
- **Real-Time Video Transmission**: Extending the system to support multiple frame processing for seamless video streaming.
- **Performance Optimization**: Enhancing encoding/decoding speed for reduced processing time.
- **Compression Techniques**: Implementing efficient compression to minimize bandwidth usage during transmission.
- **Networking Integration**: Developing network-based functionality for remote image and video transfer.

## How It Works
1. The program reads a CSV file where each pixel is stored as `R|G|B` values.
2. It processes the pixel values into a structured 2D array.
3. It reconstructs the image and saves it as a BMP file.
4. This process sets the stage for future expansion into live video streaming.

## Usage
1. Prepare an image and convert it to a CSV format following the expected `R|G|B` structure.
2. Ensure the CSV file adheres to the required resolution and format.
3. Compile and run the program to generate a BMP image.

```sh
 g++ -o image_converter image_converter.cpp
 ./image_converter
```

## Dependencies
- C++ Standard Library
- A CSV-formatted image dataset
- A compiler that supports C++ (e.g., `g++`)

## Author
This project was developed as a groundbreaking approach for efficient image transmission, pushing the boundaries of how images and videos can be shared in resource-constrained environments. Its future potential in robotics and real-time streaming opens exciting possibilities for innovation.


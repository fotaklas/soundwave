#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>

#define WIDTH 1920
#define HEIGHT 1080

// Δομή για ένα pixel
struct Pixel {
    unsigned char r, g, b;
};

// Φόρτωση δεδομένων από αρχείο CSV
bool load_pixel_data(const std::string &filename, std::vector<std::vector<Pixel> > &pixels) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    std::string line;
    int y = 0;
    while (std::getline(file, line) && y < HEIGHT) {
        std::stringstream ss(line);
        std::string token;
        std::vector<Pixel> row;
        int x = 0;
        while (std::getline(ss, token, ',') && x < WIDTH) {
            int r, g, b;
            if (sscanf(token.c_str(), "%d|%d|%d", &r, &g, &b) == 3) {
                Pixel pixel = {static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b)};
                row.push_back(pixel);
            } else {
                std::cerr << "Invalid pixel data at line " << y + 1 << ", column " << x + 1 << std::endl;
                return false;
            }
            x++;
        }
        pixels.push_back(row);
        y++;
    }

    return true;
}

// Αποθήκευση της εικόνας ως BMP
bool save_to_bmp(const std::string &filename, const std::vector<std::vector<Pixel> > &pixels) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return false;
    }

    int width = pixels[0].size();
    int height = pixels.size();

    // Επικεφαλίδα BMP
    unsigned char fileHeader[14] = {
        'B', 'M',             // Signature
        0, 0, 0, 0,           // File size (θα συμπληρωθεί αργότερα)
        0, 0, 0, 0,           // Reserved
        54, 0, 0, 0           // Offset για τα pixel data
    };
    unsigned char infoHeader[40] = {
        40, 0, 0, 0,          // Info header size
        0, 0, 0, 0,           // Width (θα συμπληρωθεί αργότερα)
        0, 0, 0, 0,           // Height (θα συμπληρωθεί αργότερα)
        1, 0,                 // Planes
        24, 0,                // Bits per pixel
        0, 0, 0, 0,           // Compression
        0, 0, 0, 0,           // Image size
        0, 0, 0, 0,           // X pixels per meter
        0, 0, 0, 0,           // Y pixels per meter
        0, 0, 0, 0,           // Colors used
        0, 0, 0, 0            // Important colors
    };

    int rowSize = (3 * width + 3) & (~3); // Padding to multiple of 4 bytes
    int imageSize = rowSize * height;
    int fileSize = 54 + imageSize;

    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;

    infoHeader[4] = width;
    infoHeader[5] = width >> 8;
    infoHeader[6] = width >> 16;
    infoHeader[7] = width >> 24;

    infoHeader[8] = height;
    infoHeader[9] = height >> 8;
    infoHeader[10] = height >> 16;
    infoHeader[11] = height >> 24;

    file.write(reinterpret_cast<const char *>(fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<const char *>(infoHeader), sizeof(infoHeader));

    // Γράφουμε τα pixels από κάτω προς τα πάνω (BMP format)
    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            const Pixel &pixel = pixels[y][x];
            file.put(pixel.b);
            file.put(pixel.g);
            file.put(pixel.r);
        }
        // Padding
        for (int p = 0; p < rowSize - 3 * width; ++p) {
            file.put(0);
        }
    }

    file.close();
    return true;
}

int main() {
    const std::string csv_file = "image_pixels.csv"; // Προκαθορισμένο αρχείο CSV
    const std::string bmp_file = "output.bmp"; // Όνομα εξαγόμενου BMP

    // Δημιουργία πίνακα για τα pixels
    std::vector<std::vector<Pixel> > pixels;

    // Φόρτωση δεδομένων
    if (!load_pixel_data(csv_file, pixels)) {
        return 1;
    }

    // Αποθήκευση ως BMP
    if (!save_to_bmp(bmp_file, pixels)) {
        return 1;
    }

    std::cout << "Image saved as " << bmp_file << std::endl;
    return 0;
}

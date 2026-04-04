#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <thread>
#include <opencv2/opencv.hpp>
#include <mutex>
#define N_THREADS  12
namespace fs = std::filesystem;



std::mutex mutex;
int current_index = 0;
std::vector<std::string> input_files;
std::vector<std::string> input_names;

const int width = 2560, height = 1440, channels = 3;
const size_t expected_bytes = width * height * channels;

void process_image(){
    while(true) {
        mutex.lock();
        int my_i = current_index++;
        mutex.unlock();

        if (my_i >= input_files.size()) {
            break;
        }
        std::string filename = input_files[my_i];
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open " << filename << std::endl;
            continue;
        }
        std::vector<unsigned char> buffer(expected_bytes);
        file.read(reinterpret_cast<char*>(buffer.data()), expected_bytes);

        if (file.gcount() != expected_bytes) {
            std::cerr << "Unexpected size in " << filename
                      << ": got " << file.gcount()
                      << ", expected " << expected_bytes << std::endl;
            continue;
        }

        cv::Mat img(height, width, CV_8UC3, buffer.data());
        cv::Mat flipped, bgr;

        cv::flip(img, flipped, 0); // Flip vertically
        cv::cvtColor(flipped, bgr, cv::COLOR_RGB2BGR); // Convert to BGR

        std::string name = input_names[my_i]; // no extension
        std::string output_file = "dataset/" + name + ".png";

        cv::imwrite(output_file, bgr, {cv::IMWRITE_PNG_COMPRESSION, 9});
        std::cout << "Created " << output_file << std::endl;
    }
}

int main()
{
    std::string path = "frames";
    for (const auto & entry : fs::directory_iterator(path)) {
        input_files.push_back(entry.path().string());
        input_names.push_back(entry.path().stem().string());
    }
    std::cout << "Loaded " <<input_files.size() << " files." << std::endl;
    std::thread *threads[N_THREADS];
    std::cout << "Spawning " << N_THREADS << " threads." << std::endl;
    for (int i = 0; i < N_THREADS; i++) {
        threads[i] = new std::thread(process_image);
    }
    for (int i = 0; i < N_THREADS; i++) {
        threads[i]->join();
    }

}

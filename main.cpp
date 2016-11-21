#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace cv;

namespace fs = boost::filesystem;

// return the filenames of all files that have the specified extension
// in the specified directory and all subdirectories

void retrieve_files(const fs::path& root, const string& ext, vector<string>& ret)
{
    if(!fs::exists(root) || !fs::is_directory(root))
        return;

    fs::recursive_directory_iterator it(root);
    fs::recursive_directory_iterator endit;

    while(it != endit)
    {
        if(fs::is_regular_file(*it) && it->path().extension() == ext)
            ret.push_back(it->path().string());
        ++it;
    }
}

void print_status(int frame_count, int thread_index, bool is_end) {
    if (is_end)
        cout << "finished processing " << frame_count << " frames at thread " << thread_index << endl;
    else
        cout << "processed " << frame_count << " frames at thread " << thread_index << endl;
}

void read_video(string filename, int thread_index) {
    Mat frame, gray_frame, edge_frame;
    int kernel_w = 3;
    int min_thrs = 30, max_thrs = 50;

    cout << "read " << filename << " at thread " << thread_index << endl;
    VideoCapture capture(filename.c_str());

    if( !capture.isOpened() )
        throw "Error when reading steam_avi";

    //namedWindow("w", 1);
    int frame_count = 0;
    for(;;) {
        capture >> frame;
        if (frame.empty())
            break;

        cvtColor(frame, gray_frame, CV_BGR2GRAY);
        blur(gray_frame, edge_frame, Size(3, 3));
        Canny(edge_frame, edge_frame, min_thrs, max_thrs, kernel_w);

        //imshow("w", edge_frame);
        waitKey(1); // waits to display frame
        frame_count++;
        if (frame_count % 1800 == 0)
            print_status(frame_count, thread_index, false);

    }

    print_status(frame_count, thread_index, true);
}

void single_processing(vector<string> &filenames) {
    for (int i = 0; i < filenames.size(); i++) {
        read_video(filenames[i], i);
    }
}

void parallel_processing(vector<string> &filenames) {

#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < filenames.size(); i++) {
            read_video(filenames[i], i);
        }
    }
}

int main() {

    double start_time;

    vector<string> filenames;
    retrieve_files("videos", ".mp4", filenames);

    //start_time = omp_get_wtime();
    //parallel_processing(filenames);
    //start_time = omp_get_wtime() - start_time;
    //cout << "parallel processing takes " << start_time << " seconds." << endl;

    start_time = omp_get_wtime();
    single_processing(filenames);
    start_time = omp_get_wtime() - start_time;
    cout << "single processing takes " << start_time << " seconds." << endl;

    //read_video("5mins.mp4");
    return 0;

}
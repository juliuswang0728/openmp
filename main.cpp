#include <string>
#include <boost/filesystem.hpp>
#include "process.h"

namespace fs = boost::filesystem;
using namespace std;

int main() {
    string filename = "videos/nokia_test_4.mp4";
    process main_process(filename);
    main_process.run();

    return 0;

}
#ifndef FILEIO_H_
#define FILEIO_H_

#include <vector>
using namespace std;


class FileIO {
public:
    FileIO() {}

    vector<char> read_file(const char* filename);
};


#endif // FILEIO_H_

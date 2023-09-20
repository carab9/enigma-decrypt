#include <vector>
#include "FileIO.h"
#include "DataBase.h"
using namespace std;


void DataBase::build(const char* data_file) {
    FileIO file;
    db = file.read_file(data_file);
}

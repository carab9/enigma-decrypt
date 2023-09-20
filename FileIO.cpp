#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "FileIO.h"
using namespace std;


vector<char> FileIO::read_file(const char* filename) {
    vector<char> data;
    string line;

    ifstream file;
    file.open(filename);

    if (file.is_open()) {
        while (getline(file, line)) {
            //cout << line;
            for (const char& c : line) {
                data.push_back(c);
            }
        }
        file.close();
    }

    /*
    for (int i = 0; i < data.size(); i++) {
        cout << data.at(i);
    }
    cout << endl;
    */

    return data;
}
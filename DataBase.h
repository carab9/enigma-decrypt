#ifndef DATABASE_H_
#define DATABASE_H_

#include <vector>
using namespace std;

class DataBase {
private:
    vector<char> db;

public:
    DataBase() {}

    void build(const char* data_file);

    const vector<char>& get_DB() const {
        return db;
    }
};

#endif // DATABASE_H_

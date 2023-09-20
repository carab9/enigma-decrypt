#include <iostream>
#include <vector>
#include "UI.h"
using namespace std;


void UI::display_results(const vector<char>& data) {
    for (int i = 0; i < data.size(); i++) {
        cout << data.at(i);
    }
    cout << endl;
}
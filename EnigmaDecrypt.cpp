// EnigmaDecrypt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "DataBase.h"
#include "Decrypt.h"
#include "UI.h"

using namespace std;

int main()
{
    DataBase db;
    db.build("encrypt.txt");

    Decrypt decrypt;
    decrypt.run(db.get_DB());

    UI ui;
    ui.display_results(decrypt.get_results());

    return 0;
}



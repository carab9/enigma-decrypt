#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include "Decrypt.h"
using namespace std;


Decrypt::Decrypt() {
    encr_1_initial = 0;
    encr_2_initial = 0;
    decr_1_initial = 0;
    decr_2_initial = 0;
    rotor_2_rotate_pos = 0;

    for (int i = 0; i < chars.size(); i++) {
        //cout << i << " " << chars[i] << endl;
        chars_index[chars[i]] = i;
    }
}

void Decrypt::run(const vector<char>& db) {
    tuple<int, int, int, int> atuple;
    int chr_index;
    char chr;
    int index = -1;
    for (int i = 1; i < db.size() - 4; i++) {
        if (chars_index[db[i]] + 4 == chars_index[db[i + 4]]) {
            //cout << "i=" << i << endl;
            if (search_words(db, i, "THE", atuple)) {
                /*
                cout << "Found" << endl;
                cout << get<0>(atuple) << " " << get<1>(atuple) << " "
                    << get<2>(atuple) << " " << get<3>(atuple) << endl;
                */
                index = i;
                break;
            }
        }
    }

    if (index < 0) {
        return;
    }

    encr_1_initial = get<0>(atuple);
    encr_2_initial = get<1>(atuple);
    decr_1_initial = get<2>(atuple);
    decr_2_initial = get<3>(atuple);

    for (int r = 0; r < chars.size(); r++) {
        cout << "Rotor 1 position when Rotor 2 rotates: " << r << endl;
        rotor_2_rotate_pos = r;
        get<0>(atuple) = encr_1_initial;
        get<1>(atuple) = encr_2_initial;
        get<2>(atuple) = decr_1_initial;
        get<3>(atuple) = decr_2_initial;

        // Find the initial roder settings
        int j = index - 1;
        for (j; j >= 0; j--) {
            get<0>(atuple) = (get<0>(atuple) - 1 + chars.size()) % chars.size();
            get<2>(atuple) = (get<2>(atuple) + 1) % chars.size();

            if (get<0>(atuple) == rotor_2_rotate_pos) {
                //cout << "Rotor 2 change" << endl;
                get<0>(atuple) = (get<0>(atuple) - 1 + chars.size()) % chars.size();
                get<3>(atuple) = (get<3>(atuple) + 1) % chars.size();
            }
            /*
            cout << j << " " << get<0>(atuple) << " " << get<1>(atuple) << " "
                << get<2>(atuple) << " " << get<3>(atuple) << endl;
            */
        }
        /*
        cout << get<0>(atuple) << " " << get<1>(atuple) << " "
            << get<2>(atuple) << " " << get<3>(atuple) << endl;
        */

        cout << "Initial rotor 1: " << get<0>(atuple) << endl;
        cout << "Initial rotor 2: " << get<1>(atuple) << endl;

        for (int i = 0; i < db.size(); i++) {
            chr_index = (chars_index[db[i]] + get<2>(atuple) + get<3>(atuple)) % chars.size();
            chr = chars[chr_index];
            /*
            cout << i << " " << get<0>(atuple) << " " << get<1>(atuple) << " "
                << get<2>(atuple) << " " << get<3>(atuple) << " " << db[i] << " " << chr << endl;
            */
            data.push_back(chr);

            get<0>(atuple) = (get<0>(atuple) + 1) % chars.size();
            get<2>(atuple) = (get<2>(atuple) - 1 + chars.size()) % chars.size();

            if (get<0>(atuple) == rotor_2_rotate_pos) {
                //cout << "Rotor 2 change" << endl;
                get<1>(atuple) = (get<1>(atuple) + 1) % chars.size();
                get<3>(atuple) = (get<3>(atuple) - 1 + chars.size()) % chars.size();
            }
        }

        if (valid_decryption()) {
            cout << "Decryption succeeded " << r << endl;
            break;
        }
        else {
            cout << "Decryption failed " << r << endl;
            data.clear();
        }
    }

}

bool Decrypt::search_words(const vector<char>& db, int index, string word, tuple<int, int, int, int>& atuple) {
    get<0>(atuple) = 0;
    get<1>(atuple) = 0;
    get<2>(atuple) = 0;
    get<3>(atuple) = 0;
    int n;
    int m;
    if (chars_index[db[index + 1]] < chars_index[word[0]]) {
        n = chars_index[db[index + 1]] + chars.size() - chars_index[word[0]];
        m = chars_index[word[0]] - chars_index[db[index + 1]];
    }
    else {
        n = chars_index[db[index + 1]] - chars_index[word[0]];
        m = chars_index[word[0]] + chars.size() - chars_index[db[index + 1]];
    }
    //cout << n << " " << m << endl;

    if ((((chars_index[db[index + 2]] + m - 1) % chars.size()) == chars_index[word[1]]) &&
        (((chars_index[db[index + 3]] + m - 2) % chars.size()) == chars_index[word[2]]) &&
        (((chars_index[db[index]] + m + 1) % chars.size()) == chars_index[' ']) &&
        (((chars_index[db[index + 4]] + m - 3) % chars.size()) == chars_index[' '])) {
        // Update the roders to the leading blank space
        get<0>(atuple) = (n - 1 + chars.size()) % chars.size();
        get<2>(atuple) = (m + 1) % chars.size();
        return true;
    }
    else {
        return false;
    }

}

bool Decrypt::valid_decryption()
{
    // Go through decrypted data and check for any invalid words
    int size = data.size();
    int i = 0;
    while (i < size) {
        // Find next word
        string word;
        word += data[i];
        if (data[i] == '\"') {
            i++;
            // The word starts with ", find the closing "
            while (i < size) {
                if (data[i] != '\"') {
                    word += data[i];
                    i++;
                }
                else {
                    // data[i] == '\"'
                    word += data[i];
                    i++;
                    if (i < size) {
                        if (data[i] == ' ') {
                            i++;
                        }
                        else if (is_punct(data[i])) {
                            word += data[i];
                            i++;
                            if (i < size) {
                                if (data[i] != ' ') {
                                    // Should end with a space 
                                    return false;
                                }
                                else {
                                    // data[i] == ' '
                                    i++;
                                }
                            }
                        }
                    }
                    break;
                }
            }
            if (word.size() == 1) {
                // word == "\""
                return false;
            }
        }
        else if (data[i] == '(') {
            i++;
            // The word starts with (, find the closing )
            while (i < size) {
                if (data[i] != ')') {
                    word += data[i];
                    i++;
                }
                else {
                    // data[i] == ')'
                    word += data[i];
                    i++;
                    if (i < size) {
                        if (data[i] == ' ') {
                            i++;
                        }
                        else if (is_punct(data[i])) {
                            word += data[i];
                            i++;
                            if (i < size) {
                                if (data[i] != ' ') {
                                    // Should end with a space 
                                    return false;
                                }
                                else {
                                    // data[i] == ' '
                                    i++;
                                }
                            }
                        }
                    }
                    break;
                }
            }
            if (word.size() == 1) {
                // word == "("
                return false;
            }
        }
        else {
            i++;
            while (i < data.size()) {
                if (data[i] != ' ') {
                    word += data[i];
                    i++;
                }
                else {
                    i++;
                    break;
                }
            }
        }

        if (!valid_word(word)) {
            //cout << "Failed " << word << endl;
            return false;
        }
    }

    return true;
}

bool Decrypt::valid_word(string word)
{
    // Remove leading and trailing spaces in the word
    remove(word.begin(), word.end(), ' ');

    if (word.empty()) {
        return true;
    }

    int hyphen = 0;
    int size = word.size();

    if (isalpha(word[0])) {
        // The word starts with a letter
        for (int i = 1; i < size; i++) {
            if (isalpha(word[i])) {
                continue;
            }
            else if (word[i] == '-') {
                // Only 1 hyphen is allowed
                if (++hyphen > 1) {
                    return false;
                }
                // Hyphen should be surrounded by letters
                if (i - 1 < 0 ||
                    !isalpha(word[i - 1]) ||
                    i + 1 >= size ||
                    !isalpha(word[i + 1])) {
                    return false;
                }
            }
            else if (word[i] == '\'') {
                if (i == size - 1) {
                    // . is the last character
                }
                else if (i == size - 2) {
                    // . is the second last character
                    // Should end with a letter or a punctuation
                    if (!isalpha(word[i + 1]) && !is_punct(word[i + 1])) {
                        return false;
                    }
                }
                else if (i == size - 3) {
                    // . is the third to last character
                    if (!isalpha(word[i + 1]) && !is_punct(word[i + 2])) {
                        return false;
                    }
                }
                else {
                    return false;
                }
            }
            else if (is_punct(word[i])) {
                // Punctutation must be at the end of the word
                if (i != size - 1) {
                    return false;
                }
            }
            else {
                return false;
            }
        }
    }
    else if (isdigit(word[0])) {
        // The word is a number
        for (int i = 1; i < size; i++) {
            if (isdigit(word[i])) {
                continue;
            }
            else if (word[i] == '.') {
                // . should not be the last character
                if (i == size - 1) {
                    return false;
                }
            }
            else if (is_punct(word[i])) {
                // Punctutation must be at the end of the word
                if (i != size - 1) {
                    return false;
                }
            }
            else {
                return false;
            }
        }
    }
    else if (word[0] == '-') {
        // "-" is allowed
        if (word.size() > 1) {
            return false;
        }
    }
    else if (word[0] == '\"') {
        // The word is enclosed by " "
        // optionally followed by a punctuation
        if (size < 3) {
            return false;
        }
        else if (is_punct(word[size - 1])) {
            if (size < 4 || word[size - 2] != '\"') {
                return false;
            }
        }
        else if (word[size - 1] != '\"') {
            return false;
        }
    }
    else if (word[0] == '(') {
        // The word is enclosed by ( )
        // optionally followed by a punctuation
        if (size < 3) {
            return false;
        }
        else if (is_punct(word[size - 1])) {
            if (size < 4 || word[size - 2] != ')') {
                return false;
            }
        }
        else if (word[size - 1] != ')') {
            return false;
        }
    }
    else {
        return false;
    }

    return true;
}

bool Decrypt::is_punct(char chr) {
    // .,;!?
    if (chr == '.' ||
        chr == ',' ||
        chr == ';' ||
        chr == '!' ||
        chr == '?') {
        return true;
    }
    else {
        return false;
    }
}

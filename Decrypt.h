#ifndef DECRYPT_H_
#define DECRYPT_H_

#include <vector>
#include <map>
using namespace std;

class Decrypt {
private:
    vector<char> data;
    int encr_1_initial;
    int encr_2_initial;
    int decr_1_initial;
    int decr_2_initial;
    //const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 .,;!?()-'\"";
    map<char, int> chars_index;
    int rotor_2_rotate_pos;

public:
    Decrypt();

    void run(const vector<char>& db);
    const vector<char>& get_results() const {
        return data;
    }

private:
    bool search_words(const vector<char>& db, int index, string word, tuple<int, int, int, int>& atuple);
    bool valid_decryption();
    bool valid_word(string word);
    bool is_punct(char chr);
};


#endif // DECRYPT_H_

// GUESS WORD GAME
// ===============

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <random>
#include <cstdlib>
#include <ctime>


using namespace std;

// convert string to uppercase
void strToUp (string&);

int main () {
    srand(static_cast<unsigned int>(time(0)));

    // read words from file and populate the vector
    vector<string> wordsVect;
    string word;
    ifstream input{"english-words.txt"};
    if (!input) {
        cerr << "file couldn't be opened!\n";
        exit(EXIT_FAILURE);
    }
    while (input >> word) wordsVect.push_back(word);

    // pick randomly a word
    word = wordsVect[rand() % wordsVect.size()];
    // make uppercase the string
    strToUp(word);
    // create a string with hyphens as the same size of the word
    string blanks(word.size(), '-');


    // allowed number of errors
    const size_t errsMax{3};


    // initial messages
    cout << "Hey! There is a word that you must guess.\n";
    cout << "Note that allowed number of errors is " << errsMax << ".\n";
    cout << "Position of each letter is replaced by a hyphen.\n\n";
    cout << "The Word : " << blanks << endl << endl;


    // errors
    size_t errs{0};
    // input character
    char ch;
    // wrong guessed characters
    string wgc{""};    
    // position of found character
    size_t found;



    // as long as user didn't have errsMax errors continue
    while (errs != errsMax) {
        // get character from user
        cout << "==> ";
        cin >> ch;
        // always convert to uppercase
        if (islower(ch)) ch = toupper(ch);


        // handle some specific situations
        while (1) {
            if (!isalpha(ch)) {
                cout << "ERR: Invalid Input\n\n";
                cout << "==> ";
                cin >> ch;
                // always convert to uppercase
                if (islower(ch)) ch = toupper(ch);
            }

            else if (wgc.find_first_of(ch) != string::npos ||
                        blanks.find_first_of(ch) != string::npos) {
                cout << "ERR: Previously Used Character\n\n";
                cout << "==> ";
                cin >> ch;
                // always convert to uppercase
                if (islower(ch)) ch = toupper(ch);
            }

            else break;
        }

        

        // replace hyphens by user characters if they match
        found = word.find_first_of(ch);
        // if character is ok
        if (found != string::npos) {
            while (found != string::npos) {
                blanks[found] = ch;
                found = word.find_first_of(ch, found + 1);
            }
        }

        // if character is NOT ok
        else {
            wgc += ch;
            ++errs;
        }
        

        cout << blanks << endl;
        cout << "Wrong Guessed Characters : " << wgc << endl << endl;


        // emerge from loop if there was no more hyphen left
        // or user guessed all characters currectly
        if (blanks.find_first_of('-') == string::npos) break;
    }



    // determine whether user won or failed
    if (errs == errsMax) {
        cout << "I'm afraid. You Failed :(\n";
        cout << "The actual word was " << word << "\n\n";
    }
    else cout << "Congratulations! You Succeeded :)\n\n";

    return 0;
}


void strToUp (string& str) {
    for (int i{0}; i < str.size(); ++i) {
        str[i] = toupper(str[i]);
    }
}

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <istream>
#include <vector>
#include <ctime>


using namespace std;


int findString(string& s, string x, bool index = false) {
    if (s.length() < x.length()) return 0;
    int res = 0;
    int length_x = x.length();
    for (int i = 0; i <= s.length() - length_x; i++) {
        if (s[i] == x[0] && s.substr(i, length_x) == x) {
            res++;
            if (index) {
                return i;
            }
        }
    }
    if (index) return -1;
    return res;
}


void task() {
    int k;
    cin >> k;
    ifstream in("file.txt");
    string word;
    int num = 0;
    while (in >> word) {
        if (num == 0) cout << word << endl;
        if (num == 4) cout << word << endl;
        if (num == k - 1) cout << word << endl;
        num++;
    }
    cout << word << endl;
    in.close();
}



void task2() {
    ifstream in("file.txt");
    vector<string> text;
    string word;
    while (in >> word)
        text.push_back(word);
    in.close();
    // a
    int length_text = text.size();
    if (length_text == 1 && text[0].length() >= 2) {
        char a = text[0][0], b = text[0][1];

        if ('9' >= a && a >= '0' && '9' >= b && b >= '0') {
            if ((int(b) - int('0')) % 2 == 0)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
        else
            cout << "No" << endl;
    }
    else if (length_text >= 2) {
        string s = text[0] + text[1];
        char a = s[0], b = s[1];

        if ('9' >= a && a >= '0' && '9' >= b && b >= '0') {
            if ((int(b) - int('0')) % 2 == 0)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
        else
            cout << "No" << endl;
    }
    else {
        cout << "No" << endl;
    }
    // б 
    int count = 0;
    map<char, int> dict;
    bool g = false;
    int temp = 0, temp2 = 0;
    for (string word : text) {


        count += findString(word, "ен") + findString(word, "не");
        if (findString(word, "ура")) g = true;
        for (char alpha : word)
            dict[alpha]++;
    }
    cout << "а: " << dict['а'] << " о: " << dict['о'] << " у: " << dict['у'] << endl;
    // в
    cout << count << endl;
    // г 
    if (g) cout << "YES";
    else cout << "NO";

}


void task3() {
    ifstream in;
    in.open("file.txt");

    ofstream out;
    out.open("file2.txt");

    string word;
    bool t = false;
    int idx;
    while (in >> word) {
        if (!t) {

            idx = findString(word, "о", true);

            if (idx > -1) {
                word.erase(idx, 1);
                t = !t;
            }
        }
        out << word << endl;;
    }
    in.close();
    out.close();
}

void task4() {
    ifstream in;
    in.open("file.txt");
    ofstream out;
    out.open("file2.txt");
    ofstream out2;
    out2.open("file3.txt");
    string word;
    while (in >> word) {
        if (int(word[word.length() - 1] - '0') % 2 == 0)
            out << word << " ";
        else
            out2 << word << " ";
    }
    in.close();
    out.close();
    out2.close();
}

void task5() {

    vector<int> mass(10);
    for (int i = 0; i < 10; i++) {
        mass[i] = rand() % 20 + 1;
        cout << mass[i] << " ";
    }
    cout << endl;

    ofstream out;
    out.open("file2.txt");
    for (int a : mass) {
        out << a << endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    task5();
}

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int find(vector<string> v, string s)
{
    for (int i = 0; i < v.size(); ++i) if (v[i] == s) return i;
    return -1;
}

class coder_decoder
{
private:
    vector<string> w_code;
    vector<string> word;
public:
    void load_dict(istream& in)
    {
        string s;
        while(getline(in, s))
        {
            w_code.push_back(s.substr(0, s.find('-')));
            word.push_back(s.substr(s.find('-')+1));
        }
    }
    string code(const string& s)
    {
        string old_s = s;
        string new_s = "";
        while (old_s.find(' ') != -1)
        {
            int n;
            string w = old_s.substr(0, n = old_s.find(' '));
            if (find(word, w) != -1) new_s += w_code[find(word, w)];
            else new_s += "*";
            old_s = old_s.substr(n+1);
        }
        if (find(word, old_s) != -1) new_s += w_code[find(word, old_s)];
        else new_s += "*";
        return new_s;
    }

    string decode(const string& s)
    {
        string new_s = "";
        int i = 0;
        while (i < s.size())
        {
            string w = s.substr(i, 2);
            if (find(w_code, w) != -1) new_s += word[find(w_code, w)] + " ";
            else new_s += "* ";
            i += 2;
        }
        return new_s;
    }
};

int main()
{
    coder_decoder cd;
    ifstream in("did2.txt");
    cd.load_dict(in);
    cout << cd.code("devil in the details") << endl;
    cout << cd.decode("08090710") << endl;
}

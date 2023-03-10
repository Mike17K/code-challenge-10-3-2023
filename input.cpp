#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <cstring>

using namespace std;

void input(string filename, void (*funct)(string, int));
void handleWords(string word, int i);

int main()
{
    input("05-input-opposite-points-holes.txt", handleWords);
}

void handleWords(string word, int i)
{
    // this function returns the word and their index in the file
    if (word.compare("*") == 0)
        cout << -1 << " ";
    // cout << word << endl;
}

//
void input(string filename, void (*funct)(string, int))
{

    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line))
    {
        string word = "", finalword;
        bool startword = 1, endword = 0;
        int i_word = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ')
            {
                if (startword)
                {
                    startword = 0;
                    endword = 1;
                }
                if (endword)
                {
                    startword = 1;
                    endword = 0;
                    // here in word i have the word i need
                    funct(word, i_word);
                    //
                    i_word++;
                }
                word = "";
            }
            else
            {
                word.push_back(line[i]);
            }
        }
        // cout << endl;
    }
}

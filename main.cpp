#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
void bruteForce(int depth, vector<int> *lengths, vector<vector<int>> *mapOfSnakes);
void getInputs(int *C, int *R, int *S, vector<int> *lengths);
void calcNewArray(int lenth, int C, int R, int d, vector<vector<int>> *mapOfSnakes, vector<vector<int>> *newMapOfSnakes);

int maxScore = 0;
int C = 0, R = 0, S = 0;
vector<vector<int>> map;
int showDepth = 1;

int main()
{

    vector<int> lengths;

    getInputs(&C, &R, &S, &lengths);

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }

    vector<vector<int>> mapOfSnakes = vector<vector<int>>(R, vector<int>(C, 0));
    cout << "=====================" << endl;

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            mapOfSnakes[i][j] = 0;
        }
    }
    cout << "=====================" << endl;

    bruteForce(0, &lengths, &mapOfSnakes);
}

void bruteForce(int depth, vector<int> *lengths, vector<vector<int>> *mapOfSnakes)
{

    if (lengths->size() == 0)
        return;
    /*
    cout << lengths << " size: " << lengths->size() << " Lengths: ";
    for (int i = 0; i < lengths->size(); i++)
    {
        cout << (*lengths)[i] << " ";
    }
    cout << endl;
    //*/

    int lenth = (*lengths)[0];
    // find leagal sq
    vector<vector<int>> leagalSq = vector<vector<int>>(R, vector<int>(C, 0));

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (map[i][j] == -1 || (*mapOfSnakes)[i][j] > 0)
            {
                leagalSq[i][j] = 0;
                continue;
            }
            leagalSq[i][j] = 1;
        }
    }

    char D[4] = {'R', 'D', 'L', 'U'};
    int dirX[4] = {1, 0, -1, 0};
    int dirY[4] = {0, -1, 0, 1};

    //  for sq in leagal sq
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (leagalSq[i][j] == 0)
                continue;

            // for each path direction
            for (int d = 0; d < 4; d++)
            {
                if (showDepth == depth)
                {
                    cout << "Current depth: " << depth << " row: " << (float)i / R << " col: " << (float)j / C << " dir: " << D[d] << " current max: " << maxScore << endl;
                }
                // calc the new arr
                vector<vector<int>> newMapOfSnakes = vector<vector<int>>(R, vector<int>(C, 0));

                calcNewArray(lenth, j, i, d, mapOfSnakes, &newMapOfSnakes);

                ////////////////////////////////////////////////////////////////////
                // call again brute force
                vector<int> lcopy;
                for (int k = 1; k < lengths->size(); k++)
                {
                    lcopy.push_back((*lengths)[k]);
                }

                bruteForce(depth + 1, &lcopy, &newMapOfSnakes);
                // calc score
                int score = 0;
                for (int k1 = 0; k1 < R; k1++)
                {
                    for (int k2 = 0; k2 < C; k2++)
                    {
                        if (newMapOfSnakes[k1][k2] > 0)
                        {
                            // cout << map[k1][k2] << " " << k1 << " " << k2 << endl;
                            score += map[k1][k2];
                        }
                    }
                }

                // store in global
                if (score > maxScore)
                {
                    maxScore = score;
                    cout << "New max score: " << score << endl;
                    cout << "=====================" << endl;
                    for (int i = 0; i < R; i++)
                    {
                        for (int j = 0; j < C; j++)
                        {
                            cout << newMapOfSnakes[i][j] << " ";
                        }
                        cout << endl;
                    }
                    cout << "=====================" << endl;
                    for (int i = 0; i < R; i++)
                    {
                        for (int j = 0; j < C; j++)
                        {
                            if (map[i][j] == -1)
                            {
                                cout << "* ";
                            }
                            else
                            {
                                cout << map[i][j] << " ";
                            }
                        }
                        cout << endl;
                    }
                    cout << "=====================" << endl;
                }
            }
        }
    }
}

void calcNewArray(int length, int c, int r, int d, vector<vector<int>> *mapOfSnakes, vector<vector<int>> *newMapOfSnakes)
{
    char D[4] = {'R', 'D', 'L', 'U'};
    int dirX[4] = {1, 0, -1, 0};
    int dirY[4] = {0, -1, 0, 1};

    int x = c;
    int y = r;
    int l = length;

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            (*newMapOfSnakes)[i][j] = (*mapOfSnakes)[i][j];
        }
    }

    while (1)
    {

        x += dirX[d];
        y += dirY[d];
        if (l == 0)
            return;
        l--;

        // check for overflow
        if (x < 0)
            x = C - 1;
        if (x > C - 1)
            x = 0;

        if (y < 0)
            y = R - 1;
        if (y > R - 1)
            y = 0;

        if ((*mapOfSnakes)[y][x] != 0)
            return;
        if (map[y][x] == -1)
        {
            // entering a loophole
            // find new loopholes
            //  for each one  or random .......
            //
            break;
        }

        (*newMapOfSnakes)[y][x] = length;
    }
}

void getInputs(int *C, int *R, int *S, vector<int> *lengths)
{

    ifstream inFile("00-example.txt"); // Open input file
    if (!inFile)
    { // Check if file was opened successfully
        cerr << "Error opening input file!" << endl;
    }

    int num;
    int i = 0;
    while (inFile >> num)
    { // Read integers from file until end-of-file
        // cout << num << " "; // Print integer to console
        if (i == 0)
        {
            *C = num;
        }
        if (i == 1)
            *R = num;
        if (i == 2)
        {
            *S = num;
            lengths->reserve(*S);
            lengths->clear();
        }
        if (i > 2 && i < 3 + *S)
        {
            // cout << num << endl;
            lengths->push_back(num);
        }
        if (i == 2 + *S && i > 2)
            break;
        i++;
    }

    map = vector<vector<int>>(*C, vector<int>(*R, 0));
    char c;
    i = 0;

    while (inFile >> c)
    { // Read integers from file until end-of-file
        //        cout << c << " "; // Print integer to console

        if (c == '*')
        {
            map[i / *C][i % *C] = -1;
        }
        else
        {
            map[i / *C][i % *C] = (int)c - '0';
        }

        i++;
    };

    inFile.close(); // Close input file
}
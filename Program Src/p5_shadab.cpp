#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

void customDelimeter(string s, vector<char> &res, char delimeter)
{
    int en = 0;
    int len = s.length();
    while (en < len)
    {
        res.push_back(s[en]);
        en = en + 2;
    }
}

void findFirst(char nonTerminal, vector<vector<char>> &productions, map<char, set<char>> &first)
{
    for (int i = 0; i < productions.size(); i++)
    {
        if (productions[i][0] == nonTerminal)
        {
            if (productions[i][1] >= 'A' && productions[i][1] <= 'Z')
            {
                findFirst(productions[i][1], productions, first);
                first[nonTerminal].insert(first[productions[i][1]].begin(), first[productions[i][1]].end());
            }
            else
            {
                first[nonTerminal].insert(productions[i][1]);
            }
        }
    }
}

void findFollow(char nonTerminal, vector<vector<char>> &productions, map<char, set<char>> &follow, map<char, set<char>> &first)
{
    for (int i = 0; i < productions.size(); i++)
    {
        for (int j = 1; j < productions[i].size(); j++)
        {
            if (productions[i][j] == nonTerminal)
            {
                if (j == productions[i].size() - 1)
                {
                    if (productions[i][0] != nonTerminal)
                    {
                        findFollow(productions[i][0], productions, follow, first);
                        follow[nonTerminal].insert(follow[productions[i][0]].begin(), follow[productions[i][0]].end());
                    }
                }
                else
                {
                    if (productions[i][j + 1] >= 'A' && productions[i][j + 1] <= 'Z')
                    {
                        follow[nonTerminal].insert(first[productions[i][j + 1]].begin(), first[productions[i][j + 1]].end());
                    }
                    else
                    {
                        follow[nonTerminal].insert(productions[i][j + 1]);
                    }
                }
            }
        }
    }
}

int main()
{

    vector<vector<char>> productions;

    fstream in;
    in.open("first&follow.txt", ios::in);

    if (!in)
    {
        cerr << "Cannot open the file first_follow.txt" << endl;
        return -1;
    }

    string str;
    while (getline(in, str))
    {
        vector<char> temp;
        customDelimeter(str, temp, ' ');
        productions.push_back(temp);
    }

    for (auto x : productions)
    {
        for (auto y : x)
        {
            cout << y << " ";
        }
        cout << endl;
    }

    cout << "========================" << endl;
    vector<char> nonTerminalsHavingEpsilonInProduction;
    // if there is production containing # add a new production containng all things except #
    for (int i = 0; i < productions.size(); i++)
    {
        for (int j = 1; j < productions[i].size(); j++)
        {
            if (productions[i][j] == '#')
            {
                nonTerminalsHavingEpsilonInProduction.push_back(productions[i][0]);
            }
        }
    }

    vector<vector<char>> tempProductions;

    for (int i = 0; i < nonTerminalsHavingEpsilonInProduction.size(); i++)
    {
        for (int j = 0; j < productions.size(); j++)
        {
            for (int k = 1; k < productions[j].size(); k++)
            {
                if (productions[j][k] == nonTerminalsHavingEpsilonInProduction[i])
                {
                    vector<char> temp;
                    temp.push_back(productions[j][0]);
                    for (int l = 1; l < productions[j].size(); l++)
                    {
                        if (l != k)
                        {
                            temp.push_back(productions[j][l]);
                        }
                    }
                    tempProductions.push_back(temp);
                }
            }
        }
    }

    for (int i = 0; i < tempProductions.size(); i++)
    {
        productions.push_back(tempProductions[i]);
    }
    for (auto x : productions)
    {
        for (auto y : x)
        {
            cout << y << " ";
        }
        cout << endl;
    }
    map<char, set<char>> first;
    for (int i = 0; i < productions.size(); i++)
    {
        findFirst(productions[i][0], productions, first);
    }
    cout << "test" << endl;

    // First of non-terminals
    cout << "\nFirst of non-terminals" << endl;
    for (auto x : first)
    {
        cout << x.first << " : ";
        for (auto y : x.second)
        {
            cout << y << " ";
        }
        cout << endl;
    }

    map<char, set<char>> follow;
    follow[productions[0][0]].insert('$');

    for (int i = 0; i < productions.size(); i++)
    {
        findFollow(productions[i][0], productions, follow, first);
    }

    for (auto x : follow)
    {
        for (auto it : x.second)
        {
            if (it == '#')
            {
                follow[x.first].erase(it);
                break;
            }
        }
    }

    // Follow of non-terminals
    cout << "\nFollow of non-terminals" << endl;
    for (auto x : follow)
    {
        cout << x.first << " : ";
        for (auto y : x.second)
        {
            cout << y << " ";
        }
        cout << endl;
    }

    return 0;
}
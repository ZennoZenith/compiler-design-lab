#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <algorithm>

using namespace std;

int Read(char *str)
{
  int i = 0;
  while (1)
  {
    str[i] = getchar();
    if (str[i] == '\n' || str[i] == '\r')
    {
      str[i] = '\0';
      return i;
    }
    i++;
  }
}

template <typename T>
void printSet(set<T> &set1)
{
  for (auto i = set1.begin(); i != set1.end(); ++i)
    cout << *i << " ";
  cout << endl;
}

template <typename T>
void printVector(vector<T> &set1)
{
  for (auto i = set1.begin(); i != set1.end(); ++i)
    cout << *i << " ";
  // cout << endl;
}

int main()
{
  FILE *filePointer = NULL;
  char ch1, ch2;
  int tempInt;

  filePointer = fopen("LL1.txt", "r");
  if (filePointer == NULL)
  {
    printf("Unable to open LL1.txt\n");
    return 1;
  }

  char startSymbol;
  vector<vector<char>> CFG2D;
  vector<char> tempVector;
  set<char> nonTerminals;
  set<char> terminals;
  map<char, set<char>> firstOf;
  map<char, set<char>> followOf;

  vector<char> LLParseTableColumn;
  vector<char> LLParseTableRow;
  vector<vector<int>> LLParseTable;
  vector<int> tempIntVector;

  fscanf(filePointer, "%c%c", &startSymbol, &ch1);
  printf("Start symbol : %c\n", startSymbol);

  while (fscanf(filePointer, "%c", &ch1) != EOF)
  {
    if (ch1 == '@')
    {
      do
      {
        fscanf(filePointer, "%c", &ch1);
      } while (ch1 != '\n');
      break;
    }
    if (ch1 == '\n')
    {
      CFG2D.push_back(tempVector);
      tempVector.clear();
      continue;
    }

    tempVector.push_back(ch1);
    if (ch1 >= 'A' && ch1 <= 'Z')
      nonTerminals.insert(ch1);
    else if (ch1 == '#')
      continue;
    else
      terminals.insert(ch1);
  }
  // CFG2D.push_back(tempVector);

  // Setting first of map
  char firstChar;
  while (fscanf(filePointer, "%c", &ch1) != EOF)
  {
    if (ch1 == '@')
    {
      do
      {
        fscanf(filePointer, "%c", &ch1);
      } while (ch1 != '\n');
      break;
    }
    firstChar = ch1;
    while (fscanf(filePointer, "%c", &ch1) != EOF)
    {
      if (ch1 == '\n')
        break;
      firstOf[firstChar].insert(ch1);
    }
  }

  // Setting follow of map
  char followChar;
  while (fscanf(filePointer, "%c", &ch1) != EOF)
  {
    if (ch1 == '@')
    {
      do
      {
        fscanf(filePointer, "%c", &ch1);
      } while (ch1 != '\n');
      break;
    }
    followChar = ch1;
    while (fscanf(filePointer, "%c", &ch1) != EOF)
    {
      if (ch1 == '\n')
        break;
      followOf[followChar].insert(ch1);
    }
  }

  // Setting parse table column meta data
  while (fscanf(filePointer, "%c%c", &ch1, &ch2) != EOF)
  {
    LLParseTableColumn.push_back(ch1);
    if (ch2 == '\n')
      break;
  }
  // Setting parse table row meta data
  while (fscanf(filePointer, "%c%c", &ch1, &ch2) != EOF)
  {
    LLParseTableRow.push_back(ch1);
    if (ch2 == '\n')
      break;
  }

  // Clearing @ line
  do
  {
    fscanf(filePointer, "%c", &ch1);
  } while (ch1 != '\n');

  while (fscanf(filePointer, "%d%c", &tempInt, &ch2) != EOF)
  {
    tempIntVector.push_back(tempInt);
    if (ch2 == '\n')
    {
      LLParseTable.push_back(tempIntVector);
      tempIntVector.clear();
    }
  }
  fclose(filePointer);

  cout << "Terminals : ";
  for (auto terminal : terminals)
    cout << terminal << " ";
  cout << endl;
  cout << "Non Terminals : ";
  for (auto nonTerminal : nonTerminals)
    cout << nonTerminal << " ";
  cout << endl;

  cout << "CFG : \n";
  int index = 0;
  for (auto i = CFG2D.begin(); i != CFG2D.end(); ++i)
  {
    auto j = (*i).begin();
    printf("%2d : ", index);
    cout << *j << " --> ";
    ++j;
    for (; j != (*i).end(); ++j)
      cout << *j;
    cout << endl;
    index++;
  }
  cout << endl;

  //* Print first of
  cout << "First of : \n";
  for (auto i = firstOf.begin(); i != firstOf.end(); ++i)
  {
    ch1 = (*i).first;
    printf("%c : ", ch1);
    auto &firstOfCh = firstOf[ch1];
    printSet(firstOfCh);
  }
  cout << endl;

  //* Print first of
  cout << "Follow of : \n";
  for (auto i = followOf.begin(); i != followOf.end(); ++i)
  {
    ch1 = (*i).first;
    printf("%c : ", ch1);
    auto &followOfCh = followOf[ch1];
    printSet(followOfCh);
  }
  cout << endl;

  //* Print LL Parsing table
  int numberOfColumns = LLParseTableColumn.size();
  int numberOfRows = LLParseTableRow.size();

  cout << "LL(1) Parsing table :\n";
  cout << "    ";
  for (int i = 0; i < numberOfColumns; i++)
  {
    printf(" %c  ", LLParseTableColumn[i]);
  }
  cout << endl;
  for (int i = 0; i < numberOfRows; i++)
  {
    printf(" %c  ", LLParseTableRow[i]);
    for (int j = 0; j < numberOfColumns; j++)
    {
      tempInt = LLParseTable[i][j];
      if (tempInt == -1)
        printf("--  ", tempInt);
      else
        printf("%2d  ", tempInt);
    }
    cout << endl;
  }

  cout << endl;

  return 0;
}
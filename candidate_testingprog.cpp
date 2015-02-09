/*
  Candidate Elimination Test program
*/

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <iterator>
#include <set>
#include <map>
#include <iostream>
#include <sstream>
#include <deque>
#include <cmath>
#include <memory.h>
#include <algorithm>
#include <utility>
#include <climits>

typedef long double ld;
typedef long long ll;
#define all(c) c.begin(),c.end()

using namespace std;

int main()
{
  int numberFeatures; //number of features in the dataset
  string data;
  bool example;
  int accuracy = 0, numEx = 0;;

  //hypothesis generated after learning
  vector<int> targetHypothesis(6);

  targetHypothesis[0] = 2;
  targetHypothesis[1] = 2;
  targetHypothesis[2] = 1;
  targetHypothesis[3] = 1;
  targetHypothesis[4] = 2;
  targetHypothesis[5] = 1;

  cin >> numberFeatures; //input the number of features

  vector <int> numberAttributes(numberFeatures); //number of attributes for each feature.
  map <string, int> instance[numberFeatures+1];
  
  for(int i=0; i<numberFeatures; i++)
  {
    cin >> numberAttributes[i];

    for(int j=1; j<=numberAttributes[i]; j++)
    {
      string temp;
      cin>> temp;
      instance[i][temp] = j; //map attribute name with number
    }
  }
  
  instance[numberFeatures]["no"] = 0;
  instance[numberFeatures]["yes"] = 1;

  vector <int> currdata(numberFeatures+1);

  //input the training data
  while( getline(cin, data) )
  {
    if(data.size()==0)
    {
      continue;
    }

    string temp;
    int st = 0, count = 0;
    int len = data.size();
    numEx++;

    for( int i=0; i<len; i++ )
    {
      if(data[i]==','|| i==len-1)
      {
        if(i==len-1)
          temp = data.substr(st, i-st+1);
        else
          temp = data.substr(st, i-st);

        currdata[count] = instance[count][temp];
        count++;
        st = i+1;
      }
    }

    //check if given training example is positive or negative
    example = true;
    for(int i=0; i<numberFeatures; i++)
    {
      if(currdata[i]!=targetHypothesis[i] && targetHypothesis[i]!=INT_MAX)
      {
        example = false;
        break;
      }
    }

    if(example==currdata[6])
    {
      accuracy++;
    }

  }


  cout<<"numEx="<<numEx<<" accuracy="<<accuracy<<endl;




  return 0;
}
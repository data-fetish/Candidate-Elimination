/*
  Candidate Elimination
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
  bool consistent;

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
  /*
  for any feature if attribute=0 -> null value;
  attribute = INT_MAX -> all
  */
  
  vector <int> currdata(numberFeatures+1), tmpData(numberFeatures);

  //set used to represent the generic and specific boundaries.
  set < vector<int> > specific, generic;

  //initialization
  for(int i=0; i<numberFeatures; i++)
  {
    tmpData[i]=0;
  }
  specific.insert(tmpData);

  for(int i=0; i<numberFeatures; i++)
  {
    tmpData[i]=INT_MAX;
  }
  generic.insert(tmpData);

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

    vector<int> m, n, p;
    
    if( currdata[count-1]==1 ) //if positive example
    {
      //remove inconsistent hypotheses from generic border
      set < vector<int> > tempg, temps;
      tempg = generic;
      for(set<vector<int> >::iterator it= generic.begin(); it!=generic.end(); it++)
      {
        m = *it;
        int er =0;
        for(int i=0; i<numberFeatures; i++)
        {
          if(m[i]!=currdata[i] && m[i]!=INT_MAX )
          {
            er = 1;
            break;
          }
        }
        if(er==1)
          tempg.erase(m);
      }
      generic = tempg;

      m = *(specific.begin());
      n = *(specific.begin());
      specific.erase(n);

      for(int i=0; i<numberFeatures; i++)
      {
        if(m[i]==0)
        {
          m[i] = currdata[i];
        }
        else if(m[i]!=currdata[i])
        {
          m[i]=INT_MAX;
        }
      }

      specific.insert(m);
    }
    else //if negative example
    {
      /*
      if example is inconsistent with spec border, then it is noise
      */

      set < vector<int> > tempg, temps;
      n = *(specific.begin());

      for(set< vector<int> >::iterator it= generic.begin(); it!=generic.end(); it++)
      {
        m = *it;

        int er=0;
        //check if given example is consistent with the present hypothesis
        for(int i=0; i<numberFeatures; i++)
        {
          if( m[i]!=INT_MAX && m[i]!=currdata[i])
          {
            er=1; //curr hyp is consistent
            break;
          }
        }

        if(er==1)//if hyp is consistent with the example
        {
          tempg.insert(m);
        }
        else//hyp is not consistent with the example
        {
          vector<int> temphyp;
          for(int i=0; i<numberFeatures; i++)
          {
            if( m[i]==INT_MAX )
            {
              temphyp = m;
              for(int j=1; j<=numberAttributes[i]; j++)//values are 1-based
              {
                if(j==currdata[i])
                  continue;
                else
                {
                  temphyp[i] = j;
                  
                  //check if temphyp is more general than specifc hyp.
                  consistent = true;
                  for(int k=0; k<numberFeatures; k++)
                  {
                    if(temphyp[k]!=INT_MAX && temphyp[k]!=n[k] && n[k]!=0)
                    {
                      consistent = false;
                      break;
                    }
                  }
                  if(consistent)
                    tempg.insert(temphyp); // new hypo is consistent
                }
              }
            }
          }
          
        }

      }

      generic.clear();
      bool mGen;
      set<vector<int> > tempgg;
      
      //remove from generic any hyp that is more specific than another hyp in generic
      for(set< vector<int> >::iterator it= tempg.begin(); it!=tempg.end(); it++)
      {
        m = *it;

        for( set< vector<int> >::iterator jt= tempg.begin(); jt!=tempg.end(); jt++ )
        {
          if(it==jt)
            continue;

          p = *jt;
          consistent = true;
          for(int k=0; k<numberFeatures; k++)
          {
            if(m[k]!=INT_MAX && m[k]!=p[k])
            {
              consistent = false;
              break;
            }
          }
          if(consistent)
            tempgg.insert(p);
        }
      }

      // generic = set_difference(tempg, tempgg );
      for( set< vector<int> >::iterator it= tempg.begin(); it!=tempg.end(); it++ )
      {
        m = *it;

        if(tempgg.find(m)==tempgg.end())
        {
          generic.insert(m);
        }
      }
    }
  }

  /*
      Printing Specific and General borders
  */
  vector<int> abc;

  cout<<"specific border"<<endl;
  abc = *(specific.begin());
  cout<<"< ";
  for(int i=0; i<numberFeatures; i++)
  {
    if( abc[i]==INT_MAX )
      cout<<"?"<<" ";
    else
    {
      for(map<string,int>::iterator jt = instance[i].begin(); jt!=instance[i].end();jt++)
      {
        if((*jt).second == abc[i])
          cout<<(*jt).first<<" ";
      }
    }
  }
  cout<<">\n";

  cout<<"\ngeneric border"<<endl;
  for(set< vector<int> >::iterator it= generic.begin(); it!=generic.end(); it++)
  {
    abc = *it;
    cout<<"< ";
    for(int i=0; i< numberFeatures; i++)
    {
      if( abc[i]==INT_MAX )
        cout<<"?"<<" ";
      else
      {
        for(map<string,int>::iterator jt = instance[i].begin(); jt!=instance[i].end();jt++)
        {
          if((*jt).second == abc[i])
            cout<<(*jt).first<<" ";
        }
      }
    }
    cout<<">\n";
  }
  
  cout<<"\ncandidate elem done! :)\n";

  return 0;
}



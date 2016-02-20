#line 73 "AverageProblem.cpp"
#include <string>   
#include <vector>   
#include <iostream>    
#include <sstream>    
#include <algorithm>   
#include <numeric>   
#include <functional>    
#include <map>    
#include <set>    
#include <cassert>   
#include <list>    
#include <deque>    
#include <iomanip>    
#include <cstring>    
#include <cmath>    
#include <cstdio>    
#include <cctype>   

using namespace std;   

#define fi(n) for(int i=0;i<(n);i++)
#define fj(n) for(int j=0;j<(n);j++)
#define f(i,a,b) for(int (i)=(a);(i)<(b);(i)++)

typedef vector <int> VI;   
typedef vector <string> VS;   
typedef vector <VI> VVI;   

template<class T>
T fromString(string inp)
{
	stringstream s(inp);
	T a;
	s>>a;
	return a;
}

VS toks(string inp,string delim)   
{   
  char *ch = strdup(inp.c_str());   
  char *ptr = strtok(ch,delim.c_str());   
  VS ret;   
  while (ptr != NULL){   
    ret.push_back(ptr);   
    ptr = strtok(NULL,delim.c_str());   
    }   
  free(ch);   
  return ret;   
}   

    class AverageProblem
        { 
        public: 
					bool ok(const VI &m, int num) {
						int i;

						fi(m.size()) {
							int p = (m[i] * num);
							p -= p % 1000;

							if (p / num != m[i] && (p + 1000) / num != m[i])
								return false;
						}

						return true;
					}
        int numberOfParticipants(vector <string> m) 
            { 
							VI ma;
							int i,j;
							fi(m.size()) {
								VS te = toks(m[i], " ");
								fj(te.size()) {
									int a,p;
									sscanf(te[j].c_str(), "%d.%d", &a,&p);
									ma.push_back(a*1000 + p);
								}
							}

							f(i,1,1001) {
								if (ok(ma, i)) 
									return i;
							}

							return 1000;
            } 
        
 
        }; 

    



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor

#line 118 "WebsiteRank.cpp"
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
typedef long long ll;

typedef pair<int,int> ScoreTimestampPair;

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

map<string, int> sites;
bool ok[3000][3000];
bool clos[3000][3000];

ll done[3000];
int tot;

ll go(int pos) {
	if (done[pos] > 0) return done[pos];
	ll ret = 1;

	fi(tot) {
		if (ok[pos][i] && !clos[i][pos]) {
			ret += go(i);
		}
	}

	return done[pos] = ret;
}

    class WebsiteRank
        { 
        public: 
        long long countVotes(vector <string> vo, string site) 
            { 
							memset(done, 0xff, sizeof(done));
							sites.clear();
							memset(ok, 0, sizeof(ok));
							tot  = 0;
							fi(vo.size()) {
								VS t = toks(vo[i], " ");
								int t0;
								if (sites.count(t[0]) > 0) {
									t0 = sites[t[0]];
								} else t0 = sites[t[0]] = tot++;

								f(j,1,t.size()) {
									int tj;
									if (sites.count(t[j]) > 0) {
										tj = sites[t[j]];
									} else tj = sites[t[j]] = tot++;
									ok[t0][tj] = true;
								}
							}

							memcpy(clos, ok, sizeof(clos));

							f(k,0,tot) {
								fi(tot) {
									fj(tot) {
										clos[i][j] |= clos[i][k] && clos[k][j];
									}
								}
							}

							return go(sites[site]);
            } 
        
 
        }; 

    



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor

#line 82 "ChessMatchup.cpp"
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

VI u,t;
int n;

int memo[55][55][55];

int go(int ul, int uh, int th) {
	if (ul >= uh) return 0;
	if (th >= n) return 0;

	if (memo[ul][uh][th] >= 0) return memo[ul][uh][th];

	int best = 0;

	int p1 = 0;
	if (u[ul] > t[th]) p1 = 2;
	if (u[ul] == t[th]) p1 = 1;

	int p2 = 0;
	if (u[uh - 1] > t[th]) p2 = 2;
	if (u[uh - 1] == t[th]) p2 = 1;

	best >?= go(ul + 1, uh , th + 1) + p1;
	best >?= go(ul, uh - 1, th + 1) + p2;

	return memo[ul][uh][th] = best;
}

    class ChessMatchup
        { 
        public: 
        int maximumScore(vector <int> us, vector <int> them) 
            { 
							n = us.size();
							sort(us.rbegin(), us.rend());
							sort(them.rbegin(), them.rend());
							memset(memo, 0xff, sizeof(memo));

							u = us;
							t = them;

							return go(0, n, 0);
            } 
        
 
        }; 

    



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor

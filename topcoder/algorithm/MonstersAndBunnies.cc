#line 115 "MonstersAndBunnies.cc"
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


long double ans[1001][1001];
int done[1001][1001];

long double go(int m, int b) {
	if (m % 2 != 0){
		return 0.0;
	}
	if (m == 0) {
		return 1.0;
	}

	if (done[m][b]) return ans[m][b];
	done[m][b] = 1;

	long double &ret = ans[m][b];
	ret = 0.0;

	if (b > 0) {
		ret += 1.0 * m * b * go(m, b - 1);
	}
	ret += 1.0 * m * (m - 1) * go(m - 2, b) / 2.0;

	if (b > 0) {
		long double t1  = 1.0 * b * go(m, b - 1);
		if ((ret + t1) > (ret + b*ret)) {
			ret += t1;
		} else {
			ret += b * ret;
		}
	}


	ret = 2.0 * ret / (m + b + 1) / (m + b);
	return ret;
}

    class MonstersAndBunnies
        { 
        public: 
        double survivalProbability(int M, int B) 
            { 
							memset(done, 0, sizeof(done));
							return go(M,B);
            } 
        
 
        }; 

    



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor

#line 71 "WordSplit.cpp"
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

string full;

pair<int, VS> memo[55][55];

bool okay(int st, int en) {
	int done[30] = {0};
	f(i,st,en+1) {
		if (done[full[i] - 'a']) return false;
		done[full[i] - 'a'] = 1;
	}

	return true;
}

pair<int, VS> go(int st, int cur) {
	if (memo[st][cur].first != -1) 
		return memo[st][cur];

	pair<int, VS> &ret = memo[st][cur];

	if (cur >= full.size() - 1) {
		ret.first = 1;
		ret.second.push_back(full.substr(st, cur - st + 1));
		return ret;
	}

	pair<int, VS> t1 = go(cur + 1, cur + 1);

	t1.first ++;
	t1.second.push_back(full.substr(st, cur - st + 1));
	sort(t1.second.begin(), t1.second.end());

	pair<int,VS> t2;
	t2.first = 1<<20;
	if (okay(st, cur + 1)) {
		t2 = go(st, cur + 1);
	}

	if (t1.first == t2.first) {
		ret = t1;
		fi(t1.first) {
			if (t1.second[i] != t2.second[i]) {
				if (t1.second[i] < t2.second[i])
					ret = t1;
				else 
					ret = t2;
				break;
			}
		}
	} else {
		if (t1.first < t2.first ) {
			ret = t1;
		} else {
				ret = t2;
			}
	}

	return ret;
}

    class WordSplit
        { 
        public: 
        vector <string> pieces(string theString) 
            { 
							fi(55) fj(55)  {
								memo[i][j].first = -1;
								memo[i][j].second.clear();
							}
							full = theString;
							pair<int, VS> t = go(0, 0);
							return t.second;
            } 
        
 
        }; 

    



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor

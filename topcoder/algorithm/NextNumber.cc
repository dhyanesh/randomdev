#line 71 "NextNumber.cc"
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

    class NextNumber
        { 
        public: 
        int getNextNumber(int N) 
            { 
              string n;

              while (N) {
                if (N&1) n+='1'; else n+='0';
                N >>=1;
              }

              n+='0';
              reverse(n.begin(), n.end());

              next_permutation(n.begin(), n.end());

              int ret = 0;
              int mul = 1;
              for(int i = n.size() - 1; i >= 0; --i) {
                if (n[i] == '1') ret += mul;
                mul <<= 1;
              }

              return ret;
            } 
        
 
        }; 

    



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor

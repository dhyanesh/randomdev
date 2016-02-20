#line 90 "CoinsExchange.cpp"
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

    class CoinsExchange
        { 
        public: 
        int countExchanges(int G1, int S1, int B1, int G2, int S2, int B2) 
            { 
							if (G1 < G2 && S1 < S2 && B1 < B2) return -1;
							if (G1 >= G2 && S1 >= S2 && B1 >= B2) return 0;

							int  ret = 0;
							int cg = G1;
							int cs = S1;
							int cb = B1;

							if (cg < G2) {
								int sil = 11 * (G2 - cg);

								if ((cs-S2) + (cb-B2) / 11 < sil) return -1;

								if (cs-S2 < sil) {
									int req = sil - (cs-S2);
									cs += req;
									cb -= req * 11;
									ret += req;
								}

								cg += sil / 11;
								cs -= sil;
								ret += sil / 11;
							}

							if (cs < S2) {
								int use = (cg - G2);
								if (use < 0) use = 0;

								int lim = min(use, (S2 - cs)/9 + int((S2-cs)%9!=0));
								cs += use * 9;
								cg -= use;
								ret += use;

								if (cs <  S2) {
									int use = (cb - B2);
									if (use < 0) use = 0;

									int lim = min(use, 11*(cs - S2));
									cs += use / 11;
									cb -= use / 11 * 11;
									ret += use / 11;
								}

								if (cs <  S2) {
									return -1;
								}
							}

							if (cb < B2) {
								int sil = (B2 - cb) / 9 + int((B2 - cb)%9!=0);

								if ((cs-S2) + (cg-G2) * 9 < sil) return -1;

								if (cs-S2 < sil) {
									int req = sil - (cs-S2);
									int c = req / 9 + int(req %9!=0);
									cs += c * 9;
									cg -= c;
									ret += c;
								}

								cb += sil * 9;
								cs -= sil;
								ret += sil;
							}

							return ret;
            } 
        
 
        }; 

    



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor

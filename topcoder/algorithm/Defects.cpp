#line 114 "Defects.cpp"
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

vector<double> pos;
double len;

double get(double p) {
	double sum = 0.0;
	fi(pos.size()) {
		sum += min(fabs(p-pos[i]),len - fabs(p - pos[i]));
	}

	return sum;
}

    class Defects
        { 
        public: 
        double maxSum(int w, int h, vector <double> dw, vector <double> dh) 
            { 
							len = 2*w + 2*h;
							
							if (dw.size() == 1) return len/2.0;

							pos.resize(dw.size(), 0.0);

							fi(dw.size()) {
								if (dh[i] == 0) pos[i] = dw[i];
								else if (dw[i]==0) pos[i] = 2*w+2*h-dh[i];
								else if (dw[i]==w)  pos[i] = w + dh[i];
								else if (dh[i]==h) pos[i] = w + h + w - dw[i];
							}

							sort(pos.begin(), pos.end());

							double  max = 0.0;
							fi(pos.size()) {
								double low = pos[i];
								double high = pos[ ( i + 1 ) % pos.size()];

								fj(1000) {
									double mid1 = (high - low) * 1.0 / 3 + low;
									double mid2 = (high - low) * 2.0 / 3 + low;

									double t1 = get(mid1);
									double t2 = get(mid2);

									if (t1 < t2) {
										low = mid1;
									} else {
										high = mid2;
									}
								}

								max >?= get(high);
							}

							return max;
            } 
        
 
        }; 

    



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor

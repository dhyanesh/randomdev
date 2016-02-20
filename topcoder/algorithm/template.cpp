#ifdef __GNUC__   
#define int64 long long   
#else /* MSVC, say */   
#define int64 _int64
#pragma warning( disable : 4786 )   
#endif   

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

template<class T>
vector<T> toksT(string inp,string delim)   
{   
  VS temp = toks(inp,delim);   
  vector<T> ret;   
  for(int i=0;i<temp.size();i++)   
    ret.push_back(fromString<T>(temp[i]));   
  return ret;   
}   

VVI toksvvi(vector <string> inp,string delim)   
{   
  VVI ret;   
  for(int i=0;i<inp.size();i++)   
    ret.push_back(toksT<int>(inp[i],delim));   
  return ret;   
}   

int vmin(VI inp)   
{   
  int mini=inp[0];   
  for(int i=1;i<inp.size();i++)   
    mini=mini<inp[i]?mini:inp[i];   
  return mini;   
}   

int vmax(VI inp)   
{   
  int maxi=inp[0];   
  for(int i=1;i<inp.size();i++)   
    maxi=maxi>inp[i]?maxi:inp[i];   
  return maxi;   
}   


int main(void)
{
	char arr[] = {"234.234 654.234 12.234 756.234 23.23423"};
	string b(arr);
	long double a = fromString<long double>("33.34234");
	cout << a << endl;

	vector<double> t = toksT<double>(b," ");
	int i;
	fi(t.size())
		cout << t[i] << " ";
	return 0;
}

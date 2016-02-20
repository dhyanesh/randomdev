// BEGIN CUT HERE
// PROBLEM STATEMENT
// You are given the adjacency matrix of a directed graph as 
// a vector <string> adjacencyMatrix. The j-th character of 
// the i-th element of adjacencyMatrix will be '1' if there 
// is an edge going from the i-th vertex to the j-th, or '0' 
// otherwise. A star in a directed graph is defined as 
// follows: it is comprised of a central vertex and at least 
// three distinct edges emanating from it, which we will call 
// the rays of the star. The number of rays in a star is not 
// bounded; the only restriction is that there must be at 
// least 3 of them. The number of distinct stars for which a 
// vertex V is central will be called the star number of V. 
// For example, if V has 5 edges emanating from it then its 
// star number is 16 = 10 + 5 + 1 since it is central for 10 
// stars with 3 rays, 5 stars with 4 rays, and 1 star with 5 
// rays. We will call a path in our graph starry if it 
// satisfies two conditions:
// Each vertex belonging to the path has a non-zero star 
// number not exceeding C. Given two subsequent vertices Vi 
// and Vi+1 in the path the star number of Vi+1 is not less 
// than the star number of Vi.
// 
// Given the directed graph in the form of its adjacency 
// matrix return the number of vertices in the longest starry 
// path it contains. If there is a starry path of infinite 
// length in the graph return -1. If there are no starry 
// paths (all vertices have star numbers either 0 or greater 
// than C) return 0.
// 
// DEFINITION
// Class:StarsInGraphs
// Method:starryPaths
// Parameters:vector <string>, int
// Returns:int
// Method signature:int starryPaths(vector <string> 
// adjacencyMatrix, int C)
// 
// 
// NOTES
// -Two stars are considered distinct if either their central 
// vertices are distinct or the sets of rays are distinct.
// 
// 
// CONSTRAINTS
// -adjacencyMatrix will contain between 2 and 50 elements, 
// inclusive.
// -The number of characters in each string of the 
// adjacencyMatrix will be equal to the total number of 
// elements in adjacencyMatrix.
// -Every character of each element of adjacencyMatrix will 
// be either '0' (zero) or '1' (one).
// -The i-th character of the i-th element of adjacencyMatrix 
// will be '0'.
// -C will be between 1 and 109, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {"01110",
//  "10111",
//  "00000",
//  "00000",
//  "00000"}
// 1000
// 
// Returns: 2
// 
// The starry path 0 -> 1 is the longest one. Vertex 0 has 
// star number 1, vertex 1 has star number 5, and all other 
// vertices have star numbers 0.
// 
// 1)
// {"01011",
//  "00111",
//  "10011",
//  "00000",
//  "00000"}
// 1
// 
// Returns: -1
// 
// Vertices 0, 1, and 2 have star numbers 1 and form a cycle, 
// thus we have an infinite starry path.
// 
// 2)
// {"0111",
//  "0000",
//  "0000",
//  "0000"}
// 1
// 
// Returns: 1
// 
// This time the longest starry path consists of a single 
// vertex.
// 
// 3)
// {"01111",
//  "00000",
//  "00000",
//  "00000",
//  "00000"}
// 4
// 
// Returns: 0
// 
// Vertex 0 has star number 5 and the rest of the vertices 
// have a zero star number, and thus none of them can appear 
// in a starry path.
// 
// 4)
// {"010001100",
//  "001001100",
//  "000101110",
//  "000010111",
//  "000001111",
//  "010000000",
//  "000110000",
//  "000100001",
//  "100001000"}
// 10
// 
// Returns: 5
// 
// 
// 
// END CUT HERE
#line 131 "StarsInGraphs.cpp"
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

    class StarsInGraphs
        { 
        public: 
        int starryPaths(vector <string> adjacencyMatrix, int C) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"01110",
 "10111",
 "00000",
 "00000",
 "00000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000; int Arg2 = 2; verify_case(0, Arg2, starryPaths(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"01011",
 "00111",
 "10011",
 "00000",
 "00000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = -1; verify_case(1, Arg2, starryPaths(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"0111",
 "0000",
 "0000",
 "0000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; verify_case(2, Arg2, starryPaths(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"01111",
 "00000",
 "00000",
 "00000",
 "00000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 0; verify_case(3, Arg2, starryPaths(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"010001100",
 "001001100",
 "000101110",
 "000010111",
 "000001111",
 "010000000",
 "000110000",
 "000100001",
 "100001000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arg2 = 5; verify_case(4, Arg2, starryPaths(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        StarsInGraphs ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    


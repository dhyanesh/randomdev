// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// A vertex cactus is a connected graph such that each vertex 
// belongs to at most one simple cycle.  A simple cycle is a 
// cycle that doesn't pass through any vertex more than 
// once.  For example, the graph in the picture below is a 
// vertex cactus:
// 
// 
// 
// 
// 
// Given a graph G with vertices numbered from 1 to n, its 
// automorphism is a permutation p[1], p[2], ..., p[n] such 
// that there is an edge i-j in G if and only if there is an 
// edge p[i]-p[j].
// 
// 
// You are given an int n - the number of vertices in a 
// vertex cactus.  The vertices are numbered 1 to n.  The 
// edges of the graph are given to you in the vector <string> 
// edges.  Concatenate the elements of edges to get a comma-
// separated list of integer pairs.  The integers in each 
// pair are separated by a space.  The pair "i j" (quotes for 
// clarity) means that there is an edge between vertices i 
// and j in the given graph.  Return the number of 
// automorphisms that exist for the given vertex cactus, 
// modulo 10^9+3.
// 
// 
// DEFINITION
// Class:CactusAutomorphisms
// Method:count
// Parameters:int, vector <string>
// Returns:int
// Method signature:int count(int n, vector <string> edges)
// 
// 
// CONSTRAINTS
// -n will be between 1 and 200, inclusive.
// -edges will contain between 0 and 50 elements, inclusive.
// -Each element of edges will contain between 1 and 50 
// characters, inclusive.
// -When concatenated edges will contain a comma separated 
// list of pairs of integers. 
// -Each integer pair will contain two distinct integers 
// between 1 and n, inclusive, separated by a space.
// -The given graph will be a vertex cactus - it will be 
// connected and each vertex will belong to at most one 
// simple cycle.
// -Every pair of vertices in the graph will be connected by 
// at most one edge.
// 
// 
// EXAMPLES
// 
// 0)
// 4
// {"1 2,1 3,1 4"}
// 
// Returns: 6
// 
// We can arbitrarily permute vertices 2, 3 and 4.
// 
// 1)
// 4
// {"1 2,2 3,3 4,4 1"}
// 
// Returns: 8
// 
// The permutation can either perform a circular shift of the 
// vertices along the cycle, or flip the cycle, or both.
// 
// 2)
// 6
// {"1 2,2 3,3 1,4 5,5 6,6 4,1 4"}
// 
// Returns: 8
// 
// The permutation can swap triangles.  Also, in each 
// triangle, the permutation can swap the two vertices that 
// are not incident to another triangle.
// 
// 3)
// 18
// {"1 2,2 3,3 4,2 4,1 5,1 10,5 10,5 6,6 7",
//  ",7 8,7 16,7 17,7 9,6 9,10 18,18 ",
//  "12,12 11,11 18,12 13,12 14,12 15"}
// 
// Returns: 144
// 
// This is the graph in the picture in the problem statement.
// 
// 4)
// 1
// {}
// 
// 
// Returns: 1
// 
// 
// 
// 5)
// 200
// {"1 2,2 3,3 4,4 5,5 6,6 7,7 8,8 9,9 10,10 11,11 2,1 ",
//  "12,12 13,13 14,14 15,15 16,16 17,17 18,18 19,19 20",
//  ",20 21,21 12,1 22,22 23,23 24,24 25,25 26,26 27,27",
//  " 28,28 29,29 30,30 31,31 22,1 32,32 33,32 34,34 35",
//  ",35 36,36 32,1 37,37 38,37 39,39 40,40 41,41 37,1 ",
//  "42,42 43,42 44,44 45,45 46,46 42,1 47,47 48,47 49,",
//  "49 50,50 51,51 47,1 52,52 53,52 54,54 55,55 56,56 ",
//  "52,1 57,57 58,57 59,59 60,60 61,61 57,1 62,62 63,6",
//  "2 64,64 65,65 66,66 62,1 67,67 68,67 69,69 70,70 7",
//  "1,71 67,1 72,72 73,72 74,74 75,75 76,76 72,1 77,77",
//  " 78,78 79,79 80,80 81,81 77,1 82,82 83,83 84,84 85",
//  ",85 86,86 82,1 87,87 88,88 89,89 90,90 91,91 87,1 ",
//  "92,92 93,93 94,94 95,95 96,96 92,1 97,97 98,98 99,",
//  "99 100,100 101,101 97,1 102,102 103,103 104,104 10",
//  "5,105 106,106 102,1 107,107 108,108 109,109 110,11",
//  "0 111,111 107,1 112,112 113,113 114,114 115,115 11",
//  "6,116 112,1 117,117 118,118 119,119 120,120 121,12",
//  "1 117,1 122,122 123,123 124,124 125,125 126,126 12",
//  "2,1 127,127 128,128 129,129 130,130 131,131 127,1 ",
//  "132,132 133,133 134,134 135,135 136,136 132,1 137,",
//  "137 138,138 139,139 140,140 141,141 137,1 142,142 ",
//  "143,142 144,142 145,1 146,146 147,146 148,146 149,",
//  "1 150,150 151,150 152,150 153,1 154,154 155,154 15",
//  "6,154 157,1 158,158 159,158 160,158 161,1 162,162 ",
//  "163,162 164,162 165,1 166,166 167,167 168,166 169,",
//  "166 170,166 171,166 172,1 173,173 174,174 175,173 ",
//  "176,173 177,173 178,173 179,1 180,180 181,181 182,",
//  "180 183,180 184,180 185,180 186,1 187,187 188,188 ",
//  "189,187 190,187 191,187 192,187 193,1 194,194 195,",
//  "195 196,194 197,194 198,194 199,194 200"}
// 
// 
// Returns: 886565533
// 
// 
// 
// END CUT HERE
#line 144 "CactusAutomorphisms.cc"
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

    class CactusAutomorphisms
        { 
        public: 
        int count(int n, vector <string> edges) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; string Arr1[] = {"1 2,1 3,1 4"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 4; string Arr1[] = {"1 2,2 3,3 4,4 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 6; string Arr1[] = {"1 2,2 3,3 1,4 5,5 6,6 4,1 4"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 18; string Arr1[] = {"1 2,2 3,3 4,2 4,1 5,1 10,5 10,5 6,6 7",
 ",7 8,7 16,7 17,7 9,6 9,10 18,18 ",
 "12,12 11,11 18,12 13,12 14,12 15"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 144; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1; string Arr1[] = {}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(4, Arg2, count(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 200; string Arr1[] = {"1 2,2 3,3 4,4 5,5 6,6 7,7 8,8 9,9 10,10 11,11 2,1 ",
 "12,12 13,13 14,14 15,15 16,16 17,17 18,18 19,19 20",
 ",20 21,21 12,1 22,22 23,23 24,24 25,25 26,26 27,27",
 " 28,28 29,29 30,30 31,31 22,1 32,32 33,32 34,34 35",
 ",35 36,36 32,1 37,37 38,37 39,39 40,40 41,41 37,1 ",
 "42,42 43,42 44,44 45,45 46,46 42,1 47,47 48,47 49,",
 "49 50,50 51,51 47,1 52,52 53,52 54,54 55,55 56,56 ",
 "52,1 57,57 58,57 59,59 60,60 61,61 57,1 62,62 63,6",
 "2 64,64 65,65 66,66 62,1 67,67 68,67 69,69 70,70 7",
 "1,71 67,1 72,72 73,72 74,74 75,75 76,76 72,1 77,77",
 " 78,78 79,79 80,80 81,81 77,1 82,82 83,83 84,84 85",
 ",85 86,86 82,1 87,87 88,88 89,89 90,90 91,91 87,1 ",
 "92,92 93,93 94,94 95,95 96,96 92,1 97,97 98,98 99,",
 "99 100,100 101,101 97,1 102,102 103,103 104,104 10",
 "5,105 106,106 102,1 107,107 108,108 109,109 110,11",
 "0 111,111 107,1 112,112 113,113 114,114 115,115 11",
 "6,116 112,1 117,117 118,118 119,119 120,120 121,12",
 "1 117,1 122,122 123,123 124,124 125,125 126,126 12",
 "2,1 127,127 128,128 129,129 130,130 131,131 127,1 ",
 "132,132 133,133 134,134 135,135 136,136 132,1 137,",
 "137 138,138 139,139 140,140 141,141 137,1 142,142 ",
 "143,142 144,142 145,1 146,146 147,146 148,146 149,",
 "1 150,150 151,150 152,150 153,1 154,154 155,154 15",
 "6,154 157,1 158,158 159,158 160,158 161,1 162,162 ",
 "163,162 164,162 165,1 166,166 167,167 168,166 169,",
 "166 170,166 171,166 172,1 173,173 174,174 175,173 ",
 "176,173 177,173 178,173 179,1 180,180 181,181 182,",
 "180 183,180 184,180 185,180 186,1 187,187 188,188 ",
 "189,187 190,187 191,187 192,187 193,1 194,194 195,",
 "195 196,194 197,194 198,194 199,194 200"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 886565533; verify_case(5, Arg2, count(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        CactusAutomorphisms ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    


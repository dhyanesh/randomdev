// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Trees are important data structures in programming.  In 
// this problem, you will be given a tree that was 
// constructed from a fully connected undirected acyclic 
// graph with exactly N nodes.  First, a distinct number 
// between 0 and N-1, inclusive, was assigned to each node.  
// Then, one of the nodes was selected to be the root of the 
// tree.  Finally, each non-root node was assigned its 
// neighbor closest to the root as its parent.
// 
// You will be given the tree as a vector <int>, where the i-
// th element is the parent of the i-th node, or -1 if the i-
// th node is the root (indices are 0-based).  A tree is 
// considered equivalent to this tree if it can be 
// constructed from the same original graph using the method 
// described above.  This means you can renumber the nodes 
// and select a different node as the root (see examples for 
// clarification).  Return a vector <int> containing the 
// equivalent tree that comes first lexicographically.  A 
// vector <int> a1 comes before vector <int> a2 
// lexicographically if a1 has a smaller value at the first 
// element where they differ.
// 
// 
// DEFINITION
// Class:NormalizingTrees
// Method:normalize
// Parameters:vector <int>
// Returns:vector <int>
// Method signature:vector <int> normalize(vector <int> tree)
// 
// 
// CONSTRAINTS
// -tree will contain between 1 and 50 elements, inclusive.
// -Each element of tree will be between -1 and N-1, 
// inclusive, where N is the number of elements in tree.
// -Exactly one element of tree will be -1.
// -tree will represent a connected acyclic graph.
// 
// 
// EXAMPLES
// 
// 0)
// {2,0,-1,4,2,4}
// 
// Returns: {-1, 0, 0, 0, 1, 4 }
// 
// This is the original drawing (with 2 as the root):
// 
//     2
//    / \
//   0   4
//  /   / \
// 1   3   5
//  
// The renumbering gives this:
// 
//     1
//    / \
//   4   0
//  /   / \
// 5   2   3
// 
// and taking the new 0 as the root gives the answer:
// 
//    0
//  / | \
// 1  2  3
// |
// 4
// |
// 5
// 
// 
// 1)
// {-1,0,1,2,3}
// 
// Returns: {-1, 0, 0, 1, 2 }
// 
// This is a simple path of length 5. Selecting the middle 
// node as root and renumbering gives the lexicographically 
// first representation.
// 
// 2)
// {3,3,3,4,-1,3}
// 
// Returns: {-1, 0, 0, 0, 0, 0 }
// 
// This tree has the shape of a star (one center node with 5 
// nodes connected to it).
// 
// 3)
// {10,9,6,10,6,9,7,-1,9,7,7,10,6}
// 
// Returns: {-1, 0, 0, 0, 0, 1, 1, 5, 5, 5, 6, 6, 6 }
// 
// 
// 
// 4)
// {-1, 0, 0, 0, 0, 1, 1, 5, 5, 5, 6, 6, 6}
// 
// Returns: {-1, 0, 0, 0, 0, 1, 1, 5, 5, 5, 6, 6, 6 }
// 
// 
// 
// END CUT HERE
#line 110 "NormalizingTrees.cpp"
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

    class NormalizingTrees
        { 
        public: 
        vector <int> normalize(vector <int> tree) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {2,0,-1,4,2,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1, 0, 0, 0, 1, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, normalize(Arg0)); }
	void test_case_1() { int Arr0[] = {-1,0,1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1, 0, 0, 1, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, normalize(Arg0)); }
	void test_case_2() { int Arr0[] = {3,3,3,4,-1,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1, 0, 0, 0, 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, normalize(Arg0)); }
	void test_case_3() { int Arr0[] = {10,9,6,10,6,9,7,-1,9,7,7,10,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1, 0, 0, 0, 0, 1, 1, 5, 5, 5, 6, 6, 6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, normalize(Arg0)); }
	void test_case_4() { int Arr0[] = {-1, 0, 0, 0, 0, 1, 1, 5, 5, 5, 6, 6, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1, 0, 0, 0, 0, 1, 1, 5, 5, 5, 6, 6, 6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, normalize(Arg0)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        NormalizingTrees ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    


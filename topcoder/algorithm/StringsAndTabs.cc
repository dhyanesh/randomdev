// BEGIN CUT HERE
// PROBLEM STATEMENT
// Tablature is a popular way of notating songs played on 
// fretted string instruments.  Each line represents a 
// string, and numbers written on the lines tell you which 
// frets to press down when playing those strings.  Here is 
// an example:
// 
// 
// ------------
// -3----------
// -------0----
// ---2--------
// -------0----
// ------------
// 
// 
// The top line is the first string, the line below that is 
// the second string, and so on.  Tablature is read from left 
// to right, and the i-th column represents the notes played 
// at time i.  In this example, there are no numbers in 
// column 0, so this means that nothing is played at time 0.  
// At time 1, a note is played by holding down the 3rd fret 
// of the second string and plucking that string.  At time 3, 
// a note is played on the 2nd fret of the fourth string.  
// Finally, at time 7, there are two notes played 
// simultaneously as a chord.  The number 0 means that you 
// should pluck a string without holding down a fret.  This 
// is called an open string.  In this example, you play the 
// open third and fifth strings simultaneously.
// 
// Each open string may have a different pitch (i.e. may 
// produce a higher or lower sound). For example, in standard 
// guitar tuning, the pitch of the first string is 5 
// semitones higher than the second string.  When you hold 
// down the n-th fret (where 1 is the first fret) while 
// playing a string, the resulting pitch is n semitones 
// higher than that open string's pitch.
// 
// You are given a vector <string> tab containing the 
// tablature for a song played on some instrument A (a 
// guitar, for example).  However, you want to play it on a 
// different instrument B (maybe a mandolin, for example).  
// You know the pitches of the open strings on each 
// instrument, and they are given in the vector <int>s 
// stringsA and stringsB.  The i-th element of each vector 
// <int> represents the pitch of the i-th string, and is 
// given as the number of semitones above some base pitch 0.  
// Both instrument A and instrument B have 35 frets.  Frets 
// numbered 10 through 35 are represented by the uppercase 
// letters 'A' to 'Z'.
// 
// Your task is to write a program that will automatically 
// transform the original tablature so it can be played on 
// instrument B.  Since different instruments have different 
// ranges, you may also want to transpose the song to a 
// different key.  For this, you are given an int d, and you 
// must increase the pitch of every note by d semitones (d 
// can be negative, so you may end up lowering the pitches).  
// Note that it is possible for different strings to play the 
// same exact pitch at the same time in the original song.  
// When that happens, the transformed tablature must also 
// play that sound the same number of times as in the 
// original version.
// 
// Sometimes there will be multiple ways to play a note on 
// instrument B.  In such cases, choose the string with the 
// highest open pitch that can play that note.  If there are 
// multiple such strings, choose the bottom-most one among 
// them (strings are listed from top to bottom).  For chords, 
// apply that same rule to each individual note in the 
// chord.  You must assign the notes in order, starting with 
// the note that has the highest pitch, then the note with 
// the second-highest pitch, and so on.  You can only play a 
// single note on each string, so only consider unused 
// strings when assigning the notes of a chord.  If you are 
// unable to find a valid way to play a note or chord on 
// instrument B using these rules, fill the entire column 
// with lowercase 'x' characters instead.
// 
// Return a vector <string> containing the transformed 
// tablature for instrument B.
// 
// DEFINITION
// Class:StringsAndTabs
// Method:transformTab
// Parameters:vector <string>, vector <int>, vector <int>, int
// Returns:vector <string>
// Method signature:vector <string> transformTab(vector 
// <string> tab, vector <int> stringsA, vector <int> 
// stringsB, int d)
// 
// 
// NOTES
// -The input tablature tab is not necessarily created using 
// the rules given.
// 
// 
// CONSTRAINTS
// -tab will contain between 1 and 50 elements, inclusive.
// -Each element of tab will contain between 1 and 50 
// characters, inclusive.
// -Each element of tab will contain the same number of 
// elements.
// -stringsA and tab will contain the same number of elements.
// -Each element of stringsA will be between -50 and 50, 
// inclusive.
// -stringsB will contain between 1 and 50 elements, inclusive.
// -Each element of stringsB will be between -50 and 50, 
// inclusive.
// -d will be between -50 and 50, inclusive.
// -Each element of tab will contain only dashes ('-'), 
// digits ('0'-'9'), and uppercase letters ('A'-'Z').
// 
// 
// EXAMPLES
// 
// 0)
// {"-----------------",
//  "-------------0-1-",
//  "---------0-2-----",
//  "---0-2-3---------",
//  "-3---------------",
//  "-----------------"}
// {28,23,19,14,9,4}
// {9}
// 0
// 
// Returns: {"-3-5-7-8-A-C-E-F-" }
// 
// This sequence of sounds (an octave of a major scale), 
// played on several guitar strings, could be also played on 
// a single string (the 5th one).
// 
// 
// 1)
// {"-4457754-20024422-4457754-20024200-"}
// {0}
// {28,23,19,14,9,4}
// 12
// 
// Returns: {"-----------------------------------", 
// "-----------------------------------", 
// "----00---------------00------------", "-223--32-0--02200-
// 223--32-0--020---", "----------33---------------33---33-", 
// "-----------------------------------" }
// 
// This time, we have a sequence of sounds played on a single 
// string (the beginning of Beethoven's Ode to Joy), and we 
// want to play it on several strings of the guitar. We also 
// make each sound higher by 12 semitones.
// 
// 2)
// {"-----------------------------------",
//  "-----------------------------------",
//  "----00---------------00------------",
//  "-223--32-0--02200-223--32-0--020---",
//  "----------33---------------33---33-",
//  "-----------------------------------"}
// {28,23,19,14,9,4}
// {33,28,24,31}
// 12
// 
// Returns: {"-----------------------------------", "-001--
// 10-----00---001--10-----0----", "---------2002--22---------
// 2002-200-", "----00---------------00------------" }
// 
// We translate the guitar tablature from the previous 
// example to be played on a ukulele. Note that the strings 
// of a ukulele are not ordered from highest to lowest.
// 
// 3)
// {"-----0------2-2222--0-------0-",
//  "----0------2---222---5-----55-",
//  "---0------2-----22----9---999-",
//  "--0------2-------2-----E-EEEE-",
//  "-0------2---------------------",
//  "0------2----------------------"}
// {28,23,19,14,9,4}
// {33,28,28}
// 12
// 
// Returns: {"xxx-27-xx-049-999x--7777-777x-", "xxx----
// xx-------5x---------Cx-", "xxx3---xx0-----99x--------CCx-" }
// 
// It is sometimes impossible to play a chord, for example, 
// when one of the sounds is too low for the second 
// instrument, or when it doesn't have enough strings.
// 
// 
// 4)
// {"012345---------",
//  "---------UVWXYZ"}
// {-2,2}
// {0}
// 0
// 
// Returns: {"xx0123---WXYZxx" }
// 
// The first two sounds are too low to be played on this 
// string. The last two sounds are too high.
// 
// 5)
// {"0220----02--",
//  "75--75----57",
//  "------B9B9B9",
//  "--242424----"}
// {33,28,24,31}
// {33,28,28}
// 0
// 
// Returns: {"222222222222", "------------", "555555555555" }
// 
// One chord played in many different ways on a ukulele. 
// Since we always start assigning the strings from the sound 
// of the highest pitch, our method transforms them all to be 
// played in the same way on a balalaika.
// 
// 
// END CUT HERE
#line 222 "StringsAndTabs.cc"
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

    class StringsAndTabs
        { 
        public: 
          int get(char ch) {
            if (ch == '-') return -1;
            if (ch >= '0' && ch <= '9') return ch - '0';
            return ch - 'A' + 10;
          }

          char getc(int no) {
            if (no < 10) return no + '0';
            return no - 10 + 'A';
          }
        vector <string> transformTab(vector <string> tab, vector <int> sa, vector <int> sb, int d) 
            { 
              int ti = tab[0].size();
              string t(ti, ' ');
              VS ret(sb.size(), t);

              fi(ti) {
                VI donea(sa.size(), 0);
                VI doneb(sb.size(), 0);
                while (true) {
                  int max = -1<<30;
                  int maxp = -1;
                  fj(sa.size()) {
                    if (donea[j]) continue;
                    int fr = get(tab[j][i]);
                    if (fr == -1) continue;
                    if (fr + sa[j] >= max) {
                      max = fr + sa[j];
                      maxp = j;
                    }
                  }

                  if (max == -1<<30) {
                    break;
                  }
                  donea[maxp] = 1;

                  max += d;

                  int maxb = -1<<30;
                  int maxbp = -1;
                  fj(sb.size()) {
                    if (doneb[j]) continue;
                    if (sb[j] >= maxb && sb[j] <= max && max - sb[j] <= 35) {
                      maxb = sb[j];
                      maxbp = j;
                    }
                  }

                  if (maxb == -1<<30) {
                    fj(sb.size()) {
                      ret[j][i] = 'x';
                    }
                    break;
                  }
                  doneb[maxbp] = 1;

                  ret[maxbp][i] = getc(max - maxb);
                }

                fj(sb.size()) {
                  if (ret[j][i] == ' ') ret[j][i] = '-';
                }
              }

              return ret;
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"-----------------",
 "-------------0-1-",
 "---------0-2-----",
 "---0-2-3---------",
 "-3---------------",
 "-----------------"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {28,23,19,14,9,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {9}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; string Arr4[] = {"-3-5-7-8-A-C-E-F-" }; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(0, Arg4, transformTab(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { string Arr0[] = {"-4457754-20024422-4457754-20024200-"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {28,23,19,14,9,4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 12; string Arr4[] = {"-----------------------------------", "-----------------------------------", "----00---------------00------------", "-223--32-0--02200-223--32-0--020---", "----------33---------------33---33-", "-----------------------------------" }; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(1, Arg4, transformTab(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { string Arr0[] = {"-----------------------------------",
 "-----------------------------------",
 "----00---------------00------------",
 "-223--32-0--02200-223--32-0--020---",
 "----------33---------------33---33-",
 "-----------------------------------"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {28,23,19,14,9,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {33,28,24,31}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 12; string Arr4[] = {"-----------------------------------", "-001--10-----00---001--10-----0----", "---------2002--22---------2002-200-", "----00---------------00------------" }; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(2, Arg4, transformTab(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { string Arr0[] = {"-----0------2-2222--0-------0-",
 "----0------2---222---5-----55-",
 "---0------2-----22----9---999-",
 "--0------2-------2-----E-EEEE-",
 "-0------2---------------------",
 "0------2----------------------"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {28,23,19,14,9,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {33,28,28}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 12; string Arr4[] = {"xxx-27-xx-049-999x--7777-777x-", "xxx----xx-------5x---------Cx-", "xxx3---xx0-----99x--------CCx-" }; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(3, Arg4, transformTab(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { string Arr0[] = {"012345---------",
 "---------UVWXYZ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-2,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; string Arr4[] = {"xx0123---WXYZxx" }; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(4, Arg4, transformTab(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { string Arr0[] = {"0220----02--",
 "75--75----57",
 "------B9B9B9",
 "--242424----"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {33,28,24,31}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {33,28,28}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; string Arr4[] = {"222222222222", "------------", "555555555555" }; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(5, Arg4, transformTab(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        StringsAndTabs ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    


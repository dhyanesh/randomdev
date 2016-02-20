// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Musical notes are are given the following 12 names, in 
// ascending order:
// 
// 
// 
// 
//     A, A#, B, C, C#, D, D#, E, F, F#, G, G#
// 
// 
// 
// The names repeat for higher and lower notes,
// so the note one step higher than "G#" is "A"
// and the note 5 steps lower than "B" is "F#".
// Notes that are a multiple of 12 steps apart have the same 
// name, and for our purposes we will consider them equivalent.
// 
// 
// 
// Guitars have a number of strings, and each string is tuned 
// to sound one of the 12 notes.
// The note each string sounds is called its "open" note.
// Underneath the strings are frets, numbered starting at 1, 
// which are used to change the note a string sounds.
// If you press a string against the i-th fret with your 
// finger, the note will be i steps higher than the string's 
// open note.
// (i.e., if you press a string tuned to "C#" against the 3rd 
// fret, it will sound the note "E").
// 
// 
// 
// Chords are sets of notes played at the same time.
// To play a chord on a guitar, each string must sound one of 
// the notes in the chord,
// and each note in the chord must be played on at least one 
// string.
// 
// 
// 
// There can be many ways to play the same chord.
// We measure the difficulty of one way to play a chord as 
// the amount you must stretch your fingers to reach the 
// required frets.
// Calculate this as the lowest fret used subtracted from the 
// highest fret used, plus 1.
// Only consider the strings which are pressed against frets 
// -- the strings that are not pressed against frets (and, 
// thus, sound their open note) do not affect the difficultly 
// of a chord.
// If a chord can be played without using any frets at all, 
// its difficulty is zero.
// 
// 
// 
// You are given a String[] strings, each element of which is 
// the open note of one string on the guitar,
// and a String[] chord, each element of which is one note in 
// a chord.
// Return the lowest possible difficulty value necessary to 
// play that chord.
// 
// 
// 
// DEFINITION
// Class:GuitarChords
// Method:stretch
// Parameters:vector <string>, vector <string>
// Returns:int
// Method signature:int stretch(vector <string> strings, 
// vector <string> chord)
// 
// 
// CONSTRAINTS
// -strings and chord will each contain between 1 and 6 
// elements, inclusive.
// -chord will not contain more elements than strings.
// -Each element of strings and chord will be one of the 12 
// note names given in the problem statement.
// -chord will not contain any duplicate elements.
// 
// 
// EXAMPLES
// 
// 0)
// { "A", "C", "F" }
// { "C#", "F#", "A#" }
// 
// Returns: 1
// 
// The three notes in the chord are each one step higher than 
// the notes played by the three strings.  So, you can play 
// this chord by putting your finger on the 1st fret on all 
// three strings.  The answer is therefore: (1-1)+1.
// 
// 1)
// { "E", "A", "D", "G", "B", "E" }
// { "E", "G#", "B" }
// 
// Returns: 2
// 
// The best way to play this chord is with your fingers on 
// the following frets:
// 
// 
// string 0, "E": no fret, plays note "E"
// string 1, "A": fret #2, plays note "B"
// string 2, "D": fret #2, plays note "E"
// string 3, "G": fret #1, plays note "G#"
// string 4, "B": no fret, plays note "B"
// string 5, "E": no fret, plays note "E"
// 
// 
// All strings are playing a note in the chord, and each note 
// in the chord is played on at least one string.  The 
// largest-numbered fret is 2, and the smallest is 1.  
// Therefore the answer is (2-1)+1.
// 
// 2)
// { "D#" }
// { "D#" }
// 
// Returns: 0
// 
// 
// 
// 3)
// { "E", "F" }
// { "F#", "D#" }
// 
// Returns: 3
// 
// You can play this chord with the 11th fret of the "E" 
// string (playing the note "D#") and the 13th fret of the 
// "F" string (playing the note "F#").  (13-11)+1 = 3. 
// 
// 4)
// { "C", "C", "C" }
// { "C", "E", "G" }
// 
// Returns: 4
// 
// 
// 
// END CUT HERE
#line 149 "GuitarChords.cc"
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

VI st, ch;


int diff(int low, int high) {
  int a1 = (high - low + 12) % 12;
  int a2 = (low - high + 12) % 12;

  return a1 < a2 ? a1 : a2;
}

int go(int pos, int set, int &low, int &high) {
  if (pos == st.size()) {
    if (set == 0) return 0;
    return 1<<30;
  }

  int lb,hb;
  fi(ch.size()) {
    int fr = (ch[i] - st[pos] + 12) % 12;
    int l1;
    int h1;
    int r1 = go(pos + 1, set & ~(1<<i), l1, h1);
    if (r1 == 1<<30) continue;
    if (r1 == 0) {
      lb = fr;
      hb = fr;
    } else {
      if (fr != 0) {
        l1 = min(l1, fr);
        h1 = max(h1, fr);
      }
      if (diff(l1, h1) < diff(lb,hb)) {
        lb = l1;
        hb = h1;
      }
    }
  }

  if (hb == 1<<30) return hb;

  low = lb;
  high = hb;

  if (be == 0 )
  return be;

  return be + 1;
}

    class GuitarChords
        { 
        public: 
        int stretch(vector <string> strings, vector <string> chord) 
            { 
              map<string, int> notes;
              //     A, A#, B, C, C#, D, D#, E, F, F#, G, G#
              notes["A"] = 0;
              notes["A#"] = 1;
              notes["B"] = 2;
              notes["C"] = 3;
              notes["C#"] = 4;
              notes["D"] = 5;
              notes["D#"] = 6;
              notes["E"] = 7;
              notes["F"] = 8;
              notes["F#"] = 9;
              notes["G"] = 10;
              notes["G#"] = 11;

              st.resize(strings.size());
              ch.resize(chord.size());

              fi(strings.size()) st[i] = notes[strings[i]];
              fi(chord.size()) ch[i] = notes[chord[i]];

              int low = 0;
              int high = 0;
              return go(0, (1 << ch.size()) - 1, low, high);
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = { "A", "C", "F" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { "C#", "F#", "A#" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(0, Arg2, stretch(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = { "E", "A", "D", "G", "B", "E" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { "E", "G#", "B" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(1, Arg2, stretch(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = { "D#" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { "D#" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, stretch(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = { "E", "F" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { "F#", "D#" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(3, Arg2, stretch(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = { "C", "C", "C" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { "C", "E", "G" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(4, Arg2, stretch(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        GuitarChords ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
    


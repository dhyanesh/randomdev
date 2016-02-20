#include <iostream>

using namespace std;

class B {
  public:
    B() : a(1) { }
    void aa(int a) { ; }
    int a;
};

class d : public B {
  public:
    void aa(int a, int b) { ; }
};

int main(void) {
  B *b  = new d;
  cout << b->a << endl;
  return 0;
}

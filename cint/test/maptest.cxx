
#if defined(interp) && defined(makecint)
#pragma include "test.dll"
#else
#include "maptest.h"
#endif

namespace std {} using namespace std;
#include <stdio.h>

int main() {
   map<string,string> mp;
   string a("a");
   string b("b");
   mp[a] = b;
   map<string,string>::iterator i = mp.begin();
   string c = (*i).second;
   const char *res = c.c_str();
   printf("the result would be b and is : %s\n",res);
   return 0;
}

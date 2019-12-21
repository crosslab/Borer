#include <map>
#include <string>

#ifndef __hpux
using namespace std;
#endif


#ifdef __MAKECINT__
#pragma link C++ class map<string,string>;
#pragma link C++ class map<string,string>::iterator;
#endif

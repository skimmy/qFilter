#ifndef _DEBUG_H_
#define _DEBUG_H_ 1

#include <stdio.h>

#include <string>
#include <iostream>

using namespace std;

extern int _debug;
extern int __out_enabled;  

#define MESSAGE_DEBUG(msg) { if (_debug > 1 && __out_enabled) { printf("%s",msg); } }

class Debug 
{
 public:
  static void message(const string &tag, const string &msg) {
    cout << "[" << tag << "] - \"" << msg << "\"" << endl;

  }
};

#endif

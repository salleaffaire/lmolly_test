#include "lmolly/ssdbsh.hpp"

#include <iostream>
#include <list>

class buffer {
public:
   buffer() {
      mSize = 1024;
      mData = new char [1024];
   }
   ~buffer() {
      std::cout << "Deleting a buffer" << std::endl;
      delete [] mData;
   }
private:
   char *mData;
   int   mSize;
};

int main(int argc, char const *argv[])
{
   std::list<buffer *> l;
   l.push_back(new buffer);
   l.push_back(new buffer);

   // When the list of (buffer *) is passed to lmolly::ssdnsh, the responsibility of releasing each buffer 
   // is trenafered to the lmolly::ssdbsh object 
   // Each buffer will be destroyed when the object 's' is destroyed 
   lmolly::ssdbsh<buffer> s(l);

   
   return 0;
}
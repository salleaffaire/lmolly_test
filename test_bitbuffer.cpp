#include "lmolly/binfile.hpp"
#include "lmolly/bitbuffer.hpp"


int main(int argc, char const *argv[])
{
   // Onpe a binary file for input
   lmolly::binfile_in bfi("test.bin");

   lmolly::bitbuffer bb(bfi.get_data_pointer(), bfi.get_size(), LMOLLY_LITTLE_ENDIAN);

   return 0;
}
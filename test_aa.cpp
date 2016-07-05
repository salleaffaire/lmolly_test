#include "lmolly/aa.hpp"

#include <string>
#include <iostream>

bool consumes(std::string &x) {
   std::cout << " " << x << std::endl;
   return true;
}

int main(int argc, char const *argv[])
{
   // Creating a synchronizayion queue
   lmolly::aa_sync_queue<std::string> *queue = 
      new lmolly::aa_sync_queue<std::string>("Luc's queue");

   // Create a listener pool - 
   // lmolly will create 1 listener per (Cores * Threads per Core)
   // Cores * HW Threads
   lmolly::aa_listener_pool<std::string> *listener_pool = 
      new lmolly::aa_listener_pool<std::string>(queue, consumes, "Luc's pool");

   // This broker is just a debugging version 
   // It will emit a message each n milliseconds.
   lmolly::aa_broker_debug *broker = new lmolly::aa_broker_debug(queue);

   char a;
   std::cin >> a;
   
   // IMPORTANT: Delete the broker first
   delete broker;

   // Delete the listner pool second 
   delete listener_pool;

   // Delete the queue (last)
   delete queue;

   return 0;
}
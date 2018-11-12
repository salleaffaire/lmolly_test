
#include <iostream>
#include <random>

#include "lmolly/asyncs.hpp"
#include "lmolly/ctest.hpp"
#include "lmolly/task.hpp"

class Filler : public lmolly::task {
 public:
  Filler() : mpAsyncSource(nullptr), mCounter(0), mDelay(1000), mName("") {}
  Filler(lmolly::asyncsource<lmolly::ctest>& source, unsigned int delay,
         const std::string& name)
      : mpAsyncSource(&source), mCounter(0), mDelay(delay), mName(name) {}

  ~Filler() {}

  virtual int init() { return 0; }
  virtual int clean() { return 0; }
  virtual int run() {
    std::this_thread::sleep_for(std::chrono::milliseconds(mDelay));
    std::cout << "Filler " << mName << " pushing  : " << mCounter << std::endl;
    lmolly::ctest ct(mCounter++);
    mpAsyncSource->push(std::move(ct));
    return 0;
  }

 private:
  lmolly::asyncsource<lmolly::ctest>* mpAsyncSource;
  int mCounter;
  int mDelay;

  std::string mName;
};

int main(int argc, char* argv[]) {
  int rval = 0;

  // Creating an Async Source for Bob
  lmolly::asyncsource<lmolly::ctest> ctSource1;

  // Creating an Async Source for Alice (but it's the same as Alice)
  lmolly::asyncsource<lmolly::ctest> ctSource2(ctSource1);

  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> dist(200, 1000);

  unsigned int rt1 = dist(rng);
  unsigned int rt2 = dist(rng);

  Filler intSourceFiller1(ctSource1, rt1, "Bob");
  intSourceFiller1.start(false);

  Filler intSourceFiller2(ctSource2, rt2, "Alice");
  intSourceFiller2.start(false);

  while (1) {
    lmolly::ctest ct;
    // Using only Bob's source we empty every objects
    ctSource1.wait(ct);
    std::cout << "Found  : " << ct.get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  intSourceFiller1.stop_and_wait();
  intSourceFiller1.stop_and_wait();
  return rval;
}

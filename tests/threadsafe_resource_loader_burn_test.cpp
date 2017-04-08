// This file is part of UFAL C++ Utils <http://github.com/ufal/cpp_utils/>.
//
// Copyright 2017 Institute of Formal and Applied Linguistics, Faculty of
// Mathematics and Physics, Charles University in Prague, Czech Republic.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <atomic>
#include <chrono>
#include <random>
#include <thread>
#include <vector>

#include "threadsafe_resource_loader.h"

using namespace std;
using namespace ufal::utils;

atomic<unsigned> concurrent_resources(0);

class resource {
 public:

  resource(unsigned id) : id(id) {}

  bool load() {
    this_thread::sleep_for(chrono::milliseconds(id));
    if (loaded) cerr << "Multiple load of resource " << id << endl;
    loaded = true;
    concurrent_resources++;
    return true;
  }

  void release() {
    loaded = false;
    concurrent_resources--;
  }

  bool loaded = false;
 private:
  unsigned id;
};

void worker(threadsafe_resource_loader<resource>* loader, unsigned limit, unsigned id, unsigned wait_for) {
  auto res = loader->load(id);
  if (!res->loaded) cerr << "Not loaded resource " << id << endl;
  if (concurrent_resources > limit) cerr << "More than allowed number of resources" << endl;
  this_thread::sleep_for(chrono::milliseconds(wait_for));
  loader->release(id);
}

int main(int argc, char* argv[]) {
  unsigned ids = argc > 1 ? stoi(argv[1]) : 100;
  unsigned limit = argc > 2 ? stoi(argv[2]) : 20;
  unsigned requests = argc > 3 ? stoi(argv[3]) : 10000;

  vector<resource> resources;
  for (unsigned i = 0; i < ids; i++)
    resources.emplace_back(i);

  threadsafe_resource_loader<resource> loader(limit);
  for (unsigned i = 0; i < ids; i++)
    loader.add(&resources[i]);

  mt19937 generator;
  uniform_int_distribution<unsigned> distribution_ids(0, ids - 1);
  uniform_int_distribution<unsigned> distribution_waits(5, 10);

  vector<thread> threads;
  for (unsigned i = 0; i < requests; i++) {
    threads.emplace_back(worker, &loader, limit, distribution_ids(generator), distribution_waits(generator));
    this_thread::sleep_for(chrono::milliseconds(1));
  }

  for (auto&& thread : threads)
    thread.join();

  return 0;
}

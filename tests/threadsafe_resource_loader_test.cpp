// This file is part of UFAL C++ Utils <http://github.com/ufal/cpp_utils/>.
//
// Copyright 2017 Institute of Formal and Applied Linguistics, Faculty of
// Mathematics and Physics, Charles University in Prague, Czech Republic.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <chrono>
#include <thread>
#include <vector>

#include "threadsafe_resource_loader.h"

using namespace ufal::utils;

class resource {
 public:

  resource(unsigned id) : id(id) {}

  bool load() {
    cout << "Starting to load resource " << id << endl;
    this_thread::sleep_for(chrono::seconds(5));
    cout << "Loaded resource " << id << endl;
    return true;
  }

  void release() {
    cout << "Released resource " << id << endl;
  }

 private:
  unsigned id;
};

vector<resource> resources;
vector<thread> threads;

int main(int argc, char* argv[]) {
  unsigned limit = argc > 1 ? stoi(argv[1]) : 4;

  for (unsigned i = 0; i < 10; i++)
    resources.emplace_back(i);

  threadsafe_resource_loader<resource> loader(limit);
  for (unsigned i = 0; i < 10; i++)
    loader.add(&resources[i]);

  string mode;
  unsigned id;
  while (cin >> mode >> id) {
    if (mode == "l") {
      threads.emplace_back([&loader](unsigned id) {
        cout << "Loader: loading " << id << endl;
        loader.load(id);
        cout << "Loader: loaded " << id << endl;
      }, id);
    }

    if (mode == "r") {
      cout << "Loader: releasing " << id << endl;
      loader.release(id);
    }
  }

  for (auto&& thread : threads)
    thread.join();

  return 0;
}

// This file is part of UFAL C++ Utils <http://github.com/ufal/cpp_utils/>.
//
// Copyright 2015 Institute of Formal and Applied Linguistics, Faculty of
// Mathematics and Physics, Charles University in Prague, Czech Republic.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "url_detector.h"

using namespace ufal::utils;

int main(void) {
  string line;
  while (getline(cin, line)) {
    auto whole_type = url_detector::detect(line);

    size_t prefix;
    auto prefix_type = url_detector::detect(line, &prefix);

    cout << "Whole type: " << whole_type << ", prefix_type: " << prefix_type << ", prefix_length: " << prefix << endl;
  }
  return 0;
}

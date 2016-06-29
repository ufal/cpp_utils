// This file is part of UFAL C++ Utils <http://github.com/ufal/cpp_utils/>.
//
// Copyright 2016 Institute of Formal and Applied Linguistics, Faculty of
// Mathematics and Physics, Charles University in Prague, Czech Republic.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "named_values.h"

using namespace ufal::utils;

int main(void) {
  named_values::map values;

  string line, error;
  while (getline(cin, line)) {
    if (!named_values::parse(line, values, error)) {
      cerr << "Cannot parse named values: " << error << endl;
    } else {
      for (auto&& named_value : values)
        cerr << "  " << named_value.first << ": " << named_value.second << endl;
      cerr << endl;
    }
  }
  return 0;
}

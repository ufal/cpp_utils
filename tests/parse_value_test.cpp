// This file is part of UFAL C++ Utils <http://github.com/ufal/cpp_utils/>.
//
// Copyright 2017 Institute of Formal and Applied Linguistics, Faculty of
// Mathematics and Physics, Charles University in Prague, Czech Republic.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "parse_double.h"
#include "parse_int.h"

using namespace ufal::utils;

int main(void) {
  string line, error;
  while (getline(cin, line)) {
    int int_value;
    if (!parse_int(line, "int_value", int_value, error))
      cerr << "Cannot parse int_value: " << error << endl;
    else
      cout << "Int value: " << int_value << endl;

    double double_value;
    if (!parse_double(line, "double_value", double_value, error))
      cerr << "Cannot parse double_value: " << error << endl;
    else
      cout << "Double value: " << double_value << endl;
  }
  return 0;
}

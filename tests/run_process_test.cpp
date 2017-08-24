// This file is part of UFAL C++ Utils <http://github.com/ufal/cpp_utils/>.
//
// Copyright 2017 Institute of Formal and Applied Linguistics, Faculty of
// Mathematics and Physics, Charles University in Prague, Czech Republic.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "run_process.h"
#include "split.h"

using namespace ufal::utils;

int main(int argc, char* argv[]) {
  if (argc > 1) {
    cout << argv[1];
    return 0;
  }

  string line, output;
  vector<string> pieces;
  while (getline(cin, line)) {
    split(line, '0', pieces);

    if (!run_process(pieces, nullptr, &output, nullptr))
      cerr << "Command failed!" << endl;
    else
      cout << "Command succeeded, result is @" << output << "@" << endl;
  }

  return 0;
}

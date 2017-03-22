// This file is part of UFAL C++ Utils <http://github.com/ufal/cpp_utils/>.
//
// Copyright 2015 Institute of Formal and Applied Linguistics, Faculty of
// Mathematics and Physics, Charles University in Prague, Czech Republic.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "binary_decoder.h"
#include "binary_encoder.h"
#include "compressor.h"
#include "getpara.h"
#include "getwhole.h"
#include "iostreams.h"
#include "named_values.h"
#include "new_unique_ptr.h"
#include "options.h"
#include "parse_double.h"
#include "parse_int.h"
#include "pointer_decoder.h"
#include "process_args.h"
#include "split.h"
#include "string_piece.h"
#include "threadsafe_stack.h"
#include "url_detector.h"
#include "xml_encoded.h"

using namespace ufal::utils;

void binary_decoder_compilation() {
  binary_decoder dec;
  string str;

  dec.fill(10);
  dec.next_1B();
  dec.next_2B();
  dec.next_4B();
  dec.next_str(str);
  dec.next<char>(1);

  dec.is_end();
  dec.seek(dec.tell());
}

void binary_encoder_compilation() {
  binary_encoder enc;
  enc.add_1B(1);
  enc.add_2B(2);
  enc.add_4B(4);
  enc.add_float(1.);
  enc.add_double(1.);
  enc.add_str("a");
  enc.add_data("a");
  enc.add_data(vector<int>{1,2,3});
  enc.add_data("a", 1);
}

void getpara_compilation() {
  string str;

  getpara(cin, str);
}

void getwhole_compilation() {
  string str;

  getwhole(cin, str);
}

void iostreams_compilation() {
  iostreams_init();
  iostreams_init_binary_input();
  iostreams_init_binary_output();
}

void named_values_compilation() {
  named_values::map values;
  string error;

  named_values::parse("a=b;c=data:3:1;2", values, error);
}

void new_unique_ptr_compilation() {
  auto ptr = new_unique_ptr<int>(1);
}

void options_compilation(int argc, char* argv[]) {
  options::map m;
  options::parse({{"none", options::value::none},{"any", options::value::any}, {"set", options::value{"set"}}}, argc, argv, m);
}

void parse_double_compilation() {
  parse_double("1.23e-45", "number");
}

void parse_int_compilation() {
  parse_int("1", "number");
}

void pointer_decoder_compilation() {
  const unsigned char* ptr = nullptr;
  pointer_decoder dec(ptr);
  string str;

  dec.next_1B();
  dec.next_2B();
  dec.next_4B();
  dec.next_str(str);
  dec.next<char>(1);
}

void process_args_compilation(int argi, int argc, char* argv[]) {
  process_args(argi, argc, argv, [](istream&, ostream&, string_piece){}, "a");
}

void split_compilation() {
  vector<string> strings;
  vector<string_piece> pieces;

  split("1 2 3", ' ', strings);
  split("1 2 3", ' ', pieces);
}

void threadsafe_stack_compilation() {
  threadsafe_stack<int> stack;
  stack.push(nullptr);
  stack.pop();
}

void url_detector_compilation() {
  url_detector::detect("http://ufal.mff.cuni.cz");
}

void xml_encoded_compilation() {
  string str;

  cout << xml_encoded("a") << xml_encoded(str, true);
}

int main(void) {
  return 0;
}

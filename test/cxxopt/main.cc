#include <exception>
#include <iostream>

#include "cxxopts.hpp"

int main(int argc, char *argv[]) {
  std::string in_file = "ai_core.bin";
  std::string out_file = "prof.json";
  std::string out_csv_file = "prof.csv";
  cxxopts::Options options("prof_tool", "One line description of prof_tool");
  options.allow_unrecognised_options().add_options()                                                       //
    ("i, input", "Input profile bin file.", cxxopts::value<std::string>())                                 // input without default value
    ("o, output", "Profile result json file.", cxxopts::value<std::string>()->default_value(out_file))     // output file with default
    ("output-csv", "Profile result csv file.", cxxopts::value<std::string>()->default_value(out_csv_file)) // output csv file with default
    ("h,help", "Usage help");

  cxxopts::ParseResult result;
  try {
    result = options.parse(argc, argv);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    std::cout << options.help() << std::endl;
    exit(0);
  }

  if (result.count("help") || !result.count("input")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }

  if (result.count("input")) in_file = result["input"].as<std::string>();
  if (result.count("output")) out_file = result["output"].as<std::string>();
  if (result.count("output-csv")) out_csv_file = result["output-csv"].as<std::string>();
}

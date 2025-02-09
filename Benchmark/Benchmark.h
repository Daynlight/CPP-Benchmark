#pragma once
#include <chrono>
#include <string>
#include <vector>

namespace Benchmark{
class Benchmark{
public:
  std::vector<std::string> result;
public:
  static Benchmark &get() {   
    static Benchmark benchmark;
    return benchmark; 
  };
}; // class Benchmark

struct Timer{
private:
  const std::string label;
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
Timer(const std::string &label = "Timer") : label(label), start(std::chrono::high_resolution_clock::now()) {};
~Timer(){
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::string result = label + ": " + std::to_string(duration.count()) + " microseconds";
  Benchmark::get().result.emplace_back(result);
};
}; // struct Timer
} // namespace Benchmark
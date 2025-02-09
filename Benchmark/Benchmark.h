#pragma once
#include <chrono>
#include <string>
#include <vector>


namespace Benchmark{
class Benchmark{
  public:
  bool count_allocs = false;
  size_t allocs;
  size_t deallocs;
  public:
  std::vector<std::string> result;
  public:
  static Benchmark &get() {   
    static Benchmark benchmark;
    return benchmark; 
  };
}; // class Benchmark

class Timer{
  private:
  const std::string label;
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
  public:
  Timer(const std::string &label = "Timer: ") : label(label), start(std::chrono::high_resolution_clock::now()) {};
  ~Timer(){
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    Benchmark::get().result.emplace_back(label + ": " + std::to_string(duration.count()) + " microseconds");
  };
}; // struct Timer

class Allocs{
  private:
    std::string label;
  public:
  Allocs(std::string label = "Allocs: ") : label(label)
    { Benchmark::get().count_allocs = true; Benchmark::get().allocs = 0; Benchmark::get().deallocs = 0; };
  ~Allocs() { 
    Benchmark::get().count_allocs = false; 
    Benchmark::get().result.emplace_back(label + ": " + std::to_string(Benchmark::get().allocs) + " allocs, " + std::to_string(Benchmark::get().deallocs) + " deallocs"); 
  };
}; // struct Allocs

}; // namespace Benchmark

void* operator new(size_t size) noexcept {
  if(Benchmark::Benchmark::get().count_allocs)
    Benchmark::Benchmark::get().allocs++;
  return malloc(size);
};

void operator delete(void *ptr) noexcept{
  if(Benchmark::Benchmark::get().count_allocs)
    Benchmark::Benchmark::get().deallocs++;
  free(ptr);
};

void operator delete(void *ptr, std::size_t size) noexcept {
  if(Benchmark::Benchmark::get().count_allocs)
      Benchmark::Benchmark::get().deallocs++;
  free(ptr);
}
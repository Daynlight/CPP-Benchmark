#include "Benchmark.h"

int main(){

  {
    Benchmark::Timer timer("Print ! 10000 times");
    for(int i = 0; i < 10000; i++)
      printf("!");
  }
  
  for(const std::string &line : Benchmark::Benchmark::get().result)
    printf("%s\n", line.c_str());
  return 0;
}
#include "Benchmark.h"
#include <vector>

struct Vec3{
  float x, y, z;
  Vec3(float x, float y, float z) : x(x), y(y), z(z) {};
};

int main(){

  {
    std::vector<Vec3*> vec;

    Benchmark::Timer timer("create vec3 10000 times");
    Benchmark::Allocs allocs("allocs vec3 10000 times");

    for(int i = 0; i < 600000000; i++)
      vec.emplace_back(new Vec3(1.0f, 2.0f, 3.0f));

    while(vec.size()) {
      Vec3* vecN = vec.back();
      vec.pop_back();
      delete vecN;
    };
  }
  
  printf("\n");
  for(const std::string &line : Benchmark::Benchmark::get().result)
    printf("%s\n", line.c_str());
  return 0;
}
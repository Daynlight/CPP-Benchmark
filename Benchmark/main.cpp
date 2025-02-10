#include "Benchmark.h"
#include <vector>

struct Vec3{
  float x, y, z;
  Vec3(float x, float y, float z) : x(x), y(y), z(z) {};
};

int main(){

  {
    std::vector<Vec3*> vec;
    vec.reserve(10000000);

    Benchmark::Timer timer("create vec3 10000 times");
    Benchmark::Allocs allocs("allocs vec3 10000 times");

    for(int i = 0; i < vec.capacity(); i++){
      allocs.start();
      Vec3* vecN = new Vec3(1.0f, 2.0f, 3.0f);
      allocs.stop();
      vec.emplace_back(vecN);
    }
     

    while(vec.size()) {
      Vec3* vecN = vec.back();
      vec.pop_back();
      allocs.start();
      delete vecN;
      allocs.stop();
    };
  }
  
  printf("\n");
  for(const std::string &line : Benchmark::Benchmark::get().result)
    printf("%s\n", line.c_str());
  return 0;
}
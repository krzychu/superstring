#include <instance.h>
int main(){
  Instance I(4);

  I.randomize(5, 100, 0.7);
  I.save("gdb.test");

  I.randomize(5, 5000, 0.7);
  I.save("test_5_5000_0.7.test");

  I.randomize(10, 5000, 0.8);
  I.save("test_10_5000_0.8.test");

  I.randomize(50, 4000, 0.8);
  I.save("test_50_4000_0.8.test");

  I.randomize(50, 50000, 0.8);
  I.save("test_50_50000_0.8.test");

  I.randomize(100, 6500, 0.4);
  I.save("test_100_6500_0.4.test");

  I.randomize(200, 40000, 0.8);
  I.save("test_200_40000_0.8.test");

  I.randomize(400, 40000, 0.8);
  I.save("test_400_40000_0.8.test");

  I.randomize(1000, 65000, 0.8);
  I.save("test_1000_65000_0.8.test");

  return 0;
}

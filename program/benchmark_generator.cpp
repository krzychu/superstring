#include <instance.h>
int main(){
  Instance I(4);
  I.randomize(7, 350, 0.7);
  I.save("temp1.txt");
  I.clear();
  I.save("temp0.txt");
  I.randomize(100, 10000, 0.5);
  I.save("temp2.txt");
  I.randomize(1000, 3500000, 0.7);
  I.save("temp3.txt");
  I.randomize(7000, 6500000, 0.85);
  I.save("temp4.txt");
  return 0;
}
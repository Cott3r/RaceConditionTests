#include <iostream>
#include "Worker.h"
#include "GradientDescent.h"

using namespace std;

int main(int argc, char* argv[])
{
//  Worker* worker = new Worker();
//  worker->doWork();

  GradientDescent gd = GradientDescent(1000);

  gd.findPosition();

  return 0;
}

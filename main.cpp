#include <iostream>
#include "Worker.h"

using namespace std;

int main(int argc, char* argv[])
{
  Worker* worker = new Worker();

  worker->doWork();

  return 0;
}

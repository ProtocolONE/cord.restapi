#include "gtest/gtest.h"
#include <QtCore/QCoreApplication>

#ifdef NDEBUG
#pragma comment(lib, "lib/gtest.lib")
#else
#pragma comment(lib, "lib/gtestd.lib")
#endif

#ifdef _DEBUG
#pragma comment(lib, "RestApiX86d.lib")
#else
#pragma comment(lib, "RestApiX86.lib")
#endif 

#include <stdio.h>

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();

  int i;
  std::cin >> i;
}

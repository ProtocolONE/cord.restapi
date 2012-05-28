#include "gtest/gtest.h"
#include <QtCore/QCoreApplication>

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

  int res = RUN_ALL_TESTS();

  return res;
}

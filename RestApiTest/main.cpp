#include <gtest/gtest.h>

#include <RestApi/GameNetCredential.h>
#include <RestApi/CommandBase>

#include <QtCore/QCoreApplication>
#include <QtCore/QMetaType>

#ifdef VLD_CHECK_ENABLED
#include <vld.h>
#pragma comment(lib, "vld.lib")
#endif

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  testing::InitGoogleTest(&argc, argv);
  int res = RUN_ALL_TESTS();
  return res;
}

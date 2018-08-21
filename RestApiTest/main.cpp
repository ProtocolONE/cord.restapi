#include <gtest/gtest.h>

#include <RestApi/GameNetCredential.h>
#include <RestApi/CommandBase.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QMetaType>

#include <RestApi/RegisterTypes.h>

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  P1::RestApi::registerTypes();

  testing::InitGoogleTest(&argc, argv);
  int res = RUN_ALL_TESTS();
  return res;
}

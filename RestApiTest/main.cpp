#include <gtest/gtest.h>

#include <RestApi/GameNetCredential.h>
#include <RestApi/Auth/GameNetAuthBase.h>
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
  
  qRegisterMetaType<GGS::RestApi::GameNetCredential>("GGS::RestApi::GameNetCredential");
  qRegisterMetaType<GGS::RestApi::Auth::GameNetAuthBase::AuthResultCodes>("GGS::RestApi::Auth::GameNetAuthBase::AuthResultCodes");
  qRegisterMetaType<GGS::RestApi::CommandBase::Error>("GGS::RestApi::CommandBase::Error");

  testing::InitGoogleTest(&argc, argv);
  int res = RUN_ALL_TESTS();

  return res;
}

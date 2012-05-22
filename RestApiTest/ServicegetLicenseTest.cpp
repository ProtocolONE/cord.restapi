#include <RestApi/Commands/Service/GetLicense.h>
#include <RestApi/RestApiManager>
#include <RestApi/HttpCommandRequest>
#include <RestApi/FakeCache>

#include <gtest/gtest.h>
#include <QtCore/QEventLoop>
#include <QtCore/QTimer>
#include <QtTest/QSignalSpy>

TEST(RestApiCommands, GetLicenseTest)
{
  using GGS::RestApi::RestApiManager;
  using GGS::RestApi::HttpCommandRequest;
  using GGS::RestApi::FakeCache;

  RestApiManager manager;
  manager.setUri("http://api.gamenet.dev/restapi");
  HttpCommandRequest httpCommandRequest;
  manager.setRequest(&httpCommandRequest);
  FakeCache fakeCache;
  httpCommandRequest.setCache(&fakeCache);

  QEventLoop loop;

  using GGS::RestApi::Commands::Service::GetLicense;
  GetLicense cmd("300002010000000000");
  cmd.setHash("fakeCache");
  manager.execute(&cmd);

  QSignalSpy spy(&cmd, SIGNAL(result(GGS::RestApi::CommandBaseInterface::CommandResults)));
  QTimer::singleShot(5000, &loop, SLOT(quit()));
  loop.exec();

  ASSERT_EQ(1, spy.count());
  ASSERT_TRUE(cmd.isLicenseNew());
  QString responseHash = cmd.responseHash();

  GetLicense cmd2("300002010000000000");
  cmd2.setHash(responseHash);

  QEventLoop loop2;
  manager.execute(&cmd2);

  QSignalSpy spy1(&cmd2, SIGNAL(result(GGS::RestApi::CommandBaseInterface::CommandResults)));
  QTimer::singleShot(5000, &loop2, SLOT(quit()));
  loop2.exec();

  ASSERT_EQ(1, spy1.count());
  ASSERT_FALSE(cmd2.isLicenseNew());
}
#include <gtest/gtest.h>

#include <QtCore/QEventLoop>
#include <QtCore/QTimer>

#include <RestApi/Api/V1/Auth/Login.h>
#include <RestApi/Api/V1/GetHost.h>

#include <RestApi/RestApiManager.h>
#include <RestApi/ProtocolOneCredential.h>

TEST(GetHost, Normal)
{
  using namespace P1::RestApi;
  using Api::V1::GetHost;

  QEventLoop loop;

  QTimer timer;
  QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
  timer.start(30000);

  RestApiManager manager;
  manager.setUri("http://vb-api.protocol.one:8021");

  GetHost *cmd = new GetHost(&manager);

  QObject::connect(cmd, &GetHost::result, &timer, &QTimer::stop);
  QObject::connect(cmd, &GetHost::result, &loop, &QEventLoop::quit);

  cmd->execute(&manager);
  loop.exec();

  ASSERT_EQ(1, cmd->servicesData().length());


}
#include <gtest/gtest.h>

#include <QtCore/QEventLoop>
#include <QtCore/QTimer>

#include <RestApi/Api/V1/Auth/Login.h>
#include <RestApi/Api/V1/Auth/Refresh.h>

#include <RestApi/RestApiManager.h>
#include <RestApi/ProtocolOneCredential.h>

TEST(Login, Simple)
{
  using namespace P1::RestApi;
  using Api::V1::Auth::Login;
  using Api::V1::Auth::Refresh;

  QEventLoop loop;

  QTimer timer;
  QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
  timer.start(30000);

  RestApiManager manager;
  manager.setUri("http://vb-auth.protocol.one:8001");

  Login *login = new Login("gna@unit.test", "123456", "", &manager);
  QObject::connect(login, &Login::result, &timer, &QTimer::stop);
  QObject::connect(login, &Login::result, &loop, &QEventLoop::quit);

  login->execute(&manager);
  loop.exec();

  ProtocolOneCredential credential(login->accessToken(), login->acccessTokenExpiredTime());
  ASSERT_TRUE(credential.isValid());

  Refresh *refresh = new Refresh(login->refreshToken(), &manager);

  QObject::connect(refresh, &Login::result, &timer, &QTimer::stop);
  QObject::connect(refresh, &Login::result, &loop, &QEventLoop::quit);

  refresh->execute(&manager);

  loop.exec();

  ProtocolOneCredential credential2(refresh->accessToken(), refresh->acccessTokenExpiredTime());
  ASSERT_TRUE(credential2.isValid());
}
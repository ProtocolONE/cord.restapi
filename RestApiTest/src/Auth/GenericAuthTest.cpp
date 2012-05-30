#include <gtest/gtest.h>
#include <TestEventLoopFinisher.h>

#include <RestApi/Auth/GenericAuth.h>
#include <RestApi/GameNetCredential.h>

#include <QtCore/QWaitCondition>
#include <QtCore/QEventLoop>
#include <QSignalSpy>

using GGS::RestApi::Auth::GenericAuth;

class GenericAuthTest : public ::testing::Test
{
public:

  void DoCheck(GGS::RestApi::Auth::GenericAuth &genericAuth, int successCount, int failedCount) {
    QSignalSpy succesSpy(&genericAuth, SIGNAL(authResult(const GGS::RestApi::GameNetCredential)));
    QSignalSpy failedSpy(&genericAuth, SIGNAL(authFailed(GGS::RestApi::Auth::GameNetAuthBase::AuthResultCodes)));

    genericAuth.login();

    QEventLoop loop;
    TestEventLoopFinisher loopKiller(&loop, 10000);
    QObject::connect(&genericAuth, SIGNAL(authResult(const GGS::RestApi::GameNetCredential)), &loopKiller, SLOT(terminateLoop()));
    QObject::connect(&genericAuth, SIGNAL(authFailed(GGS::RestApi::Auth::GameNetAuthBase::AuthResultCodes)), &loopKiller, SLOT(terminateLoop()));

    loop.exec();
    ASSERT_FALSE(loopKiller.isKilledByTimeout());

    ASSERT_EQ(successCount, succesSpy.count());
    ASSERT_EQ(failedCount, failedSpy.count());
  }
};

TEST_F(GenericAuthTest, successAuthTest)
{
  GenericAuth genericAuth;
  genericAuth.setAuthUrl(QString("https://gnlogin.gamenet.dev/"));
  genericAuth.setLogin(QString("gna@unit.test"));
  genericAuth.setPassword(QString("123456"));

  DoCheck(genericAuth, 1, 0);
}

TEST_F(GenericAuthTest, failedAuthTest)
{
  GenericAuth genericAuth;
  genericAuth.setAuthUrl(QString("https://gnlogin.gamenet.dev/"));
  genericAuth.setLogin(QString("gna@unit.test"));
  genericAuth.setPassword(QString("123456789"));

  DoCheck(genericAuth, 0, 1);
}
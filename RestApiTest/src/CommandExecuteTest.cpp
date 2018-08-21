#include <RestApi/RestApiManager.h>
#include <RestApi/CommandBase.h>
#include <RestApi/Commands/User/GetProfile.h>
#include <RestApi/GameNetCredential.h>
#include <RestApi/FakeCache.h>

#include "TestEventLoopFinisher.h"

#include <QtCore/QEventLoop>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtTest/QSignalSpy>
#include <gtest/gtest.h>

using namespace P1::RestApi;
class CommandStaticExecuteTest : public ::testing::Test {
public:
  void SetUp() {
    _credential.setUserId("400001000001634860");
    _credential.setAppKey("4c2f65777d38eb07d32d111061005dcd5a119150");
    _manager.setCache(&_cache);
    _manager.setCridential(_credential);
    _manager.setRequest(RequestFactory::Http);
    _manager.setUri("https://gnapi.com/restapi");

    RestApiManager::setCommonInstance(&_manager);
  }

  void executeCommand(CommandBase *command) {
    QEventLoop loop;
    TestEventLoopFinisher killer(&loop, 50000);
    
    QSignalSpy spy(command, SIGNAL(result(P1::RestApi::CommandBase::CommandResults)));
    QObject::connect(command, SIGNAL(result(P1::RestApi::CommandBase::CommandResults)), 
      &killer, SLOT(terminateLoop()));

    command->execute();
    loop.exec();

    ASSERT_FALSE(killer.isKilledByTimeout());
    ASSERT_EQ(1, spy.count());
    QList<QVariant> arguments = spy.takeFirst();
    this->_lastResult = arguments.at(0).value<P1::RestApi::CommandBase::CommandResults>();
  }

  GameNetCredential _credential;
  FakeCache _cache;
  RestApiManager _manager;
  P1::RestApi::CommandBase::CommandResults _lastResult;
};

TEST_F(CommandStaticExecuteTest, GetProfileTest)
{
  P1::RestApi::Commands::User::GetProfile command;
  command.setProfileId(QStringList("400001000001634860"));
  this->executeCommand(&command);
  ASSERT_EQ(CommandBase::NoError, _lastResult);

  P1::RestApi::Commands::User::Response::UserGetProfileResponse profile = command.response()["400001000001634860"];

  ASSERT_EQ(QString("gnaunittest"), profile.nickname());
  ASSERT_EQ(QString("gnaunittest"), profile.nametech());
}

TEST_F(CommandStaticExecuteTest, GenericErrorTest)
{
  P1::RestApi::Commands::User::GetProfile command;
  _credential.setAppKey("fakeAppKeyHehe");
  _manager.setCridential(_credential);
  QSignalSpy errorSpy(&_manager, SIGNAL(genericError(P1::RestApi::CommandBase::Error, QString)));

  this->executeCommand(&command);
  ASSERT_EQ(CommandBase::GenericError, _lastResult);
  this->executeCommand(&command);
  ASSERT_EQ(CommandBase::GenericError, _lastResult);

  P1::RestApi::Commands::User::GetProfile command2;

  this->executeCommand(&command2);
  ASSERT_EQ(CommandBase::GenericError, _lastResult);
  this->executeCommand(&command2);
  ASSERT_EQ(CommandBase::GenericError, _lastResult);

  ASSERT_EQ(4, errorSpy.count());
  QList<QVariant> arguments = errorSpy.takeFirst();
  ASSERT_EQ(CommandBase::AuthorizationFailed, arguments.at(0).value<P1::RestApi::CommandBase::Error>());
}
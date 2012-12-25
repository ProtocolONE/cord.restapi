#include <RestApi/RestApiManager>
#include <RestApi/CommandBase>
#include <RestApi/Commands/User/GetUserMainInfo>
#include <RestApi/GameNetCredential>
#include <RestApi/FakeCache>

#include "TestEventLoopFinisher.h"

#include <QtCore/QEventLoop>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtTest/QSignalSpy>
#include <gtest/gtest.h>

using namespace GGS::RestApi;
class CommandStaticExecuteTest : public ::testing::Test {
public:
  void SetUp() {
    _credential.setUserId("400001000001634860");
    _credential.setAppKey("c99ebc84714c0c316dd891602dc916d238ef73ed");
    _manager.setCache(&_cache);
    _manager.setCridential(_credential);
    _manager.setRequest(RequestFactory::Http);
    _manager.setUri("https://gnapi.com/restapi");

    RestApiManager::setCommonInstance(&_manager);
  }

  void executeCommand(CommandBase *command) {
    QEventLoop loop;
    TestEventLoopFinisher killer(&loop, 50000);
    
    QSignalSpy spy(command, SIGNAL(result(GGS::RestApi::CommandBase::CommandResults)));
    QObject::connect(command, SIGNAL(result(GGS::RestApi::CommandBase::CommandResults)), 
      &killer, SLOT(terminateLoop()));

    command->execute();
    loop.exec();

    ASSERT_FALSE(killer.isKilledByTimeout());
    ASSERT_EQ(1, spy.count());
    QList<QVariant> arguments = spy.takeFirst();
    this->_lastResult = arguments.at(0).value<GGS::RestApi::CommandBase::CommandResults>();
  }

  GameNetCredential _credential;
  FakeCache _cache;
  RestApiManager _manager;
  GGS::RestApi::CommandBase::CommandResults _lastResult;
};

TEST_F(CommandStaticExecuteTest, GetProfileTest)
{
  GGS::RestApi::Commands::User::GetUserMainInfo command;
  this->executeCommand(&command);
  ASSERT_EQ(CommandBase::NoError, _lastResult);
  ASSERT_EQ(QString("gnaunittest"), command.response()->nickname());
  ASSERT_EQ(QString("gnaunittest"), command.response()->nametech());
}

TEST_F(CommandStaticExecuteTest, GenericErrorTest)
{
  GGS::RestApi::Commands::User::GetUserMainInfo command;
  _credential.setAppKey("fakeAppKeyHehe");
  _manager.setCridential(_credential);
  QSignalSpy errorSpy(&_manager, SIGNAL(genericError(GGS::RestApi::CommandBase::Error, QString)));

  this->executeCommand(&command);
  ASSERT_EQ(CommandBase::GenericError, _lastResult);
  this->executeCommand(&command);
  ASSERT_EQ(CommandBase::GenericError, _lastResult);

  GGS::RestApi::Commands::User::GetUserMainInfo command2;

  this->executeCommand(&command2);
  ASSERT_EQ(CommandBase::GenericError, _lastResult);
  this->executeCommand(&command2);
  ASSERT_EQ(CommandBase::GenericError, _lastResult);

  ASSERT_EQ(4, errorSpy.count());
  QList<QVariant> arguments = errorSpy.takeFirst();
  ASSERT_EQ(CommandBase::AuthorizationFailed, arguments.at(0).value<GGS::RestApi::CommandBase::Error>());
}
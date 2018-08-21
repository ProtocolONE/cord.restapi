#include <gtest/gtest.h>
#include <TestEventLoopFinisher.h>

#include <RestApi/RestApiManager.h>
#include <RestApi/RequestFactory.h>
#include <RestApi/Commands/Service/GetDetailedServices.h>

#include <QtCore/QObject>
#include <QtCore/QEventLoop>
#include <QtConcurrentRun>
#include <QtTest/QSignalSpy>

using P1::RestApi::RestApiManager;
using P1::RestApi::RequestFactory;
using P1::RestApi::Commands::Service::GetDetailedServices;

class RestApiManagerTest : public ::testing::Test
{
public:
  virtual void SetUp() 
  {
    manager = new RestApiManager();
    manager->setRequest(RequestFactory::Http);
    manager->setUri("https://gnapi.com/restapi");
  }

  virtual void TearDown() 
  {
    delete manager;
  }

  RestApiManager *manager;
  QEventLoop loop;
};

TEST_F(RestApiManagerTest, executionTest)
{
  GetDetailedServices command;
   
  TestEventLoopFinisher loopKiller(&loop, 20000);
  QObject::connect(&command, SIGNAL(result(P1::RestApi::CommandBase::CommandResults)), 
    &loopKiller, SLOT(terminateLoop()));

  manager->execute(&command);
  loop.exec();

  ASSERT_FALSE(loopKiller.isKilledByTimeout());
  ASSERT_EQ(0, command.errorCode());
}
//DISABLED_
TEST_F(RestApiManagerTest, multiExecutionTest)
{
  GetDetailedServices command1;
  GetDetailedServices command2;
  GetDetailedServices command3;

  QSignalSpy spyCommand1(&command1, SIGNAL(result(P1::RestApi::CommandBase::CommandResults)));
  QSignalSpy spyCommand2(&command2, SIGNAL(result(P1::RestApi::CommandBase::CommandResults)));
  QSignalSpy spyCommand3(&command3, SIGNAL(result(P1::RestApi::CommandBase::CommandResults)));

  TestEventLoopFinisher loopKiller(&loop, 10000, 3);
  QObject::connect(&command1, SIGNAL(result(P1::RestApi::CommandBase::CommandResults)), 
    &loopKiller, SLOT(terminateLoop()));
  QObject::connect(&command2, SIGNAL(result(P1::RestApi::CommandBase::CommandResults)), 
    &loopKiller, SLOT(terminateLoop()));
  QObject::connect(&command3, SIGNAL(result(P1::RestApi::CommandBase::CommandResults)), 
    &loopKiller, SLOT(terminateLoop()));

  manager->execute(&command1);
  manager->execute(&command2);
  manager->execute(&command3);
  loop.exec();

  ASSERT_EQ(1, spyCommand1.count());
  ASSERT_EQ(1, spyCommand2.count());
  ASSERT_EQ(1, spyCommand3.count());
}

TEST_F(RestApiManagerTest, DISABLED_executionConcurrentTest)
{
  GetDetailedServices command;

  TestEventLoopFinisher loopKiller(&loop, 20000);
  QObject::connect(&command, SIGNAL(result(P1::RestApi::CommandBase::CommandResults)), 
    &loopKiller, SLOT(terminateLoop()));

  QtConcurrent::run(manager, &RestApiManager::execute, &command);
  loop.exec();

  ASSERT_FALSE(loopKiller.isKilledByTimeout());
  ASSERT_EQ(0, command.errorCode());
}

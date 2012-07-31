#include <CommandTest.h>
#include <TestEventLoopFinisher.h>

#include <RestApi/HttpCommandRequest>

#include <QtCore/QEventLoop>

void CommandTest::execute(GGS::RestApi::CommandBase *command)
{
  GGS::RestApi::HttpCommandRequest request;

  QEventLoop loop;
  TestEventLoopFinisher loopKiller(&loop, 20000);
  QObject::connect(command, SIGNAL(result(GGS::RestApi::CommandBase::CommandResults)), 
    &loopKiller, SLOT(terminateLoop()));

  QObject::connect(&request, SIGNAL(finish(GGS::RestApi::CommandBase::CommandResults, QString)),
    command, SLOT(resultCallback(GGS::RestApi::CommandBase::CommandResults, QString))); 

  request.execute(command->url());
  loop.exec();

  ASSERT_FALSE(loopKiller.isKilledByTimeout());
}

void CommandTest::executeWithAuth(GGS::RestApi::CommandBase *command)
{
  command->appendParameter("appKey", "c99ebc84714c0c316dd891602dc916d238ef73ed");
  command->appendParameter("userId", "400001000001634860");

  this->execute(command);
}

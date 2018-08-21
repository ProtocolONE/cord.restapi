#include <CommandTest.h>
#include <TestEventLoopFinisher.h>

#include <RestApi/HttpCommandRequest.h>

#include <QtCore/QEventLoop>

void CommandTest::execute(P1::RestApi::CommandBase *command)
{
  P1::RestApi::HttpCommandRequest request;

  QEventLoop loop;
  TestEventLoopFinisher loopKiller(&loop, 20000);
  QObject::connect(command, SIGNAL(result(P1::RestApi::CommandBase::CommandResults)), 
    &loopKiller, SLOT(terminateLoop()));

  QObject::connect(&request, SIGNAL(finish(P1::RestApi::CommandBase::CommandResults, QString)),
    command, SLOT(resultCallback(P1::RestApi::CommandBase::CommandResults, QString))); 

  request.execute(command->url());
  loop.exec();

  ASSERT_FALSE(loopKiller.isKilledByTimeout());
}

void CommandTest::executeWithAuth(P1::RestApi::CommandBase *command)
{
  command->appendParameter("appKey", "4c2f65777d38eb07d32d111061005dcd5a119150");
  command->appendParameter("userId", "400001000001634860");

  this->execute(command);
}

#include "CommandResultGetter.h"
#include "gtest/gtest.h"

CommandResultGetter::CommandResultGetter(void)
{
}


CommandResultGetter::~CommandResultGetter(void)
{
}

void CommandResultGetter::commandResult( GGS::RestApi::CommandBaseInterface::CommandResults code )
{
  ASSERT_TRUE(code == GGS::RestApi::CommandBaseInterface::NoError);
  loop.exit();
}

void CommandResultGetter::genericError(const QString& message, int messageId )
{
//   qDebug() << "[DEBUG] generic Error " << message << " " << messageId ;
}

void CommandResultGetter::test2() 
{
  using GGS::RestApi::RestApiManager;
  using GGS::RestApi::HttpCommandRequest;

  using GGS::RestApi::Commands::Service::GetDetailedServices;
  using GGS::RestApi::Commands::Service::Response::DetailedServicesResponse;
  using GGS::RestApi::Commands::Service::Response::DetailedServiceInfo;
  using GGS::RestApi::CommandBaseInterface;
  using GGS::RestApi::FakeCache;

  RestApiManager restapi;
  HttpCommandRequest request;
  FakeCache cache;
  request.setCache(&cache);

  restapi.setRequest(&request);
  restapi.setUri(QString("http://api.gamenet.dev/restapi"));

  GetDetailedServices cmd;
  cmd.appendParameter("someRusParam", QString::fromLocal8Bit("Привет, Мир!"));
  cmd.appendParameter("lang", "en");
  ASSERT_TRUE(QObject::connect(&cmd, SIGNAL(result(GGS::RestApi::CommandBaseInterface::CommandResults)), this, SLOT(commandResult(GGS::RestApi::CommandBaseInterface::CommandResults))));

  restapi.execute(&cmd);
  loop.exec();
}

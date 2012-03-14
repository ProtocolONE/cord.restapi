#include "CommandResultGetter.h"


CommandResultGetter::CommandResultGetter(void)
{
}


CommandResultGetter::~CommandResultGetter(void)
{
}

void CommandResultGetter::commandResult( )
{
  loop.exit();
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
  QObject::connect(&cmd, SIGNAL(result()), this, SLOT(commandResult()));

  restapi.execute(&cmd);
  loop.exec();
}

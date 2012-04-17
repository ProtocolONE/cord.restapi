#include "gtest/gtest.h"
#include "MemoryLeaksChecker.h"

#include "CommandResultGetter.h"

#include <RestApi/HttpCommandRequest.h>
#include <RestApi/Commands/Service/GetDetailedServices.h>
#include <RestApi/Commands/Service/Response/DetailedServiceInfo.h>
#include <RestApi/Commands/Service/Response/DetailedServicesResponse.h>
#include <RestApi/CommandBaseArgumentWraper.h>
#include <RestApi/RestApiManager.h>
#include <RestApi/FakeCache.h>

#include <QtCore/QtConcurrentRun>
#include <QtCore/QWaitCondition>
#include <QtCore/QEventLoop>

class HttpRequestCommandTest : public ::testing::Test{
public:
  HttpRequestCommandTest() {
    this->leakChecker.start();
  }

  ~HttpRequestCommandTest() {
    this->leakChecker.finish();
    if(this->leakChecker.isMemoryLeaks())
      failTest("Memory leak detected!"); 
  }



private:
  void failTest(const char* message) 
  { 
    FAIL() << message; 
  }

  MemoryLeaksChecker leakChecker;
};

TEST_F(HttpRequestCommandTest, test1)
{
  using GGS::RestApi::Commands::Service::GetDetailedServices;
  using GGS::RestApi::CommandBaseInterface;
  using GGS::RestApi::Commands::Service::Response::DetailedServicesResponse;
  using GGS::RestApi::Commands::Service::Response::DetailedServiceInfo;
  using GGS::RestApi::CommandBaseArgumentWraper;
  using GGS::RestApi::HttpCommandRequest;
  using GGS::RestApi::FakeCache;
  
  FakeCache cache;
     
  HttpCommandRequest request;
  request.setCache(&cache);

  GetDetailedServices cmd;
  cmd.appendParameter("someRusParam", QString::fromLocal8Bit("Привет, Мир!"));

  CommandBaseArgumentWraper wraper;
  wraper.setCommand(&cmd);
  wraper.setUri(QString("http://api.gamenet.dev/restapi"));

  QFuture<void> f = QtConcurrent::run(&request, &HttpCommandRequest::execute, wraper);
  f.waitForFinished();
}

TEST_F(HttpRequestCommandTest, testSpeed)
{ 
  using GGS::RestApi::Commands::Service::GetDetailedServices;
  using GGS::RestApi::Commands::Service::Response::DetailedServicesResponse;
  using GGS::RestApi::Commands::Service::Response::DetailedServiceInfo;
  using GGS::RestApi::CommandBaseInterface;
  using GGS::RestApi::CommandBaseArgumentWraper;
  using GGS::RestApi::HttpCommandRequest;
  using GGS::RestApi::FakeCache;

  GetDetailedServices cmd;
  cmd.appendParameter("someRusParam", QString::fromLocal8Bit("Привет, Мир!"));
  cmd.appendParameter("lang", "en");

  CommandBaseArgumentWraper wraper;
  wraper.setCommand(&cmd);
  wraper.setUri(QString("http://api.gamenet.dev/restapi"));

  FakeCache cache;
  HttpCommandRequest request;
  request.setCache(&cache);

  QTime time;
  time.setHMS(0,0,0,0);
  time.start();

  for (int i = 0; i < 2; ++i) {
    QFuture<void> f = QtConcurrent::run(&request, &HttpCommandRequest::execute, wraper);
    f.waitForFinished();
  }

  int elapsed = time.elapsed(); // sad - very sad 1700 ms
  qDebug() << elapsed;
}

TEST_F(HttpRequestCommandTest, testEvent)
{
  CommandResultGetter res;
  QFuture<void> f = QtConcurrent::run(&res, &CommandResultGetter::test2);
  f.waitForFinished();
}
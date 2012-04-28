#include "gtest/gtest.h"
#include "MemoryLeaksChecker.h"


#include <RestApi/HttpCommandRequest.h>
#include <RestApi/GameNetCredential.h>
#include <RestApi/CommandBaseInterface.h>
#include <RestApi/RestApiManager.h>
#include <RestApi/Commands/User/GetUserMainInfo.h>
#include <RestApi/Commands/User/SetUserActivity.h>
#include "Commands/User/SetUserActivityTest.h"
#include <RestApi/Commands/User/Response/UserMainInfoResponse.h>
#include <RestApi/FakeCache.h>
#include <QtCore/QEventLoop>
#include <QtCore/QTimer>
#include <QtCore/QDebug>


void SetUserActivityTest::SetUserActivityResult( GGS::RestApi::CommandBaseInterface::CommandResults code )
{
    ASSERT_TRUE(code == GGS::RestApi::CommandBaseInterface::NoError);
    if (code == GGS::RestApi::CommandBaseInterface::NoError)
     ASSERT_TRUE(command.getTimeout() > 0);
}

void GetUserServiceAccount::GetUserServiceAccountResult( GGS::RestApi::CommandBaseInterface::CommandResults code )
{
	if (code == GGS::RestApi::CommandBaseInterface::NoError){
		ASSERT_TRUE(command.response()->getLogin().size());
		ASSERT_TRUE(command.response()->getToken().size());
		ASSERT_TRUE(command.response()->getStatus().size());
		ASSERT_TRUE(command.response()->getPassword().size());
    } else if (code == GGS::RestApi::CommandBaseInterface::GenericError)
		ASSERT_TRUE(command.getGenericErrorMessage().size());
}


TEST_F(SetUserActivityTest, setUserActivityTestTest)
{
  using GGS::RestApi::RestApiManager;
  using GGS::RestApi::GameNetCredential;
  using GGS::RestApi::HttpCommandRequest;
  using GGS::RestApi::FakeCache;

  GameNetCredential auth;
  auth.setAppKey(QString("92da94c6a632951c8d588f596826bfd1470843f0"));
  auth.setUserId("400001000000172890");

  HttpCommandRequest request;
  FakeCache cache;
  request.setCache(&cache);

  RestApiManager restapi;

  restapi.setUri(QString("http://api.gamenet.dev/restapi"));
  restapi.setCridential(auth);
  restapi.setRequest(&request);

  ASSERT_TRUE(connect(&command, SIGNAL(result(GGS::RestApi::CommandBaseInterface::CommandResults)),
      this,SLOT(SetUserActivityResult(GGS::RestApi::CommandBaseInterface::CommandResults))));
  command.setGameId(71);

  QEventLoop loop;

  // даем 5 секунд на выполнение теста. потом убиваем евент улп
  QTimer::singleShot(5000, &loop, SLOT(quit()));
  restapi.execute(&command);
  loop.exec();
}

TEST_F(GetUserServiceAccount, getUserServiceAccountTest)
{
  using GGS::RestApi::RestApiManager;
  using GGS::RestApi::GameNetCredential;
  using GGS::RestApi::HttpCommandRequest;
  using GGS::RestApi::FakeCache;

  GameNetCredential auth;
  auth.setAppKey(QString("92da94c6a632951c8d588f596826bfd1470843f0"));
  auth.setUserId("400001000000172890");

  HttpCommandRequest request;
  FakeCache cache;
  request.setCache(&cache);

  RestApiManager restapi;

  restapi.setUri(QString("http://api.gamenet.dev/restapi"));
  restapi.setCridential(auth);
  restapi.setRequest(&request);

  connect(&command, SIGNAL(result(GGS::RestApi::CommandBaseInterface::CommandResults)),
		  this,SLOT(GetUserServiceAccountResult(GGS::RestApi::CommandBaseInterface::CommandResults)));
  command.setServiceId("300002010000000000");

  QEventLoop loop;

  // даем 5 секунд на выполнение теста. потом убиваем евент улп
  QTimer::singleShot(5000, &loop, SLOT(quit()));
  restapi.execute(&command);
  loop.exec();
  
}
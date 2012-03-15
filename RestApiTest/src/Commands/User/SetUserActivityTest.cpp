#include "gtest/gtest.h"
#include "MemoryLeaksChecker.h"

#include "GameNetCredential.h"
#include "CommandBaseInterface.h"
#include "RestApiManager.h"
#include "Commands/User/GetUserMainInfo.h"
#include "Commands/User/SetUserActivity.h"
#include "Commands/User/SetUserActivityTest.h"
#include "Commands/User/Response/UserMainInfoResponse.h"
#include "FakeCache.h"
#include <QtCore/QEventLoop>
#include <QtCore/QTimer>
#include <qdebug>


void SetUserActivityTest::SetUserActivityResult( int timeout )
{
	if (!command.getGenericErrorMessageCode())
		ASSERT_TRUE(timeout);
	else
		ASSERT_TRUE(command.getGenericErrorMessage().size());
}

void GetUserServiceAccount::GetUserServiceAccountResult( )
{
	if (!command.getGenericErrorMessageCode()){
		ASSERT_TRUE(command.response()->getLogin().size());
		ASSERT_TRUE(command.response()->getToken().size());
		ASSERT_TRUE(command.response()->getStatus().size());
		ASSERT_TRUE(command.response()->getPassword().size());
	} else
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

  ASSERT_TRUE(connect(&command, SIGNAL(result(int)),this,SLOT(SetUserActivityResult(int))));
  command.appendParameter("gameId","71");
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

  connect(&command, SIGNAL(result()),
		  this,SLOT(GetUserServiceAccountResult()));

  command.appendParameter("serviceId","300002010000000000");
  QEventLoop loop;

  // даем 5 секунд на выполнение теста. потом убиваем евент улп
  QTimer::singleShot(5000, &loop, SLOT(quit()));
  restapi.execute(&command);
  loop.exec();
  
}
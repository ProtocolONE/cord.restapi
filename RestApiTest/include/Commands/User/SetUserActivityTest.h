#ifndef _GGS_RESTAPI_SET_USER_ACTIVITY_TEST_H_
#define _GGS_RESTAPI_SET_USER_ACTIVITY_TEST_H_

#include "gtest/gtest.h"
#include <RestApi/Commands/User/SetUserActivity.h>

class SetUserActivityTest : public GGS::RestApi::Commands::User::SetUserActivity, public ::testing::Test
{
  Q_OBJECT
public slots:
  void SetUserActivityResult( int timeout );
public:
	GGS::RestApi::Commands::User::SetUserActivity command;
};

#include <RestApi/Commands/User/GetUserServiceAccount.h>
#include <RestApi/Commands/User/Response/UserServiceAccountResponse.h>

class GetUserServiceAccount : public GGS::RestApi::Commands::User::GetUserServiceAccount, public ::testing::Test
{
  Q_OBJECT
public slots:
	void GetUserServiceAccountResult( );
public:
	GGS::RestApi::Commands::User::GetUserServiceAccount command;
};

#endif
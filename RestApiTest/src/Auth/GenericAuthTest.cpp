
#include "gtest/gtest.h"
#include "MemoryLeaksChecker.h"

#include "Auth/GenericAuth.h"
#include "Auth/GameNetAuthResultInterface.h"
#include "GameNetCredential.h"

#include <QtCore/QWaitCondition>

class GenericAuthTest : public ::testing::Test, public GGS::RestApi::Auth::GameNetAuthResultInterface
{
public:
  GenericAuthTest() {
    this->leakChecker.start();
  }

  ~GenericAuthTest() {
    this->leakChecker.finish();
    if(this->leakChecker.isMemoryLeaks())
      failTest("Memory leak detected!"); 
  }

  bool _failCalled;
  bool _resultCalled;

private:
  void failTest(const char* message) 
  { 
    FAIL() << message; 
  }

  virtual void authResult( const GGS::RestApi::GameNetCredential& cridential ) 
  {
    this->_resultCalled = true;
  }

  virtual void authFailed( GGS::RestApi::Auth::GameNetAuthResultInterface::AuthResultCodes resultCode ) 
  {
    this->_failCalled = true;
  }

  MemoryLeaksChecker leakChecker;
};

TEST_F(GenericAuthTest, authTest)
{
  // UNDONE : тест не написан
  using GGS::RestApi::Auth::GenericAuth;
  GenericAuth genericAuth;
  QString login("gna@unit.test");
  QString password("123456");
  QString authUrl("https://gnlogin.gamenet.dev/");
  genericAuth.setAuthUrl(authUrl);
  genericAuth.setLogin(login);
  genericAuth.setPassword(password);
  genericAuth.setResultCallback(this);

  this->_failCalled = false;
  this->_resultCalled = false;

  genericAuth.login();

  QMutex mutex;
  QWaitCondition waiter;
  int i = 0;
  while (!(this->_failCalled || this->_resultCalled) && i < 30) {
    waiter.wait(&mutex, 1000);
    i++;
  }

  ASSERT_TRUE(this->_resultCalled);
  ASSERT_FALSE(this->_failCalled);
  

  //genericAuth.
}
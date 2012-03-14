#include "gtest/gtest.h"
#include "MemoryLeaksChecker.h"

#include "HttpRequest.h"

#include <QtCore/QString>

class HttpRequestTest : public ::testing::Test{
public:
  HttpRequestTest() {
    this->leakChecker.start();
  }

  ~HttpRequestTest() {
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

TEST_F(HttpRequestTest, restapiRequest) 
{
  using GGS::RestApi::HttpRequest;
  using GGS::RestApi::HttpRequestInterface;
  HttpRequest http;
  HttpRequestInterface::ResultCodes resultCode;
  QString response = http.execute(QString("http://api.gamenet.dev/restapi"), QString("method=user.getMainInfo&userId=400001000000172890&appKey=92da94c6a632951c8d588f596826bfd1470843f0"), resultCode);
}
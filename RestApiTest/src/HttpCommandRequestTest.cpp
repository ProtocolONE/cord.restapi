#include <gtest/gtest.h>
#include <TestEventLoopFinisher.h>

#include <RestApi/HttpCommandRequest.h>

#include <QtCore/QObject>
#include <QtCore/QEventLoop>
#include <QtCore/QList>
#include <QtCore/QVariant>

#include <QtTest/QSignalSpy>

using GGS::RestApi::CommandBase;
using GGS::RestApi::HttpCommandRequest;

class HttpRequestCommandTest : public ::testing::Test
{
public:
  void execute(HttpCommandRequest &request, QUrl &url) 
  {
    QEventLoop loop;
    TestEventLoopFinisher loopKiller(&loop, 10000);

    QObject::connect(&request, SIGNAL(finish(GGS::RestApi::CommandBase::CommandResults, QString)), 
      &loopKiller, SLOT(terminateLoop()));

    request.execute(url);
    loop.exec();

    ASSERT_FALSE(loopKiller.isKilledByTimeout());
  }
};

TEST_F(HttpRequestCommandTest, successExecuteTest)
{
  HttpCommandRequest request;
  QSignalSpy response(&request, SIGNAL(finish(GGS::RestApi::CommandBase::CommandResults, QString)));

  execute(request, QUrl("http://gnapi.com/restapi"));

  ASSERT_EQ(1, response.count());

  QList<QVariant> arguments = response.takeFirst();
  ASSERT_EQ(CommandBase::NoError, arguments.at(0).value<GGS::RestApi::CommandBase::CommandResults>());
  ASSERT_TRUE(arguments.at(1).toString().contains("<message>"));
}

TEST_F(HttpRequestCommandTest, failedExecuteTest)
{
  HttpCommandRequest request;
  QSignalSpy response(&request, SIGNAL(finish(GGS::RestApi::CommandBase::CommandResults, QString)));

  execute(request, QUrl("http://someVeryStrange.Host"));

  ASSERT_EQ(1, response.count());

  QList<QVariant> arguments = response.takeFirst();
  ASSERT_EQ(CommandBase::NetworkError, arguments.at(0).value<GGS::RestApi::CommandBase::CommandResults>());
  ASSERT_EQ("", arguments.at(1).toString());
}
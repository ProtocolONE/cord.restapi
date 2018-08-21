#include <gtest/gtest.h>

#include <RestApi/CommandBase.h>

#include <QUrl>
#include <QUrlQuery>

using P1::RestApi::CommandBase;

class CommandbaseTest : public ::testing::Test
{
};

TEST_F(CommandbaseTest, commandParametersTest) 
{
  CommandBase tst;
  tst.appendParameter("123", "123a");
  tst.appendParameter("124", "123b");
  tst.appendParameter("125", "123c");
  tst.appendParameter("126", "123d");

  const QMap<QString, QString> checkMap = *tst.commandParameters();
  
  ASSERT_TRUE(checkMap.contains("123"));
  ASSERT_TRUE(checkMap.contains("124"));
  ASSERT_TRUE(checkMap.contains("125"));
  ASSERT_TRUE(checkMap.contains("126"));
  ASSERT_EQ("123a", checkMap["123"]);
  ASSERT_EQ("123b", checkMap["124"]);
  ASSERT_EQ("123c", checkMap["125"]);
  ASSERT_EQ("123d", checkMap["126"]);
}

TEST_F(CommandbaseTest, urlTest)
{
  CommandBase tst;
  tst.appendParameter("key1", "value1");
  tst.appendParameter("ключ", "зна-че-ни-е");

  QUrl excepted(tst.restapiUrl());
  QUrlQuery query;
  query.addQueryItem("key1", "value1");
  query.addQueryItem("ключ", "зна-че-ни-е");

  excepted.setQuery(query);


  ASSERT_EQ(excepted, tst.url());
}

TEST_F(CommandbaseTest, authRequiredTest)
{
  CommandBase tst;

  ASSERT_FALSE(tst.isAuthRequire());

  tst.setAuthRequire(true);
  ASSERT_TRUE(tst.isAuthRequire());

  tst.setAuthRequire(false);
  ASSERT_FALSE(tst.isAuthRequire());
}

TEST_F(CommandbaseTest, cacheableTest)
{
  CommandBase tst;

  ASSERT_FALSE(tst.isCacheable());

  tst.setCacheable(true);
  ASSERT_TRUE(tst.isCacheable());
  
  tst.setCacheable(false);
  ASSERT_FALSE(tst.isCacheable());
}

TEST_F(CommandbaseTest, cacheTimeTest)
{
  CommandBase tst;

  tst.setCacheTime(12345);
  ASSERT_EQ(12345, tst.cacheTime());
}

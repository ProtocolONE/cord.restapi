#include <gtest/gtest.h>

#include <RestApi/ProtocolOneCredential.h>
//#include <RestApi/CommandBase.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QMetaType>

#include <RestApi/RegisterTypes.h>


#include <QtCore/QUrl>

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  //'/api/v1/app/ui/'
  QUrl url("http://vb-api.protocol.one:8021/");

  QString path = QString("/api/%1/%2/").arg("v1", "app/ui");
  url.setPath(path);

  QString tmp = url.toString();

  //P1::RestApi::registerTypes();

  testing::InitGoogleTest(&argc, argv);
  int res = RUN_ALL_TESTS();
  return res;
}

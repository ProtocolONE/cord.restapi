#ifndef _GGS_RESTAPI_TEST_COMMAND_RESULT_GETTER_H_
#define _GGS_RESTAPI_TEST_COMMAND_RESULT_GETTER_H_

#include "CommandResultGetter.h"

#include <RestApi/CommandBaseInterface.h>
#include <RestApi/HttpCommandRequest.h>
#include <RestApi/Commands/Service/GetDetailedServices.h>
#include <RestApi/Commands/Service/Response/DetailedServiceInfo.h>
#include <RestApi/Commands/Service/Response/DetailedServicesResponse.h>
#include <RestApi/CommandBaseArgumentWraper.h>
#include <RestApi/RestApiManager.h>
#include <RestApi/FakeCache.h>

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QtConcurrentRun>
#include <QtCore/QWaitCondition>
#include <QtCore/QEventLoop>

using GGS::RestApi::CommandBaseInterface;

class CommandResultGetter : public QObject
{
  Q_OBJECT
public:
  CommandResultGetter(void);
  ~CommandResultGetter(void);

  QEventLoop loop;
  void test2();

public slots:
  void commandResult();
  void genericError(const QString& message, int messageId );

};

#endif // _GGS_RESTAPI_TEST_COMMAND_RESULT_GETTER_H_
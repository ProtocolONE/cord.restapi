#ifndef _GGS_RESTAPI_TEST_COMMAND_RESULT_GETTER_H_
#define _GGS_RESTAPI_TEST_COMMAND_RESULT_GETTER_H_

#include "CommandBaseInterface.h"

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include "CommandResultGetter.h"
#include "HttpCommandRequest.h"
#include "Commands/Service/GetDetailedServices.h"
#include "Commands/Service/Response/DetailedServiceInfo.h"
#include "Commands/Service/Response/DetailedServicesResponse.h"
#include "CommandBaseArgumentWraper.h"
#include "RestApiManager.h"
#include "FakeCache.h"


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
  //void commandResult(int resultCode);

};

#endif // _GGS_RESTAPI_TEST_COMMAND_RESULT_GETTER_H_
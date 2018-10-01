#ifndef _GGS_RESTAPI_COMMANDBASEARGUMENTWRAPER_H_
#define _GGS_RESTAPI_COMMANDBASEARGUMENTWRAPER_H_

#include "restapi_global.h"
#include "CommandBaseInterface.h"

#include <QtCore/QString>
#include <QtCore/QDebug>

namespace GGS {
  namespace RestApi {


    /// <summary>��������� ����������� ������� ��� �������� ���������� � �������� ��������� ��� ������ QtConcurrentrun. </summary>
    /// <remarks>Ilya.Tkachenko, 15.02.2012.</remarks>
    class RESTAPI_EXPORT CommandBaseArgumentWraper : QObject
    {
      Q_OBJECT
    public:
      CommandBaseArgumentWraper(QObject *parrent = 0);
      ~CommandBaseArgumentWraper(void);

      CommandBaseArgumentWraper(const CommandBaseArgumentWraper& p);

      void setUri(const QString& uri) { this->_uri = uri; }
      const QString& uri() { return this->_uri; }

      void setCommand(CommandBaseInterface *command) { this->_command = command; }
      CommandBaseInterface * command() { return this->_command; }

    private:
      QString _uri;
      CommandBaseInterface *_command;
    };

  }
}
#endif // _GGS_RESTAPI_COMMANDBASEARGUMENTWRAPER_H_
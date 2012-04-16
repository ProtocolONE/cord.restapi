/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_COMMANDBASEARGUMENTWRAPER_H_
#define _GGS_RESTAPI_COMMANDBASEARGUMENTWRAPER_H_

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBaseInterface.h>

#include <QtCore/QString>
#include <QtCore/QDebug>

namespace GGS {
  namespace RestApi {


    /// <summary>Реализует необходимые условия для передачи интерфейса в качестве аргумента для метода QtConcurrentrun. </summary>
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
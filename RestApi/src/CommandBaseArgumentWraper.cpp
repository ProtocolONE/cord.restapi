#include "CommandBaseArgumentWraper.h"

namespace GGS {
  namespace RestApi {

    CommandBaseArgumentWraper::CommandBaseArgumentWraper(QObject *parrent)
      : QObject(parrent)
    {
      //qDebug() << "CommandBaseArgumentWraper";
    }

    CommandBaseArgumentWraper::CommandBaseArgumentWraper( const CommandBaseArgumentWraper& p )
      : _command(p._command), 
      _uri(p._uri)
    {
      //qDebug() << "CommandBaseArgumentWraper copy";
    }

    CommandBaseArgumentWraper::~CommandBaseArgumentWraper(void)
    {
      //qDebug() << "~CommandBaseArgumentWraper";
    }

  }
}
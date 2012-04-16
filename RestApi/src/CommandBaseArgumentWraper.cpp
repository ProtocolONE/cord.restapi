/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/CommandBaseArgumentWraper.h"

namespace GGS {
  namespace RestApi {

    CommandBaseArgumentWraper::CommandBaseArgumentWraper(QObject *parrent)
      : QObject(parrent)
    {
    }

    CommandBaseArgumentWraper::CommandBaseArgumentWraper( const CommandBaseArgumentWraper& p )
      : _command(p._command), 
      _uri(p._uri)
    {
    }

    CommandBaseArgumentWraper::~CommandBaseArgumentWraper() {
    }

  }
}
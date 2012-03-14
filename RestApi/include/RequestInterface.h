#ifndef _GGS_RESTAPI_REQUESTINTERFACE_H_
#define _GGS_RESTAPI_REQUESTINTERFACE_H_

//#include "CommandBaseInterface.h"
#include "CommandBaseArgumentWraper.h"
#include <QtCore/QString>
namespace GGS {
  namespace RestApi {


    /// <summary>Request interface. Реализация класса обязана быть реинтерабельной.</summary>
    /// <remarks>Ilya.Tkachenko, 13.02.2012.</remarks>
    class RequestInterface{
    public:
      virtual ~RequestInterface() {};

       /// <summary>Выполненить запрос на основе данных комманды. Результат передать в функцию обратного
       ///  вызова, указанную в команде.</summary>
       /// <remarks>Ilya.Tkachenko, 13.02.2012.</remarks>
       /// <param name="arguments">     [in] If non-null, the command.</param>
       virtual void execute(CommandBaseArgumentWraper &arguments) = 0;
    };

  }
}
#endif // _GGS_RESTAPI_REQUESTINTERFACE_H_
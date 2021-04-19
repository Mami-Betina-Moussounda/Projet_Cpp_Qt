#ifndef IWORKER_H
#define IWORKER_H

#include <QObject>

namespace app
{
namespace ctrw


{

class iWorker: public QObject
{
    Q_OBJECT

public:
    iWorker()
    {}
    virtual ~ iWorker()
    {}
public slots:
   virtual void initialize() =0;
};

}
}

#endif // IWORKER_H

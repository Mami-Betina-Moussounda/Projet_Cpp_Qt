#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <QThread>
#include <QObject>
#include "FirmWare/Application/ControllerWorker/iworker.h"

namespace app
{
namespace ctrw


{


class   Controller: public QObject
{
    Q_OBJECT

public:
    Controller(app::ctrw::iWorker &worker);
    ~ Controller();

private:
    app::ctrw::iWorker &m_iworker;
    QThread m_workerThread;

signals:
    void initWorker();


};

}

}
#endif // CONTROLLER_H

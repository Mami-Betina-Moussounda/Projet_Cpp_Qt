#include "Controller.h"

namespace app
{
namespace ctrw


{
Controller::Controller(app::ctrw::iWorker &worker): m_iworker(worker)
  /* This objects creates a thread for another one: the worker.
    It initiates it and destroyes it at the end.
    All the actions in the worker will be run in a new thread */
{

    m_iworker.moveToThread(&m_workerThread);
    connect(&m_workerThread, &QThread::finished, &m_iworker, &QObject::deleteLater);
    connect(this, &Controller::initWorker, &m_iworker, &app::ctrw::iWorker::initialize);

    m_workerThread.start();

    emit initWorker();

}

Controller::~ Controller()
{
    m_workerThread.quit();
    m_workerThread.wait();
}
























}
}

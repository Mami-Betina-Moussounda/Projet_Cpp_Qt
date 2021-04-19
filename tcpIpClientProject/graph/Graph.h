#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H
#include <QMainWindow>
#include <QMdiArea>
#include <QWidget>
#include <QTextEdit>
#include <QBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include <QMdiSubWindow>
#include <QtCharts>
#include <QStandardItemModel>
#include <QChart>
#include "graph/Interface/igraph.h"
#include <QList>
#include <QTime>
#include <QGridLayout>




class FenetrePrincipale : public QWidget, public IGraph
{

    Q_OBJECT

public:

    FenetrePrincipale();
    void getTempData( double &temperature, long long &temperatureTime)final;
    void updateTempChart();
    void updateSpeedChart(long long SpeedTimeReference);
    void clearLists() final;
    void showGraph() final;


private:

    QChart *m_insideChartTemp;
    QScatterSeries *m_tempSerie;
    QChartView *m_theChartTemp;
    QList <double> m_listTemp;
    QList <long long > m_listTimeTemp;
    QDateTimeAxis * m_xAxeTemp;
    QValueAxis *m_yAxeTemp;
    QGridLayout* m_Layout;
};

#endif // FENETREPRINCIPALE_H

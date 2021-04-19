#include "Graph.h"
#include <QString>
#include <string>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QtCharts>
#include <QChart>
#include <QChartView>
#include <QScatterSeries>
#include <QGraphicsItem>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRegExp>
#include <QStandardItemModel>
#include <iostream>
#include "configuration/configuration.h"

using namespace QtCharts;

FenetrePrincipale::FenetrePrincipale():

    m_insideChartTemp(nullptr),
    m_tempSerie(nullptr),
    m_theChartTemp(nullptr),
    m_xAxeTemp(nullptr),
    m_yAxeTemp(nullptr)

{
    m_Layout = new QGridLayout(this);
    m_insideChartTemp = new QChart;
    m_theChartTemp = new QChartView;

    m_xAxeTemp= new QDateTimeAxis;
    m_xAxeTemp->setFormat("hh:mm:ss");
    m_xAxeTemp->setTitleText("Hours");
    m_yAxeTemp= new QValueAxis;
    m_yAxeTemp->setTitleText("Temperature °C");


    m_insideChartTemp->addAxis(m_xAxeTemp,  Qt::AlignBottom);
    m_insideChartTemp->addAxis(m_yAxeTemp, Qt::AlignLeft);
    m_tempSerie = new QScatterSeries;
    m_insideChartTemp->addSeries(m_tempSerie);


    m_tempSerie->attachAxis(m_xAxeTemp);
    m_tempSerie->attachAxis(m_yAxeTemp);

    m_tempSerie->setPointsVisible(true);
    m_tempSerie->setPointLabelsFormat("@yPoint");
    m_tempSerie->setPointLabelsVisible(true); // Display data values on the graph



    m_tempSerie->setMarkerSize(cfig::GraphConfig::markerSize);
    m_tempSerie->setName("Temperature evolution");


    m_theChartTemp->setChart(m_insideChartTemp);


    layout()->addWidget(m_theChartTemp);

    setWindowTitle("CLIENT CHARTS");

    setMinimumSize(cfig::GraphConfig::minSizeGraphX, cfig::GraphConfig::minSizeGraphY);

}

void FenetrePrincipale::getTempData( double &temperature, long long &temperatureTime)
{


    m_listTemp.push_front(temperature);

    m_listTimeTemp.push_front(temperatureTime);


    if(m_listTemp.size()>cfig::GraphConfig::quantityDataDisplay)
    {
        m_tempSerie->remove(m_listTimeTemp.back(),m_listTemp.back());


        m_listTemp.pop_back();
        m_listTimeTemp.pop_back();
    }

    m_tempSerie->append(m_listTimeTemp.front(),m_listTemp.front());

    double min= *std::min_element(m_listTemp.begin(), m_listTemp.end());
    double max = *std::max_element(m_listTemp.begin(), m_listTemp.end());
    m_yAxeTemp->setRange(min - cfig::GraphConfig::minRangeY, max + cfig::GraphConfig::maxRangeY);

    m_xAxeTemp->setRange(QDateTime::fromMSecsSinceEpoch( static_cast<qint64>(m_tempSerie->at(cfig::GraphConfig::maxRangeX).x()) ),
                       QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(m_tempSerie->at(m_tempSerie->count()- cfig::GraphConfig::minRangeX).x()) ));

}



void FenetrePrincipale::clearLists()
{
    m_listTemp.clear();
    m_listTimeTemp.clear();
    m_tempSerie->clear();
}

void FenetrePrincipale::showGraph()
{
    this->show();
}

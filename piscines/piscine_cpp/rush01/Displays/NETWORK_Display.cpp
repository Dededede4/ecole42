#include "NETWORK_Display.hpp"
#include "Modules/NetworkModule.hpp"

NETWORK_Display_GUI::NETWORK_Display_GUI(void){}
NETWORK_Display_GUI::~NETWORK_Display_GUI(void){}
NETWORK_Display_GUI & NETWORK_Display_GUI::operator=( NETWORK_Display_GUI const & rhs) 
{
	i = rhs.i;
	series = rhs.series;
	chart = rhs.chart;
	return *this;
}
NETWORK_Display_GUI::NETWORK_Display_GUI(NETWORK_Display_GUI const & src)
{
	*this = src;
}


QWidget * NETWORK_Display_GUI::initGUI(void)
{
	
	NetworkModule network;
	nbrpaquets = std::stoull(network.getValue());
	series = new QSplineSeries();
	series->setName("spline");

	series->show();

	chart = new QChart();
	chart->legend()->hide();
	chart->addSeries(series);
	chart->setTitle("Paquets sur le réseau");
	chart->createDefaultAxes();
	chart->axisY()->setRange(0, 10000);
	chart->axisX()->setRange(0, 100);
	chart->axisX()->setVisible(false);
	chart->setAutoFillBackground(true);

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	return chartView;
}

void		NETWORK_Display_GUI::update(void)
{
	NetworkModule		network;
	unsigned long long	newNbrPaquets;
	std::string			message;

	newNbrPaquets = std::stoull(network.getValue());

	message = "Paquets sur le réseau (";
	message += std::to_string(newNbrPaquets - nbrpaquets);
	message += ")";

	
	*series << QPointF(i, newNbrPaquets - nbrpaquets);
	chart->setTitle(QString::fromStdString(message));
	nbrpaquets = newNbrPaquets;
	if (i > 100)
		chart->axisX()->setRange(i - 100, i);
	i++;
}


void		NETWORK_Display_CLI::update(void)
{
}

std::string NETWORK_Display_CLI::cliUI()
{
	NetworkModule ret;

	return ret.getValue();
}

NETWORK_Display_CLI::NETWORK_Display_CLI(void){}
NETWORK_Display_CLI::~NETWORK_Display_CLI(void){}
NETWORK_Display_CLI & NETWORK_Display_CLI::operator=( NETWORK_Display_CLI const & rhs) 
{
	(void)rhs;
	return *this;
}
NETWORK_Display_CLI::NETWORK_Display_CLI(NETWORK_Display_CLI const & src)
{
	*this = src;
}
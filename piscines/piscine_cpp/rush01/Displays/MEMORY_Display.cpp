#include "IMonitorDisplay.hpp"
#include "MEMORY_Display.hpp"
#include "Modules/MemoryModule.hpp"

MEMORY_Display_GUI::MEMORY_Display_GUI(void){}
MEMORY_Display_GUI::~MEMORY_Display_GUI(void){}
MEMORY_Display_GUI & MEMORY_Display_GUI::operator=( MEMORY_Display_GUI const & rhs) 
{
	i = rhs.i;
	series = rhs.series;
	chart = rhs.chart;
	nbrpaquets = rhs.nbrpaquets;
	return *this;
}
MEMORY_Display_GUI::MEMORY_Display_GUI(MEMORY_Display_GUI const & src)
{
	*this = src;
}

QWidget * MEMORY_Display_GUI::initGUI(void)
{
	
	MemoryModule memory;
	nbrpaquets = std::stoull(memory.getValue());
	series = new QSplineSeries();
	series->setName("spline");

	series->show();

	chart = new QChart();
	chart->legend()->hide();
	chart->addSeries(series);
	chart->setTitle("Mémoire");
	chart->createDefaultAxes();
	chart->axisY()->setRange(0, 100);
	chart->axisX()->setRange(0, 100);
	chart->axisX()->setVisible(false);
	chart->setAutoFillBackground(true);

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	return chartView;
}

void		MEMORY_Display_GUI::update(void)
{
	MemoryModule		memory;

	*series << QPointF(i, std::stof(memory.getValue()));
	if (i > 100)
		chart->axisX()->setRange(i - 100, i);
	i++;
}

void MEMORY_Display_CLI::update(void)
{
}

std::string MEMORY_Display_CLI::cliUI()
{
	//unsigned long long nb = MemoryModule::memUsed() * (col / 2) / MemoryModule::memSizeTotal();
	//unsigned long long spaces = col / 2 - nb;

	MemoryModule memory;

	std::string ret = memory.getValue() + "%";

	return ret;
}


MEMORY_Display_CLI::MEMORY_Display_CLI(void){}
MEMORY_Display_CLI::~MEMORY_Display_CLI(void){}
MEMORY_Display_CLI & MEMORY_Display_CLI::operator=( MEMORY_Display_CLI const & rhs) 
{
	(void)rhs;
	return *this;
}
MEMORY_Display_CLI::MEMORY_Display_CLI(MEMORY_Display_CLI const & src)
{
	*this = src;
}
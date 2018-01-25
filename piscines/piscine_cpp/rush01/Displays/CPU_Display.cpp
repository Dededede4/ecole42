#include "CPU_Display.hpp"

CPU_Display_GUI::CPU_Display_GUI(void){}
CPU_Display_GUI::~CPU_Display_GUI(void){}
CPU_Display_GUI & CPU_Display_GUI::operator=( CPU_Display_GUI const & rhs) 
{
	i = rhs.i;
	series = rhs.series;
	chart = rhs.chart;
	return *this;
}
CPU_Display_GUI::CPU_Display_GUI(CPU_Display_GUI const & src)
{
	*this = src;
}

QWidget * CPU_Display_GUI::initGUI(void)
{
	CpuModule cpu;
	series = new QSplineSeries();
	series->setName("spline");

	series->show();

	chart = new QChart();
	chart->legend()->hide();
	chart->addSeries(series);
	std::string			message;
	message = cpu.getModel();
	message += " ";
	message += cpu.getNbrCore();
	message += "core(s)";
	
	chart->setTitle(QString::fromStdString(message));
	chart->createDefaultAxes();
	chart->axisY()->setRange(0, 100);
	chart->axisX()->setRange(0, 100);
	chart->axisX()->setVisible(false);
	chart->setAutoFillBackground(true);

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	return chartView;
}

void		CPU_Display_GUI::update(void)
{
	CpuModule cpu;

	if (i % 10 == 0)
	{
		*series << QPointF(i, 100 - std::stoull(cpu.getValue()));
		if (i > 100)
			chart->axisX()->setRange(i - 100, i);
	}
	i++;
}


void CPU_Display_CLI::update(void){}


std::string CPU_Display_CLI::cliUI()
{
	CpuModule cpumod;

	return cpumod.getValue();
}

CPU_Display_CLI::CPU_Display_CLI(){}
CPU_Display_CLI::~CPU_Display_CLI(void){}
CPU_Display_CLI & CPU_Display_CLI::operator=( CPU_Display_CLI const & rhs) 
{
	(void)rhs;
	return *this;
}
CPU_Display_CLI::CPU_Display_CLI(CPU_Display_CLI const & src)
{
	*this = src;
}

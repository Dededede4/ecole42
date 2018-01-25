#include <QApplication>
#include <QPushButton>
#include <QtCharts>

#include "Displays/CPU_Display.hpp"
#include "Displays/TIME_Display.hpp"
#include "Displays/PONEY_Display.hpp"
#include "Displays/GENERALINFORMATION_Display.hpp"
#include "Displays/NETWORK_Display.hpp"
#include "Displays/MEMORY_Display.hpp"

//ncurses
#include "ncurses.h"
#include <stdlib.h>
#include <time.h>

#include "main.hpp"


std::vector<IMonitorDisplay*> displays;
void update_all(void)
{
	for (auto &display : displays)
	{

		display->update();
	}
}

void				init_screen()
{
	srand(time(NULL));

	initscr();
	start_color();
	curs_set(0);
	noecho();
	nodelay(stdscr, true);
	intrflush(stdscr, true);
	keypad(stdscr, TRUE);
	cbreak();
	timeout(0);
}

int mainCLI()
{
	CPU_Display_CLI		cpu;
	TIME_Display_CLI	time;
	PONEY_Display_CLI	poney;
	GENERALINFORMATION_Display_CLI generalinformation;
	NETWORK_Display_CLI	network;
	MEMORY_Display_CLI memory;
	init_screen();																				/* start the curses mode */
	
	while (1)
	{
		int row, col;																		/* to store the number of rows and the number of colums of the screen */
		int ch;
		MemoryModule memorymod;


		werase(stdscr);																	
		getmaxyx(stdscr,row, col);													/* get the number of rows and columns */
		if(TIME_ENABLED)
			printw("Time :\n%s\n",time.cliUI().c_str());

		if (GENERALINFORMATION_ENABLED)
			printw("Infos:\n%s\n\n",generalinformation.cliUI().c_str());

		if (MEMORY_ENABLED)
		{
			printw("Memory usage: %s\n",memory.cliUI().c_str());
			unsigned long long nb = memorymod.memUsed() * (col / 2) / memorymod.memSizeTotal();
			unsigned long long spaces = col / 2 - nb;
			printw("[%s%s]\n\n", std::string(nb ,'|').c_str(), std::string(spaces ,' ').c_str());
		}

		if (CPU_ENABLED)
			printw("CPU usage (percentage of use of all cores):\n%s\n",cpu.cliUI().c_str());

		if (NETWORK_ENABLED)
			printw("Network usage : (packets received)\n%s\n", network.cliUI().c_str());

		if (PONEY_ENABLED)
			printw("Pony:\n%s\n",poney.cliUI().c_str());
		mvprintw(row - 1 , (col - 24) / 2, "Press 'q' or ESC to quit");
		if ((ch = getch()) == 'q' ) {
			break;
		}
		refresh();
	}

	endwin();
	return 0;
}

int mainGUI(int argc, char **argv)
{
	QApplication	app(argc, argv);
	QMainWindow		window;
	QWidget			mainWidget;
	CPU_Display_GUI		cpu;
	TIME_Display_GUI	time;
	PONEY_Display_GUI	poney;
	GENERALINFORMATION_Display_GUI generalinformation;
	NETWORK_Display_GUI	network;
	MEMORY_Display_GUI memory;

	QGridLayout *layout = new QGridLayout;
	if(TIME_ENABLED)
		layout->addWidget(time.initGUI(), TIME_POSITION, 0);
	if (GENERALINFORMATION_ENABLED)
		layout->addWidget(generalinformation.initGUI(), GENERALINFORMATION_POSITION, 0);
	if (MEMORY_ENABLED)
		layout->addWidget(memory.initGUI(), MEMORY_POSITION, 0);
	if (CPU_ENABLED)
		layout->addWidget(cpu.initGUI(), CPU_POSITION, 0);
	if (NETWORK_ENABLED)
		layout->addWidget(network.initGUI(), NETWORK_POSITION, 0);
	if (PONEY_ENABLED)
		layout->addWidget(poney.initGUI(), PONEY_POSITION, 0);
	layout->setColumnMinimumWidth(0, 200);

	mainWidget.setLayout(layout);

	window.setCentralWidget(&mainWidget);
	window.resize(200, 1200);
	window.show();

	if(CPU_ENABLED)
		displays.push_back(&cpu);
	if(TIME_ENABLED)
		displays.push_back(&time);
	if (GENERALINFORMATION_ENABLED)
		displays.push_back(&generalinformation);
	if (NETWORK_ENABLED)
		displays.push_back(&network);
	if (MEMORY_ENABLED)
		displays.push_back(&memory);

	// Execute display's "update" method in regular interval.
	QTimer timer;
	QObject::connect(&timer, &QTimer::timeout, update_all);
	timer.start(100);



	return app.exec();
}

int main(int argc, char **argv)
{
	if (argc == 2 && strncmp(argv[1], "--nogui", 7) == 0)
	{
		return mainCLI();
	}
	else
	{
		return mainGUI(argc, argv);
	}

}

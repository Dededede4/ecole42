#include "GENERALINFORMATION_Display.hpp"

GENERALINFORMATION_Display_GUI::GENERALINFORMATION_Display_GUI(void){}
GENERALINFORMATION_Display_GUI::~GENERALINFORMATION_Display_GUI(void){}
GENERALINFORMATION_Display_GUI & GENERALINFORMATION_Display_GUI::operator=( GENERALINFORMATION_Display_GUI const & rhs) 
{
    (void)rhs;
    return *this;
}
GENERALINFORMATION_Display_GUI::GENERALINFORMATION_Display_GUI(GENERALINFORMATION_Display_GUI const & src)
{
    *this = src;
}

QWidget * GENERALINFORMATION_Display_GUI::initGUI(void)
{
	QLabel *label = 				new QLabel();
	QGroupBox *horizontalGroupBox = new QGroupBox("Informations générales");
    QHBoxLayout *layoutBox = 		new QHBoxLayout;
    SysnameModule sysname;
    HostnameModule hostname;
    std::string 					message;

    message = "<b>Système d'exploitation :</b> ";
    message += sysname.getValue();
    message += "<br/><b>Nom d'hôte :</b> ";
    message += hostname.getValue();
    message += " <br/><b>Nom d'utilisateur :</b> ";
    message += getlogin();

    label->setText(QString::fromStdString(message));
    layoutBox->addWidget(label);
    horizontalGroupBox->setLayout(layoutBox);

	return horizontalGroupBox;
}

void		GENERALINFORMATION_Display_GUI::update(void)
{
}


void GENERALINFORMATION_Display_CLI::update(void)
{
}

std::string GENERALINFORMATION_Display_CLI::cliUI()
{
	SysnameModule sysname;
    HostnameModule hostname;

	return 
	"Informations générales :\nSystème d'exploitation : " + sysname.getValue() + "\nNom d'hôte : " + hostname.getValue() + "\nNom d'utilisateur : " + getlogin();
}

GENERALINFORMATION_Display_CLI::GENERALINFORMATION_Display_CLI(void){}
GENERALINFORMATION_Display_CLI::~GENERALINFORMATION_Display_CLI(void){}
GENERALINFORMATION_Display_CLI & GENERALINFORMATION_Display_CLI::operator=( GENERALINFORMATION_Display_CLI const & rhs) 
{
    (void)rhs;
    return *this;
}
GENERALINFORMATION_Display_CLI::GENERALINFORMATION_Display_CLI(GENERALINFORMATION_Display_CLI const & src)
{
    *this = src;
}
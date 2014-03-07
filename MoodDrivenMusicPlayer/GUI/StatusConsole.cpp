#include "StatusConsole.h"
#include "ui_statusconsole.h"

StatusConsole::StatusConsole(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusConsole)
{
    ui->setupUi(this);
}

StatusConsole::~StatusConsole()
{
    delete ui;
}

void StatusConsole::addMessage(QString _message)
{
    ui->statusOutput->append(_message);
}

#ifndef STATUSCONSOLE_H
#define STATUSCONSOLE_H

#include <QWidget>

namespace Ui {
class StatusConsole;
}

class StatusConsole : public QWidget
{
    Q_OBJECT

public:
    explicit StatusConsole(QWidget *parent = 0);
    ~StatusConsole();
    void addMessage(QString _message);

private:
    Ui::StatusConsole *ui;
};

#endif // STATUSCONSOLE_H

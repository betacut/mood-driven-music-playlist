/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QLabel *image_mood;
    QLabel *label_mood;
    QGroupBox *groupBox_2;
    QListWidget *listWidged_playlist;
    QLabel *image_cover;
    QPushButton *button_play;
    QPushButton *button_next;
    QPushButton *button_prev;
    QLabel *label_mediastate;
    QGroupBox *groupBox_3;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(600, 406);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(490, 10, 101, 111));
        image_mood = new QLabel(groupBox);
        image_mood->setObjectName(QStringLiteral("image_mood"));
        image_mood->setGeometry(QRect(25, 30, 50, 50));
        label_mood = new QLabel(groupBox);
        label_mood->setObjectName(QStringLiteral("label_mood"));
        label_mood->setGeometry(QRect(14, 80, 71, 25));
        label_mood->setTextFormat(Qt::RichText);
        label_mood->setScaledContents(false);
        label_mood->setAlignment(Qt::AlignCenter);
        label_mood->setWordWrap(false);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 120, 581, 251));
        listWidged_playlist = new QListWidget(groupBox_2);
        listWidged_playlist->setObjectName(QStringLiteral("listWidged_playlist"));
        listWidged_playlist->setGeometry(QRect(200, 30, 371, 175));
        listWidged_playlist->setSelectionMode(QAbstractItemView::NoSelection);
        listWidged_playlist->setSelectionBehavior(QAbstractItemView::SelectItems);
        image_cover = new QLabel(groupBox_2);
        image_cover->setObjectName(QStringLiteral("image_cover"));
        image_cover->setGeometry(QRect(10, 30, 175, 175));
        button_play = new QPushButton(groupBox_2);
        button_play->setObjectName(QStringLiteral("button_play"));
        button_play->setGeometry(QRect(240, 215, 40, 25));
        button_next = new QPushButton(groupBox_2);
        button_next->setObjectName(QStringLiteral("button_next"));
        button_next->setGeometry(QRect(280, 215, 40, 25));
        button_prev = new QPushButton(groupBox_2);
        button_prev->setObjectName(QStringLiteral("button_prev"));
        button_prev->setGeometry(QRect(200, 215, 40, 25));
        label_mediastate = new QLabel(groupBox_2);
        label_mediastate->setObjectName(QStringLiteral("label_mediastate"));
        label_mediastate->setGeometry(QRect(10, 215, 181, 25));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 10, 471, 111));
        MainWindow->setCentralWidget(centralWidget);
        groupBox_2->raise();
        groupBox->raise();
        groupBox_3->raise();
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Mood Detection", 0));
        image_mood->setText(QString());
        label_mood->setText(QApplication::translate("MainWindow", "Waiting...", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Player Control", 0));
        image_cover->setText(QString());
        button_play->setText(QApplication::translate("MainWindow", "Play", 0));
        button_next->setText(QApplication::translate("MainWindow", ">>", 0));
        button_prev->setText(QApplication::translate("MainWindow", "<<", 0));
        label_mediastate->setText(QApplication::translate("MainWindow", "Player Status", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Info", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

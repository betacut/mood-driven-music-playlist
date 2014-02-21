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
#include <QtWidgets/QRadioButton>
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
    QGroupBox *groupBox_4;
    QRadioButton *radio_affectiv;
    QRadioButton *radio_expressiv;
    QGroupBox *groupBox_5;
    QPushButton *btn_connect;
    QPushButton *btn_disconnect;
    QRadioButton *radio_emoEngine;
    QRadioButton *radio_emoComposer;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(600, 414);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(490, 10, 101, 111));
        groupBox->setAlignment(Qt::AlignCenter);
        image_mood = new QLabel(groupBox);
        image_mood->setObjectName(QStringLiteral("image_mood"));
        image_mood->setGeometry(QRect(25, 30, 50, 50));
        label_mood = new QLabel(groupBox);
        label_mood->setObjectName(QStringLiteral("label_mood"));
        label_mood->setGeometry(QRect(13, 80, 71, 25));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_mood->setFont(font);
        label_mood->setStyleSheet(QStringLiteral(""));
        label_mood->setTextFormat(Qt::RichText);
        label_mood->setScaledContents(false);
        label_mood->setAlignment(Qt::AlignCenter);
        label_mood->setWordWrap(false);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 130, 581, 251));
        groupBox_2->setAlignment(Qt::AlignCenter);
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
        groupBox_3->setAlignment(Qt::AlignCenter);
        groupBox_3->setFlat(false);
        groupBox_3->setCheckable(false);
        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(320, 20, 141, 81));
        radio_affectiv = new QRadioButton(groupBox_4);
        radio_affectiv->setObjectName(QStringLiteral("radio_affectiv"));
        radio_affectiv->setGeometry(QRect(10, 25, 121, 20));
        radio_affectiv->setChecked(true);
        radio_expressiv = new QRadioButton(groupBox_4);
        radio_expressiv->setObjectName(QStringLiteral("radio_expressiv"));
        radio_expressiv->setGeometry(QRect(10, 50, 121, 20));
        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 20, 301, 80));
        btn_connect = new QPushButton(groupBox_5);
        btn_connect->setObjectName(QStringLiteral("btn_connect"));
        btn_connect->setGeometry(QRect(190, 20, 111, 32));
        btn_disconnect = new QPushButton(groupBox_5);
        btn_disconnect->setObjectName(QStringLiteral("btn_disconnect"));
        btn_disconnect->setEnabled(false);
        btn_disconnect->setGeometry(QRect(190, 45, 112, 32));
        radio_emoEngine = new QRadioButton(groupBox_5);
        radio_emoEngine->setObjectName(QStringLiteral("radio_emoEngine"));
        radio_emoEngine->setGeometry(QRect(10, 25, 121, 20));
        radio_emoComposer = new QRadioButton(groupBox_5);
        radio_emoComposer->setObjectName(QStringLiteral("radio_emoComposer"));
        radio_emoComposer->setGeometry(QRect(10, 50, 121, 20));
        radio_emoComposer->setChecked(true);
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
        label_mood->setText(QString());
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Player Control", 0));
        image_cover->setText(QString());
        button_play->setText(QApplication::translate("MainWindow", "Play", 0));
        button_next->setText(QApplication::translate("MainWindow", ">>", 0));
        button_prev->setText(QApplication::translate("MainWindow", "<<", 0));
        label_mediastate->setText(QApplication::translate("MainWindow", "Player Status", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Mood Control", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Detection Suite:", 0));
        radio_affectiv->setText(QApplication::translate("MainWindow", "Expressiv Suite", 0));
        radio_expressiv->setText(QApplication::translate("MainWindow", "Affectiv Suite", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Emotiv Engine:", 0));
        btn_connect->setText(QApplication::translate("MainWindow", "Connect", 0));
        btn_disconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        radio_emoEngine->setText(QApplication::translate("MainWindow", "EmoEngine", 0));
        radio_emoComposer->setText(QApplication::translate("MainWindow", "EmoComposer", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

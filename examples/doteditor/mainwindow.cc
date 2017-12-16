//
//
//

#include "drawingpanel.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
	,ui(new Ui::MainWindow)
    ,m_drawingPanel()
{
	ui->setupUi(this);
	setWindowTitle(tr("doteditor"));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionExit_triggered()
{
	this->close();
}

#include <QMessageBox>

// connected automatically by QMetaObject::connectSlotsByName
void MainWindow::on_actionAbout_triggered()
{
	qDebug() << "About...";
	QMessageBox::about(this, tr("About doteditor"),
		tr("Example Bezier curve editor\n"
			"yyk (c) 2017"));
}

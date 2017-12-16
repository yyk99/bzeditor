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

void MainWindow::on_actionNew_triggered()
{
	ui->m_drawingPanel->startOver();
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

// end of file

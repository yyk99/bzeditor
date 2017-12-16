//
//
//

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include "drawingpanel.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
	,ui(new Ui::MainWindow)
    ,m_drawingPanel()
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionExit_triggered()
{
	this->close();
}

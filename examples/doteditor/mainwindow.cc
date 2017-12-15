//
//
//

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

class DrawingPanel : public QWidget
{
public:
    DrawingPanel(QWidget *papa = 0) : QWidget(papa) {
    }

protected:
    virtual void resizeEvent(QResizeEvent *evnt) override
    {
        std::cout << "Resize event..." << std::endl;
        QWidget::resizeEvent(evnt);
    }
};

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
	,ui(new Ui::MainWindow)
    ,m_drawingPanel()
{
	ui->setupUi(this);
    m_drawingPanel = new DrawingPanel(ui->m_drawing_container);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionExit_triggered()
{
	this->close();
}

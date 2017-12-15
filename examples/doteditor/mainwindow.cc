//
//
//

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "rasterwindow.h"

class SimpleRasterEditor : public RasterWindow {
public:
    SimpleRasterEditor(QWindow *parent = 0) : RasterWindow(parent) {}
    void render(QPainter *p) override
    {
    }
};

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
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

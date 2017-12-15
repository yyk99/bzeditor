#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class DrawingPanel;
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_actionExit_triggered();

private:
	Ui::MainWindow *ui;
    DrawingPanel *m_drawingPanel;
};

#endif // MAINWINDOW_H

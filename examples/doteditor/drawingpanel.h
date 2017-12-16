//
//
//

#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include <QWidget>

class DrawingPanel : public QWidget
{
	Q_OBJECT
public:
    DrawingPanel(QWidget *papa = 0);

protected:
    virtual void resizeEvent(QResizeEvent *) override;
	virtual void paintEvent(QPaintEvent *) override;
};

#endif // DRAWINGPANEL_H

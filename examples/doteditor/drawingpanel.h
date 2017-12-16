//
//
//

#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include <QWidget>

class Model;
class DrawingPanel : public QWidget
{
	Q_OBJECT
public:
    DrawingPanel(QWidget *papa = 0);
	virtual ~DrawingPanel();

protected:
    virtual void resizeEvent(QResizeEvent *) override;
	virtual void paintEvent(QPaintEvent *) override;

	virtual void enterEvent(QEvent *) override;
	virtual void leaveEvent(QEvent *) override;

	virtual void mousePressEvent(QMouseEvent *event) override;
	virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
	QCursor m_savedCursor;
	Model *m_model;
};

#endif // DRAWINGPANEL_H

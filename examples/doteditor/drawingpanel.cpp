//
//
//

#include "drawingpanel.h"

#include <iostream>

#include <QPainter>

DrawingPanel::DrawingPanel(QWidget *papa /*= 0*/) : QWidget(papa)
{

}

void DrawingPanel::resizeEvent(QResizeEvent *evnt)
{
	std::cout << "Resize event..." << std::endl;
	QWidget::resizeEvent(evnt);
}

void DrawingPanel::paintEvent(QPaintEvent *event)
{
	std::cout << "w=" << this->width() << ", h=" << this->height() << std::endl;

	QPainterPath path;
	path.moveTo(20, 80);
	path.lineTo(20, 30);
	path.cubicTo(80, 0, 50, 50, 80, 80);

	int startAngle = 20 * 16;
	int arcLength = 120 * 16;

	QPainter painter(this);
	//painter.setPen(pen);
	//painter.setBrush(brush);
	//painter.setRenderHint(QPainter::Antialiasing, true);

	painter.setPen(Qt::black);
	painter.drawPath(path);

	painter.setPen(Qt::red);
	int margin = 4;
	painter.drawRect(margin, margin, this->width() - 2*margin, this->height() - 2*margin);
}

//
//
//

#include "drawingpanel.h"
#include "bezierMk2.h"

#include <iostream>

#include <QPainter>
#include <QDebug>

#include <list>
#include <QPoint>

class Model {
public:
	Model() {

	}

	void addClick(QPoint const &p)
	{
		m_clicks.push_back(p);
	}

	void clear() {
		m_clicks.clear();
	}

	std::list<QPoint>::const_iterator begin() const { 
		return m_clicks.begin(); 
	}
	std::list<QPoint>::const_iterator end() const { 
		return m_clicks.end(); 
	}
	size_t size() const {
		return m_clicks.size();
	}
private:
	std::list<QPoint> m_clicks;
};

DrawingPanel::DrawingPanel(QWidget *papa /*= 0*/) : QWidget(papa), m_model()
{
	m_savedCursor = this->cursor();
	m_model = new Model();
}

DrawingPanel::~DrawingPanel()
{
	delete m_model;
}

void DrawingPanel::resizeEvent(QResizeEvent *evnt)
{
	qDebug() << "Resize event...";
	QWidget::resizeEvent(evnt);
}

void DrawingPanel::paintEvent(QPaintEvent *event)
{
	qDebug() << "w =" << this->width() << "h =" << this->height();

	QPainter painter(this);

	painter.setPen(Qt::red);
	int margin = 0;
	painter.drawRect(margin, margin, this->width() - 2*margin - 1, this->height() - 2*margin - 1);

	painter.setPen(Qt::blue);
	for (QPoint p : *m_model) {
		painter.drawPoint(p);
		painter.drawRect(QRect(p - QPoint(2,2), p + QPoint(2,2)));
	}

	{
		QPainterPath path;
		int count = 0;
		for (QPoint p : *m_model) {
			++count;
			if (count == 1)
				path.moveTo(p);
			else
				path.lineTo(p);
		}
		painter.setPen(Qt::black);
		painter.drawPath(path);
	}

	if(m_model->size() > 2){
		const int N = 300;
		std::vector<point2d_t> controls; controls.reserve(m_model->size());
		for (QPoint p : *m_model)
			controls.push_back(point2d_t(p.x(), p.y()));

		QPainterPath path;
		for (int i = 0; i <= N; ++i) {
			double u = 1.0 / N * i;
			QPointF p = make_QPointF(bezierMk2(u, controls));
			if (i == 0)
				path.moveTo(p);
			else
				path.lineTo(p);
		}
		painter.setPen(Qt::green);
		painter.drawPath(path);
	}
}

void DrawingPanel::enterEvent(QEvent *event)
{
	qDebug() << "Enter...";
	m_savedCursor = cursor();
	setCursor(Qt::CrossCursor);
}

void DrawingPanel::leaveEvent(QEvent *event)
{
	qDebug() << "Leaving...";
	setCursor(m_savedCursor);
}

#include <QMouseEvent>

void DrawingPanel::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::MouseButton::LeftButton) {
		m_model->addClick(e->pos());
		update();
	}
}

void DrawingPanel::mouseDoubleClickEvent(QMouseEvent *e)
{
	m_model->clear();
	update();
}

QPointF DrawingPanel::make_QPointF(point2d_t const &p)
{
	return QPointF(std::get<0>(p), std::get<1>(p));
}

//
//
//

#include "bezierMk2.h"
#include "Plotter.h"

void Plotter::setupTransformator(std::vector<point2d_t> const & controls)
{
	double x_min = std::numeric_limits<double>::max(), y_min = std::numeric_limits<double>::max();
	double x_max = std::numeric_limits<double>::min(), y_max = std::numeric_limits<double>::min();

	for (point2d_t p : controls) {
		if (x_min > std::get<0>(p))
			x_min = std::get<0>(p);
		if (x_max < std::get<0>(p))
			x_max = std::get<0>(p);

		if (y_min > std::get<1>(p))
			y_min = std::get<1>(p);
		if (y_max < std::get<1>(p))
			y_max = std::get<1>(p);
	}

	double dx = (x_max - x_min);
	double cx = m_WI / dx;
	double dy = (y_max - y_min);
	double cy = m_HI / dy;
	m_trans = CoordinateTransformator(cx, 0, 0,
		0, -cy, m_HI * y_max / dy);
}

QPointF Plotter::makeQPointF(point2d_t const & p)
{
	auto pp = m_trans(p);
	return QPointF(std::get<0>(pp), std::get<1>(pp));
}

// See: http://www.java2s.com/Code/Cpp/Qt/CreatepixmalwithQPixmapsavetopngfile.htm

void Plotter::plot_image(std::string const & filename, std::vector<point2d_t> const & controls, std::vector<point2d_t> const & points)
{
	int n = 0;
	QApplication app(n, 0);
#if 0
	QPixmap pixmap(200, 200);
	pixmap.fill(Qt::white);

	QPainterPath path;

	path.addEllipse(80, 80, 80, 80);

	path.moveTo(120, 120);
	path.lineTo(120, 40);
	path.arcTo(40, 40, 160, 160, 90, 90);
	path.lineTo(120, 120);

	QFont font = QApplication::font();
	font.setPixelSize(40);

	path.addText(20, 180, font, "Path");

	QPainter painter(&pixmap);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.setPen(Qt::black);
	painter.setBrush(Qt::gray);

	painter.drawPath(path);
#else
	setupTransformator(controls);

	QPixmap pixmap(m_WI, m_HI);
	pixmap.fill(Qt::white);
	QPainter painter(&pixmap);
	painter.setRenderHint(QPainter::Antialiasing);

	{
		QPainterPath path;
		path.moveTo(makeQPointF(controls[0]));
		for (int i = 1; i != controls.size(); ++i)
			path.lineTo(makeQPointF(controls[i]));
		painter.setPen(Qt::black);
		painter.drawPath(path);
	}

	{
		QPainterPath path;
		path.moveTo(makeQPointF(points[0]));
		for (int i = 1; i != points.size(); ++i)
			path.lineTo(makeQPointF(points[i]));
		painter.setPen(Qt::red);
		painter.drawPath(path);
	}

#endif
	pixmap.save(filename.c_str());
}

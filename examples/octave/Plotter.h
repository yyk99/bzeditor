//
//
//

#ifndef PLOTTER_H
#define PLOTTER_H

#include "CoordinateTransformator.h"

#include <QPainter>
#include <QPixmap>
#include <QApplication>

class point2d_t;
class Plotter {
private:
    int m_HI;
    int m_WI;

    CoordinateTransformator m_trans;

	void setupTransformator(std::vector<point2d_t> const & controls);

public:
    Plotter(int width = 1024, int height = 1024) : m_HI(height), m_WI(width)
    {

    }

	QPointF makeQPointF(point2d_t const &p);

    // See: http://www.java2s.com/Code/Cpp/Qt/CreatepixmalwithQPixmapsavetopngfile.htm
	void plot_image(std::string const &filename, std::vector<point2d_t> const &controls, std::vector<point2d_t> const &points);
};


#endif // PLOTTER_H 
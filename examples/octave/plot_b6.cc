//
//
//

#include "bezierMk2.h"

#include <iostream>
#include <stdexcept>

std::ostream &operator<< (std::ostream &s, point2d_t const &p)
{
    s << p.to_string();
    return s;
}

#include <QPainter>
#include <QPixmap>
#include <QApplication>

class CoordinateTransformator {
private:
    double a11, a12, a13;
    double a21, a22, a23;

public:
    CoordinateTransformator() :
        a11(1), a12(0), a13(0),
        a21(0), a22(1), a23(0)
    {}

    CoordinateTransformator(double a1, double a2, double a3, double a4, double a5, double a6) :
        a11(a1), a12(a2), a13(a3),
        a21(a4), a22(a5), a23(a6)
    {}

    std::tuple<double, double> operator() (std::tuple<double, double> const &p) const
    {
        return std::make_tuple(a11 * std::get<0>(p) + a12 * std::get<1>(p) + a13,
            a21 * std::get<0>(p) + a22 * std::get<1>(p) + a23);
    }
};

class Plotter {
private:
    int m_HI;
    int m_WI;

    CoordinateTransformator m_trans;

    void setupTransformator(std::vector<point2d_t> const & controls)
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

public:
    Plotter(int width = 1024, int height = 1024) : m_HI(height), m_WI(width)
    {

    }

    QPointF makeQPointF(point2d_t const &p)
    {
        auto pp = m_trans(p);
        return QPointF(std::get<0>(pp), std::get<1>(pp));
    }

    // See: http://www.java2s.com/Code/Cpp/Qt/CreatepixmalwithQPixmapsavetopngfile.htm
    void plot_image(std::string const &filename, std::vector<point2d_t> const &controls, std::vector<point2d_t> const &points)
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
};

void plot_b6_UT() /* unit test */
{
    point2d_t p0 = point2d_t(10, 10);
    point2d_t p1 = point2d_t(0, 20);
    point2d_t p2 = point2d_t(30, 30);
    point2d_t p3 = point2d_t(50, 20);
    point2d_t p4 = point2d_t(40, 0);
    point2d_t p5 = point2d_t(20, 0);
    point2d_t p6 = p0;

    {
        std::vector<point2d_t> points = { p0, p1 };
        auto r = bezierMk2(0, points);

        if (r != p0)
            throw std::logic_error("Expected p0");
    }

    {
        std::vector<point2d_t> points = { p0, p1 };
        auto r = bezierMk2(1, points);

        if (r != p1)
            throw std::logic_error("Expected p1");
    }

    {
        {
            std::vector<point2d_t> points = { p0, p1 };

            double u = 0.5;
            auto r = bezierMk2(0.5, points);

            std::cout << "bz(" << u << ") = " << r << std::endl;

            if (r != point2d_t(5, 15))
                throw std::logic_error("Expected {5, 15}");
        }
        {
            std::vector<point2d_t> points = { p0, p1, p2, p3, p4, p5, p6 };

            double u = 0.5;
            auto r = bezierMk2(0.5, points);

            std::cout << "bz(" << u << ") = " << r << std::endl;
            point2d_t expected = point2d_t(34.2187500000000, 15.4687500000000);
            if (r != point2d_t(34.2187500000000, 15.4687500000000))
                throw std::logic_error("Expected " + expected.to_string());
        }
    }
}

void plot_b6()
{
    point2d_t p0 = point2d_t(10, 10);
    point2d_t p1 = point2d_t(0, 20);
    point2d_t p2 = point2d_t(30, 30);
    point2d_t p3 = point2d_t(50, 20);
    point2d_t p4 = point2d_t(40, 0);
    point2d_t p5 = point2d_t(20, 0);
    point2d_t p6 = p0;
    std::vector<point2d_t> controls = { p0, p1, p2, p3, p4, p5, p6 };

    std::cout << "X,Y" << std::endl;
    const int N = 200;
    std::vector<point2d_t> points(N+1);
    for(int i = 0 ; i <= N ; ++i)
    {
        double u = 1.0 / N * i;
        auto p = bezierMk2(u, controls);
        std::cout << std::get<0>(p) << "," << std::get<1>(p) << std::endl;
        points[i] = p;
    }

    Plotter plotter;

    plotter.plot_image("plot_b6.png", controls, points);
}

int main()
{
    try {
        plot_b6();
    } catch (std::exception ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

// end of file

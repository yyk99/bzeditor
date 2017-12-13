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

void plot_image(std::string const &filename, std::vector<point2d_t> const &controls, std::vector<point2d_t> const &point);

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

    plot_image("plot_b6.png", controls, points);
}

#include <QPainter>
#include <QPixmap>
#include <QApplication>

// See: http://www.java2s.com/Code/Cpp/Qt/CreatepixmalwithQPixmapsavetopngfile.htm
void plot_image(std::string const &filename, std::vector<point2d_t> const &controls, std::vector<point2d_t> const &point)
{
    int n = 0;
    QApplication app(n, 0);

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

    pixmap.save(filename.c_str());
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

#include <circle.hpp>
#include <mainwindow.h>

// include files for class Point

void Circle::draw()
{
    MainWindow* mainW = MainWindow::getInstance();
    if(this->selected)
    {
        mainW->SetPen(3,Qt::blue);
    }

    QPointF help1 = QPointF(center.getx(),center.gety()+r);
    QPointF help = mainW -> mapToMyScene(help1.x(),help1.y());
    QPointF cen = mainW->mapToMyScene(center.getx(),center.gety()); //doesn't work?
    mainW->drawPoint(cen);
    mainW->drawCircle(cen,help);

    mainW->ResetPen();
}

void Circle::translate(double dx, double dy){

    center.translate(dx,dy);
}

bool Circle::in_personal_area(double x, double y)
{
    double ro = distance(Point(x,y),center);
    if (ro>r-5 && ro<r+5)
    {
        return true;
    }
    return false;
}

void Circle::zoom(double coef, double c_x, double c_y)
{
    this->r*=coef;
    this->center.setx((this->center.getx()-c_x)*coef+c_x);
    this->center.sety((this->center.gety()-c_y)*coef+c_y);
}

Circle:: Circle(Point &p, double r) : MathObject()
{
    this->center = p;
    this->r = r;
    MainWindow* mainW = MainWindow::getInstance();
    this->r_t = r / mainW->mainGrid->unit;
}

Circle::Circle(Point &center, Point x) : MathObject()
{
    this->center = center;
    this->r = sqrt(pow(x.getx()-center.getx(),2)+pow(x.gety()-center.gety(),2));
    MainWindow* mainW = MainWindow::getInstance();
    this->r_t = this->r / mainW->mainGrid->unit;
}

Circle:: ~Circle()
{
    std::cout << "Destroying Circle( " << center.getx() << " , " << center.gety() << " , "<< r <<" )"<< std::endl;

}

double Circle:: getX()
{
  return center.getx();
}

double Circle:: getY()
{
  return center.gety();
}

double Circle:: getR()
{
  return r;
}

void Circle:: setX(double x)
{
  double y = center.gety();
  center = Point(x, y);
}

void Circle:: setY(double y)
{
  double x = center.getx();
  center = Point(x,y);
}

void Circle:: setR(double r)
{
  (*this).r = r;
}

void Circle:: movecenter(double x, double y)
{
  setX(x);
  setY(y);
}

double Circle:: surface()
{
  return r*r*M_PI;
}

double Circle:: perimeter()
{
  return 2*r*M_PI;
}

double Circle::diameter()
{
  return 2*r;
}

std::vector<Line> Circle::tangent(Point M)
{
    std::vector<Line> l;
    double r = getR();
    double xp = M.getx();
    double yp = M.gety();
    double a = center.getx();
    double b = center.gety();
    double del = pow(xp-a,2)+pow(yp-b,2)-pow(r,2);

    if (pow(10,-5)<del) //point outside the circle
    {
        double x1 = (r*r*(xp-a)+r*(yp-b)*sqrt(del))/(pow(xp-a,2)+pow(yp-b,2)) + a;
        double y1 = (r*r*(yp-b)-r*(xp-a)*sqrt(del))/(pow(xp-a,2)+pow(yp-b,2)) + b;
        double x2 = (r*r*(xp-a)-r*(yp-b)*sqrt(del))/(pow(xp-a,2)+pow(yp-b,2)) + a;
        double y2 = (r*r*(yp-b)+r*(xp-a)*sqrt(del))/(pow(xp-a,2)+pow(yp-b,2)) + b;
        Point p1 = Point(x1,y1);
        Point p2 = Point(x2,y2);
        Line l1 = Line(p1,M);
        Line l2 = Line(p2,M);
        l.push_back(l1);
        l.push_back(l2);
        std::cout << "There are two tangents:" << std::endl;
        if (l1.y_intercept() >= 0)
            std::cout << "y = " << l1.slope() << " * x + "<< l1.y_intercept() << std::endl;
        else
            std::cout << "y = " << l1.slope() << " * x  "<< l1.y_intercept() << std::endl;
        if (l2.y_intercept() >= 0)
            std::cout << "y = " << l2.slope() << " * x + "<< l2.y_intercept() << std::endl;
        else
            std::cout << "y = " << l2.slope() << " * x  "<< l2.y_intercept() << std::endl;
    }
    else if (pow(10,-5)>del && del>=0) //point on circle
    {
        Line l1 = Line(center,M);
        double m = -1/l1.slope();
        double x1 = M.getx()-20;
        double y1 = M.gety()+m*(x1-M.getx());
        Point p = Point(x1,y1);
        Line l2 = Line(p,M);
        l.push_back(l2);
        if (l2.y_intercept() >= 0)
            std::cout << "y = " << l2.slope() << " * x + "<< l2.y_intercept() << std::endl;
        else
            std::cout << "y = " << l2.slope() << " * x  "<< l2.y_intercept() << std::endl;
    }

    return l; //it is empty if point is inside the circle
}

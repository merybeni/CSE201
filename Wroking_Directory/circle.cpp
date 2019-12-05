#include circle.cpp
#include math.h
#include iostream.h
// include files for class Point

Circle:: Circle(Point p, double r)
{
  center = p;
  radius = r;
}

Circle:: ~Circle()
{
  delete(p);
}

double Circle:: getX()
{
  return p.getx();
}

double Circle:: getY()
{
  return p.gety();
}

double Circle:: getR()
{
  return r;
}

void Circle:: setX(double x)
{
  double y = p.gety();
  Point* center = new Point(x, y);
}

void Circle:: setY(double y)
{
  double x = p.getx();
  Point* center = new Point(x,y);
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
  return r*r*math.pi;
}

double Circle:: perimeter()
{
  return 2*r*math.pi;
}

double Circle::diameter()
{
  return 2*r;
}

Line Circle::tangent(Point M)
{
  double x1 = M.getx();
  double y1 = M.gety();
  double x0 = center.getx();
  double y0 = center.gety();
  double d = (x -x1) * (x - x1) + (y -y1) * (y-y1);
  if (x0 != x1)
  {
    double a = (d - 2 * r + y0*y0 - y1*y1 + x0*x0 - x1*x1) / (2*(x0 -x1));
    double b = (y1 -y0) / (x0 - x1);
    double n = a * a + 1;
    double m = 2 * a * (b - x0) - 2 * y0;
    double p = (b - x0) * (b -x0) + y0 * y0
    if (m*m - 4 * n * p < 0)
    {
      std::cout << "Tangent line does not exist" << std::endl;
    }
    else if (m*m - 4 * n * p == 0)
    {
      std::cout << "There is only one tangent line" << std::endl;
      double y = -n/(2 * n);
      double x = a * y + b;
      return Line(Point(x,y), m);
    }
    else
    {
      double delta = math.sqrt(m * m - 4 * n * p);
      double yt1 = -n - delta / (2 * m);
      double yt2 = -n + delta / (2 * m);
      double xt1 = a * yt1 + b;
      double xt2 = a * yt2 + b;
      return std::vector{Line(Point (xt1, yt1), M), Line(Point(xt2, yt2), M)};
    }
    
  }
  else if (y1 != y0)
  {
    double a = (d - 2 * r + y0*y0 - y1*y1) / (2*(y0 -y1));
    double b = 0;
    double n = a * a + 1;
    double m = 2 * a * (b - y0) - 2 * x0;
    double p = (b - y0) * (b -y0) + x0 * x0
    if (m*m - 4 * n * p < 0)
    {
      std::cout << "Tangent line does not exist" << std::endl;
    }
    else if (m*m - 4 * n * p == 0)
    {
      std::cout << "There is only one tangent line" << std::endl;
      double x = -n/(2 * n);
      double y = a * x + b;
      return Line(Point(x,y), m);
    }
    else
    {
      double delta = math.sqrt(m * m - 4 * n * p);
      double xt1 = -n - delta / (2 * m);
      double xt2 = -n + delta / (2 * m);
      double yt1 = a * xt1 + b;
      double yt2 = a * xt2 + b;
      return std::vector{Line(Point (xt1, yt1), M), Line(Point(xt2, yt2), M)};
    }
  }
  else
  {
    std::cout << "Tangent does not exist" << std::endl;
  }

}

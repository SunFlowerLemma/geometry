#include <iostream>
#include <string>
#include <Eigen/Dense>

using namespace Eigen;

class Plane
{
public:
     Plane(Vector3d n, Vector3d p) : normal(n), planar_point(p){};

     Vector3d normal;
     Vector3d planar_point;

     Vector3d Projection_Normal(Vector3d);
     Vector3d Projection_Planar(Vector3d);
     bool SeparatesPoints(Vector3d, Vector3d);
};

Vector3d Plane::Projection_Normal(Vector3d point)
{
     /* projection of point along normal with respect to the planar_point*/
     double scalar = (point - planar_point).dot(normal) / normal.dot(normal);
     Vector3d proj = scalar * normal;
     return proj;
};

Vector3d Plane::Projection_Planar(Vector3d point)
{
     /* projection of point onto plane with respect to the planar_point*/
     return point - Projection_Normal(point);
};

bool Plane::SeparatesPoints(Vector3d p, Vector3d q)
{
     /* if points lie on opposite sides of plane, return 1 */
     return Projection_Normal(p).dot(Projection_Normal(q)) < 0;
};

bool Coplanar(Plane plane, Vector3d unknown_point)
{
     return (plane.planar_point - unknown_point).dot(plane.normal) == 0;
}

int main()
{
     // vertices of triangle
     Vector3d P, Q, R;

     P << 1, 4, 6;
     Q << -2, 5, -1;
     R << 1, -1, 1;

     // edges of triangle
     Vector3d PQ, PR;

     PQ = Q - P;
     PR = R - P;

     // unit normal of triangle
     Vector3d n = PQ.cross(PR);
     n = n / n.norm();

     Plane plane(n, P);

     /*
     does Q lie on the plane determined by normal n and point P?
     can be used to determine if 4 points form a planr polygon
     */
     std::string same_plane = Coplanar(plane, 30 * Q) ? "are coplanar" : "not coplanar";

     // print results
     std::cout << "---unit normal---\n"
               << n << "\n-----------------\n";

     std::cout << same_plane << std::endl;

     std::cout << plane.Projection_Normal(P + Q) << std::endl;
     std::cout << plane.SeparatesPoints(P + Q, 0 * P) << std::endl;

     return 0;
}
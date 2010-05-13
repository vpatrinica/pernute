#include <list>
#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
#include <vector>
#include <cassert>

#include  <ADSLIB.H>
#include "dbobjptr.h"
#include "dbpl.h"
#include "dbents.h"
#include "aced.h"
#include "dbsymtb.h"
#include "dbapserv.h"
#include "acgi.h"
#include "tchar.h"


#include <CGAL/Cartesian.h>
#include <CGAL/Homogeneous.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/Convex_hull_d.h>
#include <CGAL/Convex_hull_d_traits_3.h>
#include <CGAL/Convex_hull_d_to_polyhedron_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/algorithm.h>
#include <CGAL/number_utils.h>


#ifdef CGAL_USE_LEDA
#include <CGAL/leda_integer.h>
typedef leda_integer RT;
#else
#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz RT;
#else
// NOTE: the choice of double here for a number type may cause problems
//       for degenerate point sets
#include <CGAL/double.h>
typedef double RT;
#endif
#endif


typedef CGAL::Homogeneous<RT>                  Kernel;
typedef Kernel::Point_3                             Point_3;
typedef CGAL::Polyhedron_3< Kernel>                 Polyhedron;
//typedef CGAL::Polyhedron_3< Kernel,
 //                           CGAL::Polyhedron_items_3,
 //                           CGAL::HalfedgeDS_vector>   Polyhedron;
typedef CGAL::Convex_hull_d_traits_3<Kernel>        Hull_traits_3;
typedef CGAL::Convex_hull_d< Hull_traits_3 >   Convex_hull_3;
typedef CGAL::Creator_uniform_3<double, Point_3>   Creator;

typedef Polyhedron::Facet_iterator                           Facet_iterator;
typedef Polyhedron::Vertex_iterator                          Vertex_iterator;
typedef Polyhedron::Halfedge_around_facet_circulator
                                            Halfedge_around_facet_circulator;
typedef Polyhedron::Halfedge_around_vertex_circulator Halfedge_around_vertex_circulator;




class ConvexHull
{
public:
	ConvexHull(AcArray<AcGePoint3d>*);
	ConvexHull(){};
	~ConvexHull(){};
	void printPoints(int color, AcArray<AcGePoint3d>* _pointArray);
	void printSegment(int color, AcGePoint3d _point1, AcGePoint3d _point2);
	void printPolyhedron();
	int edgeCoincides(double X11, double Y11, double Z11, double X21, double Y21, double Z21, double X12, double Y12, double Z12, double X22, double Y22, double Z22);

};


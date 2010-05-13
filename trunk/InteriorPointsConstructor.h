#pragma once
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif
#include <algorithm>

#include "aced.h"
#include "dbsymtb.h"
#include "dbapserv.h"
#include "acgi.h"
#include "tchar.h"
#include <list>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include  <ADSLIB.H>
#include "dbobjptr.h"
#include "dbpl.h"
#include "dbents.h"

#include "ConvexHull.h"
using namespace std;
typedef pair<pair<int, int>, double> my_pair;
bool sort_pred(const my_pair& left, const my_pair& right);

class InteriorPointsConstructor
{
	public:
		InteriorPointsConstructor();
		~InteriorPointsConstructor();
		void setContour(AcArray<AcGePoint3d>*);
		void constructInteriorPoints();
		void printInteriorPoints(int, bool);
		void printFirstInteriorPoints(int color, bool flag);
		void ForceDirectedAlgorithm();
		void ForceDirectedAlgorithm2();
		void makePolyhedron();
		void computeNumberVertices();
		void PrintContourPoints();
		void arrayNeighbour(vector<pair<int,int>>&, int, int);
		void findNeighboursAtDist(int, double, vector<pair<int, int>>&, int, int);
		double distanceNeighbours(int, int, int, int);
		void drawNet(int);
		void setKappa(double);
		double F_attractive(double);
		double F_repulsive(double);
		double maxX();
		double maxY();
		double maxZ();
		double minX();
		double minY();
		double minZ();
	
	private:
		AcArray<AcGePoint3d>* _contourArray;
		AcArray<AcGePoint3d>* _interiorArray;
		AcArray<AcGePoint3d>* _interiorDisplacementArray;
		long int _numVertices;
		double _kappa;

};
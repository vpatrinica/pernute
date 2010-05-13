#include "ConvexHull.h"

ConvexHull::ConvexHull(AcArray<AcGePoint3d>* _pointArray)
{
	int i;

  Convex_hull_3 CH(3);

  
  for (i = 0; i < _pointArray->length(); i++)
  {
	 	
	  CH.insert(Point_3(_pointArray->at(i).x, _pointArray->at(i).y, _pointArray->at(i).z, 1));
  }
//  assert(CH.is_valid());
	acutPrintf(_T("\nInserted %d vertices into the convex hull..\n"), _pointArray->length());
	
  // define polyhedron to hold convex hull and create it
  Polyhedron P;
  CGAL::convex_hull_d_to_polyhedron_3(CH,P);

	 int nr = 0;
	 double x1, x2, y1, y2, z1, z2;
	   //double d, dx, dy, dz = 0;
	   double x, y, z; 
		AcArray<AcGePoint3d> * ApointArray = new AcArray<AcGePoint3d>;
	   int color = 2;
	   for ( Polyhedron::Vertex_iterator j = P.vertices_begin(); j != P.vertices_end(); ++j) {
        //Halfedge_around_facet_circulator j = i->facet_begin();
        // Facets in polyhedral surfaces are at least triangles.
        //CGAL_assertion( CGAL::circulator_size(j) >= 3);
        //std::cout << CGAL::circulator_size(j) << " ";
		//color++;
        //do {
           nr++;
			///dx = to_double(P.vertices_begin()->point().x()) - to_double(j->vertex()->point().x());
			//dy = to_double(P.vertices_begin()->point().y()) - to_double(j->vertex()->point().y());
			//dz = to_double(P.vertices_begin()->point().z()) - to_double(j->vertex()->point().z());
			/*x = to_double(j->vertex()->point().x());
			y = to_double(j->vertex()->point().y());
			z = to_double(j->vertex()->point().z());*/
			x = to_double(j->point().x());
			y = to_double(j->point().y());
			z = to_double(j->point().z());
			ApointArray -> append(AcGePoint3d(x, y, z));
			
			
			//d = sqrt(dx*dx + dy*dy + dz*dz);
			//acutPrintf(_T(" %f"), d);
			//ApointArray->removeAll();
        //} while ( ++j != i->facet_begin());

        acutPrintf(_T("\n"));
    }
	   //printPoints(color, ApointArray);
   acutPrintf(_T("\n %d vertices generatedl..\n"), nr);
   acutPrintf(_T("Generating the two criteria of faces..."));
//the two adjacent
//find the adjacent face
	Polyhedron::Facet_iterator itF, itF1, itF2;
	Halfedge_around_facet_circulator itH;

 /*  for ( itF = P.facets_begin(); itF != P.facets_end(); ++itF) 
	{
		itH = itF->facet_begin();
        
        
        do {
			
			x1 = to_double(itH->vertex()->point().x());
			y1 = to_double(itH->vertex()->point().y());
			z1 = to_double(itH->vertex()->point().z());
			
			x2 = to_double(itH->next()->vertex()->point().x());
			y2 = to_double(itH->next()->vertex()->point().y());
			z2 = to_double(itH->next()->vertex()->point().z());
			printSegment(4, AcGePoint3d(x1, y1, z1), AcGePoint3d(x2, y2, z2));
            
        } while ( ++itH != itF->facet_begin());
       
	}
	*/
   
	
	bool found = false;
	itF = P.facets_begin();
	//Halfedge_around_facet_circulator auxH;
	i=0;
	while ((itF != P.facets_end()) && (!found)) 
	{

		itH = itF->facet_begin();
        
        
        do {
			
			x1 = to_double(itH->vertex()->point().x());
			y1 = to_double(itH->vertex()->point().y());
			z1 = to_double(itH->vertex()->point().z());
			
			x2 = to_double(itH->next()->vertex()->point().x());
			y2 = to_double(itH->next()->vertex()->point().y());
			z2 = to_double(itH->next()->vertex()->point().z());
			if (edgeCoincides(x1, y1, z1, x2, y2, z2, _pointArray->at(0).x, _pointArray->at(0).y,_pointArray->at(0).z, _pointArray->at(1).x, _pointArray->at(1).y,_pointArray->at(1).z) == 1)
			{
				found = true;
				//nextH = itH;
				printSegment(5, AcGePoint3d(x1, y1, z1), AcGePoint3d(x2, y2, z2));
				i++;
				//auxH = itF->facet_begin();
				x1 = to_double(itH->next()->next()->vertex()->point().x());
				y1 = to_double(itH->next()->next()->vertex()->point().y());
				z1 = to_double(itH->next()->next()->vertex()->point().z());
				if edgeCoincides(x2, y2, z2, x1, y1, z1, _pointArray->at(1).x, _pointArray->at(1).y,_pointArray->at(1).z, _pointArray->at(2).x, _pointArray->at(2).y,_pointArray->at(2).z) == 1)
				{
						
						printSegment(5, AcGePoint3d(x1, y1, z1), AcGePoint3d(x2, y2, z2));
				}
			}
			else if (edgeCoincides(x1, y1, z1, x2, y2, z2, _pointArray->at(0).x, _pointArray->at(0).y,_pointArray->at(0).z, _pointArray->at(1).x, _pointArray->at(1).y,_pointArray->at(1).z) == -1)
			{
				found = true;
				//nextH = itH;
				printSegment(5, AcGePoint3d(x1, y1, z1), AcGePoint3d(x2, y2, z2));
				i++;
				if edgeCoincides(x1, y1, z1, x2, y2, z2, _pointArray->at(1).x, _pointArray->at(1).y,_pointArray->at(1).z, _pointArray->at(2).x, _pointArray->at(2).y,_pointArray->at(2).z) == -1)
				{
						
						printSegment(5, AcGePoint3d(x1, y1, z1), AcGePoint3d(x2, y2, z2));
				}
				//auxH = itF->facet_begin();
				
			}
            
        } while (( ++itH != itF->facet_begin()) && (!found) );
       
	   itF++;
	}
	//loop
	//print the found face
	
	//}
	i = 1;
	while (i < _pointArray->length())
	{
		
		i++;
	}

}
int ConvexHull::edgeCoincides(double X11, double Y11, double Z11, double X21, double Y21, double Z21, double X12, double Y12, double Z12, double X22, double Y22, double Z22)
{
	double d1 = sqrt((X11 - X12)*(X11 - X12) + (Y11 - Y12)*(Y11 - Y12) + (Z11 - Z12)*(Z11 - Z12));
	double d2 = sqrt((X21 - X22)*(X21 - X22) + (Y21 - Y22)*(Y21 - Y22) + (Z21 - Z22)*(Z21 - Z22));
	double d3 = sqrt((X11 - X22)*(X11 - X22) + (Y11 - Y22)*(Y11 - Y22) + (Z11 - Z22)*(Z11 - Z22));
	double d4 = sqrt((X21 - X12)*(X21 - X12) + (Y21 - Y12)*(Y21 - Y12) + (Z21 - Z12)*(Z21 - Z12));
	if (d1 + d2 < 10) return 1;
	if (d4 + d3 < 10) return -1;
	return 0;
}

void ConvexHull::printSegment(int color, AcGePoint3d _point1, AcGePoint3d _point2)
{
	AcGePoint3dArray ptArr;

	ptArr.setLogicalLength(2);
	ptArr[0].set(_point1.x, _point1.y, _point1.z);
	ptArr[1].set(_point2.x, _point2.y, _point2.z);
	AcDb3dPolyline *pNewPline = new AcDb3dPolyline(AcDb::k3dSimplePoly , ptArr, Adesk::kFalse);
		
		pNewPline->setColorIndex(color);

		AcDbBlockTable *pBlockTable;
		AcDbBlockTableRecord *pBlockTableRecord;


		acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pBlockTable, AcDb::kForRead);

		
		
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);


		AcDbObjectId plineObjId;
		pBlockTableRecord->appendAcDbEntity(plineObjId, pNewPline);
		
		pBlockTable->close();
		pBlockTableRecord->close();

		pNewPline->close();
			
}

void ConvexHull::printPoints(int color, AcArray<AcGePoint3d>* _pointArray)
{
		int j = 0;
		
		
		AcGePoint3dArray ptArr;

		ptArr.setLogicalLength(_pointArray->length());
		
		
		
		while (j < _pointArray->length())
		{
			
			ptArr[j].set(_pointArray->at(j).x, _pointArray->at(j).y, _pointArray->at(j).z);
			

		
			j++;
		}
		
		AcDb3dPolyline *pNewPline = new AcDb3dPolyline(AcDb::k3dSimplePoly , ptArr, Adesk::kFalse);
		
		pNewPline->setColorIndex(color);

		AcDbBlockTable *pBlockTable;
		AcDbBlockTableRecord *pBlockTableRecord;


		acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pBlockTable, AcDb::kForRead);

		
		
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);


		AcDbObjectId plineObjId;
		pBlockTableRecord->appendAcDbEntity(plineObjId, pNewPline);
		
		pBlockTable->close();
		pBlockTableRecord->close();

		pNewPline->close();
		
}
void ConvexHull::printPolyhedron()
{
}
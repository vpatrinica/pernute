#include "FramePointsConstructor.h"
#include "dbobjptr.h"
#include "LineFrameBuilder.h"
#include "dbents.h"
#include "PLine2DFrameBuilder.h"
#include "PLineFrameBuilder.h"
#include "PLine3DFrameBuilder.h"
#include "ArcFrameBuilder.h"
#include "SplineFrameBuilder.h"
#include <vector>
#include <cmath>

bool static isEqualPoint(AcGePoint3d& pA, AcGePoint3d& pB)
{
	if ( abs(pA.x - pB.x) + abs(pA.y - pB.y) + abs(pA.z - pB.z) <0.001 ) return true;
	else return false;
}

int FramePointsConstructor::getNumberOfPoints()
{
		return _lengthPointArray;
}

void FramePointsConstructor::getLinearArrayFramePoints(AcArray<AcGePoint3d>&  linArrayFrame, AcArray<int>& linArrayFrameLengths)
{
	int i = 0;
	int j;
	bool next;
	//acutPrintf(_T("This is the list of the frame points%d\n"), _lengthPointArray);
	//acutPrintf(_T("Here 000 %d \n"), _lengthPointArray);
	linArrayFrame.append(_pointArray[0]);
	linArrayFrameLengths.append(_pointArray[0].length());
	//acutPrintf(_T("Here 000 %d \n"), _pointArray->length());

	std::vector<int> marksV = std::vector<int>(_lengthPointArray, 0);
	marksV[0] = 1;
	std::vector<int>::iterator it;
	//_pointArray[0].removeFirst();
	//_pointArray[0].removeLast();

	//acutPrintf(_T("Here 000 %d \n"), _pointArray->length());

	while (i < _lengthPointArray-1)
	{
		//acutPrintf(_T("The number of prcessed:%d, %d\n"), i, marksV.size());
		
		//for (it = marksV.begin(); it!=marksV.end(); it++) acutPrintf(_T("%d"), *it);

		next = true;
		j = 0;
		//acutPrintf(_T("Here 0\n"));
		while ((j < _lengthPointArray) && (next))
		{
			//acutPrintf(_T("The number of point:%d, %f, %f, %f\n"), j, _pointArray[j].first().x, _pointArray[j].first().y, _pointArray[j].first().z);
			//acutPrintf(_T("The number of point:%d, %f, %f, %f\n"), j, _pointArray[j].last().x, _pointArray[j].last().y, _pointArray[j].last().z);
		
			//acutPrintf(_T("The value of j: %d\n"), j);
			if  ((isEqualPoint(_pointArray[j].first(), linArrayFrame.last())) && (marksV[j] == 0))
			{

				//_pointArray[j].removeFirst();
				linArrayFrame.append(_pointArray[j]);
				next = false;
				linArrayFrameLengths.append(_pointArray[j].length());
				marksV[j] = 1;
				//_pointArray[j].removeFirst();
				//_pointArray[j].removeLast();
				//acutPrintf(_T("Here 1\n"));
			}
			else if ((isEqualPoint(_pointArray[j].last(), linArrayFrame.last())) && (marksV[j] == 0))
			{
				//_pointArray[j].removeLast();
				linArrayFrame.append(_pointArray[j].reverse());

				next = false;
				linArrayFrameLengths.append(_pointArray[j].length());
				marksV[j] = 1;
				//_pointArray[j].removeFirst();
				//_pointArray[j].removeLast();
				//acutPrintf(_T("Here 2\n"));
			}
			else
			{	
				//acutPrintf(_T("The number of point:%d, %f, %f, %f\n"), j, linArrayFrame.last().x, linArrayFrame.last().y, linArrayFrame.last().z);
				//acutPrintf(_T("\n The point i = %d doesnot match point j = %d , marked: %d are equal: %d\n"), i, j, marksV[j], isEqualPoint(_pointArray[j].last(), linArrayFrame.last()));
			}
			//acutPrintf(_T("Here 4\n"));
			j++;
		}
		//acutPrintf(_T("Here 3\n"));
		i++;
		//for (it = marksV.begin(); it!=marksV.end(); it++) acutPrintf(_T("%d"), *it);

	}


	//while (i < _lengthPointArray)
	//{
	//	linArrayFrameLengths.append(_pointArray[i].length());
	//	//TODO: Consistency assumed.
	//	
	//	int j = 0;
	//	if (i == 0)
	//	{
	//		while (j < _pointArray[i].length())
	//		{
	//			/*acutPrintf(_T("Printing the data of the point i: %d , j: %d ... \n"), i, j);
	//			*/acutPrintf(_T("Printing the data of the point x: %f , y: %f z: %f ... \n"), _pointArray[i][j].x, _pointArray[i][j].y, _pointArray[i][j].z);
	//			linArrayFrame.append(_pointArray[i][j]);
	//			j++;
	//		}
	//	}
	//	else if (isEqualPoint(linArrayFrame.last(), _pointArray[i][j]))
	//	{

	//		/*acutPrintf(_T("Printing the data of first the point i: %d , j: %d ... \n"), i, j);
	//		acutPrintf(_T("Printing the data of first the point x: %f , y: %f z: %f ... \n"), _pointArray[i][j].x, _pointArray[i][j].y, _pointArray[i][j].z);
	//		acutPrintf(_T("Printing the data of second the point i: %d , j: %d ... \n"), i, j);
	//		acutPrintf(_T("Printing the data of second the point x: %f , y: %f z: %f ... \n"), linArrayFrame.last().x, linArrayFrame.last().y, linArrayFrame.last().z);
	//		*/
	//		
	//		j++;
	//		/*acutPrintf(_T("The vertices are equal, the j is now: %d\n"), j);
	//		*/while (j < _pointArray[i].length())
	//		{
	//			/*acutPrintf(_T("Printing the data of the point i: %d , j: %d ... \n"), i, j);
	//			*/acutPrintf(_T("Printing the data of the point x: %f , y: %f z: %f ... \n"), _pointArray[i][j].x, _pointArray[i][j].y, _pointArray[i][j].z);
	//			linArrayFrame.append(_pointArray[i][j]);
	//			j++;
	//		}
	//	}
	//	else
	//	{
	//		/*acutPrintf(_T("Printing the data of first the point i: %d , j: %d ... \n"), i, j);
	//		acutPrintf(_T("Printing the data of first the point x: %f , y: %f z: %f ... \n"), _pointArray[i][j].x, _pointArray[i][j].y, _pointArray[i][j].z);
	//		acutPrintf(_T("Printing the data of second the point i: %d , j: %d ... \n"), i, j);
	//		acutPrintf(_T("Printing the data of second the point x: %f , y: %f z: %f ... \n"), linArrayFrame.last().x, linArrayFrame.last().y, linArrayFrame.last().z);
	//		
	//		acutPrintf(_T("The vertices are not equal"));
	//		*/j++;
	//		while (j < _pointArray[i].length())
	//		{
	//			/*acutPrintf(_T("Printing the data of the point i: %d , j: %d ... \n"), i, j);
	//			*/acutPrintf(_T("Printing the data of the point x: %f , y: %f z: %f ... \n"), _pointArray[i][j].x, _pointArray[i][j].y, _pointArray[i][j].z);
	//			linArrayFrame.append(_pointArray[i][_pointArray[i].length()- j - 1]);
	//			j++;
	//		}

	//	}
	//	i++;
	//}
	//closing the loop
	linArrayFrame.remove(linArrayFrame.last());

	/*for (i = 0; i<linArrayFrame.length(); i++)
	{
		acutPrintf(_T("Printing the data of point: %f , y: %f z: %f ... \n"), linArrayFrame[i].x, linArrayFrame[i].y, linArrayFrame[i].z);
	}
	acutPrintf(_T("The length of the contour: %d\n"), linArrayFrame.length());*/
}


FramePointsConstructor::FramePointsConstructor()
{
	acutPrintf(_T("Constructor of the FramePointsConstructor called... \n"));
	_lengthPointArray = 0;
	_pointArray = NULL;
}

FramePointsConstructor::FramePointsConstructor(AcDbObjectIdArray* selSetIds)
{
	acutPrintf(_T("Constructor of the FramePointsConstructor called... \n"));
	_obArrayId = selSetIds;
	_lengthPointArray = 0;
	_pointArray = NULL;
}

FramePointsConstructor::~FramePointsConstructor()
{
	acutPrintf(_T("Destructor of the FramePointsConstructor called... \n"));
	if (_pointArray) delete [] _pointArray;
	
}

void FramePointsConstructor::setSetIds(AcDbObjectIdArray* selSetIds)
{
	_obArrayId = selSetIds;
}


void FramePointsConstructor::getConstructedPointsAsArray()
{
	
}


void FramePointsConstructor::printConstructedPoints()
{
	int i = 0;

	while (i < _lengthPointArray)
	{
		int j = 0;
		while (j < _pointArray[i].length())
		{
			acutPrintf(_T("Printing the data of the point i: %d , j: %d ... \n"), i, j);
			acutPrintf(_T("Printing the data of the point x: %f , y: %f z: %f ... \n"), _pointArray[i][j].x, _pointArray[i][j].y, _pointArray[i][j].z);
			j++;
		}

		i++;
	}

}

Acad::ErrorStatus FramePointsConstructor::constructFramePoints(int granularity)
{
	
	_pointArray = new AcArray<AcGePoint3d>[_obArrayId->length()];
	

	LineFrameBuilder * _lineBuilder = new LineFrameBuilder();
	PLine2DFrameBuilder * _pline2dBuilder = new PLine2DFrameBuilder();
	PLine3DFrameBuilder * _pline3dBuilder = new PLine3DFrameBuilder();
	PLineFrameBuilder * _plineBuilder = new PLineFrameBuilder();
	SplineFrameBuilder * _splineBuilder = new SplineFrameBuilder();
	ArcFrameBuilder * _arcBuilder = new ArcFrameBuilder();
	while (_obArrayId->isEmpty()!=Adesk::kTrue)
	{
		acutPrintf(_T("Accessing the object... \n"));

		AcDbObjectPointer<AcDbEntity> pEnt(_obArrayId->first(), AcDb::kForRead);
		 
		if (pEnt.openStatus() != Acad::eOk)
		{
			acutPrintf(_T("The object was not properly openned ... \n"));
			return Acad::eObjectIsReferenced;
		}

		
		acutPrintf(_T("Registering a corresponding frame points builder... \n"));
		
		

		if(pEnt->isA() == AcDbLine::desc())
        {
			
			
			AcDbLine *pLine = AcDbLine::cast(pEnt);
			if(pLine)
			{
				_lengthPointArray++;
				setBuilder(_lineBuilder);
			
			}
        }
		else if(pEnt->isA() == AcDb2dPolyline::desc())
        {
			
			
			AcDb2dPolyline *p2dPLine = AcDb2dPolyline::cast(pEnt);
			if(p2dPLine)
			{
				_lengthPointArray++;
				setBuilder(_pline2dBuilder);
			
			}
        }
		else if(pEnt->isA() == AcDb3dPolyline::desc())
        {
			
			
			AcDb3dPolyline *p3dPLine = AcDb3dPolyline::cast(pEnt);
			if(p3dPLine)
			{
				_lengthPointArray++;
				setBuilder(_pline3dBuilder);
			
			}
        }
		else if (pEnt->isA() == AcDbPolyline::desc())
        {
			
			
			AcDbPolyline *pPLine = AcDbPolyline::cast(pEnt);
			if(pPLine)
			{
				_lengthPointArray++;
				setBuilder(_plineBuilder);
			
			} 
		}
		else if (pEnt->isA() == AcDbSpline::desc())
        {
			
			
			AcDbSpline *pSpline = AcDbSpline::cast(pEnt);
			if(pSpline)
			{
				_lengthPointArray++;
				setBuilder(_splineBuilder);
			
			} 
		}
		else if (pEnt->isA() == AcDbSpline::desc())
        {
			
			
			AcDbArc *pArc = AcDbArc::cast(pEnt);
			if(pArc)
			{
				_lengthPointArray++;
				setBuilder(_arcBuilder);
			
			} 
		}
		else break;
		
			
		_builder->buildFramePoints(_pointArray[_lengthPointArray-1], pEnt, granularity);
		_obArrayId->remove(_obArrayId->first());
		pEnt->close();
		
		//pEnt->release();
		
	}
	
	delete _lineBuilder;
	return Acad::eOk;
}


void FramePointsConstructor::getFramePoints(AcArray<AcGePoint3d> * _arrayPoints)
{
	_builder->getFramePoints(_arrayPoints);
}

void FramePointsConstructor::setBuilder(FramePointsBuilder *b)
{
	_builder = b;
}
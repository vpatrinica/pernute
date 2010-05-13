#include "InteriorPointsConstructor.h"


InteriorPointsConstructor::InteriorPointsConstructor()
{
	acutPrintf(_T("Constructor of the FramePointsConstructor called... \n"));
	
	_interiorArray = NULL;
	_interiorDisplacementArray = NULL;
	_contourArray = NULL;
}


InteriorPointsConstructor::~InteriorPointsConstructor()
{
	acutPrintf(_T("Destructor of the InteriorPointsConstructor called... \n"));
	//if (_interiorArray) delete [] _interiorArray;
	//if (_interiorDisplacementArray) delete [] _interiorDisplacementArray;
	acutPrintf(_T("Destructor of the InteriorPointsConstructor finished... \n"));
	
}

static void AddEntityToDataBase(AcDbEntity *pEnt) 
  {
    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    AcDbBlockTableRecordPointer pBTR(pDb->currentSpaceId(), AcDb::kForWrite); 
    if (pEnt && Acad::eOk == pBTR.openStatus())
    {
      pBTR->appendAcDbEntity(pEnt);
      pEnt->close();
    }
  }



void InteriorPointsConstructor::setContour(AcArray<AcGePoint3d>* cntArray)
{
	_contourArray = cntArray;
}

void InteriorPointsConstructor::constructInteriorPoints()
{
	acutPrintf(_T("Called the constructInteriorPoints().."));
	if ((_contourArray->length() /2)*2 != _contourArray->length())
		_contourArray->removeLast();
	int n = _contourArray->length()/2;

	_interiorArray = new AcArray<AcGePoint3d>[n+1];
	_interiorArray[0].append(_contourArray->first());
	_interiorArray[n].append(_contourArray->at(n));
	int j, iIndex;
	for (int i = 1; i<n; i++)
	{
		if (i <= n/2) iIndex = i;
		else iIndex = n - i;
		//acutPrintf(_T("The number n is: %d, %d"), n, _contourArray->length());
		for (j = 0; j <= iIndex; j++)
		{
			AcGePoint3d * newPoint = new AcGePoint3d;
			newPoint->x = (j/(iIndex*1.0))*((n-i)*1.0/n * _contourArray->first().x + i*1.0/n *_contourArray->at(n).x ) + (iIndex-j)/(iIndex*1.0)*(_contourArray->at(i).x);
			newPoint->y = (j/(iIndex*1.0))*((n-i)*1.0/n * _contourArray->first().y + i*1.0/n * _contourArray->at(n).y ) + (iIndex-j)/(iIndex*1.0)*(_contourArray->at(i).y);
			newPoint->z = (j/(iIndex*1.0))*((n-i)*1.0/n * _contourArray->first().z + i*1.0/n * _contourArray->at(n).z ) + (iIndex-j)/(iIndex*1.0)*(_contourArray->at(i).z);
			_interiorArray[i].append(*newPoint);
		}
		for (j = (iIndex-1); j >= 0; j--)
		{
			AcGePoint3d * newPoint = new AcGePoint3d;
			newPoint->x = (j/(iIndex*1.0))*((n-i)*1.0/n * _contourArray->first().x + i*1.0/n * _contourArray->at(n).x ) + (iIndex-j)/(iIndex*1.0)*(_contourArray->at(2*n-i).x);
			newPoint->y = (j/(iIndex*1.0))*((n-i)*1.0/n * _contourArray->first().y + i*1.0/n * _contourArray->at(n).y ) + (iIndex-j)/(iIndex*1.0)*(_contourArray->at(2*n-i).y);
			newPoint->z = (j/(iIndex*1.0))*((n-i)*1.0/n * _contourArray->first().z + i*1.0/n * _contourArray->at(n).z ) + (iIndex-j)/(iIndex*1.0)*(_contourArray->at(2*n-i).z);
			_interiorArray[i].append(*newPoint);
		}
	}
	acutPrintf(_T("Finished the constructInteriorPoints().."));

}


void InteriorPointsConstructor::printInteriorPoints(int color, bool flag)
{
	int i = 0;

	

	while (i < _contourArray->length()/2 + 1)
	{
		int j = 0;
		
		
		AcGePoint3dArray ptArr;

		if ((flag)|| (_interiorArray[i].length() <2)) ptArr.setLogicalLength(_interiorArray[i].length());
		else  ptArr.setLogicalLength(_interiorArray[i].length()-1);
		
		if ((flag)|| (_interiorArray[i].length() < 2))
		while (j < _interiorArray[i].length())
		{
			
			ptArr[j].set(_interiorArray[i][j].x, _interiorArray[i][j].y, _interiorArray[i][j].z);
			

		
			j++;
		}
		else
		{
				while (j < _interiorArray[i].length()-2)
				{
			
						ptArr[j].set(_interiorArray[i][j].x, _interiorArray[i][j].y, _interiorArray[i][j].z);
						if (sqrt(_interiorArray[i][j].x*_interiorArray[i][j].x + _interiorArray[i][j].y*_interiorArray[i][j].y + _interiorArray[i][j].z*_interiorArray[i][j].z) < 100)
							acutPrintf(_T("The shitty: %d, %d\n"), i, j);

		
				j++;
				}
				j++;
				ptArr[j].set(_interiorArray[i][j].x, _interiorArray[i][j].y, _interiorArray[i][j].z);
			
		}
		//if (i == 10){
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

		//pNewPline->setLayer(_T("0"));
		//pNewPline->setClosed(Adesk::kFalse);
		pNewPline->close();
		//}
		//delete pNewPline;
		
		i++;
	}
}

void InteriorPointsConstructor::printFirstInteriorPoints(int color, bool flag)
{
	int i = 1;
	int j = 0;
		
		
		AcGePoint3dArray ptArr;
		ptArr.setLogicalLength(_interiorArray[i].length()+1);
		
		
		while (j < _interiorArray[i].length())
		{
			
			ptArr[j].set(_interiorArray[i][j].x, _interiorArray[i][j].y, _interiorArray[i][j].z);
			
			
		
			j++;
		}
		ptArr[j].set(_interiorArray[0][0].x, _interiorArray[0][0].y, _interiorArray[0][0].z);
			

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

		//pNewPline->setLayer(_T("0"));
		//pNewPline->setClosed(Adesk::kFalse);
		pNewPline->close();
		//}
		//delete pNewPline;
		
	
	
}

void InteriorPointsConstructor::computeNumberVertices()
{
	_numVertices = 0;
	for (int i = 0; i < _contourArray->length()/2+1; i++)
	{
		for (int j = 0; j < _interiorArray[i].length(); j++)
		{
			_numVertices++;
		}
	}
}

void InteriorPointsConstructor::ForceDirectedAlgorithm()
{
	//Clone the data structure, and initialize it to 0;
	int n = _contourArray->length()/2;
	computeNumberVertices();
	_interiorDisplacementArray = new AcArray<AcGePoint3d>[n+1];
	int i, j, k, l, vIter;
	AcGePoint3d delta;
	//int vIter;
	double Volume = (maxX() - minX())*(maxY() - minY())*(maxZ() - minZ());

	double kappa = sqrt(Volume/_numVertices);
	setKappa(kappa);
				vector<pair<int, int>> v;
		vector<pair<int, int>>::iterator it;
		
	for (vIter = 0; vIter<5; vIter++)
	{

		//Calculate repulsive forces

		for (i = 0; i < _contourArray->length()/2+1; i++)
		{
			for (j = 0; j < _interiorArray[i].length(); j++)
			{
				if (vIter == 0)
				{
					
					AcGePoint3d * newPoint = new AcGePoint3d;
					newPoint->x = 0.0;
					newPoint->y = 0.0;
					newPoint->z = 0.0;
					_interiorDisplacementArray[i].append(*newPoint);
				}
				else
				{
					_interiorDisplacementArray[i][j].x = 0.0;
					_interiorDisplacementArray[i][j].y = 0.0;
					_interiorDisplacementArray[i][j].z = 0.0;
				}
				
				for (k = 0; k<_contourArray->length()/2+1; k++)
				{
					for (l = 0; l < _interiorArray[k].length(); l++)
					{
						
							if ((k!=i) && (l!=j) )
							{
								delta.x = _interiorArray[i][j].x - _interiorArray[k][l].x;
								delta.y = _interiorArray[i][j].y - _interiorArray[k][l].y;
								delta.z = _interiorArray[i][j].z - _interiorArray[k][l].z;
								if(delta.x != 0) _interiorDisplacementArray[i][j].x = _interiorDisplacementArray[i][j].x + ((delta.x)/abs(delta.x))* F_attractive(delta.x);
								if(delta.y != 0)_interiorDisplacementArray[i][j].y = _interiorDisplacementArray[i][j].y + ((delta.y)/abs(delta.y))* F_attractive(delta.y);
								if(delta.z != 0)_interiorDisplacementArray[i][j].z = _interiorDisplacementArray[i][j].z + ((delta.z)/abs(delta.z))* F_attractive(delta.z);
							}
						
					}
				}
			
			}
		}
	

			

		//acutPrintf(_T("Proceeding...attractive ...\n"));
		//Calculate attractive forces;
		
	
		for (i = 0; i < _contourArray->length()/2; i++)
		{	
			for (j = 0; j < _interiorArray[i].length(); j++)
			{
				if ((i != 0) && (j!=_interiorArray[i].length() - 1) && (j!=0) && (i!=_contourArray->length()/2))
				{	
							arrayNeighbour(v, i, j);
							for (it = v.begin(); it!=v.end(); it++)
							{

								delta.x = _interiorArray[(*it).first][(*it).second].x - _interiorArray[i][j].x;
								delta.y = _interiorArray[(*it).first][(*it).second].y - _interiorArray[i][j].y;
								delta.z = _interiorArray[(*it).first][(*it).second].z - _interiorArray[i][j].z;
								_interiorDisplacementArray[i][j].x = _interiorDisplacementArray[i][j].x + F_attractive(delta.x);
								_interiorDisplacementArray[i][j].y = _interiorDisplacementArray[i][j].y + F_attractive(delta.y);
								_interiorDisplacementArray[i][j].z = _interiorDisplacementArray[i][j].z + F_attractive(delta.z);
							}
							
						
				}		
							
			}
		}
		//Limit the fluctuations first step:
		for (i = 0; i < _contourArray->length()/2+1; i++)
		{
			for (j = 0; j < _interiorArray[i].length(); j++)
			{
				
					_interiorArray[i][j].x = _interiorArray[i][j].x + _interiorDisplacementArray[i][j].x;
					_interiorArray[i][j].y = _interiorArray[i][j].y + _interiorDisplacementArray[i][j].y;
					_interiorArray[i][j].z = _interiorArray[i][j].z + _interiorDisplacementArray[i][j].z;
			}
		}	
	}
}
double InteriorPointsConstructor::distanceNeighbours(int i1, int j1, int i2, int j2)
{
	return sqrt((_interiorArray[i1][j1].x - _interiorArray[i2][j2].x)*(_interiorArray[i1][j1].x - _interiorArray[i2][j2].x) + (_interiorArray[i1][j1].y - _interiorArray[i2][j2].y)*(_interiorArray[i1][j1].y - _interiorArray[i2][j2].y) + (_interiorArray[i1][j1].z - _interiorArray[i2][j2].z)*(_interiorArray[i1][j1].z - _interiorArray[i2][j2].z));
}




bool sort_pred(const my_pair& left, const my_pair& right)
{
	return left.second < right.second;
}


void InteriorPointsConstructor::findNeighboursAtDist(int numNeighbours, double distTO, vector<pair<int,int>>& vNeighbours, int originI, int originJ)
{
	int len = _contourArray->length();
	double dist;
	vector<pair<pair<int, int>, double>> v;
	vNeighbours.erase(vNeighbours.begin(), vNeighbours.end());
	
	for (int i = 0; i < len/2 + 1; i++)
	{
		for (int j = 0; j < _interiorArray[i].length(); j++)
			if (i + j - originI - originJ < numNeighbours)
			{
					dist = distanceNeighbours(i, j, originI, originJ);
					v.push_back(my_pair(make_pair(i, j), abs(dist - distTO)));
			}
	}
	sort(v.begin(), v.end(), sort_pred);
	int k = 0;
	vector<pair<pair<int, int>, double>>::iterator it = v.begin();
	while ((k < numNeighbours) && it != v.end())
	{
		vNeighbours.push_back((*it).first);
		it++;
		k++;
	}
}

void InteriorPointsConstructor::arrayNeighbour(vector<pair<int,int>>& neighbours, int i, int j)
{
	
	neighbours.erase(neighbours.begin(), neighbours.end());
	int len = _contourArray->length(); 
	if (i == 0)
	{
		neighbours.push_back(make_pair(1, 0));
		neighbours.push_back(make_pair(1, 1));
		neighbours.push_back(make_pair(1, 2));
	}
	else if ((i == len/2) && (i > 1))
	{
		neighbours.push_back(make_pair(len/2 - 1, 0));
		neighbours.push_back(make_pair(len/2 - 1, 1));
		neighbours.push_back(make_pair(len/2 - 1, 2));
	}
	else if ((i == len/2) && (i == 1))
	{
		neighbours.push_back(make_pair(0, 0));
	}
	else if ((i!=0) && (i!= len/2) && (i < len/4) && (j == 0))
	{
		neighbours.push_back(make_pair(i - 1, 0));
		neighbours.push_back(make_pair(i + 1, 0));
		neighbours.push_back(make_pair(i, 1));
		neighbours.push_back(make_pair(i + 1, 1));
	}
	else if ((i!=0) && (i!= len/2) && (i < len/4) && (j == 2*i) && (j!=0))
	{
		neighbours.push_back(make_pair(i - 1, j - 2));
		neighbours.push_back(make_pair(i + 1, j + 2));
		neighbours.push_back(make_pair(i, j - 1));
		neighbours.push_back(make_pair(i + 1, j + 1));
	}
	else if ((i!=0) && (i!= len/2) && (len/2 - i < len/4) && (j == 0))
	{
		neighbours.push_back(make_pair(i - 1, 0));
		neighbours.push_back(make_pair(i + 1, 0));
		neighbours.push_back(make_pair(i - 1, 1));
		neighbours.push_back(make_pair(i, 1));
	}
	else if ((i!=0) && (i!= len/2) && (len/2 - i < len/4) && (j == 2*(len/2 - i)) && (j!=0))
	{
		neighbours.push_back(make_pair(i - 1, j + 2));
		neighbours.push_back(make_pair(i + 1, j - 2));
		neighbours.push_back(make_pair(i, j - 1));
		neighbours.push_back(make_pair(i, j + 1));
	}
	else if ((i!=0) && (i!= len/2) && ((i == len/4) || (len/2 - i == len/4)) && (j == 0))
	{
		neighbours.push_back(make_pair(i - 1, 0));
		neighbours.push_back(make_pair(i + 1, 0));
		neighbours.push_back(make_pair(i, 1));
		
	}
	else if ((i!=0) && (i!= len/2) && ((i == len/4) || (len/2 - i == len/4)) && (j != 0) && ((j == 2*(len/2 - i))||(j == 2*i)))
	{
		
		neighbours.push_back(make_pair(i, j - 1));
		if ((i*2 == len/2) && (i== len/4))
		{
			neighbours.push_back(make_pair(i - 1, j - 2));
			neighbours.push_back(make_pair(i + 1, j + 2));
		}
		else if ((i*2 != len/2) && (i == len/4))
		{
			neighbours.push_back(make_pair(i - 1, j - 2));
			neighbours.push_back(make_pair(i + 1, j));
		}
		else if ((len/2 - i == len/4) && (i != len/4))
		{
			neighbours.push_back(make_pair(i - 1, j));
			neighbours.push_back(make_pair(i + 1, j - 2));
		}
		
	}
	else if ((j != 0) && (i != 0) && (i != len/2) && (j != 2*i) && (j != 2*(len/2 - i)) )
	{
		neighbours.push_back(make_pair(i, j - 1));
		neighbours.push_back(make_pair(i, j + 1));
		if (i < len/4)
		{
			neighbours.push_back(make_pair(i - 1, j - 1));
			neighbours.push_back(make_pair(i + 1, j + 1));
		}
		else if (len/2 - i < len/4)
		{
			neighbours.push_back(make_pair(i - 1, j + 1));
			neighbours.push_back(make_pair(i + 1, j - 1));		
		}
		else if ((i == len/4) && (len/2 - i == len/4))
		{
			neighbours.push_back(make_pair(i - 1, j - 1));
			neighbours.push_back(make_pair(i + 1, j - 1));
		}
		else if ((i == len/4) && (len/2 - i != len/4))
		{
			neighbours.push_back(make_pair(i - 1, j - 1));
			neighbours.push_back(make_pair(i + 1, j));
		}
		else if ((len/2 - i == len/4) && (2*i != len/2))
		{
			neighbours.push_back(make_pair(i - 1, j));
			neighbours.push_back(make_pair(i + 1, j - 1));
		}
	}
}

void InteriorPointsConstructor::drawNet(int netGranularity)
{
	int n = _contourArray->length()/2;
	

}
void InteriorPointsConstructor::ForceDirectedAlgorithm2()
{
	//Clone the data structure, and initialize it to 0;
	int n = _contourArray->length()/2;
	computeNumberVertices();
	_interiorDisplacementArray = new AcArray<AcGePoint3d>[n+1];
	int i,j, vIter;
	//int i,j,vIter;
	AcGePoint3d delta;
	//int vIter;
	double Volume = (maxX() - minX())*(maxY() - minY())*(maxZ() - minZ());
	double surface = (maxX() - minX())*(maxY() - minY());
	double kappa;
	if (Volume)
		kappa = sqrt(Volume/_numVertices);
	else kappa = sqrt(surface/_numVertices);
	setKappa(kappa);
	//acutPrintf(_T("Proceeding...\n"));
		vector<pair<int, int>> v;
		vector<pair<int, int>>::iterator it;
		
	for (vIter = 0; vIter<2; vIter++)
	{

		//Calculate repulsive forces

		for (i = 0; i < _contourArray->length()/2+1; i++)
		{
			for (j = 0; j < _interiorArray[i].length(); j++)
			{
				if (vIter == 0)
				{
					
					AcGePoint3d * newPoint = new AcGePoint3d;
					newPoint->x = 0.0;
					newPoint->y = 0.0;
					newPoint->z = 0.0;
					_interiorDisplacementArray[i].append(*newPoint);
				}
				else
				{
					_interiorDisplacementArray[i][j].x = 0.0;
					_interiorDisplacementArray[i][j].y = 0.0;
					_interiorDisplacementArray[i][j].z = 0.0;
				}

			
			}
		}
		//acutPrintf(_T("Proceeding...attractive ...\n"));
		//Calculate attractive forces;
		
	
		for (i = 0; i < _contourArray->length()/2; i++)
		{	
			for (j = 0; j < _interiorArray[i].length(); j++)
			{
				if ((i != 0) && (j!=_interiorArray[i].length() - 1) && (j!=0) && (i!=_contourArray->length()/2))
				{	
							arrayNeighbour(v, i, j);
							for (it = v.begin(); it!=v.end(); it++)
							{

								delta.x = _interiorArray[(*it).first][(*it).second].x - _interiorArray[i][j].x;
								delta.y = _interiorArray[(*it).first][(*it).second].y - _interiorArray[i][j].y;
								delta.z = _interiorArray[(*it).first][(*it).second].z - _interiorArray[i][j].z;
								_interiorDisplacementArray[i][j].x = _interiorDisplacementArray[i][j].x + F_attractive(delta.x);
								_interiorDisplacementArray[i][j].y = _interiorDisplacementArray[i][j].y + F_attractive(delta.y);
								_interiorDisplacementArray[i][j].z = _interiorDisplacementArray[i][j].z + F_attractive(delta.z);
							}
							
						
				}		
							
			}
		}
		//Limit the fluctuations first step:
		for (i = 0; i < _contourArray->length()/2+1; i++)
		{
			for (j = 0; j < _interiorArray[i].length(); j++)
			{
				
					_interiorArray[i][j].x = _interiorArray[i][j].x + _interiorDisplacementArray[i][j].x;
					_interiorArray[i][j].y = _interiorArray[i][j].y + _interiorDisplacementArray[i][j].y;
					_interiorArray[i][j].z = _interiorArray[i][j].z + _interiorDisplacementArray[i][j].z;
			}
		}

		

	}
	acutPrintf(_T("\nVolume: %f, numPoints: %d, kappa: %f\n"), Volume, _numVertices, _kappa);
	
}

double InteriorPointsConstructor::maxX()
{
	double maxX = _interiorArray[0][0].x;
	
	for (int i = 0; i < _contourArray->length()/2+1; i++)
	{
		for (int j = 0; j < _interiorArray[i].length(); j++)
		{
			if (maxX<_interiorArray[i][j].x) maxX = _interiorArray[i][j].x;
		}
	}
	return maxX;
}
void InteriorPointsConstructor::makePolyhedron()
{
	ConvexHull* C = new ConvexHull(_contourArray);
}
double InteriorPointsConstructor::minX()
{
	double minX = _interiorArray[0][0].x;
	
	for (int i = 0; i < _contourArray->length()/2+1; i++)
	{
		for (int j = 0; j < _interiorArray[i].length(); j++)
		{
			if (minX>_interiorArray[i][j].x) minX = _interiorArray[i][j].x;
		}
	}
	return minX;
}

double InteriorPointsConstructor::maxY()
{
	double maxY = _interiorArray[0][0].y;
	
	for (int i = 0; i < _contourArray->length()/2+1; i++)
	{
		for (int j = 0; j < _interiorArray[i].length(); j++)
		{
			if (maxY<_interiorArray[i][j].y) maxY = _interiorArray[i][j].y;
		}
	}
	return maxY;
}

double InteriorPointsConstructor::minY()
{
	double minY = _interiorArray[0][0].y;
	
	for (int i = 0; i < _contourArray->length()/2+1; i++)
	{
		for (int j = 0; j < _interiorArray[i].length(); j++)
		{
			if (minY>_interiorArray[i][j].y) minY = _interiorArray[i][j].y;
		}
	}
	return minY;
}
double InteriorPointsConstructor::maxZ()
{
	double maxZ = _interiorArray[0][0].z;
	
	for (int i = 0; i < _contourArray->length()/2+1; i++)
	{
		for (int j = 0; j < _interiorArray[i].length(); j++)
		{
			if (maxZ<_interiorArray[i][j].z) maxZ = _interiorArray[i][j].z;
		}
	}
	return maxZ;
}

double InteriorPointsConstructor::minZ()
{
	double minZ = _interiorArray[0][0].z;
	
	for (int i = 0; i < _contourArray->length()/2+1; i++)
	{
		for (int j = 0; j < _interiorArray[i].length(); j++)
		{
			if (minZ>_interiorArray[i][j].z) minZ = _interiorArray[i][j].z;
		}

	}
	return minZ;
}
double InteriorPointsConstructor::F_attractive(double x)
{
	if (_kappa>0.001) return 0.01*(x-0.05)*(x-0.05)/_kappa; else return 0;
	//if (x<0.1) return 0.000001*_kappa*_kappa/x; else return 0;
}

double InteriorPointsConstructor::F_repulsive(double x)
{
	if (x!=0) return 10*_kappa*_kappa/x; else return 0;
}
void InteriorPointsConstructor::setKappa(double k)
{
	_kappa = k;
}
void InteriorPointsConstructor::PrintContourPoints()
{

int i = 0;
int j;
	while (i < _contourArray->length()/2 + 1)
	{
		j=0;	
		acutPrintf(_T("Coordinates: length: %d i: %d, j: %d, %f, %f %f\n"),_interiorArray[i].length(), i, j, _interiorArray[i][j].x,  _interiorArray[i][j].y, _interiorArray[i][j].z);    
		j = _interiorArray[i].length()-1;
		acutPrintf(_T("Coordinates: i: %d, j: %d, %f, %f %f\n"), i, j, _interiorArray[i][j].x,  _interiorArray[i][j].y, _interiorArray[i][j].z);    
		i++;
	}
	
}
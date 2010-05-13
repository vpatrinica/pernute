#include "InputReader.h"



InputReader::InputReader(void)
{
	acutPrintf(_T("The constructor of InputReader was called ...\n"));
	inputSelectionSet[0] = 0L;
    inputSelectionSet[1] = 0L;
}


InputReader::~InputReader()
{
	acutPrintf(_T("The destructor of InputReader called freeing the memory of the inputSelectionSet...\n"));
	acedSSFree(inputSelectionSet);
}

bool InputReader::isNull()
{
  return inputSelectionSet[0] == 0L && inputSelectionSet[1] == 0L;
}

/*

*/
Acad::ErrorStatus InputReader::getAsArray( AcDbObjectIdArray &setIds )
{
  if(this->isNull())
    return Acad::eNullPtr;

  long sslength;
  ads_name ent;


  acedSSLength(inputSelectionSet, &sslength);
  for (long i = 0; i < sslength; i++)
  {
    AcDbObjectId oId;
    acedSSName(inputSelectionSet, i, ent);
	if(acdbGetObjectId(oId, ent) == Acad::eOk)
      setIds.append(oId);
    else
      return Acad::eNullObjectId;
  }
  return Acad::eOk;
}

ads_name& InputReader::getInputSelectionSet()
{
	acutPrintf(_T("The getInputSelectionSet() of InputReader called ...\n"));
	return inputSelectionSet;
}

Acad::PromptStatus InputReader::readInputSelectionSet(const resbuf *pFilter)
{
	acutPrintf(_T("The readInputSelectionSet() of InputReader called the selection proceeds ...\n"));
	
	acedSSFree(inputSelectionSet);
  
	acutPrintf(_T("The acedSSGet will be called within readInputSelectionSet() ...\n"));

	return (Acad::PromptStatus) acedSSGet(NULL, NULL, NULL, pFilter, inputSelectionSet);
	
}

void InputReader::cleanInputSelectionSet()
{
	acedSSFree(inputSelectionSet);
	inputSelectionSet[0] = 0L;
    inputSelectionSet[1] = 0L;
}


#pragma once
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "aced.h"
#include "dbsymtb.h"
#include "dbapserv.h"
#include "acgi.h"
#include "tchar.h"
#include <list>
#include <stdio.h>
#include <iostream>

#include  <ADSLIB.H>



class InputReader
{
	public:

		InputReader(void);
		~InputReader();
		ads_name& getInputSelectionSet();
		bool isNull();
		Acad::PromptStatus readInputSelectionSet(const resbuf *);	
		void cleanInputSelectionSet();
		Acad::ErrorStatus getAsArray(AcDbObjectIdArray&);

	private:
		
		ads_name inputSelectionSet;
};

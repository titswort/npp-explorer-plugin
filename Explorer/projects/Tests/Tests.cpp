#include "pch.h"
#include "CppUnitTest.h"
#include "Explorer.h"

#include <assert.h>
#include <iostream>

// Context Menu Includes
/*
#include "ExplorerDialog.h"

#include <shellapi.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <dbt.h>

#include "Explorer.h"
#include "ExplorerResource.h"
#include "ContextMenu.h"
#include "NewDlg.h"
#include "NppInterface.h"
#include "ToolTip.h"
#include "resource.h"*/

#include "DragDropImpl.h"
#include <shlobj.h>
#include "ExplorerResource.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		//Tests for Drag and Drop

		TEST_METHOD(CIDDropSourceInit)
		{
			CIDropSource VarA;
		}
		TEST_METHOD(CIDDropSourceDestruct)
		{
			CIDropSource* VarA = new CIDropSource{};
			delete VarA;
			assert(VarA == NULL);
		}
		TEST_METHOD(CIDataObjectInit)
		{
			CIDropSource VarA{};
			CIDataObject VarB(&VarA);
		}

		TEST_METHOD(CIDataObjectDestruct)
		{
			CIDropSource VarA{};
			CIDataObject* VarB = new CIDataObject(&VarA);
			delete VarB;
			assert(VarB == NULL);

		}

		TEST_METHOD(DataObjectAddRefTest)
		{
			CIDropSource VarA{};
			CIDataObject VarB(&VarA);

			STDMETHODIMP_(ULONG) C = VarB.AddRef();
			assert(C != NULL);

		}

		TEST_METHOD(DataObjectReleaseTest)
		{
			CIDropSource VarA{};
			CIDataObject VarB(&VarA);
			STDMETHODIMP_(ULONG) D = VarB.Release();
			assert(D != NULL);
		}
		// Write your unit tests here or in a separate testing file.
		// For separate files, make sure to use the correct namespace, macros and types. 
		// Be sure to _at least_ include CppUnitTest.h.
	private:
		/// <summary>
		/// This text will pop up when you hover over the method name <em>anywhere</em>!
		/// <para>This text appears on the next line</para>
		/// </summary>
		/// <param name="param">This text describes what to pass in to the function</param>
		/// 
		int _documentedMethod(string param)
		{
			cout << "This method has Intellisense-documented code!" << endl;
			return 1;
		}
	};
}

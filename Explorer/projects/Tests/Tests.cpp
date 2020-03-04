#include "pch.h"
#include "CppUnitTest.h"
#include "Explorer.h"
#include "FavesDialog.h"
#include <assert.h>


#include <shlobj.h>

#include "ExplorerResource.h"


#include <dbt.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <shlobj.h>

#include "Explorer.h"
#include "ExplorerDialog.h"
#include "ExplorerResource.h"
#include "NewDlg.h"
#include "ToolTip.h"
#include "resource.h"
#include "NppInterface.h"


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


using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:

		//Tests for Faves Dialog
		TEST_METHOD(FavesInit)
		{
			HINSTANCE hInst{};
			NppData nppData{};
			LPTSTR pCurrentElement{};
			ExProp* prop{};


			FavesDialog dlg;
			dlg.init(hInst, nppData, pCurrentElement, prop); // This just tests if FavesInit intializes properly
		}


		TEST_METHOD(AddToFavsA)
		{

			HINSTANCE hInst{};
			NppData nppData{};
			LPTSTR pCurrentElement{};
			ExProp* prop{};

			FavesDialog dlg;
			dlg.init(hInst, nppData, pCurrentElement, prop);
			dlg.doDialog(true); // StaticDialog.create() fails
			dlg.AddToFavorties(true, pCurrentElement);

		}

		TEST_METHOD(AddToFavsB)
		{

			HINSTANCE hInst{};
			NppData nppData{};
			LPTSTR pCurrentElement{};
			ExProp* prop{};

			FavesDialog dlg;
			dlg.init(hInst, nppData, pCurrentElement, prop);
			dlg.doDialog(true); // StaticDialog.create() fails
			dlg.AddToFavorties(false, pCurrentElement);

		}

		TEST_METHOD(SessionSave)
			{

				HINSTANCE hInst{};
				NppData nppData{};
				LPTSTR pCurrentElement{};
				ExProp* prop{};

				FavesDialog dlg;
				dlg.init(hInst, nppData, pCurrentElement, prop);
				dlg.doDialog(true); // StaticDialog.create() fails
				dlg.SaveSession();
			}


		TEST_METHOD(FavesDestroy)
			{
				HINSTANCE hInst{};
				NppData nppData{};
				LPTSTR pCurrentElement{};
				ExProp* prop{};


				FavesDialog dlg;
				dlg.init(hInst, nppData, pCurrentElement, prop);
				dlg.destroy(); //Allocater<Item Element>	>::size() Fails
			}

		TEST_METHOD(FavesDestructor)
		{
			HINSTANCE hInst{};
			NppData nppData{};
			LPTSTR pCurrentElement{};
			ExProp* prop{};

			
			FavesDialog *dlg = new FavesDialog;
			dlg->init(hInst, nppData, pCurrentElement, prop);
			//dlg.~FavesDialog();
			delete dlg;
			assert(dlg == NULL); //This should cause a failurre as dlg is deallocated
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

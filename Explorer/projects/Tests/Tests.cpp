#include "pch.h"
#include "CppUnitTest.h"
#include "Explorer.h"

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

#include <ShlObj.h>
#include "ContextMenu.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:

		TEST_METHOD(BoilerplateTest)
		{
			cout << "Hello world! This is Group 36's test framework!" << endl;
			int foo = _documentedMethod("some value");
			Assert::IsTrue(2 + 2 == 4);
		}

		TEST_METHOD(SettingsLoadTest)
		{
			//loadSettings();
		}

		TEST_METHOD(ContextMenuInit)
		{
			ContextMenu cm;
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

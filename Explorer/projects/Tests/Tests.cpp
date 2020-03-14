#include "pch.h"
#include "CppUnitTest.h"
#include "Explorer.h"

#include <iostream> // For printing to console
#include <Windows.h>

/* WSTRING stuff */
#include <locale>
#include <codecvt>
#include <string>

// Context Menu Includes

#include <ShlObj.h>
#include "ContextMenu.h"
#include <atlcomcli.h>

// Directory Index Includes
#include "DirectoryIndex.h"

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

		/* Context Menu Unit Tests (Eric Prather) */

		//Basic initalization test.
		TEST_METHOD(ContextMenuInit)
		{
			ContextMenu cm;

			HMENU h = cm.GetMenu();

			// Expected output: Some data value was initalized by the constructor.
			Assert::IsNotNull(h);
		}

		// Sets a single item in the context menu
		// No expected output because the class being tested does not expose its
		// items without adding additional behavior which we don't currently
		// want to test.
		TEST_METHOD(ContextMenuOneObject)
		{
			ContextMenu cm;

			string basic = "hello world";
			// wstring = "wide" string.
			wstring* item = _widenString(basic);
			
			cm.SetObjects(*item);
			
			delete item;
		}
		
		// Creates a context menu with several items.
		TEST_METHOD(ContextMenuManyObject)
		{
			ContextMenu cm;
			string toAdd[3];
			vector<wstring> contextMenuList;
			int i;

			toAdd[0] = "Hello world!";
			toAdd[1] = "I like foo!";
			toAdd[2] = "I like bar!";


			for (i = 0; i < 3; i++)
			{
				wstring* whatToAdd = _widenString(toAdd[i]);
				contextMenuList.push_back(*whatToAdd);
				delete whatToAdd;
			}

			// This is the load bearing line of the unit test.
			cm.SetObjects(contextMenuList);

		}

		// Note: There is no unit test for adding 0 items to the list
		// because there is no function to support it.

		TEST_METHOD(ContextMenuBlankArgShow)
		{
			// The next 5 lines of code are tested by a separate
			// unit test, so the failure should not occur here.
			ContextMenu cm;
			string basic = "hello world";
			wstring* item = _widenString(basic);
			cm.SetObjects(*item);
			delete item;

			// New items
			HINSTANCE inst{};
			HWND wnd1{};
			HWND wnd2{};
			POINT pt{0};
			
			// Figure out what happens
			cm.ShowContextMenu(inst,wnd1,wnd2,pt);
		}

		TEST_METHOD(ContextMenuDetailedArgShow)
		{
			// The next 5 lines of code are tested by a separate
			// unit test, so the failure should not occur here.
			ContextMenu cm;
			string basic = "hello world";
			wstring* item = _widenString(basic);
			cm.SetObjects(*item);
			delete item;			

			// Example implementation in ExplorerDialog.cpp
			// WARNING: HISTANCE should _never_ be used directly in code.
			// So it is not initalized here
			HINSTANCE inst{}; 
			// HWND translates to "handle to a window"
			HWND wnd1 = FindWindow(NULL, NULL); // Find any window
			HWND wnd2 = FindWindow(NULL, NULL);
			POINT pt{ 0 };

			DWORD dwpos = ::GetMessagePos();
			pt.x = GET_X_LPARAM(dwpos);
			pt.y = GET_Y_LPARAM(dwpos);


			cm.ShowContextMenu(inst, wnd1, wnd2, pt);
		}

		/******************************************/
		
		/* Directory Index Unit Tests (Eric Prather) */
		// See also: void QuickOpenDlg::setCurrentPath(const std::filesystem::path& currentPath)

		// Initalize a directory index.
		TEST_METHOD(DIdxInit)
		{
			DirectoryIndex di; // Constructor called
			WCHAR wide_text[MAX_PATH];
			LPWSTR dest = wide_text;
			_writeMyDesktopPath(&dest);
			wstring formattedPath = dest;
			
			di.init(formattedPath);
		}

		// Initalizes AND BUILDS
		TEST_METHOD(DIdxBuild)
		{
			DirectoryIndex di; // Constructor called
			WCHAR wide_text[MAX_PATH];
			LPWSTR dest = wide_text;
			_writeMyDesktopPath(&dest);
			wstring formattedPath = dest;
			di.init(formattedPath);
			// end of setup, begin load

			di.build();
		}

		// Makes sure a directory index built about a certain
		// directory remains in that directory and can identify itself.
		TEST_METHOD(DIdxLoadIntoDir)
		{
			DirectoryIndex di; // Constructor called
			WCHAR wide_text[MAX_PATH];
			LPWSTR dest = wide_text;
			_writeMyDesktopPath(&dest);
			wstring formattedPath = dest;
			di.init(formattedPath);
			di.build();
			// end of setup, begin load

			std::filesystem::path myPath = di.GetCurrentDir();
			Assert::IsTrue((myPath) == formattedPath);
		}

		// Verifies that at least 1 OTHER file or directory
		// were found in this query.
		TEST_METHOD(DIdxRealFile)
		{
			DirectoryIndex di; // Constructor called
			WCHAR wide_text[MAX_PATH];
			LPWSTR dest = wide_text;
			_writeMyDesktopPath(&dest);
			wstring formattedPath = dest;
			di.init(formattedPath);
			di.build();
			// end of setup, begin load

			std::vector<std::filesystem::path> output;
			output = di.GetFileIndex();

			// AT LEAST 2 things are present in My Documents:
			// 1. "."
			// 2. "../"
			Assert::IsTrue(output.size() > (size_t)2);
		}

		// Loops through all of the files found in a given 
		// directory index and make sure the non-existant
		// file "imnotarealfile.lmao" is not within them.
		TEST_METHOD(DIdxFakeFile)
		{
			DirectoryIndex di; // Constructor called
			WCHAR wide_text[MAX_PATH];
			LPWSTR dest = wide_text;
			_writeMyDesktopPath(&dest);
			wstring formattedPath = dest;
			di.init(formattedPath);
			di.build();
			std::vector<std::filesystem::path> output;
			output = di.GetFileIndex();
			// end of setup, begin load

			for each (std::filesystem::path p in output)
			{
				Assert::IsTrue(p.generic_string().find("imnotarealfile.lmao") == string::npos);
			}
		}

		/*********************************************/

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

		/// <summary>Takes a regular string and makes it wide. Free storage.</summary>
		/// <param name="s"> The regular string to convert to a wide string </paramref>
		/// <returns>1-byte-wide ascii to 2-byte-wide tchar equivalents.</returns>
		/// <remarks>
		/// https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
		/// </remarks>
		wstring* _widenString(string s)
		{
			// I couldn't figure out how to use codecvt_utf8 in a timely manner.
			//codecvt_utf8<wchar_t> converter(s.size());
			// converter.
			wstring* newStr = new wstring(s.begin(), s.end());
			return newStr;
		}

		///<summary>Finds the "My Documents" folder.</summary>
		///<param name="dest">Overwriten with file path of My Documents</param>
		void _writeMyDesktopPath(LPWSTR* dest)
		{
			HRESULT result = SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, SHGFP_TYPE_CURRENT, *dest);
			cout << "My Documents: " << *dest << endl;
			// For some reason, this assert was failing even though I think the above call is fine.
			Assert::IsTrue(result == S_OK);
		}
	};
}

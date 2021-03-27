#include "lklApp.h"

wxIMPLEMENT_APP(lklApp);


lklApp::lklApp()
{
}


lklApp::~lklApp()
{
}


bool lklApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	//wxLocale* locale = new wxLocale(wxLANGUAGE_LITHUANIAN);
	/*setlocale(LC_ALL, "Lithuanian");
	setlocale(LC_ALL, "lt_LT.UTF-8");
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_TEXT);
	setlocale(LC_ALL, "Lithuanian");
	setlocale(LC_ALL, "en_US.utf8");
	_setmode(_fileno(stdout), _O_WTEXT);*/



	m_frame1 = new lklMain();
	m_frame1->Show(true);

	
	return true;
}
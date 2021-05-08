#pragma once
#include "wx/wx.h"
#include "lklMain.h"



class lklApp : public wxApp
{
private:
	wxWindow *m_frame1 = nullptr;

public:
	lklApp();

	virtual bool OnInit();
};


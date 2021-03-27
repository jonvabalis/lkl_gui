#pragma once

#include "wx/wx.h"
#include "lklMain.h"



class lklApp : public wxApp
{
public:
	lklApp();
	~lklApp();
private:
	lklMain *m_frame1 = nullptr;
public:
	virtual bool OnInit();
};


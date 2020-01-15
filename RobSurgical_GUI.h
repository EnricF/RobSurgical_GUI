#pragma once

#include "resource.h"

//-------------Text---------------
LPCWSTR editControlDefaultDecimal = L"Write a decimal value here";
//--------------------------------

//Layout----------------------------------------
int defaultHeight	= 25;//default height for any object
int defaultWidth	= 200;//default width for any object

int ix_start		= 50;//X-pixel coordinates
int iy_start		= 50;//Y-pixel coordinates

int ix_inc			= int(1.1*float(defaultWidth));//X-pixel coordinates increment
int iy_inc			= int(1.1*float(defaultHeight));//Y-pixel coordinates increment
//-----------------------------------------------

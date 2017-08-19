//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                /// 
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <rdebug_pch.h>

#define RTM_LIBHANDLER_DEFINE
#include <rbase/inc/libhandler.h>

namespace rdebug {

	bool init(rtmLibInterface* _libInterface)
	{
		g_allocator = _libInterface ? _libInterface->m_memory : 0;
		g_errorHandler = _libInterface ? _libInterface->m_error : 0;

		return false;
	}

	void shutDown()
	{
	}
}

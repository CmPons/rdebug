//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_DEBUG_H__
#define __RTM_DEBUG_H__

#include <stdint.h>

namespace rdebug {

	/// Toolchain description structure
	struct Toolchain
	{
		enum Type
		{
			TC_MSVC,	// pdb
			TC_GCC,		// nm, addr2line, c++filt
			TC_PS3SNC	// ps3bin
		};

		Toolchain::Type	m_type;
		const char*		m_toolchainPath;	// or symbol store path list for MSVC
		const char*		m_toolchainPrefix;
	};

	/// Module information structure
	struct ModuleInfo
	{
		uint64_t		m_baseAddress;
		uint64_t		m_size;
		const char*		m_modulePath;
		Toolchain		m_toolchain;

		inline bool checkAddress(uint64_t _address) const
		{
			return ((_address >= m_baseAddress) && (_address < (m_baseAddress + m_size)));
		}
	};

	/// Single entry (frame) in stack trace
	struct StackFrame
	{
		char		m_moduleName[256];
		char		m_file[1024];
		char		m_func[16384];			// very big in order to support dumb code (templates, lambdas and such)
		uint32_t	m_line;
	};

	/// Initialize rdebug library
	///
	/// @param _libInterface
	///
	bool init(rtm::LibInterface* _libInterface = nullptr);

	/// Shut down rdebug library and release internal resources
	///
	void shutDown(); 

	/// Creates debug symbol resolver based on 
	///
	/// @param _moduleInfos
	/// @param _numInfos
	/// @param _tc
	///
	uintptr_t	symbolResolverCreate(ModuleInfo* _moduleInfos, uint32_t _numInfos, Toolchain* _tc);

	/// Creates debug symbol resolver based on 
	///
	uintptr_t	symbolResolverCreateForCurrentProcess();

	/// Creates debug symbol resolver based on 
	///
	/// @param _resolver
	///
	void		symbolResolverDelete(uintptr_t _resolver);

	/// Creates debug symbol resolver based on 
	///
	/// @param _resolver
	/// @param _address
	/// @param _frame
	///
	void		symbolResolverGetFrame(uintptr_t _resolver, uint64_t _address, StackFrame& _frame);

	/// Creates debug symbol resolver based on 
	///
	/// @param _resolver
	/// @param _address
	/// @param _executablePath
	///
	uint64_t	symbolResolverGetAddressID(uintptr_t _resolver, uint64_t _address, bool* _isRTMdll = 0);
	
} // namespace rdebug

#endif // __RTM_DEBUG_H__


#include "Windows.h"
#define BEA_ENGINE_STATIC
#define BEA_USE_STDCALL
#include "beaengine/BeaEngine.h"
#pragma comment(lib,"Bee\\BeaEngine_s_d_l_64.lib")
typedef unsigned char* ucptr;
typedef unsigned char uchar;
typedef signed char schar;
class HookHelper {
	HookHelper() {

	}
public: 
	inline static unsigned int CalculateJ_X86(ucptr from, ucptr to) {
		return 0 - (from - to) - 5;
	}
	inline static void cProtection(void* ptr, size_t size, DWORD& protection) {
		VirtualProtect(ptr, size, protection, &protection);
	}
	inline static void* Alloc(size_t size, DWORD protection) {
		return VirtualAlloc(0, size, MEM_RESERVE | MEM_COMMIT, protection);
	}
	static void HookFunction(ucptr originPtr, ucptr hookPtr, ucptr& tramploline);
};
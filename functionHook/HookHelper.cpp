#include "HookHelper.h"
#include <iostream>

void HookHelper::HookFunction(ucptr originPtr, ucptr hookPtr, ucptr& tramploline)
{
	DISASM disasm = { 0 };
	disasm.EIP = reinterpret_cast<size_t>(originPtr);
	uchar totalLen = 0;
	uchar jmp[5] = { 0xe9 };
	schar delta = 0;
	while (totalLen < 5) {
		uchar currentLen = Disasm(&disasm);
		totalLen += currentLen;
		disasm.EIP += currentLen;
	}
	delta = totalLen - 5;

	tramploline = reinterpret_cast<ucptr> (HookHelper::Alloc(totalLen + 5,PAGE_EXECUTE_READWRITE));
	(*(unsigned int*)(jmp + 1)) = HookHelper::CalculateJ_X86(tramploline + totalLen, originPtr + 5 + delta);
	memcpy(tramploline, originPtr, totalLen);
	memcpy(tramploline + 5, jmp, 5);
	(*(unsigned int*)(jmp + 1)) = HookHelper::CalculateJ_X86(originPtr, hookPtr);
	std::cout << (*(unsigned int*)(jmp));
	DWORD prot = PAGE_EXECUTE_READWRITE;

	HookHelper::cProtection(originPtr, totalLen + delta, prot);

	memcpy(originPtr, jmp, 5);
	if (delta) memset(originPtr, 0x90, delta);

	HookHelper::cProtection(originPtr, totalLen + delta, prot);
}

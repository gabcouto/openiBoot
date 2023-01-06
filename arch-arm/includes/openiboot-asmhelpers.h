#ifndef OPENIBOOT_ASMHELPERS_H
#define OPENIBOOT_ASMHELPERS_H

void IncrementCriticalLock();
void DecrementCriticalLock();
void EnterCriticalSection();
void LeaveCriticalSection();

void EnableCPUIRQ();
void EnableCPUFIQ();
void DisableCPUIRQ();
void DisableCPUFIQ();

uint32_t ReadAuxiliaryControlRegister();
void ClearCPUInstructionCache();
uint32_t ReadControlRegisterConfigData();

uint32_t ReadControlRegisterConfigData();
void WriteControlRegisterConfigData(uint32_t regData);
uint32_t ReadAuxiliaryControlRegister();
void WriteAuxiliaryControlRegister(uint32_t regData);
void WriteDomainAccessControlRegister(uint32_t regData);
uint32_t ReadDataFaultStatusRegister();
uint32_t ReadFaultAddressRegister();
void WritePeripheralPortMemoryRemapRegister(uint32_t regData);
void GiveFullAccessCP10CP11();
void EnableVFP();
void WaitForInterrupt();
void WriteTranslationTableBaseRegister0(void* translationTableBase);
uint32_t ReadTranslationTableBaseRegister0();

void InvalidateUnifiedTLBUnlockedEntries();
void ClearCPUInstructionCache();
void CleanDataCacheLineMVA();
void CleanCPUDataCache();
void InvalidateCPUDataCache();
void CleanAndInvalidateCPUDataCache();
void ClearCPUCaches();

uint32_t GetC9C012();
void SetC9C012(uint32_t _val);

void CallArm(uint32_t address);
void CallThumb(uint32_t address);

void Reboot();
void EndlessLoop();

void SwapTask(TaskDescriptor *_td);
void StartTask();

#endif


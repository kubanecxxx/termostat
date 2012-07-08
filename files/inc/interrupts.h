#ifndef __INTERRUPTS_SET
#define __INTERRUPTS_SET

#ifdef __cplusplus
extern "C" {
#endif 

void SysTick_Handler(void);
void HardFault_Handler (void);
void MemManage_Handler  (void);
void BusFault_Handler (void);
void UsageFault_Handler (void);
void SVC_Handler (void);
void out_of_memory(void);
uint32_t GetTimeCounter();

#ifdef __cplusplus
}
#endif 

#endif //__INTERRUPTS_SET

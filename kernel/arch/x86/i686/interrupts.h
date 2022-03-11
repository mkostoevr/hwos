#include <kernel/types.h>

typedef struct {
  u32  ds;
  u32  edi, esi, ebp, esp, ebx, edx, ecx, eax;
  u32  int_num, err_code;
  u32  eip, cs, eflags, useresp, ss;
} __attribute__((packed)) interrupt_ctx_t;

typedef void (*interrupt_handler_t)(interrupt_ctx_t);

void set_interrupt_handler(u8 num, interrupt_handler_t handler);
void common_interrupt_handler(interrupt_ctx_t regs);
void divide_by_zero(interrupt_ctx_t regs);


// interrupt handlers declarations:
void interrupt_handler0();
void interrupt_handler1();
void interrupt_handler2();
void interrupt_handler3();
void interrupt_handler4();
void interrupt_handler5();
void interrupt_handler6();
void interrupt_handler7();
void interrupt_handler8();
void interrupt_handler9();
void interrupt_handler10();
void interrupt_handler11();
void interrupt_handler12();
void interrupt_handler13();
void interrupt_handler14();
void interrupt_handler15();
void interrupt_handler16();
void interrupt_handler17();
void interrupt_handler18();
void interrupt_handler19();
void interrupt_handler20();
void interrupt_handler21();
void interrupt_handler22();
void interrupt_handler23();
void interrupt_handler24();
void interrupt_handler25();
void interrupt_handler26();
void interrupt_handler27();
void interrupt_handler28();
void interrupt_handler29();
void interrupt_handler30();
void interrupt_handler31();
void interrupt_handler32();
void interrupt_handler33();
void interrupt_handler34();
void interrupt_handler35();
void interrupt_handler36();
void interrupt_handler37();
void interrupt_handler38();
void interrupt_handler39();
void interrupt_handler40();
void interrupt_handler41();
void interrupt_handler42();
void interrupt_handler43();
void interrupt_handler44();
void interrupt_handler45();
void interrupt_handler46();
void interrupt_handler47();

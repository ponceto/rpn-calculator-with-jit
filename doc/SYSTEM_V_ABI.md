# SYSTEM V ABI

This document describes the System V ABI and the calling convention for the Linux x86-64 architecture.

## SYSTEM V ABI AND CALLING CONVENTION FOR X86-64

This is a 64-bit platform. The stack grows downwards. Parameters to functions are passed in the registers rdi, rsi, rdx, rcx, r8, r9, and further values are passed on the stack in reverse order. Parameters passed on the stack may be modified by the called function. Functions are called using the call instruction that pushes the address of the next instruction to the stack and jumps to the operand. Functions return to the caller using the ret instruction that pops a value from the stack and jump to it. The stack is 16-byte aligned just before the call instruction is called.

Functions preserve the registers rbx, rsp, rbp, r12, r13, r14, and r15; while rax, rdi, rsi, rdx, rcx, r8, r9, r10, r11 are scratch registers. The return value is stored in the rax register, or if it is a 128-bit value, then the higher 64-bits go in rdx. Optionally, functions push rbp such that the caller-return-rip is 8 bytes above it, and set rbp to the address of the saved rbp. This allows iterating through the existing stack frames. This can be eliminated by specifying the -fomit-frame-pointer GCC option.

Signal handlers are executed on the same stack, but 128 bytes known as the red zone is subtracted from the stack before anything is pushed to the stack. This allows small leaf functions to use 128 bytes of stack space without reserving stack space by subtracting from the stack pointer. The red zone is well-known to cause problems for x86-64 kernel developers, as the CPU itself doesn't respect the red zone when calling interrupt handlers. This leads to a subtle kernel breakage as the ABI contradicts the CPU behavior. The solution is to build all kernel code with -mno-red-zone or by handling interrupts in kernel mode on another stack than the current (and thus implementing the ABI). 

| Name | Notes                                                                                                         | Type      | 64-bit long | 32-bit int | 16-bit short | 8-bit char |
|------|---------------------------------------------------------------------------------------------------------------|-----------|-------------|------------|--------------|------------|
| rax  | Values are returned from functions in this register.                                                          | scratch   | rax         | eax        | ax           | ah and al  |
| rcx  | Typical scratch register.  Some instructions also use it as a counter.                                        | scratch   | rcx         | ecx        | cx           | ch and cl  |
| rdx  | Scratch register.                                                                                             | scratch   | rdx         | edx        | dx           | dh and dl  |
| rbx  | Preserved register: don't use it without saving it!                                                           | preserved | rbx         | ebx        | bx           | bh and bl  |
| rsp  | The stack pointer.  Points to the top of the stack (details coming soon!)                                     | preserved | rsp         | esp        | sp           | spl        |
| rbp  | Preserved register.  Sometimes used to store the old value of the stack pointer, or the "base".               | preserved | rbp         | ebp        | bp           | bpl        |
| rsi  | Scratch register used to pass function argument #2 in 64-bit Linux.  In 64-bit Windows, a preserved register. | scratch   | rsi         | esi        | si           | sil        |
| rdi  | Scratch register and function argument #1 in 64-bit Linux.  In 64-bit Windows, a preserved register.          | scratch   | rdi         | edi        | di           | dil        |
| r8   | Scratch register.  These were added in 64-bit mode, so they have numbers, not names.                          | scratch   | r8          | r8d        | r8w          | r8b        |
| r9   | Scratch register.                                                                                             | scratch   | r9          | r9d        | r9w          | r9b        |
| r10  | Scratch register.                                                                                             | scratch   | r10         | r10d       | r10w         | r10b       |
| r11  | Scratch register.                                                                                             | scratch   | r11         | r11d       | r11w         | r11b       |
| r12  | Preserved register.  You can use it, but you need to save and restore it.                                     | preserved | r12         | r12d       | r12w         | r12b       |
| r13  | Preserved register.                                                                                           | preserved | r13         | r13d       | r13w         | r13b       |
| r14  | Preserved register.                                                                                           | preserved | r14         | r14d       | r14w         | r14b       |
| r15  | Preserved register.                                                                                           | preserved | r15         | r15d       | r15w         | r15b       |

## REFERENCE DOCUMENTS

  - [System V ABI](https://wiki.osdev.org/System_V_ABI)
  - [x86_64 NASM Assembly Quick Reference](https://www.cs.uaf.edu/2017/fall/cs301/reference/x86_64.html)

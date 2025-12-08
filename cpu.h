#ifndef CPU_H
#define CPU_H

typedef unsigned char uchar;

#include "mmu.h"
#include "proc.h"

struct cpu {
  uchar apicid;               // Local APIC ID
  struct context *scheduler;  // swtch() here to enter scheduler
  struct taskstate ts;        // Used by x86 to find stack for interrupts
  struct segdesc gdt[NSEGS];  // x86 global descriptor table
  volatile int started;       // Has the CPU started?
  int ncli;                   // Depth of pushcli nesting
  int intena;                 // Were interrupts enabled before pushcli?
  struct proc *proc;          // The process running on this cpu or null
};

extern struct cpu cpus[NCPU];
extern int ncpu;

// Return pointer to the current cpu
struct cpu* mycpu(void);

// Return pointer to the current process
struct proc* myproc(void);

#endif

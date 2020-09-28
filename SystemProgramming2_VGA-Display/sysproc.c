#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_fork(void)
{
	return fork();
}

int sys_exit(void)
{
	exit();
	return 0;  // not reached
}

int sys_wait(void)
{
	return wait();
}

int sys_kill(void)
{
	int pid;

	if (argint(0, &pid) < 0)
	{
		return -1;
	}
	return kill(pid);
}

int sys_getpid(void)
{
	return myProcess()->ProcessId;
}

int sys_setvideomode(int mode)
{
	int n;

	if (argint(0, &n) < 0)
	{
		return -1;
	}
	
	videoSetMode(n);

	return 0;
}

int sys_clearscreen(void)
{
	uint8_t* memoryAddress;
	memoryAddress = (uint8_t*)P2V(0xA0000);



	for (int x = 0; x <= 320; x++)
	{
		for (int y = 0; y <= 200; y++)
		{
			memoryAddress[320 * y + x] = 0;
		}
	}
	return 0;
}


int sys_setpixel(void)
{

	int x, y, color;

	if (argint(0, &x) < 0)
	{
		return -1;
	}
	if (argint(0, &y) < 0)
	{
		return -1;
	}
	if (argint(0, &color) < 0)
	{
		return -1;
	}
	return 0;
}


int setpixel(int x, int y, int color)
{
	uint8_t* memoryAddress;
	memoryAddress = (uint8_t*)P2V(0xA0000);

	if (getCurrentVideoMode() == 0x13)
	{
		memoryAddress[320 * y + x] = color;
	}
	return 0;
}

int sys_sbrk(void)
{
	int addr;
	int n;

	if (argint(0, &n) < 0)
	{
		return -1;
	}
	addr = myProcess()->MemorySize;
	if (growProcess(n) < 0)
	{
		return -1;
	}
	return addr;
}

int sys_sleep(void)
{
	int n;
	uint32_t ticks0;

	if (argint(0, &n) < 0)
	{
		return -1;
	}
	spinlockAcquire(&tickslock);
	ticks0 = ticks;
	while (ticks - ticks0 < n) 
	{
		if (myProcess()->IsKilled) 
		{
			spinlockRelease(&tickslock);
			return -1;
		}
		sleep(&ticks, &tickslock);
	}
	spinlockRelease(&tickslock);
	return 0;
}

int abs(int i)
{
	return i < 0 ? -i : i;
}

int sys_drawline(void)
{
	int x0, y0, x1, y1, color;

	if (argint(0, &x0) < 0)
	{
		return -1;
	}
	if (argint(1, &y0) < 0)
	{
		return -1;
	}
	if (argint(2, &x1) < 0)
	{
		return -1;
	}
	if (argint(3, &y1) < 0)
	{
		return -1;
	}
	if (argint(4, &color) < 0)
	{
		return -1;
	}
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;

	for (;;) {
		setpixel(x0, y0, color);
		if (x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; }
		if (e2 <= dx) { err += dx; y0 += sy; }
	}
	return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
	uint32_t xticks;

	spinlockAcquire(&tickslock);
	xticks = ticks;
	spinlockRelease(&tickslock);
	return xticks;
}

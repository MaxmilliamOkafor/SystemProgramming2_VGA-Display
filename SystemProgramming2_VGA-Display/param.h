#define NPROC			64		// maximum number of processes
#define KSTACKSIZE		4096	// size of per-process kernel stack
#define NCPU			8		// maximum number of CPUs
#define NOFILE			16		// open files per process
#define NFILE			100		// open files per system
#define NDEV			10		// maximum major device number
#define ROOTDEV			1		// device number of file system root disk
#define MAXARG			32		// max exec arguments
#define NBUF			30		// size of disk block cache
#define MAXFATSIZE		10		// Maximum number of sectors occupied by a FAT
#define MAXCWDSIZE		200		// Maximum length of current working directory in process structure
#define CONSOLEWIDTH	80		// Width of console (in characters)
#define CONSOLEHEIGHT	25		// Height of console (in characters)

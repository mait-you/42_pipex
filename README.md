# UNIX System Calls and Functions Reference

## File Operations

### open
```c
#include <fcntl.h>
int open(const char *pathname, int flags, mode_t mode);
```
- Opens or creates a file for reading/writing
- Returns file descriptor on success, -1 on error
- Common flags: **O_RDONLY**, **O_WRONLY**, **O_RDWR**, **O_CREAT**, **O_APPEND**
- Mode specifies permissions when creating new files

### close
```c
#include <unistd.h>
int close(int fd);
```
- Closes a file descriptor
- Returns 0 on success, -1 on error
- Releases system resources associated with the file descriptor

### read
```c
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);
```
- Reads up to count bytes from file descriptor into buffer
- Returns number of bytes read, 0 at EOF, -1 on error
- May read fewer bytes than requested

### write
```c
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
```
- Writes up to count bytes from buffer to file descriptor
- Returns number of bytes written, -1 on error
- May write fewer bytes than requested

### unlink
```c
#include <unistd.h>
int unlink(const char *pathname);
```
- Removes a name from the filesystem
- Returns 0 on success, -1 on error
- File is deleted when all links are removed and no processes have it open

## Memory Management

### malloc
```c
#include <stdlib.h>
void *malloc(size_t size);
```
- Allocates size bytes of memory
- Returns pointer to allocated memory, NULL on error
- Memory is not initialized

### free
```c
#include <stdlib.h>
void free(void *ptr);
```
- Deallocates memory previously allocated by malloc
- ptr must be previously returned by malloc/calloc/realloc
- No return value

## Error Handling

### perror
```c
#include <stdio.h>
void perror(const char *s);
```
- Prints a system error message to stderr
- Message includes string s followed by error description
- Uses current value of errno

### strerror
```c
#include <string.h>
char *strerror(int errnum);
```
- Returns string describing error code
- Thread-safe alternative to sys_errlist[]
- Returns "Unknown error" if errnum is invalid

### access
```c
#include <unistd.h>
int access(const char *pathname, int mode);
```
- Checks if calling process can access file
- Returns 0 if allowed, -1 if file does not have the requested permissions  or if the file does not exist (`errno` is set to indicate the error)
- Mode can be :
  - **F_OK** flag: test for existence of file
  - **X_OK** flag: test for execute or search permission 
  - **W_OK** flag: test for write permission
  - **R_OK** flag: test for read permission

## Process Management

### fork
```c
#include <unistd.h>
pid_t fork(void);
```
- Creates new process by duplicating calling process
- Returns 0 to child, child's PID to parent, -1 on error
- Child is exact copy of parent except for PID

### execve
```c
#include <unistd.h>
int execve(const char *pathname, char *const argv[], char *const envp[]);
```
- Executes program specified by pathname
- Returns only on error (-1)
- Replaces current process image with new program

### exit
```c
#include <stdlib.h>
void exit(int status);
```
- Terminates calling process
- Status is returned to parent
- Flushes and closes all open streams

### wait
```c
#include <sys/wait.h>
pid_t wait(int *status);
```
- Waits for any child process to terminate
- Returns terminated child's PID, -1 on error
- Status stores child's exit status

### waitpid
```c
#include <sys/wait.h>
pid_t waitpid(pid_t pid, int *status, int options);
```
- Waits for specific child process to terminate
- More control than wait()
- Options can specify non-blocking behavior

## File Descriptor Operations

### dup
```c
#include <unistd.h>
int dup(int oldfd);
```
- Creates copy of file descriptor
- Returns new file descriptor, -1 on error
- New descriptor uses lowest available number
- They both refer to the same open file description and thus share file offset and file status flags

### dup2
```c
#include <unistd.h>
int dup2(int oldfd, int newfd);
```
- Creates copy of file descriptor with specific number
- Returns new file descriptor, -1 on error
- Closes newfd first if it was open

### pipe
```c
#include <unistd.h>
int pipe(int pipefd[2]);
```
- Creates pipe for communication between two processes
- Returns 0 on success, -1 on error
- pipefd[0] is read end, pipefd[1] is write end
- Pipes behave FIFO(First in First out)


# Understanding Fork() System Call

## Code Analysis
```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    printf("main process_id(pid) = %d\n\n", getpid());
    
    pid_t P_0 = fork();
    printf("P_0 :%d\n", P_0);
    printf("process_id(pid) = %d\n\n", getpid());
    
    pid_t P_1 = fork();
    printf("P_1 :%d\n", P_1);
    printf("process_id(pid) = %d\n\n", getpid());
    
    pid_t P_2 = fork();
    printf("P_2 :%d\n", P_2);
    printf("process_id(pid) = %d\n\n", getpid());
    
    return 0;
}
```

## How Fork() Works

1. When `fork()` is called, it creates a new process by duplicating the calling process
2. The new process (child) is an exact copy of the parent process
3. `fork()` returns:
   - To the parent process: the PID of the child
   - To the child process: 0
   - -1 if the fork failed

## Process Tree Creation

Let's track the process creation step by step:

```
Initial Process
└── Main Process (let's say PID = 1000)
```

### After first fork() (P_0):
```
                    ┌── Child 1 (PID = 1001)
Main (PID = 1000) ──┘
```

### After second fork() (P_1):
```
                    ┌── Child 1 (PID = 1001) ──┐
Main (PID = 1000) ──┤                          └── Child 2 (PID = 1003)
                    └── Child 3 (PID = 1002)
```

### After third fork() (P_2):
```
                    ┌── Child 1 (PID = 1001) ──┬── Child 2 (PID = 1003) ──┐
Main (PID = 1000) ──┤                          └── Child 4 (PID = 1004)   └── Child 5 (PID = 1006)
                    └── Child 3 (PID = 1002) ──┘                          └── Child 6 (PID = 1005)
                                               └── Child 7 (PID = 1007)
```

## Execution Flow

1. **Initial State**:
   - Program starts with main process
   - Prints initial PID

2. **First fork() (P_0)**:
   - Creates 2 processes
   - Parent sees P_0 = child's PID
   - Child sees P_0 = 0

3. **Second fork() (P_1)**:
   - Both existing processes execute fork()
   - Creates 4 processes total
   - Each parent sees P_1 = new child's PID
   - Each child sees P_1 = 0

4. **Third fork() (P_2)**:
   - All 4 existing processes execute fork()
   - Creates 8 processes total
   - Each parent sees P_2 = new child's PID
   - Each child sees P_2 = 0

## Number of Processes
- After P_0: 2 processes (2¹)
- After P_1: 4 processes (2²)
- After P_2: 8 processes (2³)

The total number of processes follows the formula: 2ⁿ, where n is the number of fork() calls.

## Important Notes

1. Each child process starts executing from the point of fork()
2. Child processes inherit copies of the parent's variables
3. Memory space is copied but separate for each process
4. Each process has its own unique PID
5. The order of execution between parent and child is not guaranteed



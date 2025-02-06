# pipex

## System calls
System calls are the calls that a program makes to the system kernel to provide the services to which the program does not have direct access.

### File Descriptor
The file descriptor is an unsigned (except -1) integer used by a process to identify an open file, The number of file descriptors available to a process is limited by the **/OPEN_MAX** control in the **sys/limits.h** file, and `ulimit -n` flag.
- **File Descriptor table**: A file descriptor table is the collection of integer array indices that are file descriptors in which elements are pointers to file table entries. One unique file descriptors table is provided in the operating system for each process.
- **File Table Entry**: File table entries are a structure In-memory surrogate for an open file, which is created when processing a request to open the file and these entries maintain file position.
- **Standard File Descriptors**: When any process starts, then that process file descriptors table’s fd(file descriptor) 0, 1, 2 open automatically, (By default) each of these 3 fd references file table entry for a file named `/dev/tty`.
```
Keyboard -> /dev/tty -> fd 0 -> Your Program
Your Program -> fd 1 -> /dev/tty -> Screen
```

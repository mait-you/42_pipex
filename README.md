# pipex

## File Descriptor
The file descriptor is an unsigned (except -1) integer used by a process to identify an open file, The number of file descriptors available to a process is limited by the **/OPEN_MAX** control in the **sys/limits.h** file, and `ulimit -n` flag.

- **File Descriptor table**: A file descriptor table is the collection of integer array indices that are file descriptors in which elements are pointers to file table entries. One unique file descriptors table is provided in the operating system for each process.

- **File Table Entry**: File table entries are a structure In-memory surrogate for an open file, which is created when processing a request to open the file and these entries maintain file position.

- **Standard File Descriptors**: When any process starts, then that process file descriptors table’s fd(file descriptor) 0, 1, 2 open automatically, (By default) each of these 3 fd references file table entry for a file named `/dev/tty`.

## Open File Table
The Open File Table stores the information about all the files that are open while the OS is running. It consists of **/MAX_OPENFILE_NUM**, Every entry of the Open File Table has the following format :

<div align="center">

| Inode Index | Open Instance Count | Lseek | Unused |
|-------------|---------------------|-------|--------|

</div>


## System calls
System calls are the calls that a program makes to the system kernel to provide the services to which the program does not have direct access.

### `open`
The `open()` function in C is used to open the file for reading, writing, or both. It is also capable of creating the file if it does not exist. 
```c
int open(const char *path, int oflag, ... );
```

<div align="center">

| **Flag**       | **Description** |
|---------------|------------------------------------------------------|
| `O_RDONLY`    | Opens the file in *read-only* mode. |
| `O_WRONLY`    | Opens the file in *write-only* mode. |
| `O_RDWR`      | Opens the file in *both read and write* mode. |
| `O_CREAT`     | *Creates the file* if it does not exist (requires mode permissions). |
| `O_EXCL`      | Used with `O_CREAT`, *fails if the file already exists* (prevents overwriting). |
| `O_APPEND`    | Opens the file and *moves the cursor to the end*, so writes *always append* to the file. |
| `O_ASYNC`     | Enables *asynchronous I/O*: Signals (`SIGIO`) will be sent when I/O operations are available. |
| `O_CLOEXEC`   | Ensures the file descriptor is *closed automatically* if `exec()` is called (prevents file leaks across exec'ed programs). |
| `O_NONBLOCK`  | Opens the file in *non-blocking mode*, meaning `read()` and `write()` return immediately instead of waiting. |
| `O_TRUNC`     | *Truncates (clears) the file* to zero size if it already exists (only works with `O_WRONLY` or `O_RDWR`). |
| `O_DIRECT`    | Reduces kernel caching, performing *direct disk I/O* (bypasses buffering for better performance in some cases). |
| `O_NOFOLLOW`  | Prevents following *symbolic links* when opening a file (fails if the target is a symlink). |
| `O_TMPFILE`   | Creates a *temporary file* that is deleted when closed (used for secure, unlinked temporary storage). |

</div>

**How C open() works in OS**
- Find the existing file on the disk.
- Create file table entry.
- Set the first unused file descriptor to point to the file table entry.
- Return file descriptor used, -1 upon failure.

### `close`
The `close()` function in C tells the operating system that you are done with a file descriptor and closes the file pointed by the file descriptor.
```c
int close(int fd);
```

**How C close() works in the OS**
- Destroy file table entry referenced by element fd of the file descriptor table (As long as no other process is pointing to it!)







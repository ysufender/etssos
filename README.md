# ETSSOS

ETSSOS is an attempt to program an RTOS completely from scratch, by hand, for ESP8266 LX106 boards.

## Compiling

### Requirements

- GCC XTensa Cross Compiler
- GNU XTensa Binutils
- [Efile](https://codeberg.org/ysufender/Efile) Standalone Executable
- Python 3 (for monitoring, otherwise it is not needed)

### Building

```bash
usage: efile <target>
targets:
    all
    arch
    kernel
    link
    help
    clean
    upload
```

> Note: Windows is not supported, natively at least. Build script uses UNIX shell commands.

### Uploading

Upload step will only work if you have `esptool` on your path.

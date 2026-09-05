# ETSSOS

## Compiling

### Requirements

- GCC XTensa Cross Compiler
- GNU XTensa Binutils
- [Efile](https://codeberg.org/ysufender/Efile) Standalone Executable

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

> Note: Windows is not supported.

### Uploading

Upload step will only work if you have `esptool` on your path.

#ifndef A9MEMFS_H
#define A9MEMFS_H

void dump_fcramvram();
void dump_fcramaxiwram();
void loadfile_charpath(char *path, u32 *addr, u32 maxsize);

#endif

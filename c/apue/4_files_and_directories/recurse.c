/*
 * Recursively descend a directory structure and count the file types along the way
 */
#include "apue.h"
#include <dirent.h>
#include <limits.h>

typedef int newFunc(const char *, const struct stat *, int);

static newFunc newfunc;
static int new_ftw(char *, newFunc *);
static int dopath(newFunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[])
{

    int ret;

    if (argc != 2)
        err_quit("Usage: ./a.out <start path>");

    ret = new_ftw(argv[1], newfunc);

    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;

    if (ntot == 0)
        ntot = 1; // avoiding divide by zero errors

    printf("[+] Regular files: \t %7ld, %5.2f %%\n", nreg, nreg*100.0/ntot);
    printf("[+] Directories:   \t %7ld, %5.2f %%\n", ndir, ndir*100.0/ntot);
    printf("[+] Block special: \t %7ld, %5.2f %%\n", nblk, nblk*100.0/ntot);
    printf("[+] Char special:  \t %7ld, %5.2f %%\n", nchr, nchr*100.0/ntot);
    printf("[+] FIFOs:         \t %7ld, %5.2f %%\n", nfifo, nfifo*100.0/ntot);
    printf("[+] Symbolic links:\t %7ld, %5.2f %%\n", nslink, nslink*100.0/ntot);
    printf("[+] Sockets:       \t %7ld, %5.2f %%\n", nsock, nsock*100.0/ntot);

    exit(ret);
}

// Descend through the hierarchy, starting at pathnam
// Caller's func() is called for every file
#define FTW_F 1 // file other than a directory
#define FTW_D 2 // directory
#define FTW_DNR 3 // unreadable directory
#define FTW_NS 4 // unable to stat

static char *fullpath;
static size_t pathlen;

static int new_ftw(char *pathname, newFunc *func)
{
    fullpath = path_alloc(&pathlen);

    if (pathlen <= strlen(pathname))
    {
        pathlen = strlen(pathname) * 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL)
            err_sys("realloc failed");
    }
    strcpy(fullpath, pathname);
    return(dopath(func));
}

// Descend through hierarchy starting at fullpath
// If full path is anything other than a directory, we lstat() it
// call func() and return. For a dir, we call ourself recursively for each name
// in the dir.

static int dopath(newFunc *func)
{
    struct stat buf;
    struct dirent *dirp;
    DIR *dp;
    int ret, n;

    if (lstat(fullpath, &buf) < 0) // stat error
        return(func(fullpath, &buf, FTW_NS));
    if (S_ISDIR(buf.st_mode) == 0) // Not a directory
        return(func(fullpath, &buf, FTW_F));

    // Its a DIR! Call func() then process the filenames
    if ((ret = func(fullpath, &buf, FTW_D)) != 0)
        return(ret);

    n = strlen(fullpath);
    if (n + NAME_MAX + 2 > pathlen)
    {
        pathlen *= 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL)
            err_sys("realloc failed");
    }
    fullpath[n++] = '/';
    fullpath[n] = 0;

    if ((dp = opendir(fullpath)) == NULL)
        return (func(fullpath, &buf, FTW_DNR));

    while ((dirp = readdir(dp)) != NULL)
    {
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
            continue;
        strcpy(&fullpath[n], dirp->d_name);
        if ((ret = dopath(func)) != 0)
            break;
    }
    fullpath[n-1] = 0;

    if (closedir(dp) < 0)
        err_ret("can't close directory %s", fullpath);
    return (ret);
}

static int newfunc(const char *pathname, const struct stat *statptr, int type)
{
    switch(type){
    case FTW_F:
        switch(statptr->st_mode & S_IFMT){
        case S_IFREG:   nreg++; break;
        case S_IFBLK:   nblk++; break;
        case S_IFCHR:   nchr++; break;
        case S_IFIFO:   nfifo++;    break;
        case S_IFLNK:   nslink++;   break;
        case S_IFSOCK:  nsock++;    break;
        case S_IFDIR:
            err_dump("for S_IFDIR for %s", pathname);
        }
        break;
    case FTW_D:
        ndir++;
        break;
    case FTW_DNR:
        err_ret("can't read directory %s", pathname);
        break;
    case FTW_NS:
        err_ret("stat error for %s", pathname);
        break;
    default:
        err_dump("unknown type %d for pathname %s", type, pathname);
    }
    return 0;
}

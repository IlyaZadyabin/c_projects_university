#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <string.h>

enum { GROUP_SHIFT = 3, USER_SHIFT = 6 };

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

static unsigned int group_rights(int mode)
{
    return (mode & S_IRWXG) >> GROUP_SHIFT;
}

static unsigned int user_rights(int mode)
{
    return (mode & S_IRWXU) >> USER_SHIFT;
}

static unsigned int other_rights(int mode)
{
    return mode & S_IRWXO;
}

int myaccess(const struct stat *stb, const struct Task *task, int access)
{
    int i = 0;
    if(task->uid == 0) {
        return 1;
    }

    if(stb->st_uid == task->uid) {
        if((access & (~user_rights(stb->st_mode))) == 0) {
            return 1;
        } else {
            return 0;
        } 
    }

    for(i = 0; i < task->gid_count; i++) {
        if(*(task->gids + i) == stb->st_gid) {
            if((access & (~group_rights(stb->st_mode))) == 0) {
                return 1;
            } else {
                return 0;
            }
        }
    }

    if((access & (~other_rights(stb->st_mode))) == 0) {
        return 1;
    } else {
        return 0;
    }
}

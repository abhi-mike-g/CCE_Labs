// UNIX Simulation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>

// Simulate the `ls -l` command
void ls_l() {
    struct dirent *entry;
    struct stat fileStat;
    DIR *dp = opendir(".");

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    printf("Permissions\tLinks\tOwner\tGroup\tSize\tModified Time\t\tName\n");
    while ((entry = readdir(dp)) != NULL) {
        if (stat(entry->d_name, &fileStat) == -1) {
            perror("stat");
            continue;
        }

        // File permissions
        char perms[11];
        snprintf(perms, sizeof(perms), "%c%c%c%c%c%c%c%c%c%c",
            (S_ISDIR(fileStat.st_mode)) ? 'd' : '-',
            (fileStat.st_mode & S_IRUSR) ? 'r' : '-',
            (fileStat.st_mode & S_IWUSR) ? 'w' : '-',
            (fileStat.st_mode & S_IXUSR) ? 'x' : '-',
            (fileStat.st_mode & S_IRGRP) ? 'r' : '-',
            (fileStat.st_mode & S_IWGRP) ? 'w' : '-',
            (fileStat.st_mode & S_IXGRP) ? 'x' : '-',
            (fileStat.st_mode & S_IROTH) ? 'r' : '-',
            (fileStat.st_mode & S_IWOTH) ? 'w' : '-',
            (fileStat.st_mode & S_IXOTH) ? 'x' : '-'
        );

        // File modification time
        char timeBuff[20];
        strftime(timeBuff, sizeof(timeBuff), "%b %d %H:%M", localtime(&fileStat.st_mtime));

        // Print details
        printf("%s\t%d\t%d\t%d\t%ld\t%s\t%s\n", perms, fileStat.st_nlink, fileStat.st_uid, fileStat.st_gid, fileStat.st_size, timeBuff, entry->d_name);
    }

    closedir(dp);
}

// Simulate the `cp` command
void cp(const char *source, const char *dest) {
    int srcFd = open(source, O_RDONLY);
    if (srcFd == -1) {
        perror("Source file open failed");
        return;
    }

    int destFd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFd == -1) {
        perror("Destination file open failed");
        close(srcFd);
        return;
    }

    char buffer[1024];
    ssize_t bytesRead, bytesWritten;
    while ((bytesRead = read(srcFd, buffer, sizeof(buffer))) > 0) {
        bytesWritten = write(destFd, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Write failed");
            break;
        }
    }

    if (bytesRead == -1) {
        perror("Read failed");
    }

    close(srcFd);
    close(destFd);
}

// Simulate the `wc` command
void wc(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("File open failed");
        return;
    }

    ssize_t bytesRead;
    char buffer[1024];
    int lines = 0, words = 0, chars = 0;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytesRead; i++) {
            chars++;
            if (buffer[i] == '\n') {
                lines++;
            }
            if (buffer[i] == ' ' || buffer[i] == '\n') {
                words++;
            }
        }
    }

    if (bytesRead == -1) {
        perror("Read failed");
    }

    // Count words for the last line if there's no newline at the end
    if (chars > 0 && buffer[bytesRead - 1] != '\n') {
        words++;
    }

    printf("Lines: %d Words: %d Chars: %d\n", lines, words, chars);

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command> [args...]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "ls-l") == 0) {
        ls_l();
    }
    else if (strcmp(argv[1], "cp") == 0 && argc == 4) {
        cp(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "wc") == 0 && argc == 3) {
        wc(argv[2]);
    }
    else {
        printf("Invalid command or arguments.\n");
    }

    return 0;
}

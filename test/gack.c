#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_USERS 100

typedef struct {
    char username[64];
    char tty[64];
} User;

int get_logged_in_users(User users[], int max_users) {
    FILE *fp = popen("who", "r");
    if (!fp) {
        perror("popen who");
        return -1;
    }

    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp) && count < max_users) {
        sscanf(line, "%s %s", users[count].username, users[count].tty);
        count++;
    }

    pclose(fp);
    return count;
}

void spam_user(const char* username, const char* tty) {
    char cmd[256];
    FILE *write_fp;

    snprintf(cmd, sizeof(cmd), "write %s %s", username, tty);
    write_fp = popen(cmd, "w");
    if (!write_fp) {
        perror("popen write");
        return;
    }

    for (int i = 0; i < 10; i++) {
        int percent = rand() % 101;
        fprintf(write_fp, "DATA IS BEING DOWNLOADED... [%d%%]\n", percent);
        fflush(write_fp);
        sleep(1);
    }

    pclose(write_fp);
}

int main() {
    srand(time(NULL));

    User users[MAX_USERS];
    int user_count = get_logged_in_users(users, MAX_USERS);
    if (user_count <= 0) {
        printf("No users found.\n");
        return 1;
    }

    printf("Spamming %d users...\n", user_count);

    for (int i = 0; i < user_count; i++) {
        printf("Sending to %s on %s\n", users[i].username, users[i].tty);
        spam_user(users[i].username, users[i].tty);
    }

    return 0;
}

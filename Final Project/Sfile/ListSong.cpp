#include "Song.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 100

typedef struct Song {
	char name[NAME_LEN];
	struct Song* next;
} Song;
Song* CreateSong(const char* name);
void AddSong(Song** head, const char* name);
void DeleteSong(Song** head, const char* name);
void PlaySongs(Song* head);
void MenuSong();

Song* CreateSong(const char* name) {
	Song* newSong = (Song*)malloc(sizeof(Song));
	strncpy(newSong->name, name, NAME_LEN - 1);
	newSong->name[NAME_LEN - 1] = '\0';
	newSong->next = NULL;
	return newSong;
}

void AddSong(Song** head, const char* name) {
	Song* newSong = CreateSong(name);
	if (*head == NULL) {
		*head = newSong;
		return;
	}
	Song* temp = *head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newSong;
}

void DeleteSong(Song** head, const char* name) {
	Song* temp = *head;
	Song* prev = NULL;
	while (temp != NULL) {
		if (strcmp(temp->name, name) == 0) {
			if (prev == NULL) {
				*head = temp->next;
			} else {
				prev->next = temp->next;
			}
			free(temp);
			printf("已删除歌曲: %s\n", name);
			return;
		}
		prev = temp;
		temp = temp->next;
	}
	printf("未找到歌曲: %s\n", name);
}

void PlaySongs(Song* head) {
	Song* temp = head;
	int idx = 1;
	while (temp != NULL) {
		printf("正在播放第 %d 首: %s\n", idx++, temp->name);
		temp = temp->next;
	}
}

void MenuSong() {
	printf("播放列表菜单\n");
	printf("1. 添加歌曲\n");
	printf("2. 删除歌曲\n");
	printf("3. 顺序播放\n");
	printf("4. 退出\n");
}

int MainSong() {
	Song* playlist = NULL;
	int choice;
	char name[NAME_LEN];
	
	while (1) {
		MenuSong();
		printf("请选择: ");
		scanf("%d", &choice);
		while (getchar() != '\n');
		
		switch (choice) {
		case 1:
			printf("请输入歌曲名: ");
			fgets(name, NAME_LEN, stdin);
			name[strcspn(name, "\n")] = '\0'; // 去除换行符
			AddSong(&playlist, name);
			printf("已添加歌曲: %s\n", name);
			break;
		case 2:
			printf("请输入要删除的歌曲名: ");
			fgets(name, NAME_LEN, stdin);
			name[strcspn(name, "\n")] = '\0';
			DeleteSong(&playlist, name);
			break;
		case 3:
			printf("当前播放列表: \n");
			PlaySongs(playlist);
			break;
		case 4:
			printf("程序退出！\n");
			return 0;
		}
	}
}

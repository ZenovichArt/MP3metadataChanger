//
//  main.c
//  MP3MetadataChanger
//
//  Created by ArtemZ on 3/16/19.
//  Copyright © 2019 ArtemZ. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char tag[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[30];
    unsigned char genre;
} MetadataMP3;

int main(int argc, const char * argv[]) {
    
    FILE *mp3File;
    mp3File = fopen("TestFile.mp3", "rb+");
    
    char command[256];
    
    if (mp3File == NULL) {
        
        printf("mp3 file is not opening.\n");
        exit(0);
        
    } else {
        
        MetadataMP3 metadataStructure;
        
        fseek(mp3File, -sizeof(MetadataMP3), SEEK_END);
        
        if (fread(&metadataStructure, sizeof(MetadataMP3), 1, mp3File) != 1) {
            
            printf("Metadata can not be obtained\n");
            exit (0);
        }
        
        if (memcmp(metadataStructure.tag, "TAG", 3) == 0) {
            
            printf("Title: %.30s\n", metadataStructure.title);
            /*printf("Enter new title: ");
            scanf("%s", metadataStructure.title);*/
            
            printf("Artist: %.30s\n", metadataStructure.artist);
            /*printf("Enter new Artist: ");
            scanf("%s", metadataStructure.artist);*/
            
            printf("Album: %.30s\n", metadataStructure.album);
            /*printf("Enter new album: ");
            scanf("%s", metadataStructure.album);*/
            
            printf("Year: %.4s\n", metadataStructure.year);
            /*printf("Enter new year: ");
            scanf("%s", metadataStructure.year);*/
            
            if (metadataStructure.comment[28] == '\0') {
                
                printf("Comment: %.28s\n", metadataStructure.comment);
                printf("Track: %d\n", metadataStructure.comment[29]);
            }
            
            /*printf("Comment: %.30s\n", metadataStructure.comment);
            printf("Enter new comment: ");
            scanf("%s", metadataStructure.comment);*/
            
            printf("Genre: %d\n", metadataStructure.genre);
            /*printf("Enter new genre number: ");
            scanf("%d", metadataStructure.genre);*/
            
        } else {
            
            fprintf(stderr, "TAGs can not be obtained\n");
            return EXIT_FAILURE;
        }
        
        /*printf("\nWhat do you want to change?\n");
        scanf("%s", command);*/
        
        do {
        
            printf("\nWhat do you want to change?\n");
            scanf("%s", command);
            
            if (strcmp(command,"title") == 0) {
                
                printf("Enter new title: ");
                scanf("%s", metadataStructure.title);
            }
            
            if (strcmp(command,"artist") == 0) {
                
                printf("Enter new artist: ");
                scanf("%s", metadataStructure.artist);
            }
            
            if (strcmp(command,"album") == 0) {
                
                printf("Enter new album: ");
                scanf("%s", metadataStructure.album);
            }
            
            if (strcmp(command,"year") == 0) {
                
                printf("Enter new year: ");
                scanf("%s", metadataStructure.year);
            }
            
            if (strcmp(command,"comment") == 0) {
                
                printf("Enter new comment: ");
                scanf("%s", metadataStructure.comment);
            }
            
            
            
        } while ((strcmp(command, "finish")) != 0);
        
        if (fwrite(&metadataStructure, sizeof(MetadataMP3), 1, mp3File) != 1) {
            
            printf("Metadata can not be changed\n");
            exit (0);
        }
        
        fclose(mp3File);
        return 0;
    }
}

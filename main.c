#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char pagetable[16][10];
char frametable[16][10];
char shadowtable[16][10];
char nestedtable [16][10];
int frame = 0; int shadowframe=5; int nestedframe=7; int NestI = 0 ; int ShadowI = 0;
int pd; int I =0;

char converttohex(int a)
{
    char b;
    switch(a) {
        case 10 : b = 'A';
        break;
        case 11 : b = 'B';
        break;
        case 12 : b = 'C';
        break;
        case 13 : b = 'D';
        break;
        case 14 : b = 'E';
        break;
        case 15 : b = 'F';
        break;
        default: b = a + '0';
        }
    return (b);
}

void map_address()
{
    printf("Enter the process id - \n");
    char pageid[10];
    scanf("%s",pageid);
    char nestedid[10];
    char frameid[10];
    strcpy(frameid,pageid);
    strcpy(nestedid,pageid);
    printf("Enter the virtual address\n");
    char virtual1[10];
    scanf("%s",virtual1);
    strcat(pageid,virtual1);
    char Frameno = converttohex(frame);
    virtual1[2]=Frameno;
    strcat(frameid,virtual1);
    strcpy(pagetable[I],pageid);
    strcpy(frametable[I],frameid);
    char NestedFrameno = converttohex(nestedframe);
    virtual1[2]=NestedFrameno;
    strcat(nestedid,virtual1);
    strcpy(nestedtable[NestI],nestedid);
    nestedframe++; I++;
    frame++; NestI++;
}

void print_pagetable()
{
    printf("\nPid Virtual Page Number and Offset\n");
    for(int i = 0 ; i < I; i++)
        {
            char pagenumber[10];
            for(int j =0; j<9; j++)
                {
                    pagenumber[j] = pagetable[i][j+1];
                }
            printf("%c   %s\n",pagetable[i][0],pagenumber);
        }
}

void print_frametable()
{
    printf("\nPid Frame Number and Offset\n");
    for(int i = 0 ; i < I; i++)
        {
            char framenumber[10];
            for(int j =0; j<9; j++)
                {
                    framenumber[j]=frametable[i][j+1];
                }
            printf("%c   %s\n",frametable[i][0],framenumber);
        }
}

void find_page()
{
    printf("Enter the process id - \n");
    char pageid[10];
    scanf("%s",pageid);

    char nestedid[10];
    strcpy(nestedid,pageid);

    char frameid[10];
    char shadowid[10];
    strcpy(shadowid,pageid);
    strcpy(frameid,pageid);
    printf("Enter the virtual address\n");
    char virtual1[10];
    scanf("%s",virtual1);
    strcat(pageid,virtual1);
    int flag = 0; int i;

    for(i = 0 ; i < I ; i++)
        {
            if(strcmp(pageid,pagetable[i])==0)
            {
                flag = 1; break;
            }
        }
    if(flag==1)
        {
            printf("Page Hit\n");
            printf("Shadow frame will be made\n");
            printf("Physical Address is \n");
            char framenumber[10];
            for(int j =0; j<9; j++)
                {
                    framenumber[j]=frametable[i][j+1];
                }
            printf("%s\n",framenumber);
            char ShadowFrameno = converttohex(shadowframe);
            virtual1[2]=ShadowFrameno;
            strcat(shadowid,virtual1);
            strcpy(shadowtable[ShadowI],shadowid);
            ShadowI++; shadowframe++;
        }
    else
        {
            char Frameno = converttohex(frame);
            virtual1[2]=Frameno;
            printf("Page Fault, page will be mapped\n");
            printf("Nested frame will be added as well\n");
            strcat(frameid,virtual1);
            strcpy(pagetable[I],pageid);
            strcpy(frametable[I],frameid);

            char NestedFrameno = converttohex(nestedframe);
            virtual1[2]=NestedFrameno;
            strcat(nestedid,virtual1);
            strcpy(nestedtable[NestI],nestedid);
            nestedframe++; I++;
            frame++; NestI++;
            //frame++; I++;
        }
}

void shadow_page()
{
    printf("\nShadow Table");
    printf("\nPid Frame Number and Offset\n");
    for(int i = 0 ; i < ShadowI; i++)
        {
            char framenumber[10];
            for(int j =0; j<10; j++)
                {
                    framenumber[j]=shadowtable[i][j+1];
                }
            printf("%c   %s\n",shadowtable[i][0],framenumber);
        }
}

void nested_page()
{
     printf("\nNested Table");
     printf("\nPid Frame Number and Offset\n");
     for(int i = 0 ; i < NestI; i++)
        {
            char framenumber[10];
            for(int j =0; j<9; j++)
                {
                    framenumber[j]=nestedtable[i][j+1];
                }
            printf("%c   %s\n",nestedtable[i][0],framenumber);
        }
}

int main()
{
   // printf("Enter number of processes ");
    //scanf("%d",&pd);
    printf("Size of virtual address = 16 bits(For each process)\n");
    printf("Size of page = 4Kb\n");
    char choice = 'Y';
    int option;
    do
        {
            printf("1.Map an address\n2.Find page\n3.Display page table\n4.Display Frame Table\n5.ShadowTable\n6.NestedTable\n7.Exit\n");
            printf("Enter the option\n");
            scanf("%d",&option);
            switch (option)
            {
                case 1 : map_address();
                break;
                case 2 : find_page();
                break;
                case 3 : print_pagetable();
                break;
                case 4 : print_frametable();
                break;
                case 5 : shadow_page();
                break;
                case 6 : nested_page();
                break;
                case 7 : exit(0);
            }
            printf("Do you want to continue?(Y/N)");
            scanf(" %c",&choice);
        }while(choice == 'Y' || choice == 'y');
        return 0;
}

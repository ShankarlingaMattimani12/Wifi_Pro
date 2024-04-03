#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<wifi.h>
struct wifi
{
    int serial_num;
    char password[20];
    char name[20];
    int stregth_s;
    char saved[10];
};

void read_file(struct wifi wi[10], int size);
void sort_wifi(struct wifi wi[10], int size);
void sort_wifi_saved(struct wifi wi[10], int size);
void show_wifi(struct wifi wi[10], int size);
void choose_wifi(struct wifi wi[10], int size);

int main()
{
    struct wifi wi[10];
    int choice;
    read_file(wi, 10);

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Show Available Wi-Fi Networks\n");
        printf("2. Connect to a Wi-Fi Network\n");
        printf("3. Disconnect Wi-Fi Network\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("i am in case1\n");
            sort_wifi(wi, 10);
            show_wifi(wi, 10);
            break;
        case 2:
            printf("i am in case2\n");
            choose_wifi(wi, 10);
            break;
        case 3:
            printf("i am in case3\n");
            sort_wifi_saved(wi, 10);
            show_wifi(wi, 10);
            break;
        case 4:
            printf("Exiting the program. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
void read_file(struct wifi wi[10],int size)
{
    FILE *fp;
    fp=fopen("wifi.txt","r");
    if(!fp)
    {
        printf("file not found\n");
        fclose(fp);
    }
    else
    {
        printf("file opened successfully\n");
    }
    int i=0;
    while(fscanf(fp," %d %s %s %d",&wi[i].serial_num,wi[i].password,wi[i].name,&wi[i].stregth_s)!=EOF)
    {
        i++;
    }
    fclose(fp);
    for(int i=0;i<size;i++)
    {
        strcpy(wi[i].saved," ");
    }

}

void sort_wifi(struct wifi wi[10], int size)
{
    struct wifi temp;

    for (int i = 0; i < size; i++)
    {


        for (int j = i + 1; j < size; j++)
        {

            if (wi[i].stregth_s < wi[j].stregth_s)
            {
                if(strcmp(wi[i].saved,"saved"))
                {

                    temp = wi[i];
                    wi[i] = wi[j];
                    wi[j] = temp;
                }
                else
                {
                    if(strcmp(wi[j].saved,"saved")==0)
                    {
                        temp=wi[i];
                        wi[i]=wi[j];
                        wi[j]=temp;
                    }


                }
            }

        }


    }
}
void sort_wifi_saved(struct wifi wi[10],int size)
{
    printf("sort wifi by saved password\n");
    struct wifi temp1;
    int s=0;
    for (int i = 0; i < size; i++)
    {

        if (strcmp(wi[i].saved,"saved"))
        {
            continue;
        }
        else
        {

            temp1 = wi[s];
            wi[s] = wi[i];
            wi[i] = temp1;
            s++;
        }

    }
    sort_wifi(wi,size);
    return;

}

void show_wifi(struct wifi w[10],int size)
{

    for(int i=0,s=1;i<size;i++,s++)
    {
        printf("%d %s  %s %d\n",s,w[i].name,w[i].saved,w[i].stregth_s);
    }
    printf("\n");
    choose_wifi(w,size);
}


void choose_wifi(struct wifi wi[10],int size)
{
    int choose=0;
    while(1)
    {
        printf("choose wifi serial_num to connect=");
        scanf("%d",&choose);
        if(choose >10 || choose<1 )
        {
            printf("wrong wifiserial_num!\n");
        }
        else
        {
            break;
        }
    }
    char match_p[20];
    if(strcmp(wi[choose-1].saved,"saved"))
    {
        printf("enter %s password=",wi[choose-1].name);
        scanf("%s",match_p);
    }
    else
    {
        strcpy(match_p,wi[choose-1].password);
    }
    if(strcmp(match_p,wi[choose-1].password))
    {
        printf("password mismatch!\n");
        int looping=0;
        printf("for other network choose 1 or to exit 2===");
        scanf("%d",&looping);
        if(looping==1)
        {
            choose_wifi(wi,size);
        }
        else
        {
            exit(0);
        }

    }
    else
    {
        printf("%s  connected\n",wi[choose-1].name);

        strcpy(wi[choose-1].saved,"saved");
        for(int i=0;i<10;i++)
        {
            if(i==(choose-1))
            {
                continue;
            }

            printf("%s %s  %d\n",wi[i].name,wi[i].saved,wi[i].stregth_s);

        }
    }
    int l=0;
    printf("do you want to disconnect? choose 1,exit 2==");
    scanf("%d",&l);
    if(l==1)
    {
        sort_wifi_saved(wi,size);
        printf("sort wifi done\n");
        show_wifi(wi,size);

    }
    else
    {
        printf("thank you bye bye..!\n");
        exit(0);

    }

}





#include <stdio.h>
#include <string.h>

typedef struct{
  char name[32];
  int age;
  char sex[1];
}person;


void print_person(person *data,int i);
void read_person(FILE *file,person *data);
void gets_person(person *data);
void write_person(FILE *file,person *data);

int main(void){
  int n,i=0,check,mode;
  char file_name[32],*filetype;
  person data;
  FILE *file,*file_csv;

  file = fopen("name_list.dat","rb");
  fread(&n,sizeof(n),1,file);
  fclose(file);

  printf("( 表示->0, 追加->1, excelファイルを作成->2, 初期化->3 )     >>");
  scanf("%d",&mode);
  printf("\n");

  switch(mode){
    case 0: file = fopen("name_list.txt","r");         //name_list.txtを読み取って表示
            for(i=1;i<n;i++){
            read_person(file,&data);
            print_person(&data,i);
            }
            fclose(file);
            break;
    case 1: do{                                                 //
              printf("Person%2d:\n",n);
              gets_person(&data);

              file = fopen("name_list.txt","a");
              write_person(file,&data);
              fclose(file);

              printf("(終了->0 続行->1)   >>");
              scanf("%d",&check);
              printf("\n");
              i++;
              n++;
            }while(check != 0);

            file = fopen("name_list.dat","wb");
            fwrite(&n,sizeof(n),1,file);
            fclose(file);
            break;
    case 2: printf("作成するファイル名を入力  >>");
            scanf("%32s",file_name);

            if(strstr(file_name,".csv") == NULL){
              filetype = strstr(file_name,".");
              if(filetype != NULL){
                *filetype = '\0';
              }
              strcat(file_name,".csv\0");
            }

            file = fopen("name_list.txt","r");
            file_csv = fopen(file_name,"w");

            fprintf(file_csv,"番号,名前,年齢,性別\n");
            for(i=1;i<n;i++){
              read_person(file,&data);
              fprintf(file_csv,"%d,%s,%d,%s\n",i,data.name,data.age,data.sex);
            }

            fclose(file);
            fclose(file_csv);
            break;
    case 3: i=1;
            file = fopen("name_list.dat","wb");
            fwrite(&i,sizeof(i),1,file);
            fclose(file);

            file = fopen("name_list.txt","w");
            fclose(file);
            break;
  }

  return 0;
}


void print_person(person *data,int i){
  printf("Person%2d:%3d歳 %s  %s\n",i,data->age,data->sex,data->name);
  return;
}
void read_person(FILE *file,person *data){
  fscanf(file,"%s%d%s",&data->name,&data->age,&data->sex);
  return;
}
void gets_person(person *data){
  printf("名前 >>");
  scanf("%32s",&data->name);
  printf("年齢 >>");
  scanf("%d",&data->age);
  printf("性別 >>");
  scanf("%1s",&data->sex);
  return;
}
void write_person(FILE *file,person *data){
  fprintf(file,"%s %d %s ",data->name,data->age,data->sex);
}

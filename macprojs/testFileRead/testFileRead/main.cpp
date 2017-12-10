#include <cstdio>

int main() {
    
    FILE *fp, *fp2;
    char buff[255];
    
    fp = fopen("File.txt", "r");
    
    if (!fp) {
        printf("dddd");
    }
    
//    fprintf(fp, "eeeeee");
//    fscanf(fp, "%s", buff);
//    printf("1 : %s\n", buff );
//
//    fgets(buff, 255, (FILE*)fp);
//    printf("2: %s\n", buff );
//
//    fgets(buff, 255, (FILE*)fp);
//    printf("3: %s\n", buff );
//    printf("ok");
//    fclose(fp);
    
//    fp2 = fopen("FileMYYY.txt", "wr");
    fscanf(fp, "%s", buff);
    printf("%s\n", buff );
    fclose(fp);
    
    
    return 0;
}

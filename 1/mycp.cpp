#include <bits/stdc++.h>
using namespace std;

int main(int argc, char * argv[])
{
    if(argc != 3){
        cout<<"Enter the correct number of arguments"<<endl;
        exit(EXIT_FAILURE);
    }

    char * srcFile = argv[1];
    char * destFile = argv[2];

    FILE * src = fopen(srcFile,"r");

    if(!src){
        cout<<"Source file not found"<<endl;
        exit(EXIT_FAILURE);
    }

    FILE * dest = fopen(destFile,"w");
    if(!dest){
        cout<<"Destination file not found"<<endl;
        exit(EXIT_FAILURE);
    }

    char buffer[1000];
    int bytes;

    while((bytes = fread(buffer,1,1000,src)) > 0){
        if(fwrite(buffer,1,bytes,dest) != bytes){
            cout<<"Error writing to destination file"<<endl;
            fclose(src);
            fclose(dest);
            exit(EXIT_FAILURE);
        }
    }
    fclose(src);
    fclose(dest);
    cout<<"File copied successfully"<<endl;
    return 0;
}
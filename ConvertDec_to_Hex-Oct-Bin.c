//includes functions like printf and scanf, input and output functions
#include <stdio.h>
//appends strings and includes strings
#include <string.h>
//finds current time
#include <time.h>
//standard library
#include <stdlib.h>
//can be used to verify assumptions made by the program and print diagnostic messages if assumption is false
#include <assert.h>

int getInteger();
char *getDateAndTime();
void decimalToBinary(int decValue, char	binString[]);
void decimalToHex(int decValue,	char hexString[]);
void decimalToOct(int decValue,	char octString[]);
void reverseStr(char str[]);
void fillFile(char *name,int deci,char *hexString,char *octString,char *binString);

int main(){
    //Asks for Users name
    int deci = 0;
    char name[20];
    printf("Enter your name: ");
    fgets(name,20,stdin);

    //keep going until user enters x
    while(deci!=-1){
        deci = getInteger();
        int num;
        char file_name[50], saveToFile;
        FILE *filePtr;

        //Exit condition
        if(deci==-1){
            printf("Goodbye!");
            return 0;
        }

        //Outputs
        printf("\n%s",name);
        printf("Today's date: %s\n",getDateAndTime());
        printf("Decimal: %d\n", deci);
        char binString[20], hexString[20], octString[20];

        //prints hex, octal, and binary of the decimal
        decimalToBinary(deci,binString);
        decimalToOct(deci,octString);
        decimalToHex(deci,hexString);

        printf("Hexadecimal: %s\n", hexString);
        printf("Octal: %s\n", octString);
        printf("Binary: %s\n", binString);

        //asks if user wants to save to file
        char x_or_y[8];
        printf("\nSave to a file?(y/n): ");
        fgets(x_or_y,8,stdin);

        //if x_or_y equals y, then use fillFile to create a file
        if(x_or_y[0]=='y')
        {
            fillFile(name,deci,hexString,octString,binString);
        }
    }
    return 0;
}

int getInteger(){
    char num[8];
    while(num[0]!='x'){

        //asking user for inputs
        printf("Enter an Integer[1-1000000] or type x to exit: ");
        fgets(num,8,stdin);

        //if atoi is 0, continue
        if(atoi(num) == 0){
            continue;
        }

        //if atoi(num) is within 1 to 1000000, then return the integer value of user input
        if(1000000 >= atoi(num) && atoi(num) >= 1){
            return atoi(num);
        }

        //else then make a recursion and print error, as long as atoi does not equal 0
        else if (atoi(num)!=0) {
            printf("Error: %d is out of range\n", atoi(num));
            continue;
        }
    }
    return -1;
}

//this is the getDateAndTime function that finds the date and time for main
char *getDateAndTime() {
    time_t t;
    time(&t);
    return ctime(&t);
}

void decimalToBinary(int decValue, char	binString[]) {
    int i=0;
    while(decValue!=0){
       binString[i]= decValue % 2+48;
       decValue = decValue / 2;
       i++;
    }

    //set last variable to null
    binString[i] = '\0';

    //uses reverseStr function to reverse the string
    reverseStr(binString);
}

//converts decimalToHex
void decimalToHex(int decValue,	char hexString[]){
    long int quotient = decValue;
    int i=0,j,temp;
    char hexadecimalNumber[100];

    while(quotient!=0){
        temp = quotient % 16;
        // Convert integer into character
        if( temp >= 10)
            hexString[i] =temp + 55;
        else
            hexString[i] = temp + 48;

        quotient = quotient / 16;
        i++;
    }

    //set last variable to null
    hexString[i]='\0';

    //uses reverseStr function to reverse the string
    reverseStr(hexString);
}

//converts decimal to octal
void decimalToOct(int decValue,	char octString[]){
    int temp = 0;

    while (decValue!=0){
    	octString[temp] = decValue % 8 + 48;
    	decValue = decValue / 8;
        temp++;
    }
    //setting last value of octString to null
    octString[temp] = '\0';
    reverseStr(octString);

}

//reverses character array
void reverseStr(char str[]){
    //y is length of string -1 to remove null
    int x=0,y=strlen(str)-1;

    while(x<y){
        //sets temporary character to the first value of the string
        char temp=str[x];
        //sets first variable to the last variable
        str[x] = str[y];
        //sets last variable to the temporary value
        str[y] = temp;

        //increases i and decreases j
        x++;
        y--;
    }
}

//create fill file function to fill a file
void fillFile(char *name,int deci,char *hexString,char *octString,char *binString){
    char fileName[100];
    //asks for user to enter a file name
    printf("Enter file name: ");
    scanf("%s",fileName);

    //converts getDateAndTime to string
    char *timePtr=getDateAndTime();
    char currentTime[25];

    int i=0;

    //set current time to the characters in timePtr
    while(i<25){
        currentTime[i]=timePtr[i];
        i++;
    }

    //sets last value of current time to null
    currentTime[i]='\0';

    //writes in the file name given
    FILE *filePtr=fopen(fileName,"w");

    //writes all of the values in the file
    fprintf(filePtr,"%s\n",name);
    fprintf(filePtr,"Today's date: %s\n\n",currentTime);
    fprintf(filePtr,"Decimal: %d\n",deci);
    fprintf(filePtr,"Hexadecimal: %s\n",hexString);
    fprintf(filePtr,"Octal: %s\n",octString);
    fprintf(filePtr,"Binary: %s\n",binString);

    //closes the file
    fclose(filePtr);

    //tells user it saved file
    printf("File saved\n");
}

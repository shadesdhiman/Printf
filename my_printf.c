#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_ARR_SIZE 128
#define MAX_SPACE 128
int my_function(const char *fmt,...);
int my_print_int(int val);
int my_print_char(char val);
int my_print_double(double val);
int my_print_float(float val);
int my_print_str(char *val);
int main()
{
	int a =5;
	int b = 8;
	char c= 'w';
	char d = 'e';
	int e = 5226;
    float f= 6346.23;  // Mouli: This was earlier declared as double
    double g = 456.65;
    char str1[MAX_SPACE] = "sa";
    char str2[MAX_SPACE] = "My name is Shubham";



   // my_function("size of float %d\n", sizeof(float));
  //  my_function("size of double %d\n", sizeof(double));
	//printf("a =%d, b= %d, c= %c, d= %c,e=%d, f =%lf, g =%lf\n",a,b,c,d,e,f,g);
    //print("Dummy cnt is passed %d,%d,%c,%c,%d,%f,%f \n",a,b,c,d,e,f,g);

    my_function("Dummy cnt1 is passed %d, %d, %d, %s, %d \n",a,b,e,str1,a);

    my_function("Dummy cnt2 is passed %d, %d, %d,  %f, %d %s %f\n",a,b,e, g, a, str2, f);

    my_function("Dummy cnt3 is passed %d, %d, %d, %c, %c, \n",a,b,e, c, d);

    my_function("Dummy cnt4 is passed %d, %d, %d, %f, %d, %f %c\n",a,b,e, g, a, g, d);

}


int my_function(const char *fmt,...)
{
    bool StckDirDwn = true;
    char *strDirChk;

    int Numints = 1;
    int numParams;
    int *addrcnt;
    int *addrint;
    char *addrchar;
    char charParams;
    char **addrstr;
    char *strParams;
    double *addrdouble;
    double doubleParams;
    float *addrfloat;
    float floatParams;
    int paramsOffset = 0; // Mouli added it

    if((void*)&StckDirDwn >(void*)&fmt)
    {
     StckDirDwn = false;
    }
    addrcnt = (char *)((void *)&fmt);
    numParams = *addrcnt;
    //printf("The direction of the stack is downward %s \n",strDirChk);


  int len;
    len=strlen(fmt)-1;
    int i =0;
    while(len)
    {

       // printf("paramsOffset = %d\n",paramsOffset);

        if(fmt[i]=='%' && ((fmt[i+1]=='d') ||(fmt[i+1]=='q')||(fmt[i+1]=='f')||(fmt[i+1]=='c')||(fmt[i+1]=='s')))
        {
        if(fmt[i+1] =='d')
        {
            //addrint = (int *)(((void*)&fmt) + Numints*sizeof(char*));
            addrint = (int *)(((void*)&fmt) + sizeof(char*) + paramsOffset);

            //printf("addrint ->%d\n",addrint);
            numParams = *addrint;
            my_print_int(numParams);
            //Numints++;
            paramsOffset += sizeof(int);
            i++;i++;
        }

        if(fmt[i+1] =='s')
        {
            addrstr = (char *)(((void*)&fmt) + sizeof(char*) + paramsOffset);
           // printf("addrstr ->%d\n",addrstr);
            strParams = *addrstr;
            my_print_str(strParams);
            //Numints++;
            paramsOffset += sizeof(int); // though char is passed into the stack, on the stack a char occupies a size of an int
            i++;i++;
        }

         if(fmt[i+1] =='c')
        {
            //addrchar = (char *)(((void*)&fmt) + Numints*sizeof(char*));
            addrchar = (char *)(((void*)&fmt) + sizeof(char*) + paramsOffset);

           // printf("addrchar ->%d\n",addrchar);
            charParams = *addrchar;
            my_print_char(charParams);
            //Numints++;
            paramsOffset += sizeof(int); // though char is passed into the stack, on the stack a char occupies a size of an int
            i++;i++;
        }

        if(fmt[i+1] =='f')
        {
            addrdouble = (double *)(((void*)&fmt) + sizeof(char*) + paramsOffset);
            //printf("addfloat ->%d\n",addrdouble);
            doubleParams = *addrdouble;
            my_print_double(doubleParams);
            //Numints++;
            paramsOffset += sizeof(double);
            i++;i++;
        }

        if(fmt[i+1] =='q')
        {
            addrfloat = (float *)(((void*)&fmt) + sizeof(char*) + paramsOffset);
           //printf("addrdouble ->%d\n",addrfloat);
            floatParams = *addrfloat;
            my_print_float(floatParams);
           // Numints++;
            paramsOffset += sizeof(float);
            i++;i++;
        }
        else
        {
            if(i<strlen(fmt))
            {

                printf("%c",fmt[i]);

            }

        }
        }
        else {
            if(i<strlen(fmt))
            {

                printf("%c",fmt[i]);

            }
            }

        len--;
        i++;

    }
}

int my_print_int(int val)
{
    char valBuf[MAX_ARR_SIZE];
    int numChar = 0;
    itoa(val,valBuf,10);
    numChar = strlen(valBuf);
    int i = 0;
    while(numChar)
    {
        putchar(valBuf[i]);
        i++;
        numChar--;
    }
    //putchar('\n');

    return 0;
}

int my_print_char(char val)
{
    putchar(val);
   // putchar('\n');  // Mouli, you should only print out the value, do not add \n

    return 0;
}

int my_print_double(double val)
{
    char valBuf[MAX_ARR_SIZE];
    int numChar = 0;
    gcvt(val,5,valBuf);
    numChar = strlen(valBuf);
    int i = 0;
    while(numChar)
    {
        putchar(valBuf[i]);
        i++;
        numChar--;
    }
    //putchar('\n');

    return 0;
}

int my_print_str(char *val)
{
    int i=0;
while(val[i]!='\0')
{


    putchar(val[i]);
    i++;
}
}


int my_print_float(float valFloat)
{
    // val = (double)val;
    double val = valFloat;   // Mouli
    char valBuf[MAX_ARR_SIZE];
    int numChar = 0;
    gcvt(val,5,valBuf);
    numChar = strlen(valBuf);
    int i = 0;
    while(numChar)
    {
        putchar(valBuf[i]);
        i++;
        numChar--;
    }
    //putchar('\n');

    return 0;
}

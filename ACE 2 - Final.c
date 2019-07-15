/**************************************************************************
 *
 * Filename: ACE2.c
 *
 * Synopsis: ACE 2 is a CPU performance calculator.
 *
 * Purpose: A performance calculator that prompts the user for input.
			From the input the program determines if the input is 
			valid and if it has enough factors to provide a performance 
			table. If it does not it will continue to prompt the user 
			for input until it does.
**************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 7
#define INERR -1
#define UNCHANGED 0
#define MAXIN 4096
#define ERROR "Invalid input has been detected - please re-enter"
#define OOR "Number is not within allowed range - please re-enter"
#define VERSION "ACE 2 v2.0 Created by Christopher Crawford. Last Update 22/11/2015"

/*Datatypes defined here*/
typedef struct{
	double input;
}factors_CPUA;

typedef struct{
    double range[7];
}inputRange;

typedef struct{
    double input;
}factors_CPUB;

/*Prototyping methods*/
void display(const char *q[], double *f, inputRange *r);
void calcIC(double *f);
void calcCPI(double *f);
void calcCC(double *f);
void calcCR(double *f);
void calcCP(double *f);
void calcMIPS(double *f);
void calcET(double *f);
void rangeCheck(inputRange *r);
double GetDouble();
void outputResults(double *f);
void cloneCPU(double *f);

int main()
{
    printf(VERSION"\n\n");
    /*List of methods being called*/
    const char* question[7];
    factors_CPUA factor[7];
    factors_CPUB factorB[7];
    inputRange range[7];
    rangeCheck(range);
    display(question, factor, range);
    calcIC(factor);
    calcCPI(factor);
    calcCC(factor);
    calcCR(factor);
    calcCP(factor);
    calcMIPS(factor);
    calcET(factor);
    outputResults(factor);
    cloneCPU(factor);

    return 0;
}

void display(const char *q[], double *f, inputRange *r){
    int i;

    /*Outputs question along with an allowed input range for the user*/
    q[0] = "IC\t(1e+02...1e+09)";
	q[1] = "CPI\t(1e-01...1e+02)";
	q[2] = "CC\t(1e+02...1e+10)";
	q[3] = "CR_GHz\t(1e-01...1e+01)";
	q[4] = "CP_ns\t(1e-01...1e+01)";
	q[5] = "MIPS\t(1e+00...1e+05)";
	q[6] = "ET_sec\t(1e-09...1e+03)";

    /*Value initialization*/
	for(i=0; i < SIZE; i++){
        f[i] = -1;
	}

    /*prints out a question for the user to respond with input,
    the input is checked to see if it has changed from its
    initialized state of -1 if it has not the program returns an
    error and will ask for the input again unless it has been skipped
    then the program will enter an UNCHANGED value of 0 for said specific input,
    if input is valid it checks to see if it is in range, if so the value is stored
    else it will inform the user with OOR and continue to ask for input*/
	for(i = 0; i < SIZE; i++){
        printf("%s", q[i]);
         while(f[i] == INERR){
            f[i] = GetDouble();

            if(f[i] == -1)
            {
                printf(ERROR "\n");
                printf("%s", q[i]);
            }
            else if((f[i] < r[i].range[0] || f[i] > r[i].range[1]) && f[i] != 0)
            {
                f[i] = -1;
                printf(OOR "\n");
                printf("%s", q[i]);
            }
         }
	}
	return;
}

void calcIC(double *f){
    /*Looks at all possible combinations of calculations*/
    if(f[2] != 0 && f[1] !=0){
        f[0] = f[2] / f[1];

    }else if(f[6] != 0 && f[1] != 0 && f[4] != 0){
        f[0] = f[6] / ((f[1] * f[4])/1e+09);

    }else if(f[6] != 0 && f[5] != 0){
        f[0] = f[6] * f[5] * 1e+06;
    }
}

void calcCPI(double *f){
    /*Looks at all possible combinations of calculations*/
    if(f[2] != 0 && f[0] != 0){
        f[1] = f[2] / f[0];
    }
}

void calcCC(double *f){
    /*Looks at all possible combinations of calculations*/
    if(f[0] != 0 && f[1] != 0){
        f[2] = f[0] * f[1];

    } else if (f[6] !=0 && f[3] != 0){
        f[2] = f[6] * f[3] * 1e+09;

    }else if (f[6] != 0 && f[1] != 0 && f[5] != 0){
        f[2] = (f[6] * f[1] * f[5]) * 1e+06;
    }

}

void calcCR(double *f){
    /*Looks at all possible combinations of calculations*/
    if(f[2] != 0 && f[6] != 0){
        f[3] = (f[2] / f[6]) / 1e+09;

    }else if(f[4] != 0){
        f[3] = 1 / f[4];
    }
}

void calcCP(double *f){
    /*Looks at all possible combinations of calculations*/
    if(f[3] != 0){
        f[4] = 1 / f[3];

    }else if(f[6] != 0 && f[2] != 0){
        f[4] = (f[6] * 1e+09) / f[2];
    }

}

void calcMIPS(double *f){
    /*Looks at all possible combinations of calculations*/
    if(f[0] != 0 && f[6] != 0){
        f[5] = f[0] / (f[6] * 1e+06);

    }else if(f[2] != 0 && f[1] !=0 && f[6] != 0){
        f[5] = (f[2] / f[1]) / (f[6] * 1e+06);

    }else if(f[3] != 0 && f[1] != 0){
        f[5] = (f[3] * (1e+09/1e+06)) / f[1];
    }
}

void calcET(double *f){
    /*Looks at all possible combinations of calculations*/
    if(f[2] != 0 && f[4] != 0){
        f[6] = (f[2] * f[6]) / 1e+09;

    }else if( f[0] != 0 && f[1] != 0 && f[4] != 0){
        f[6] = f[0] * f[1] * (f[4] / 1e+09);

    }else if(f[0] != 0 && f[5] != 0){
        f[6] = f[0] / (f[5] * 1e+06);
    }
}

/*Storage for different ranges to be checked against user
  input*/
void rangeCheck(inputRange *r){
    /* .range[0] = lower range specific to each individual input
       .range[1] = upper range specific to each individual input*/
    r[0].range[0] = 1e+02;
    r[0].range[1] = 1e+09;

    r[1].range[0] = 1e-01;
    r[1].range[1] = 1e+02;

    r[2].range[0] = 1e+02;
    r[2].range[1] = 1e+10;

    r[3].range[0] = 1e-01;
    r[3].range[1] = 1e+01;

    r[4].range[0] = 1e-01;
    r[4].range[1] = 1e+01;

    r[5].range[0] = 1e+00;
    r[5].range[1] = 1e+05;

    r[6].range[0] = 1e-09;
    r[6].range[1] = 1e+03;
    return;
}

/*Method created by Duncan Smeed*/
double GetDouble() {
  static char input[MAXIN];
  char last;
  double result;

  fgets(input,MAXIN,stdin);

  if ('\n' == input[0]) return(UNCHANGED);
  if ((sscanf(input,"%lf%c",&result,&last) < 2)) return(INERR);
  if ('\n' != last) return(INERR);
  return(result);
}

/*Prints each value out and formats according to what it is*/
void outputResults(double *f){
    printf("\nCPU A Performance Table\n");
    printf("IC_#\tCPI_#\tCC_#\tCR_GHz\tCP_ns\tMIPS\tET_sec\n");
    printf("%.0e\t%.0lf\t%.0e\t%.1lf\t%.2lf\t%.0e\t%.0lf",
           f[0],f[1],f[2],f[3],f[4],f[5],f[6]);
}

/*Will prompt user to select either Y or N, if Y code will run
to clone data to CPU B, if N then program will close.*/
void cloneCPU(double *f){
    char uInput;
    printf("\nClone to use with CPU B [Y/N]?");
    scanf("%c", &uInput);
    if(uInput == 'Y' || uInput == 'y'){
        printf("To be Added");
    }else{
        printf("Program Closing...");
    }
}


/*****************Program Output*****************/
/*ACE 2 v2.0 Created by Christopher Crawford. Last Update 22/11/2015

IC      (1e+02...1e+09)1000000000
CPI     (1e-01...1e+02)1
CC      (1e+02...1e+10)
CR_GHz  (1e-01...1e+01)1
CP_ns   (1e-01...1e+01)
MIPS    (1e+00...1e+05)
ET_sec  (1e-09...1e+03)

CPU A Performance Table
IC_#    CPI_#   CC_#    CR_GHz  CP_ns   MIPS    ET_sec
1e+009  1       1e+009  1.0     1.00    1e+003  0
Clone to use with CPU B [Y/N]?n
Program Closing...*/
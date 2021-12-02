#include "input.h"
/***************************************************************************************************
Command Instructions
***************************************************************************************************/
//To Compile: make
//To Run: ./project c17.isc 
/***************************************************************************************************
 Main Function
***************************************************************************************************/
int main(int argc,char **argv)
{
LIST* Dfront = NULL;


FILE *Isc,*Pat,*Res, *fwrite;                  //File pointers used for .isc, .pattern, and .res files
int Npi,Npo,Tgat;                     //Tot no of PIs,Pos,Maxid,Tot no of patterns in.vec,.fau
GATE *Node;                           //Structure to store the ckt given in .isc file 
static PATTERN p_vect[Mpt]; 
clock_t Start,End;                    //Clock variables to calculate the Cputime
double Cpu;                           //Total cpu time
int i,j;                              //Temporary variables



/****************PART 1.-Read the .isc file and store the information in Node structure***********/
Npi=Npo=Tgat=0;                                //Intialize values of all variables
Isc=fopen(argv[1],"r");                        //File pointer to open .isc file 
Node=(GATE *) malloc(Mnod * sizeof(GATE));     //Dynamic memory allocation for Node structure
Tgat=ReadIsc(Isc,Node);                        //Read .isc file and return index of last node
fclose(Isc);                                   //Close file pointer for .isc file
PrintGats(Node,Tgat);                          //Print the information of each active gate in Node structure after reading .isc file
CountPri(Node,Tgat,&Npi,&Npo);                 //Count the No of Pis and Pos
printf("\n\nNpi: %d Npo: %d\n",Npi,Npo);       //Print the no of primary inputs and outputs
/***************************************************************************************************/
int a;
fwrite=fopen("output.txt","w");
Pat=fopen(argv[2],"r");                          


nodeValuesFor returnBack;
int IdOfFault, ValueOfFault;
int number, number1;
int faultId;
int faultValue;
int POnodes[1000];
int result1;
int count1=0;
int count2=0;
float faultCoverage;
int totalCount, totalFaults;
// PrimaryOutput( Tgat, Node, POnodes);
//int size;
 
//fwrite=fopen("output.txt","w");

/***************************************************************************************************
 ************************************************************************************************/
//PODEM_recursion(POnodes, Node , Tgat, &Dfront);

// IdOfFault=156;
// ValueOfFault=1;
// result1= PODEM_recursion(POnodes, Node , Tgat, &Dfront, IdOfFault,ValueOfFault);
// if(result1 == 1) 
// {   fprintf(fwrite, "\n  %d/SAF %d \t", IdOfFault, ValueOfFault);
//     printTestPattern(Tgat, Node, faultValue,fwrite);
//     printf("\n  %d/SAF %d \t", IdOfFault, ValueOfFault);
//     printTestPattern(Tgat, Node, faultValue,fwrite);
// }

for(number=1; number<=Tgat; number++)
{   
    IdOfFault=number;
    ValueOfFault=0;
        // IdOfFault=19;
    // ValueOfFault=1;
    result1= PODEM_recursion(POnodes, Node , Tgat, &Dfront, IdOfFault,ValueOfFault);
    if(result1 == 1) 
    {   fprintf(fwrite, "\n  %d/SAF %d \t", IdOfFault, ValueOfFault);
        printTestPattern(Tgat, Node, faultValue,fwrite);
        count1= count1+1;
    }
    for(number1=1; number1<=Tgat; number1++)
    {   
        Node[number1].Val =2;
        //InitiGat(Node, number1);
    }
}   


/*************************Repeat for s-s1- fault ***********************/
for(number=1; number<=Tgat; number++)
{   
    IdOfFault=number;
    ValueOfFault=1;
        // IdOfFault=19;
    // ValueOfFault=1;
    result1= PODEM_recursion(POnodes, Node , Tgat, &Dfront, IdOfFault,ValueOfFault);
    if(result1 == 1) 
    {   fprintf(fwrite,"\n  %d/SAF %d \t", IdOfFault, ValueOfFault);
        printTestPattern(Tgat, Node, faultValue, fwrite);
        count2= count2+1;
    }
    for(number1=1; number1<=Tgat; number1++)
    {   
        Node[number1].Val =2;
        //InitiGat(Node, number1);
    }
}   

totalCount= count1 + count2;
printf("the toal faults detected are %d \n",totalCount);
totalFaults= Tgat *2;
faultCoverage= (totalCount / (float)totalFaults) * 100;
printf("The fault coverage is %f", faultCoverage);

// if(PODEM_recursion(POnodes, Node , Tgat))
// {
//     printf("PODEM is successful");
//     for (i=0; i<Tgat; i++)
//         {
//             if(Node[i].Type == INPT)
//             {
//                 printf("the test pattern is %d", Node[i].Val);
//             }
//             else    
//             {
//                 printf("The  fault is untestable");
//             }
//         }
    
    
// }   






/***************************************************************************************************/
fclose(fwrite);
ClearGat(Node,Tgat);  free(Node);                                      
return 0;
}//end of main
/****************************************************************************************************************************/




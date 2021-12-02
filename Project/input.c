#include "input.h"
#include <stdio.h>

nodeValuesFor object;

/***************************************************************************************************
Insert an element "X" at end of LIST "Cur", if "X" is not already in "Cur". 
If the "Cur" is Null, it creates a single element List using "X"
***************************************************************************************************/
void InsertEle(LIST **Cur, int X)
{
  LIST *tl = NULL;
  LIST *nl = NULL;

  if ((tl = (LIST *)malloc(sizeof(LIST))) == NULL)
  {
    printf("LIST: Out of memory\n");
    exit(1);
  }
  else
  {
    tl->Id = X;
    tl->Next = NULL;
    if (*Cur == NULL)
    {
      *Cur = tl;
      return;
    }
    nl = *Cur;
    while (nl != NULL)
    {
      if (nl->Id == X)
      {
        break;
      }
      if (nl->Next == NULL)
      {
        nl->Next = tl;
      }
      nl = nl->Next;
    }
  }
  return;
} //end of InsertEle
/***************************************************************************************************
Delete an element "X" from LIST "Cur",
***************************************************************************************************/
void DeleteEle(LIST **Cur, int X)
{
  LIST *fir = (*Cur);
  LIST *lst = NULL;

  if (fir == NULL)
    return;
  while ((fir->Id != X) && (fir != NULL))
  {
    lst = fir;
    fir = fir->Next;
  }
  if (fir != NULL)
  {
    if (lst == NULL)
    {
      (*Cur) = (*Cur)->Next;
    }
    else
    {
      lst->Next = fir->Next;
    }
    free(fir);
  }
  else
  {
    return;
  }
  return;
} //end of DeleteEle
/***************************************************************************************************************************
Return 1 if the element "x" is present in LIST "Cur"; Otherwise return  0  
*****************************************************************************************************************************/
int FindEle(LIST *Cur, int X)
{
  LIST *temp = NULL;

  temp = Cur;
  while (temp != NULL)
  {
    if (temp->Id == X)
      return 1;
    temp = temp->Next;
  }
  return 0;
} //end of FindEle
/***************************************************************************************************
Print the elements in LIST "Cur"          
***************************************************************************************************/
void PrintList(LIST *Cur)
{
  LIST *tmp = Cur;

  while (tmp != NULL)
  {
    printf("%d  ", tmp->Id);
    tmp = tmp->Next;
  }
  return;
} //end of PrintList
/***************************************************************************************************
Count the total number  of elements in LIST "Cur"          
***************************************************************************************************/
int CountList(LIST *Cur)
{
  LIST *tmp = Cur;
  int size = 0;

  while (tmp != NULL)
  {
    size++;
    tmp = tmp->Next;
  }
  return size;
} //end of PrintList
/***************************************************************************************************
Free all elements in  LIST "Cur"  
***************************************************************************************************/
void FreeList(LIST **Cur)
{
  LIST *tmp = NULL;

  if (*Cur == NULL)
  {
    return;
  }
  tmp = (*Cur);
  while ((*Cur) != NULL)
  {
    tmp = tmp->Next;
    free(*Cur);
    (*Cur) = tmp;
  }
  (*Cur) = NULL;
  return;
} //end of FreeList
/***************************************************************************************************
Initialize the paricular member of GATE structure
***************************************************************************************************/
void InitiGat(GATE *Node, int Num)
{
  Node[Num].Name = (char *)malloc(Mnam * sizeof(char)); //Dynamic memory allocation for an array
  bzero(Node[Num].Name, Mnam);                          //Clearing the string
  Node[Num].Type = Node[Num].Nfi = Node[Num].Nfo = Node[Num].Mark = 0;
  Node[Num].Val = 2;
  Node[Num].Fin = Node[Num].Fot = NULL;
  //Node[Num].Rpath=Node[Num].Fpath=NULL;
  return;
} //end of InitiGat
/***************************************************************************************************
Print all contents(attribute) of all active member of GATE structure(DdNodes are not printed)
***************************************************************************************************/
void PrintGats(GATE *Node, int Tgat)
{
  int i;

  printf("\nId\tName\tType\t#In\t#Out\tMark\tValue\t\tFanin\t\tFanout");
  for (i = 1; i <= Tgat; i++)
  {
    if (Node[i].Type != 0)
    {
      printf("\n%d\t%s\t%d\t%d\t%d\t%d\t%d\t\t", i, Node[i].Name, Node[i].Type, Node[i].Nfi, Node[i].Nfo, Node[i].Mark, Node[i].Val);
      PrintList(Node[i].Fin);
      printf("\t\t");
      PrintList(Node[i].Fot);
    }
  }
  return;
} //end of PrintGats
/***************************************************************************************************
Free the memory of all contents of all members of GATE structure(DdNodes are already cleared)
***************************************************************************************************/
void ClearGat(GATE *Node, int Tgat)
{
  int i;

  for (i = 1; i <= Tgat; i++)
  {
    free(Node[i].Name);
    Node[i].Type = Node[i].Nfi = Node[i].Nfo = Node[i].Mark = Node[i].Val = 0;
    FreeList(&Node[i].Fin);
    FreeList(&Node[i].Fot);
  }
  return;
} //end of ClearGat
/***************************************************************************************************
Count the Total Number of Primary inputs and outputs
***************************************************************************************************/
void CountPri(GATE *Node, int Tgat, int *Npi, int *Npo)
{
  int i, j, k;

  i = j = k = 0;
  for (i = 1; i <= Tgat; i++)
  {
    if (Node[i].Type != 0)
    {
      if (Node[i].Nfi == 0)
      {
        j++;
      }
      if (Node[i].Nfo == 0)
      {
        k++;
      }
    }
  }
  *Npi = j;
  *Npo = k;
  return;
} //end of CountPri
/***************************************************************************************************
Convert (char *) type read to (int)     
***************************************************************************************************/
int AssignType(char *Gtyp)
{
  if ((strcmp(Gtyp, "inpt") == 0) || (strcmp(Gtyp, "INPT") == 0))
    return 1;
  else if ((strcmp(Gtyp, "from") == 0) || (strcmp(Gtyp, "FROM") == 0))
    return 2;
  else if ((strcmp(Gtyp, "buff") == 0) || (strcmp(Gtyp, "BUFF") == 0))
    return 3;
  else if ((strcmp(Gtyp, "not") == 0) || (strcmp(Gtyp, "NOT") == 0))
    return 4;
  else if ((strcmp(Gtyp, "and") == 0) || (strcmp(Gtyp, "AND") == 0))
    return 5;
  else if ((strcmp(Gtyp, "nand") == 0) || (strcmp(Gtyp, "NAND") == 0))
    return 6;
  else if ((strcmp(Gtyp, "or") == 0) || (strcmp(Gtyp, "OR") == 0))
    return 7;
  else if ((strcmp(Gtyp, "nor") == 0) || (strcmp(Gtyp, "NOR") == 0))
    return 8;
  else if ((strcmp(Gtyp, "xor") == 0) || (strcmp(Gtyp, "XOR") == 0))
    return 9;
  else if ((strcmp(Gtyp, "xnor") == 0) || (strcmp(Gtyp, "XNOR") == 0))
    return 10;
  else
    return 0;
} //end of AssignType
/***************************************************************************************************
 Function to read the Bench Mark(.isc files)
***************************************************************************************************/
int ReadIsc(FILE *Isc, GATE *Node)
{
  char types[Mtyp], name[Mnam], lines[Mlin], SNfo[Mlin], SNfi[Mlin], path[Mlin];
  int ch, i, index, Nfo, Nfi, Gtyp, fid;
  int pos = 0;

  for (i = 0; i < Mnod; i++)
  {
    InitiGat(Node, i);
  }

  do
    fgets(lines, Mlin, Isc);
  while (lines[0] == '*');

  while (!feof(Isc))
  {

    sscanf(lines, "%d %s %s %s %s ", &index, name, types, SNfo, SNfi);

    strcpy(Node[index].Name, name);

    Gtyp = AssignType(types);
    Node[index].Type = Gtyp;

    if (Node[index].Type == FROM)
    {
      Nfo = Nfi = 1;
      strcpy(path, SNfo);
    }

    else
    {
      Nfo = strtol(SNfo, NULL, 10);
      Nfi = strtol(SNfi, NULL, 10);
    }
    if (index > pos)
    {
      pos = index;
    }
    Node[index].Nfo = Nfo;
    Node[index].Nfi = Nfi;

    switch (Node[index].Type)
    {
    case INPT:
      break;
    case BUFF:
    case NOT:
    case AND:
    case NAND:
    case OR:
    case NOR:
    case XOR:
    case XNOR:
      for (i = 1; i <= Nfi; i++)
      {
        fscanf(Isc, "%d", &fid);
        InsertEle(&Node[index].Fin, fid);
        InsertEle(&Node[fid].Fot, index);
      }
      fscanf(Isc, "\n");
      break;

    case FROM:
      for (i = pos; i > 0; i--)
      {
        if (Node[i].Type != 0)
        {
          if (strcmp(Node[i].Name, path) == 0)
          {
            fid = i;
            break;
          }
        }
      }

      InsertEle(&Node[index].Fin, fid);
      InsertEle(&Node[fid].Fot, index);
      break;
    }
    fgets(lines, Mlin, Isc);
  }

  return pos;
} //end of ReadIsc
/****************************************************************************************************************************/

/*******************Function To Read vector File**********************************************************/
int ReadVec(FILE *Pat, PATTERN *p_vect)
{

  char str[Mpi];
  int a = 0;

  while (!feof(Pat))
  {

    fgets(str, Mpi, Pat);
    if (*str != '\0')
    {
      strcpy(p_vect[a].PI, str);
      a++;
    }
  }
  return a;
}
/***************************  Simulation of Circuit **************************************/

int and [5][5] = {
    {
        0,
        0,
        0,
        0,
        0,
    },
    {0, 1, 2, 3, 4},
    {0, 2, 2, 2, 2},
    {0, 3, 2, 3, 0},
    {0, 4, 2, 0, 4}};

int or [5][5] = {
    {0, 1, 2, 3, 4}, {1, 1, 1, 1, 1}, {2, 1, 2, 2, 2}, {3, 1, 2, 3, 1}, {4, 1, 2, 1, 4}};

int inv[5] = {1, 0, 2, 4, 3};

int from[5] = {0, 1, 2, 3, 4};

int charToInt(char c)
{
  int int_value;

  if (c == 'x')
  {
    int_value = 2;
  }
  else
  {
    int_value = c - '0';
  }
  return int_value;
}

char intToChar(int n)
{
  char c;
  if (n == 2)
  {
    c = 'x';
  }
  else

  {
    c = '0' + n;
  }
  return c;
}

int output(int gate, int in1, int in2)
{
  int out;
  switch (gate)
  {

  case 2:
    out = from[in1];
    break;
  case 3:
    out = from[in1];
    break;
  case 4:
    out = inv[in1];
    break;
  case 5:
  case 6:
    out = and[in1][in2];
    break;
  case 7:
  case 8:
    out = or [in1][in2];
    break;

  case 10:
  case 9:
    out = and[or [in1][in2]][or [inv[in1]][inv[in2]]];
    break;
  default:
    out = from[in1];
  }
  return out;
}

/*************************** Assign Non-Controlling values **************************************/
int nonControlling(int Type)
{
  int out;
  switch (Type)
  {

  case 2:
    out = 6;
    break;
  case 3:
    out = 6;
    break;
  case 4:
    out = 6;
    break;
  case 5:
  case 6:
    out = 1;
    break;
  case 7:
  case 8:
    out = 0;
    break;

  case 10:
  case 9:
    out = 6;
    break;
  default:
    out = 6;
  }
  return out;
}

/*************************** Print the final test Patterns **************************************/
void printTestPattern(int Tgat, GATE *node, int faultValue, FILE *fwrite)
{
  int i;
  for (i = 0; i <= Tgat; i++)
  {
    if (node[i].Val == 4 || node[i].Val == 3)
    {
      node[i].Val = !faultValue;
    }
    if (node[i].Type == INPT)
    {
      fprintf(fwrite, "%d", node[i].Val);
    }
  }
  fprintf(fwrite,"\n");
}

/***************************Check if D or D_bar is at the Primary output**************************************/
int checkPrimaryOutput(int Tgat, GATE *node)
{
  int i;
  for (i = 1; i <= Tgat; i++)
  {
    if (node[i].Fot == NULL)
    {
      int PO = i;
      if (node[PO].Val == D || node[PO].Val == D_bar)
        return 1;
    }
  }
}

/*************************** Check if a gate is a D-frontier**************************************/
int checkDfrontier(GATE *node, int node_Line, int faultId, int faultValue)
{
  LIST *Fin;
  int ret = 0;
  Fin = node[node_Line].Fin;
  int check = node[faultId].Val;
  // if (node[faultId].Val == !faultValue)
  // {
  //   if (faultValue == 0)
  //     node[faultId].Val = D;

  //   else
  //     node[faultId].Val = D_bar;
  // }


  if (node[node_Line].Val == 2)
  {
    while (Fin != NULL)
    {
      if (node[Fin->Id].Val == D || node[Fin->Id].Val == D_bar)
      {
        ret = 1;
        break;
      }
      Fin = Fin->Next;
    }
  }
  return ret;
}

/*************************** return The Current Objetive **************************************/
nodeValuesFor getObjective(GATE *node, LIST *dfront, int faultValue, int faultId)
{

  int d;
  LIST *Fin;
  object.nodeNumber = 0;
  object.nodeValue = 0;

  if (node[faultId].Val != faultValue && node[faultId].Val != 3 && node[faultId].Val != 4)
  {
    object.nodeNumber = faultId;
    object.nodeValue = inv[faultValue];
    return object;
  }

  while (dfront != NULL)
  {
    d = dfront->Id;
    Fin = node[d].Fin;
    while (Fin != NULL)
    {
      if (node[Fin->Id].Val == 2)
      {
        object.nodeNumber = Fin->Id;
        break;
      }

      Fin = Fin->Next;
    }

    object.nodeValue = nonControlling(node[d].Type);
    return object;
  }
}

/*************************** Backtrace **************************************/
nodeValuesFor Backtrace(nodeValuesFor object, GATE *node, nodeValuesFor backtraceReturns)
{
  LIST *temp;
  int a = object.nodeNumber;
  int num_inversion = 0;

  if (node[a].Type == 4 || node[a].Type == 6 || node[a].Type == 8 || node[a].Type == 10)
    num_inversion = num_inversion + 1;

  while (node[a].Nfi != 0)
  {
    temp = node[a].Fin;

    while (temp != NULL)
    {
      a = temp->Id;

      if (node[a].Val == 2)
      {

        if (node[a].Type == 4 || node[a].Type == 6 || node[a].Type == 8 || node[a].Type == 10)
          num_inversion = num_inversion + 1;
        break;
      }

      temp = temp->Next;
    }
  }

  backtraceReturns.nodeNumber = a;

  if (num_inversion % 2 == 0)
    backtraceReturns.nodeValue = object.nodeValue;

  else
    backtraceReturns.nodeValue = inv[object.nodeValue];
  return backtraceReturns;
}

/*************************** PODEM Resursion Function **************************************/
int PODEM_recursion(int *POnodes, GATE *node, int Tgat, LIST **Dfront, int IdOfFault, int ValueOfFault)

{

  int objectiveReturnID, objectiveReturnValue, faultId, faultValue;
  nodeValuesFor o, b, backtraceReturns;
  int simulateCircuit;
  int y;
  int result = 0, checkPO = 0;
  int i;
  int line;
  int number = 0;

  faultId = IdOfFault;
  faultValue = ValueOfFault;

  checkPO = checkPrimaryOutput(Tgat, node);

  if (checkPO == 1)
  {
    return 1;
  }

  o = getObjective(node, *Dfront, faultValue, faultId);
  objectiveReturnID = o.nodeNumber;
  objectiveReturnValue = o.nodeValue;

  //Dfront = NULL;
  FreeList(Dfront);

  b = Backtrace(o, node, backtraceReturns);
  node[b.nodeNumber].Val = b.nodeValue;

  simulateCircuit = simulatee(Tgat, node, b, objectiveReturnID, objectiveReturnValue, Dfront, faultId, faultValue);

  checkPO = checkPrimaryOutput(Tgat, node);
  if (checkPO == 1)
  {
    return 1;
  }

  int check3; 
  check3= node[faultId].Val;
 
  //if (node[faultId].Val != !faultValue && (node[faultId].Val == 2 || node[faultId].Val == 3 || node[faultId].Val == 4))
  if(*Dfront != NULL || node[faultId].Val == 2)
  { 
    result = PODEM_recursion(POnodes, node, Tgat, Dfront, faultId, faultValue);

    if (result == 1)
    {
      // printf("\n  %d/SAF %d \t", faultId, faultValue);
      // printTestPattern(Tgat, node, faultValue);
      return 1;
    }
  
  }

  //else if (node[faultId].Val == faultValue || *Dfront == NULL)
  //{
      b.nodeValue = !node[b.nodeNumber].Val;
      node[b.nodeNumber].Val = b.nodeValue;

      simulateCircuit = simulatee(Tgat, node, b, objectiveReturnID, objectiveReturnValue, Dfront, faultId, faultValue);
      checkPO = checkPrimaryOutput(Tgat, node);

      if (checkPO == 1)
      {
        return 1;
      }
      if(*Dfront != NULL)
      {
        result = PODEM_recursion(POnodes, node, Tgat, Dfront, faultId, faultValue);

        if (result == 1)
        {
          //printTestPattern(Tgat, node, faultValue);
          return 1;
        }
      }
    
  //}

  //else
  //{
    //b.nodeNumber = 2;
    b.nodeValue = 2;
    simulatee(Tgat, node, b, objectiveReturnID, objectiveReturnValue, Dfront, faultId, faultValue);
    return 0;
  //}
}

/***************************  Simulation of Circuit By Using the values Returned By BAcktrace **************************************/
int simulatee(int Tgat, GATE *node, nodeValuesFor backtraceReturns, int objectiveReturnID, int objectiveReturnValue, LIST **Dfront, int faultId, int faultValue)
{
  int node_Line;
  LIST *temp;
  int x, y = 0;
  int checkDfrontierFlag = 0;

  for (node_Line = 1; node_Line <= Tgat; node_Line++)
  { 
    // checkDfrontierFlag = checkDfrontier(node, node_Line, faultId, faultValue);
    
    // if (checkDfrontierFlag)
    // {
    //   InsertEle(Dfront, node_Line);
    // }
    
    if (node[node_Line].Fin != NULL)
    {
      temp = node[node_Line].Fin;
      temp = node[node_Line].Fin;
      x = node[temp->Id].Val;
      while (temp != NULL)
      {
        if (temp->Next != NULL)
        {
          y = node[temp->Next->Id].Val;

          x = output(node[node_Line].Type, x, y);
        }
        temp = temp->Next;
      }

      if (node[node_Line].Type == FROM || node[node_Line].Type == NOT || node[node_Line].Type == BUFF)
      {
        node[node_Line].Val = output(node[node_Line].Type, x, 1);
      }
      else
      {

        node[node_Line].Val = x;
      }
      if (node[node_Line].Type == NAND || node[node_Line].Type == NOR || node[node_Line].Type == XNOR)
      {
        node[node_Line].Val = inv[node[node_Line].Val];
      }
    }
    
    if (node[faultId].Val == !faultValue)
    {
      if (faultValue == 0)
        node[faultId].Val = D;

      else
        node[faultId].Val = D_bar;
    }
    
    
    checkDfrontierFlag = checkDfrontier(node, node_Line, faultId, faultValue);

    if (checkDfrontierFlag)
      InsertEle(Dfront, node_Line);
  }

  // PrintGats(node,Tgat);
}

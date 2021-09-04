#include<stdio.h>
#include<string.h>

char s[15];
int str1[4][4],com[3][10], key[3][3], a[3][3],encryptM[3][10],decryptMatrix[3][10], size = 0,columnS=0;
float inverseKey[3][3];

/*
*Method to create coolumns dynamically according to the string
*/
int countingColumn()
{
    if(size < 3)
    {
        printf("Choose a larger string");
        return 0;
    }
    else
    {
     
        if(size%3 <= 2)
        {
            return (size+2)/3;
        }
        else if(size%3 == 0 )
        {
        return size/3;
        }
    }

    return 0;
}




/*
Method to inverse the key
*/

void inverse()
{
    int i, j, k;
    float p,q;

    for( i = 0; i < 3; i++)
    {
        for( j = 0; j < 3; j++)
        {
            if(i == j)
            {
                inverseKey[i][j]=1;
            }
            else{

                inverseKey[i][j]=0;
            }
        }

    }

    for( k = 0; k < 3; k++)
    {
        for(i = 0; i < 3; i++)
        {
            p = key[i][k];
            q = key[k][k];

            for(j = 0; j < 3; j++)
            {
                if(i != k)
                {
                    key[i][j] = key[i][j]*q - p*key[k][j];
                    inverseKey[i][j] = inverseKey[i][j]*q - p*inverseKey[k][j];
                }
            }
        }
    }

    for( i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            inverseKey[i][j] = inverseKey[i][j]/key[i][i];
        }
    }

    printf("\n\n**********Inverse Matrix is******* : \n");
    for( i = 0; i < 3; i++)
    {
        for( j = 0; j < 3; j++)
        {
            printf("%f ",inverseKey[i][j]);
        }
        printf("\n");
    }
}




/*
*Method to change the string into matrix having row of 3
*Check if convert to the correct matrix
*/


void messageEncrypt(char * str)
{
    int j = 0, k = 0, m=0;
    int code  = 125;
    
    
    for(int i = 0; i < 3; i++)
    {
       
        if(str[k] != '\0')
        {
        
            str1[i][j] = str[k] - 97;
            com[i][j] = str1[i][j];
        
        }   
        else
        {  
            while(i<3)
            {
                if(i >= 1)
                {
                    com[i][j] = code;
                    i++;
                }
                else{
                    break;
                }        
            }
            break;          
        }
        
        
        if(i == 2)
        {
            i = -1;
            j++;
        }
     k++;
    }

    columnS = countingColumn();//dynamically counting how many columns will be there
    printf("printing the matrix\n");
    for(int r = 0; r < columnS; r++)
    {
        for(int p = 0; p < 3;  p++)
        {
            
            printf("str1[%d][%d] :%d\n",p,r,com[p][r]);
        }
    }
    

    printf("\nIf converted matrix of string is correct\n");
    for(int c = 0; c < columnS; c++)
    {
        for(int r = 0; r < 3; r++)
        {
            if(com[r][c] > 120)
            {
                s[m] = '\0';
                break;
            }
            else
            {
                s[m] = com[r][c] + 97;
                m++;
            }
           
        }
    }
    s[m] = '\0';
    printf("%s\n",s);

   
}


/*
8Method to the encrypt the string matrix by multiplying with key matrix
*YOu can your encrypted string too

*/
void encrypt()
{
    int i, j, k, sum = 0, m = 0;
   for(i = 0; i < 3; i++){

       for(j = 0; j < columnS; j++)
       {
           for(k = 0; k < 3; k++)
           {
              encryptM[i][j] = encryptM[i][j] + a[i][k]*com[k][j];
           }
            
       }
   }

   //iS encrypted matrix in correct from
   printf("\n********Encrypted matrix************\n");
    for(i = 0; i < 3; i++){

       for(j = 0; j < columnS; j++){

            printf("%d ",encryptM[i][j]);
       }
       printf("\n");
    }
    printf("\n\nEncrypted String\n");
     for(int c = 0; c < columnS; c++)
    {
        for(int r = 0; r < 3; r++)
        {
            s[m] = encryptM[r][c] ;
            m++;          
           
        }
    }
    s[m] = '\0';
    printf("%s\n",s);
   
}


/*
*Method to decrypt the encrypted matrix by multiplying it with inverse of key matrix
*/

void decrypt()
{
    inverse();
    int i, j, k,m = 0,sum = 0;
    for(i = 0; i < 3; i++){

        for(j = 0; j < columnS; j++)
        {
            for(k = 0; k < 3; k++)
            {
                decryptMatrix[i][j] = decryptMatrix[i][j] + inverseKey[i][k]*encryptM[k][j];
            }
                
        }
    } 
    printf("\nPrinting decrypt matrix\n");
    for(i = 0; i < 3; i++){

       for(j = 0; j < columnS; j++){

            printf("%d ",decryptMatrix[i][j]);
       }
       printf("\n");
    }
    

    printf("\n\nPrinting the decrypted string:\n");
     for(int c = 0; c < columnS; c++)
    {
        for(int r = 0; r < 3; r++)
        {
            if(com[r][c] > 120)
            {
                s[m] = '\0';
                break;
            }
            else
            {
                s[m] = decryptMatrix[r][c] + 97;
                m++;
            }
           
        }
    }
    s[m] = '\0';
    printf("\t%s\n",s);
    printf("\n\n");
}


 
int main()
{
   
    int choice, flag = 0;
    char str[20];
    
    int t = 1;
    while(t == 1)
    {
        printf("Choose the option:\n1.Encrypt\n2.Decrypt\n3.Download the encrypted value(Method will be soon available)\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
             flag = 1;
             printf("\nEnter the string you want to encrypt\n");
             scanf("%s",str);
             size = strlen(str);
             messageEncrypt(str);
             printf("Enter a 3x3 matrix to be used as a key(//It should be invertible which means matrix determinant shouldn't be zero//)\n");
             for(int i = 0; i < 3; i++)
             {
                 for(int j = 0; j < 3; j++)
                 {
                     scanf("%d",&a[i][j]);
                     key[i][j] = a[i][j];         
                 }
             }
             encrypt();
             break;

            case 2:

             if(flag == 0)
             {
                 printf("\nFirst encrypt a value\n");
                 break;
             }
             else
             {
                 decrypt();
                 break;
             }
             

            default:
              printf("Wrong entry");
        }

        printf("\n\nWould you like to continue?(1 for yes | 0 for no)\n");
        scanf("%d",&t);
    }

    printf("\n\n"); 

   
   
}


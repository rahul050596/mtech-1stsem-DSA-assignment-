#include<stdio.h>
#include<stdlib.h>
struct operation {
	int cofficent;
	int power;
    char operator;
};

int number_of_terms1,number_of_terms2,number_of_terms3,number_of_terms4;
struct operation *operation1, *operation2, *operation3, *operation4;
int print_polynomial(struct operation operation[],int number_of_terms)
{
	int i=0;
	while(i<number_of_terms)
	{
		printf("((%d * X)^ %d)", operation[i].cofficent,operation[i].power);
		if(i+1<number_of_terms)
		{
			printf("%c",operation[i].operator);
		}
		i++;
	}
	printf("\n");
	return 0;
}
// this function is used for sort a polynomial expression in decreasing order based on power of variable
int quick_sort(struct operation operation[],int low,int high,int number_of_terms)
{
	int i,j,k,pivot,pivot_term_power;
	struct operation temp;
	char temp_operator;
	if(low<high)
	{
		pivot=high;
		i=low;
		j=i;
		pivot_term_power=operation[pivot].power;
		while(i<high)
		{
		  if(operation[i].power>=pivot_term_power)
		  {
			
			if(operation[i].power>pivot_term_power)
			{
				temp=operation[j];
				operation[j]=operation[i];
				operation[i]=temp;
				j++;
			}
			else
			{
				if(i>0)
				{
					operation[i-1].operator=operation[i].operator;
				}
				operation[pivot].cofficent+=operation[i].cofficent;
				for(k=i;k<number_of_terms;k++)
				{
					operation[k]=operation[k+1];
				}
				pivot--;
				high--;
				number_of_terms--;
				i--;
			}
	      }
	      i++;
		}
//if power of jth element is less than power of the element of pivot then only swap them and also their operators

		if(operation[j].power<operation[pivot].power)
		{
		  temp_operator=operation[pivot].operator;
		  operation[pivot].operator=operation[j].operator;
		  operation[j].operator=temp_operator;
		  temp=operation[pivot];
		  operation[pivot]=operation[j];
		  operation[j]=temp;
		}
		number_of_terms=quick_sort(operation,low,j-1,number_of_terms);
		number_of_terms=quick_sort(operation,j+1,high,number_of_terms);
	}
	return number_of_terms;
}

int sort_polynomial(struct operation operation[],int *number_of_terms)
{
	int i,j,temp_number_of_terms;
	temp_number_of_terms=* number_of_terms;
	* number_of_terms=quick_sort(operation,0,temp_number_of_terms-1,temp_number_of_terms);
	temp_number_of_terms= * number_of_terms;
	i=0;
	while(i<temp_number_of_terms)
	{
		if(operation[i].cofficent==0)
		{
			if(i+i<temp_number_of_terms)
			{
				operation[i]=operation[i+1];
				* number_of_terms=--temp_number_of_terms;
				i--;
			}
			else
			{
				* number_of_terms=--temp_number_of_terms;
			}
		}
		i++;
	}
	return 0;
}
//this is used for add two polynomials and return its result
struct operation * addition(struct operation operation1[],int number_of_terms1,struct operation operation2[],int number_of_terms2,int *number_of_terms)
{
	int i,j,k;
	struct operation * operation;
	operation=(struct operation *) malloc(sizeof(struct operation) * (number_of_terms1 + number_of_terms2));
	if(number_of_terms1==0)
	{
		operation = operation2;
		* number_of_terms=number_of_terms1;
	}
	else
	{
		if(number_of_terms2==0)
		{
			operation = operation1;
			* number_of_terms= number_of_terms1;
		}
		else
		{
			i=0,j=0,k=0;
			do
			{
				//if power are same add cofficient of both the terms and copy power of those terms
				if(operation1[i].power==operation2[j].power)
				{
					operation[k].cofficent=operation1[i].cofficent+operation2[j++].cofficent;
					operation[k].power=operation[i++].power;
					operation[k].operator='+';
				}
				else
				{
					if(operation1[i].power>operation2[j].power)
					{
						operation[k]=operation1[i++];
					}
					else
					{
						operation[k]=operation2[j++];
					}
				}
				k++;
			}while(i<number_of_terms1 && j<number_of_terms2);
			//copy any left term from first polynomial expression
			while(i<number_of_terms1)
			{
				operation[k++]=operation1[i++];
			}
			while(j<number_of_terms2)
			{
				operation[k++]=operation2[j++];
			}
			operation[k-1].operator='\0';
			* number_of_terms=k;
		}
	}
	return operation;
}
// this function multiplies two polynomial expression and return the result
struct operation * multiplication(struct operation operation1[],int number_of_terms1,struct operation operation2[],int number_of_terms2,int * number_of_terms)
{
	int i,j,k;
	// this could be maximum size of multiplication result of two polynomial
	* number_of_terms=number_of_terms1 * number_of_terms2;
	//this store the result of multiplication of two polynomials
	struct operation * operation;
	operation=(struct operation *) malloc(sizeof(struct operation) * (* number_of_terms));
	k=0;
	for(i=0;i<number_of_terms1;i++)
	{
		j=0;
		while(j<number_of_terms2)
		{
		  //multplies cofficients of both the polynomials
		  operation[k].cofficent=operation[i].cofficent * operation2[j].cofficent;
		  //add power of both the multiplied polynomial terms
		  operation[k].power=operation1[i++].power+operation2[j++].power;
		  operation[k++].operator='+';
		   	
		}
		i++;
	}
	operation[k-1].operator='\0';
	//sorting is needed here because after multiplication it require to simplify it,this will redundar terms(terms which is same power
    sort_polynomial(operation,number_of_terms);
    return operation;
}
// this function ask for polynomial expression from user
struct operation * read_polynomial(int * number_of_terms)
{
	int i,temp_number_of_terms;
	struct operation * operation;
	printf("enter the number of terms the polynomial will have: ");
	scanf("%d",&temp_number_of_terms);
	operation =(struct operation *) malloc(sizeof(struct operation) * temp_number_of_terms);
	for(i=0;i<temp_number_of_terms;i++)
	{
		printf("enter cofficient for this terms:");
		scanf("%d",&(operation[i].cofficent));
		if(i>0 && operation[i-1].operator=='-')
		{
			operation[i].cofficent=-operation[i].cofficent;
			operation[i-1].operator='+';
			
		}
		printf("enter power of this term: ");
		scanf("%d",&(operation[i].power));
		if(i+1<temp_number_of_terms)
		{
			do
			{
				printf("enter operator(+ or -):");
				scanf("%c",&(operation[i].operator));
			}while(operation[i].operator!='+'&& operation[i].operator!='-');
		}
		else
		
		{
		  operation[i].operator='\0';	
		}
	}
	* number_of_terms=temp_number_of_terms;
	return operation;
}
int main()
{
	operation1=read_polynomial(&number_of_terms1);
	
	operation2=read_polynomial(&number_of_terms2);
		printf("before sorting:\n");
	printf("expression1:\t");
	print_polynomial(operation1,number_of_terms1);
	printf("Expression2:\t");
	print_polynomial(operation2,number_of_terms2);
	sort_polynomial(operation1,&number_of_terms1);
	sort_polynomial(operation2,&number_of_terms2);
	printf("after sorting:\n");
	printf("expression1:\t");
	operation1= (struct operation *) realloc(operation1,sizeof(struct operation) * number_of_terms1);
	operation2= (struct operation *) realloc(operation2,sizeof(struct operation) * number_of_terms2);
		if(number_of_terms1> 0)
	{
		print_polynomial(operation1,number_of_terms1);
		
	}
	else
	{
		printf("expression is empty.\n");
	}
		if(number_of_terms2> 0)
	{
		print_polynomial(operation2,number_of_terms2);
		
	}
	else
	{
		printf("expression is empty.\n");
	}
	printf("-----------------------------------\n");
	printf("Addition of expression1 and expression2:\n");
	if(number_of_terms1>0|| number_of_terms2>0)
	{
		operation3=addition(operation1,number_of_terms1,operation2,number_of_terms2,&number_of_terms3);
		operation3=(struct operation *)realloc(operation3,sizeof(struct operation) * number_of_terms3);
		print_polynomial(operation3,number_of_terms3);
		
		
	}
	else
	{
		printf("addition is o \n");
	}
	printf("multiplication of expression1 & expression2:\n");
	if(number_of_terms1>0 && number_of_terms2>0)
	{
		operation4=multiplication(operation1,number_of_terms1,operation2,number_of_terms2,&number_of_terms4);
		operation4=(struct operation *)realloc(operation4,sizeof(struct operation) * number_of_terms4);
		print_polynomial(operation4,number_of_terms4);
	}
		else
	{
		printf("addition is o \n");
	}
	return 0;
}

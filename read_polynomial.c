#include<stdio.h>
#include<stdlib.h>
struct operation {
	int cofficent;
	int power;
    char operator;
};

int number_of_terms1;
struct operation *operation1;
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
	printf("before sorting:\n");
	printf("expression1:\t");
	print_polynomial(operation1,number_of_terms1);
	sort_polynomial(operation1,&number_of_terms1);
	printf("Expression1:\t");
	operation1= (struct operation *) realloc(operation1,sizeof(struct operation) * number_of_terms1);
	if(number_of_terms1> 0)
	{
		print_polynomial(operation1,number_of_terms1);
		
	}
	else
	{
		printf("expression is empty.\n");
	}
	return 0;
	
}

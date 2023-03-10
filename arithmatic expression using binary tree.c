#include<stdio.h>
#include<stdlib.h>
struct expression
{
	union
	{
		struct expression * left_sub_tree;
		int left_operand;
		
	};
	int in_left_sub_tree;
	char operator;
	int in_right_sub_tree;
	union
	{
		struct expression * right_sub_tree;
		int right_operand;
	};
};
typedef struct expression exp;
// stores no of terms an airthmatic expression has.
int number_of_terms;
// pointer to root of the binary tree
exp * root_node;
//evaluate airthmetic expression using postorder tree traversal (left,right,data)
int post_order_traversal(exp * parent)
{
	int left_operand,right_operand;
	left_operand=0;
	right_operand=0;
	if(parent -> in_left_sub_tree==1)
	{
		left_operand =post_order_traversal(parent ->left_sub_tree);
		
	}
	else
	{
		left_operand=parent -> left_operand;
		
	}
	if(parent -> in_right_sub_tree==1)
	{
		right_operand=post_order_traversal(parent -> right_sub_tree);
	}
	else
	{
		right_operand=parent -> right_operand;
	}
switch(parent -> operator)
{
	case '+':  left_operand=left_operand+right_operand;
	             break;
	case '-':   left_operand=left_operand-right_operand; 
	             break;   
    case '*':   left_operand=left_operand*right_operand;
	              break;
	case '/':   left_operand=left_operand/right_operand;
	                break;
	default:   
	           printf("no operators found");
			   break;              
				        
}
return left_operand;
}
// print airrthmetic expression using inorder tree traversal(left,data,right)
int in_order_traversal(exp * parent)
{
	if(parent -> in_left_sub_tree==1)
	{
		in_order_traversal(parent -> left_sub_tree);
		
	}
	else
	{
		printf("%d",parent -> left_operand);
		
	}
	printf("%c",parent -> operator);
	if(parent -> in_right_sub_tree==1)
	{
		in_order_traversal(parent -> right_sub_tree);
	}
	else
	{
		printf("%d",parent -> right_operand);
	}
	return 0;
}
// read and store airthmetic expression
int read_arithmatic_expression()
{
	int i,operand;
	char operator,pre_operator;
	exp * exp1, * pre_exp;
	// ask user for total numbewr of terms
	printf("how many no of terms expression is:");
	scanf("%d",&number_of_terms);
	for(i=0;i<number_of_terms;i++)
	{
		//ask user for left operand of the operator
		printf("enter operand:");
		scanf("%d",&operand);
		// if it is not last term go for operator part
		if(i+1<number_of_terms)
		{
			//ask user for operator
			do
			{
				printf("enter the operator:");
				scanf("%c",&operator);
				
			}
			while(operator != '+' && operator!='-' && operator!='*' && operator!='/');
			//create new node for recently read operator
			exp1=(exp *) malloc(sizeof(exp *));
			exp1 -> operator= operator;
			// if there are already some nodes in tree
			if(i>0)
			{
			
			// fetch previous operator from previous node
			pre_operator=pre_exp -> operator;
			//put it in switch
			switch(pre_operator)
			{
				case '+':  
				case '-': 
				           if(operator=='+'|| operator=='-')
				           {
				           	 if(pre_operator=='+'&&pre_exp -> in_left_sub_tree==1)
				           	 {
				           	 	pre_exp -> right_sub_tree=exp1;
				           	 	pre_exp-> in_right_sub_tree=1;
				           	 	exp1-> left_operand=operand;
				           	 	exp1->in_left_sub_tree=0;
				           	 	
			        	     }
			        	     else
			        	     {
			        	     	pre_exp->right_operand=operand;
			        	     	pre_exp->in_right_sub_tree=0;
			        	     	exp1->left_sub_tree=pre_exp;
			        	     	exp1-> in_left_sub_tree=1;
			        	     	root_node=exp1;
			        	     	
							 }
						   }
						   else
						   {
						   	exp1->left_operand=operand;
						   	exp1-> in_left_sub_tree=0;
						   	pre_exp-> right_sub_tree=exp1;
						   	pre_exp-> in_right_sub_tree=1;
						   }
						   break;
			    case'*':
			    case'/':   //pre->,& curr->+,- this new node will become parent of previous node
				
				            if(operator=='+'||operator=='-')
							{
								pre_exp->right_operand=operand;
								pre_exp->in_right_sub_tree=0;
								exp1->left_sub_tree=pre_exp;
								exp1->in_left_sub_tree=1;
								root_node=exp1;
								
					    	}
					    	else
					    	{
					    		if(pre_exp->in_left_sub_tree==1)
					    		{
					    			pre_exp->right_sub_tree=exp1;
					    			pre_exp->in_right_sub_tree=1;
					    			exp1->left_operand=operand;
					    			exp1->in_left_sub_tree=0;
								}
								else
								{
									pre_exp->right_operand=operand;
									pre_exp->in_right_sub_tree=0;
									exp1->left_sub_tree=pre_exp;
									exp1->in_left_sub_tree=1;
									root_node=exp1;
								}
							}
	        
	                        break;
			}
		  }
		  else
		  {
		  	//if it is first node then enter the operand left to its operator and markit as root node of tree
		  	exp1->left_operand=operand;
		  	exp1->in_left_sub_tree=0;
		  	root_node=exp1;
		  }
		  //if cuu node will be previous node for next iteration.
		  pre_exp=exp1;
		}
		else
		{
			// if it is last term then enter operand right to previous operator
			pre_exp->right_operand=operand;
			pre_exp->in_right_sub_tree=0;
		}
	}
	return 0;
}
int main()
{
	read_arithmatic_expression();
	in_order_traversal(root_node);
	printf("\t=\t");
	printf("%d\n",post_order_traversal(root_node));
	return 0;
}


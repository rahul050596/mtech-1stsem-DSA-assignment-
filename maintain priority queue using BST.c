#include<stdio.h>
#include<stdlib.h>
//this structure defines a node of binary tree.left part of node can have a subtree or an operand
struct  Queue
{
	struct Queue * left_sub_tree;
	int value;
	struct Queue * right_sub_tree;
	
};
typedef struct Queue Que;
//pointer to root of the binary tree.
Que * root_node;
//print binary search tree using inorder tree traversal.(left,data,right)
int in_order_traversal(Que * parent)
{
	if(parent -> left_sub_tree!=NULL)
	{
		in_order_traversal(parent->left_sub_tree);
		
		
	}
	printf("%d \t",parent->value);
	if(parent->right_sub_tree!=NULL)
	{
		in_order_traversal(parent->right_sub_tree);
	}
	return 0;
}
// tfunction return null when tree is empty otherwise it will return parent node of given value
Que * find(Que * root_node,int value)
{
	Que * curr_elem;
	curr_elem=root_node;
	while(curr_elem!=NULL)
	{
		// if given key is lesser than the nodes key then go down for left subtree check whether left child is the key we are looking for
		if((value<curr_elem->value)&& (curr_elem->left_sub_tree!=NULL && curr_elem-> left_sub_tree->value!=value))
		{
		  curr_elem=curr_elem->left_sub_tree;	
		}
		else if((value>curr_elem->value) &&(curr_elem->right_sub_tree!=NULL&& curr_elem->right_sub_tree->value!=value))
		{
			//else if key is greater than the node keys go to right
			curr_elem=curr_elem->right_sub_tree;
		}
		else
		{
			break;
		}
	}
	return 0;
	
}
// this function inserts the new elewment at its proper position 
int insert(Que ** root_node,int value)
{
	Que * curr_elem, * pre_elem;
	//Search the tree for expected parent;
	pre_elem=find( *root_node,value);
	curr_elem=(Que *) malloc(sizeof(Que));
	curr_elem->value=value;
	curr_elem->left_sub_tree=NULL;
	//if parent is null then tree is emptymake the node at root
	if( pre_elem==NULL)
	{
		* root_node=curr_elem;
	}
	else if(pre_elem->value<value && pre_elem->right_sub_tree==NULL)
	{
		// if value is greater than parent node and right part of parent is empty then add new node as right child parent
		pre_elem->right_sub_tree=curr_elem;
	}
	else if(pre_elem->value>value&& pre_elem->left_sub_tree==NULL)
	{
		//if value is lesser than parent value left part of parent is empty add new npde as child 
		pre_elem->left_sub_tree=curr_elem;
	}
	else
	{
		// if value already exists then existfrom function
		printf("element already exist\n");
		free(curr_elem);
	}
	return 0;
}

//This function delete given value element from the tree
int delete(Que ** rootNode, int value){
    Que *f, *p, * q, *r, *s;
    //Expected parent node of value element is found
    q = find(* rootNode, value);
    //If value is lesser than parent's key then mark it's left child as p
    if(value < q -> value){
        p = q -> left_sub_tree;
    } else {
        //If value is greater than parent's key then mark it's right child as p
        p = q -> right_sub_tree;
    }
    //If p has single child then mark its child as r
    if(p -> left_sub_tree == NULL){
        r = p -> right_sub_tree;
    } else if(p -> right_sub_tree== NULL){
        r = p -> left_sub_tree;
    } else {
        //Else go for current p's inorder successor
        f = p;
        r = p -> right_sub_tree;
        s = r -> left_sub_tree;
        while(s != NULL){
            f = r;
            r = s;
            s = s -> left_sub_tree;
        }
        q = f;
        p = r;
    }
    //Compare inorder successor and expected parent node q's value of  values, if successor has lesser then make it left child of expected parent q else make it right child
    if(p -> value< q -> value){
        q -> left_sub_tree = r;
    } else {
        q -> right_sub_tree = r;
    }
    //Since we removed p, free the storage it occupied
    free(p);
    return 0;
}
int main()
{
	int i,number_of_elements;
	int A[]={4,6,2,10,8,15,32,16};
	number_of_elements=8;
	for(i=0;i<number_of_elements;i++)
	{
		insert(&root_node,A[i]);
	}
	in_order_traversal(root_node);
	printf("\n");
	delete(&root_node,9);
	in_order_traversaL(root_node);
	printf("\n");
	return 0;
}

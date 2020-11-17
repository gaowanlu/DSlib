#include <stdio.h>
#include <stdlib.h>
#include "/media/gaowanlu/DIST1/DSlib/DataType/DataType.h"
struct TreeNode
{
	union ds_DataType data;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
};

struct TreeNode *InsterBST(struct TreeNode *root, union ds_DataType data)
{
	if (!root)
	{ //根节点为空时
		struct TreeNode *newNode = NULL;
		newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode) * 1);
		newNode->data = data;
		return newNode;
	}
	else if (data.ds_int < root->data.ds_int)
	{ //插入左子树
		root->lchild = InsterBST(root->lchild, data);
		return root;
	}
	else if (data.ds_int > root->data.ds_int)
	{ //插入右子树
		root->rchild = InsterBST(root->rchild, data);
		return root;
	}
}

struct TreeNode *CreateBST(union ds_DataType *array, int length)
{
	struct TreeNode *root = NULL;
	for (int i = 0; i < length; i++)
	{
		root = InsterBST(root, array[i]);
	}
	return root;
}

void freeTree(struct TreeNode *root)
{
	if (root)
	{
		freeTree(root->lchild);
		freeTree(root->rchild);
		free(root);
	}
}

void printTree(struct TreeNode *root)
{
	if (root)
	{
		printTree(root->lchild);
		printf(" %d ", root->data.ds_int);
		printTree(root->rchild);
	}
}

int main(void)
{
	union ds_DataType array[10];
	array[0].ds_int = 23;
	array[1].ds_int = 3;
	array[2].ds_int = 6;
	array[3].ds_int = 2;
	array[4].ds_int = 1;
	array[5].ds_int = 10;
	array[6].ds_int = 89;
	array[7].ds_int = 67;
	array[8].ds_int = 98;
	array[9].ds_int = 34;
	struct TreeNode *tree = CreateBST(array, 10);
	printTree(tree);
	freeTree(tree);
	return 0;
}

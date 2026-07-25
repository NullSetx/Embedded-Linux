#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

#define MAX 10

//定义树节点
struct tree_t{
	int data;//数据节点数据
	struct tree_t *left;//左子树 或者 左孩子
	struct tree_t *right;//右子树 或者 右孩子
};


//                形参
void insert(struct tree_t **root, int data)
{
	struct tree_t *new = NULL;
	struct tree_t *tail = NULL;
	
	new = (struct tree_t *)malloc(sizeof(struct tree_t));
	ERRP(NULL == new, malloc, goto ERR1);

	new->data = data;
	new->left =  NULL;
	new->right = NULL;

	if (*root == NULL)
	{
		*root = new;
		return ;
	}
	
	tail = *root;
	while (1)
	{
		if (new->data < tail->data)
		{
			//左子树为空
			if (tail->left == NULL)
			{
				tail->left = new;
				break;
			}
			tail = tail->left;
		}

		if (new->data >= tail->data)
		{
			//右子树为空
			if (tail->right == NULL)
			{
				tail->right = new;
				break;
			}
			tail = tail->right;
		}
	}
	 return ;
ERR1:
	return ;
}

void fri(struct tree_t *root)
{
	if (root == NULL)
		return ;
	printf("%d ", root->data);
	fri(root->left);
	fri(root->right);
}
void mid(struct tree_t *root)
{
	if (root == NULL)
		return ;
	mid(root->left);
	printf("%d ", root->data);
	mid(root->right);
}

void end(struct tree_t *root)
{
	if (root == NULL)
		return ;
	end(root->left);
	end(root->right);
	printf("%d ", root->data);
}

void level(struct tree_t *root)
{
	//定义队列
	struct tree_t *queue[MAX];
	int front = 0; 
	int end = 0;


	queue[end++] = root;//入队

	while (front != end)
	{
		root = queue[front++];//出队
		printf("%d ", root->data);
		if (root->left != NULL)
			queue[end++] = root->left;
		if (root->right != NULL)
			queue[end++] = root->right;
	}
	putchar(10);
}

void show(struct tree_t *root)
{
	static int lev = 0;
	int i;

	if (root == NULL)
		return ;
	lev++;
	show(root->right);
	lev--;
	
	for (i = 0; i < lev; i++)
	{
		printf("    ");
	}
	printf("%d\n", root->data);

	lev++;
	show(root->left);
	lev--;
}

//求最大数 求最小数 节点数 树深度
//删除 查找  销毁

struct tree_t *max(struct tree_t *root)
{
	if (root == NULL)
		return NULL;

	//先判断
	while (root->right != NULL)
	{	//再赋值
		root = root->right;
	}

	return root;
}
struct tree_t *min(struct tree_t *root)
{
	if (root == NULL)
		return NULL;

	while (root->left != NULL)
	{
		root = root->left;
	}

	return root;
}

int count(struct tree_t *root)
{
	
	if (root == NULL)
		return 0;
	//root root->left  1 + 1 + 0
	return 1 + count(root->left) + count(root->right);

}

int depth(struct tree_t *root)
{
	if (root == NULL)
		return 0;

	return 1 + (depth(root->left) > depth(root->right) ? depth(root->left) : depth(root->right));
}


struct tree_t *find(struct tree_t *root, int key)
{
	if (root == NULL)
		return NULL;

	while (1)
	{
		if (key > root->data)
		{
			if (root->right == NULL)
			{
					break;
			}
			root = root->right;
		}
		else if (key < root->data)
		{
			if (root->left == NULL)
			{
				break;
			}
			root = root->left;
		}
		else
		{
			return root;
		}
	}

	return NULL;
}

void destroy(struct tree_t **root)
{

	if (*root == NULL)
		return ;

	destroy(&((*root)->left));
	destroy(&((*root)->right));
	free(*root);
	*root = NULL;
}

void del(struct tree_t **root, int key)
{
	struct tree_t *parent = NULL;
	struct tree_t *tail = *root;
	struct tree_t *new = NULL;

	//l r
	//l max < r min
	//l => r min(r)->left = l
	//r => l max(l)->right = r
	//
	if (root == NULL)
		return ;

	while (1)
	{
		if (key > tail->data)
		{
			parent = tail;
			if (tail->right == NULL)
			{
					return ;
			}
			tail = tail->right;
		}
		else if (key < tail->data)
		{
			parent = tail;
			if (tail->left == NULL)
			{
				return ;
			}
			tail = tail->left;
		}
		else
		{
			break;
		}
	}
    /*
	 *printf("parent : %d\n", parent->data);
	 *printf("current : %d\n", tail->data);
     */

	if (tail->left == NULL && tail->right != NULL)
	{
		new = tail->right;
	}
	if (tail->left != NULL && tail->right == NULL)
	{
		new = tail->left;
	}
	if (tail->left != NULL && tail->right != NULL)
	{
		#if 1
		//l => r
		min(tail->right)->left = tail->left;
		new = tail->right;
		#else
		//r => l
		max(tail->left)->right = tail->right;
		new = tail->left;
		#endif
	}

	if (parent == NULL)
	{
		*root = new;
	}
	else
	{
		if (key > parent->data)
		{
			parent->right = new;
		}
		else
		{
			parent->left = new;
		}
	}
	free(tail);
	tail = NULL;

}
int main(int argc, char *argv[])
{
	int i;
	int num;
	struct tree_t *root = NULL;//根节点 空树
	int key; 
	struct tree_t *ret = NULL;


	srand(time(NULL));

	for (i = 0 ; i < MAX; i++)
	{
		num = rand() % 100;
		printf("%d ", num);

		//调用函数   实参
		insert(&root, num);
	}
	putchar(10);

    /*
	 *printf("fri : ");
	 *fri(root);
	 *putchar(10);
	 *printf("mid : ");
	 *mid(root);
	 *putchar(10);
	 *printf("end : ");
	 *end(root);
	 *putchar(10);
	 *printf("level : ");
	 *level(root);
	 *putchar(10);
     */
	printf("=============================\n");
	show(root);
	printf("=============================\n");
    /*
	 *printf("max : %d\n", max(root)->data);
	 *printf("min : %d\n", min(root)->data);
	 *printf("count : %d\n", count(root));
	 *printf("depth : %d\n", depth(root));
     */
	printf("input find key : ");
	scanf("%d", &key);

	del(&root, key);
	printf("=============================\n");
	show(root);
	printf("=============================\n");

    /*
	 *ret = find(root, key);
	 *if (ret == NULL)
	 *{
	 *    printf("no find!\n");
	 *}
	 *else
	 *{
	 *    printf("find : %d\n", ret->data);
	 *}
     */

	destroy(&root);
	return 0;
}



#include "ft_ls.h"

void	split(t_lst *src, t_lst **left, t_lst **right)
{
	t_lst *fst;
	t_lst *nxt;

    if (!src || !src->next)
    {
        *left = src;
        *right = NULL;
		return ;
    }
	fst = src;
	nxt = src->next;
	while (nxt)
	{
		nxt = nxt->next;
		if (nxt)
		{
			fst = fst->next;
			nxt = nxt->next;
		}
    }
    *left = src;
	*right = fst->next;
	fst->next = NULL;
}
/*t_lst	*merge(t_lst *l, t_lst *r)
{
	t_lst *res;

    if (!l || !r)
        return ((!l) ? r : l);

    if (l->data <= r->data)
	{
        res = l;
        res->next = merge(l->next, r);
    }
    else
	{
        res = r;
        res->next = merge(l, r->next);
    }
    return (res); 
}*/

void	merge_helper(t_lst **curr1, t_lst **curr2)
{
	t_lst *next1;
	t_lst *next2;

	next1 = (*curr1)->next;
	next2 = (*curr2)->next;
    while (*curr1 && *curr2)
	{
        if (((*curr2)->data) >= ((*curr1)->data) \
			&& ((*curr2)->data < next1->data))
		{ 
            next2 = (*curr2)->next; 
            (*curr1)->next = *curr2; 
            (*curr2)->next = next1; 
			*curr1 = *curr2; 
            *curr2 = next2; 
        } 
        else if (next1->next)
		{ 
            next1 = next1->next; 
            *curr1 = (*curr1)->next; 
        }
        else
		{ 
			next1->next = *curr2; 
			return ; 
		} 
    } 
}


t_lst	*merge_tool(t_lst *l1, t_lst* l2) 
{
	t_lst *curr1;
	t_lst *curr2;

	if (!l1->next)
	{ 
		l1->next = l2; 
		return (l1); 
    } 
    curr1 = l1;
    curr2 = l2; 
	merge_helper(&curr1, &curr2);
    return (l1); 
} 

t_lst	*merge(t_lst *l, t_lst *r)
{
	t_lst *res;

    if (!l || !r)
        return ((!l) ? r : l);
	if (l->data < r->data)
		return (merge_tool(l, r)); 
    else
        return (merge_tool(r, l)); 
}

void merge_sort(t_lst **list)
{
	t_lst *left;
	t_lst *right;
	t_lst	*root;

	if (!list || !*list || !(*list)->next)
		return ;
	root = *list;
	split(root, &left, &right);
	merge_sort(&left);
	merge_sort(&right);
	*list = merge(left, right);
}

#include <stdio.h>
int		main(void)
{
	t_lst *l;
	int		i;
	t_lst	*t;
	t_lst	*b;

	i = 10;
	l = malloc(sizeof(t_lst));
	t = l;
	b = l;
	while (i)
	{
		l->data = rand() % 1000;
		l->next = malloc(sizeof(t_lst));
		l = l->next;
		--i;
	}
	l->data = (int)"fromage";
	l->next = NULL;
	while (t)
	{
		printf("%d ", t->data);
		t = t->next;
		++i;
	}
	merge_sort(&b);
	printf("\n");
	while (b)
	{
		printf("%d ", b->data);
		b = b->next;
		++i;
	}
}
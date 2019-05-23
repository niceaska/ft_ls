/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:17:56 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/23 14:49:13 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void insert(t_lst **next1, t_lst **next2,
					t_lst **curr1, t_lst **curr2)
{
    *next2 = (*curr2)->next; 
	(*curr1)->next = *curr2; 
	(*curr2)->next = *next1; 
	*curr1 = *curr2; 
	*curr2 = *next2; 
}

static void	merge_helper(t_lst **curr1, t_lst **curr2, t_cmp_func cmp, t_env *e)
{
	t_lst *next1;
	t_lst *next2;

	next1 = (*curr1)->next;
	next2 = (*curr2)->next;
    while (*curr1 && *curr2)
	{
        if ((cmp(*curr2, *curr1, e) >= 0) \
			&& (cmp(*curr2, next1, e) < 0))
			insert(&next1, &next2, curr1, curr2);
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


static t_lst	*merge_tool(t_lst *l1, t_lst* l2, t_cmp_func cmp, t_env *e) 
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
	merge_helper(&curr1, &curr2, cmp, e);
    return (l1); 
} 

static t_lst	*merge(t_lst *l, t_lst *r, t_cmp_func cmp, t_env *e)
{
    if (!l || !r)
	{
        return ((!l) ? r : l);
	}
	if (cmp(l, r, e) < 0)
		return (merge_tool(l, r, cmp, e)); 
	else
		return (merge_tool(r, l, cmp, e)); 
}

void merge_sort(t_lst **list, t_cmp_func cmp, t_env *e)
{
	t_lst	*left;
	t_lst	*right;
	t_lst	*root;

	if (!list || !*list || !(*list)->next)
		return ;
	root = *list;
	split(root, &left, &right);
	merge_sort(&left, cmp, e);
	merge_sort(&right, cmp, e);
	*list = merge(left, right, cmp, e);
}

/*static t_lst	*merge(t_lst *l, t_lst *r, cmp_func cmp)
{
	t_lst *res;

    if (!l || !r)
        return ((!l) ? r : l);

    if (cmp(l, r) < 0)
	{
        res = l;
        res->next = merge(l->next, r, cmp);
    }
    else
	{
        res = r;
        res->next = merge(l, r->next, cmp);
    }
    return (res); 
}*/
/*
#include <stdio.h>
int		main(void)
{
	t_lst *l;
	int		i;
	char *name = "test";
	t_lst	*t;
	t_lst	*b;

	i = 3;
	l = malloc(sizeof(t_lst));
	t = l;
	b = l;
	while (i)
	{
		l->name = name;
		name = name + 1;
		l->next = malloc(sizeof(t_lst));
		l = l->next;
		--i;
	}
			l->name = "..";

		l->next = malloc(sizeof(t_lst));
		l = l->next;
	l->name = ".";
	l->next = NULL;
	while (t)
	{
		printf("%s ", t->name);
		t = t->next;
		++i;
	}
	merge_sort(&b, NULL, ft_byalfa);
	printf("\n");
	while (b)
	{
		printf("%s ", b->name);
		b = b->next;
		++i;
	}
}*/
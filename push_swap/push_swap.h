/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:52:28 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/10 15:52:30 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

# define INSTRUCT_SA 1
# define INSTRUCT_SB 2
# define INSTRUCT_SS 3
# define INSTRUCT_PA 4
# define INSTRUCT_PB 5
# define INSTRUCT_RA 6
# define INSTRUCT_RB 7
# define INSTRUCT_RRA 8
# define INSTRUCT_RRB 9
# define INSTRUCT_RR 10
# define INSTRUCT_RRR 11

# define INT_MAX	+2147483647

typedef t_list				t_instructs;
typedef t_list				t_vals;

typedef struct				s_stacks
{
	t_instructs				*instructs;
	t_vals					*stacka;
	t_vals					*stackb;
}							t_stacks;

t_stacks					*ft_pushswap_selectsort(t_vals *vals);
t_stacks					*ft_pushswap_quicksort(t_vals *vals);
t_stacks					*ft_pushswap_bublesort(t_vals *vals);
t_list						*ft_arraytolst(char **str, int size);
int							*ft_intdup(int nbr);
t_list						*ft_lstcpy(t_list *src);
size_t						ft_lstlen(t_list *lst);
t_list						*ft_lstsort(t_list *lst);
t_list						*ft_lstcpy_max(t_list *src, size_t max);
t_list						*ft_lstsort_rev(t_list *lst);
void						ft_lstadd_end(t_list **lst, t_list *new);
t_bool						ft_intlst_issorted(t_vals *lst);
void						ft_lstrotate_reverse(t_list **lst);
void						ft_lstrotate(t_list **lst);
t_bool						ft_pushswap_quicksort_isfixed(
								t_vals *fixeds, int nbr);
t_vals						*ft_pushswap_quicksort_findfirst(
								t_vals *fixeds, t_vals *lst);
int							ft_pushswap_quicksort_findlast(
								t_vals *fixeds, t_vals *lst);
int							ft_pushswap_quicksort_findmin(
								t_vals *lst);
int							ft_pushswap_quicksort_findmax(
								t_vals *lst);
int							ft_pushswap_quicksort_mediane(
								t_vals *fixeds, t_vals *lst);
void						ft_pushswap_quicksort_setfixed(
								t_vals **fixeds, int nbr);
t_bool						ft_pushswap_quicksort_isallfixed(
								t_vals **fixeds, t_vals *lst);
void						ft_pushswap_quicksort_fixalones(
								t_vals **fixeds, t_vals *lst);
void						ft_pushswap_instruct(
								char instruct, t_stacks *stacks);
void						ft_instructnew(
								t_stacks *stacks, char *instruct_str);
void						ft_pushswap_pa(t_stacks *stacks);
void						ft_pushswap_pb(t_stacks *stacks);
void						ft_pushswap_ra(t_stacks *stacks);
void						ft_pushswap_rb(t_stacks *stacks);
void						ft_pushswap_rr(t_stacks *stacks);
void						ft_pushswap_rra(t_stacks *stacks);
void						ft_pushswap_rrb(t_stacks *stacks);
void						ft_pushswap_rrr(t_stacks *stacks);
void						ft_pushswap_sa(t_stacks *stacks);
void						ft_pushswap_sb(t_stacks *stacks);
void						ft_pushswap_ss(t_stacks *stacks);
void						ft_printlst(t_list *lst);
void						ft_printlst_str(t_list *lst);
int							ft_freetvals(t_vals **vals);
void						ft_pushswap_instructs_simplificator(
								t_instructs	**lst);
void						ft_pushswap_quicksort_fixgoodposition_a(
								t_vals **fixeds, t_vals *lst, int start);
void						ft_pushswap_quicksort_fixgoodposition_b(
								t_vals **fixeds, t_vals *lst, int start);
#endif

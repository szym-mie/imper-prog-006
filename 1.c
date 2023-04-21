#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 100
#define MAX_RANGE 100

typedef struct {
	int first;
	int second;
} pair;

// Add pair to existing relation if not already there
int add_relation (pair*, int, pair);

// Case 1:

// The relation R is reflexive if xRx for every x in X
int is_reflexive(pair*, int);

// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(pair*, int);

// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(pair*, int);

// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(pair*, int);

// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(pair*, int);

// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(pair*, int);

// Case 2:

// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(pair*, int);

// A total order relation is a partial order relation that is connected
int is_total_order(pair*, int);

// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(pair*, int);

int find_max_elements(pair*, int, int*);
int find_min_elements(pair*, int, int*);
int get_domain(pair*, int, int*);

// Case 3:

int composition (pair*, int, pair*, int, pair*);

// Comparator for pair
int cmp_pair_x(const void *a, const void *b) {
	pair *pa = (pair *) a;
	pair *pb = (pair *) b;

	if (pa->first != pb->first) return pa->first - pb->first;
	if (pa->second != pb->second) return pa->second - pb->second;
	return 0;
}

int cmp_pair_y(const void *a, const void *b) {
	pair *pa = (pair *) a;
	pair *pb = (pair *) b;

	if (pa->second != pb->second) return pa->second - pb->second;
	if (pa->first != pb->first) return pa->first - pb->first;
	return 0;
}

int insert_int (int *tab, int n, int new_element) {
	// no use
	return 0;
}

// Add pair to existing relation if not already there
int add_relation (pair *tab, int n, pair new_pair) {
	for (int i = 0; i < n; i++)
	{
		if (!cmp_pair_x(&new_pair, tab+i)) return 0;
	}

	memcpy(tab+n, &new_pair, sizeof(pair));

	return 1;
}


int is_reflexive(pair *p, int n) 
{
	qsort(p, n, sizeof(pair), cmp_pair_x);
	int cfirst = p->first;
	int has_refl = 0;
	for (int i = 0; i < n; i++) 
	{
		if ((p+i)->first != cfirst)
		{
			if (!has_refl) return 0;
			cfirst = (p+i)->first;
			has_refl = 0;
		}
		if ((p+i)->second == cfirst) has_refl = 1;
	}

	return 1;
}

int is_irreflexive(pair *p, int n)
{
	for (int i = 0; i < n; i++) 
	{
		if ((p+i)->first == (p+i)->second) return 0;
	}

	return 1;
}

int sym_pair(pair *a, pair *b)
{
	return a->first == b->second && a->second == b->first;
}

int ident_pair(pair *a)
{
	return a->first == a->second;
}

int is_symmetric(pair *p, int n)
{
	qsort(p, n, sizeof(pair), cmp_pair_x);
	int m =  n / 2 + n % 2; // round up
	for (int i = 0; i < m; i++)
	{
		if (ident_pair(p+i)) continue;
		int has_sym = 0;
		for (int j = n - 1; j > i; j--)
		{
			if (sym_pair(p+i, p+j))
			{
				has_sym = 1;
				break;
			}
		}

		if (!has_sym) return 0;
	}

	return 1;
}

int is_antisymmetric(pair *p, int n)
{
	qsort(p, n, sizeof(pair), cmp_pair_x);
	int m =  n / 2 + n % 2; // round up
	for (int i = 0; i < m; i++)
	{
		int has_sym = 0;
		for (int j = n - 1; j > i; j--)
		{
			if (sym_pair(p+i, p+j))
			{
				has_sym = 1;
				break;
			}
		}

		if (has_sym && (p+i)->first != (p+i)->second) return 0;
	}

	return 1;
}

int is_asymmetric(pair *p, int n)
{
	return is_irreflexive(p, n) && is_antisymmetric(p, n); 
}

int is_transitive(pair *p, int n)
{
	qsort(p, n, sizeof(pair), cmp_pair_x);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((p+j)->first != (p+i)->second) continue;
			int has_rel = 0;
			for (int k = 0; k < n; k++)
			{
				if ((p+k)->second == (p+j)->second)
				{
					puts("has rel");
					has_rel = 1;
					break;
				}
			}
			if (!has_rel) return 0;
			else break;
		}
	}

	return 1;
}

int is_partial_order(pair *p, int n)
{
	return is_reflexive(p, n) && 
		is_antisymmetric(p, n) && 
		is_transitive(p, n);
}

int is_total_order(pair *p, int n)
{
	return is_connected(p, n) && 
		is_partial_order(p, n);
}

int is_connected(pair *p, int n)
{
	for (int i = 0; i < n; i++)
	{
	}

	return 1;
}

int find_max_elements(pair *p, int n, int *ia)
{
	qsort(p, n, sizeof(pair), cmp_pair_y);
	int cn = p->second;
	int is_max = 1;

	for (int i = 0; i < n; i++)
	{
		if (cn != (p+i)->second)
		{
			if (is_max) *(ia++) = cn;
			cn = (p+i)->second;
			is_max = 1;
		}
		if ((p+i)->first > cn) is_max = 0;
	}
	
	return 0;
}

int find_min_elements(pair *p, int n, int *ia)
{
	qsort(p, n, sizeof(pair), cmp_pair_x);
	int cn = p->first;
	int is_max = 1;

	for (int i = 0; i < n; i++)
	{
		if (cn != (p+i)->first)
		{
			if (is_max) *(ia++) = cn;
			cn = (p+i)->first;
			is_max = 1;
		}
		if ((p+i)->second < cn) is_max = 0;
	}
	
	return 0;
}

int get_domain(pair *p, int n, int *ia)
{
	qsort(p, n, sizeof(pair), cmp_pair_x);
	int c = p->first;
	*ia = c;
	int s = 1;

	for (int i = 1; i < n; i++)
	{
		if ((p+i)->first != c)
		{
			c = (p+i)->first;
			*(++ia) = c;
			s++;
		}
	}

	return s;
}

/*
 * p, r - input relations
 * n, m - sizes of input relations (in order of input relations)
 * s - output relation
 */
int composition (pair *p, int n, pair *r, int m, pair *s)
{
	int k = 0;

	qsort(p, n, sizeof(pair), cmp_pair_y);
	qsort(r, m, sizeof(pair), cmp_pair_x);
	int a, b;

	int i = 0;
	int j = 0;

	while (i < n && j < m)
	{
		a = (p+i)->second;
		b = (r+j)->first;
		
		if (a == b)
		{
			// find all pairs from 'r' that have same 'x'
			for (int js = j; js < m; js++)
			{
				if ((r+js)->first != b) break;
				(s+k)->first = (p+i)->first;
				(s+k)->second = (r+js)->second;
				k++;
			}
			i++;
			continue;
		}
		
		// seek next number to close the gap
		if (a < b) i++;
		else j++;
	}

	return k;
}

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair *relation) {
	int n = 0;
	scanf("%d", &n);
	if (n == 0) return 0;
	
	int first, second;
	int i = 0;
	while (i < n && scanf("%d %d", &first, &second) == 2)
	{
		pair *p = relation+i++;
		p->first = first;
		p->second = second;
	}

	// if could not load all 'n' elements, return loaded only
	return i;
}

void print_int_array(int *array, int n) {
	for (int i = 0; i < n; i++) printf("%d ", *(array+i));
}

int main(void) {
	int to_do;
	pair relation[MAX_REL_SIZE];
	pair relation_2[MAX_REL_SIZE];
	pair comp_relation[MAX_REL_SIZE];
	int domain[MAX_REL_SIZE];
	int max_elements[MAX_REL_SIZE];
	int min_elements[MAX_REL_SIZE];

	scanf("%d",&to_do);
	int size = read_relation(relation);
	int ordered, size_2, n_domain;

	switch (to_do) {
		case 1:
			printf("%d ", is_reflexive(relation, size));
			printf("%d ", is_irreflexive(relation, size));
			printf("%d ", is_symmetric(relation, size));
			printf("%d ", is_antisymmetric(relation, size));
			printf("%d ", is_asymmetric(relation, size));
			printf("%d\n", is_transitive(relation, size));
			break;
		case 2:
			ordered = is_partial_order(relation, size);
			n_domain = get_domain(relation, size, domain);
			printf("%d %d\n", ordered, is_total_order(relation, size));
			print_int_array(domain, n_domain);
			if (!ordered) break;
			int no_max_elements = find_max_elements(relation, size, max_elements);
			int no_min_elements = find_min_elements(relation, size, min_elements);
			print_int_array(max_elements, no_max_elements);
			print_int_array(min_elements, no_min_elements);
			break;
		case 3:
			size_2 = read_relation(relation_2);
			printf("%d\n", composition(relation, size, relation_2, size_2, comp_relation));
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}


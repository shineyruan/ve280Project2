#include <iostream>
#include <cstdlib>
#include "p2.h"
using namespace std;

int size(list_t list) {
	// EFFECTS: Returns the number of elements in "list".
	//          Returns zero if "list" is empty.
	if (list_isEmpty(list)) return 0;
	else return 1 + size(list_rest(list));
}

int sum(list_t list) {
	// EFFECTS: Returns the sum of each element in "list".
	//          Returns zero if "list" is empty.
	if (list_isEmpty(list)) return 0;
	else return list_first(list) + sum(list_rest(list));
}

int product(list_t list) {
	// EFFECTS: Returns the product of each element in "list".
	//          Returns one if "list" is empty.
	if (list_isEmpty(list)) return 1;
	else return list_first(list)*product(list_rest(list));
}

int accumulate(list_t list, int(*fn)(int, int), int base) {
	// REQUIRES: "fn" must be associative.
	//
	// EFFECTS: Returns "base" if "list" is empty.
	//          Returns fn(list_first(list), 
	//                      accumulate(list_rest(list), fn, base) otherwise.
	if (list_isEmpty(list)) return base;
	else return fn(list_first(list), accumulate(list_rest(list), fn, base));
}

static list_t int2list(int i) { 
	//EFFECTS: Returns an int type as a list type.
	return list_make(i, list_make()); 
}
list_t reverse(list_t list) {
	// EFFECTS: Returns the reverse of "list".
	if (list_isEmpty(list)) return list;
	else return append(reverse(list_rest(list)), int2list(list_first(list)));
}

list_t append(list_t first, list_t second) {
	// EFFECTS: Returns the list (first second).
	if (list_isEmpty(first)) return second;
	else 
		if (list_isEmpty(list_rest(first))) return list_make(list_first(first), second);
		else return list_make(list_first(first), append(list_rest(first), second));
}

list_t filter_odd(list_t list) {
	// EFFECTS: Returns a new list containing only the elements of the
	//          original "list" which are odd in value, 
	//          in the order in which they appeared in list.
	//
	// For example, if you apply filter_odd to the list ( 3 4 1 5 6 ),
	// you would get the list ( 3 1 5 ).
	if (list_isEmpty(list)) return list_make();
	else
		if (list_first(list) % 2 == 1) return list_make(list_first(list), filter_odd(list_rest(list)));
		else return filter_odd(list_rest(list));
}

list_t filter_even(list_t list) {
	// EFFECTS: Returns a new list containing only the elements of the
	//          original "list" which are even in value, 
	//          in the order in which they appeared in list.
	if (list_isEmpty(list)) return list_make();
	else
		if (list_first(list) % 2 == 0) return list_make(list_first(list), filter_even(list_rest(list)));
		else return filter_even(list_rest(list));
}

list_t filter(list_t list, bool(*fn)(int)) {
	// EFFECTS: Returns a list containing precisely the elements of "list"
	//          for which the predicate fn() evaluates to true, in the
	//          order in which they appeared in list.
	//
	// For example, if predicate bool odd(int a) returns true if a is odd,
	// then the function filter(list, odd) has the same behavior as the
	// function filter_odd(list).
	if (list_isEmpty(list)) return list_make();
	else
		if (fn(list_first(list))) return list_make(list_first(list), filter(list_rest(list), fn));
		else return filter(list_rest(list), fn);
}

list_t insert_list(list_t first, list_t second, unsigned int n) {
	// REQUIRES: n <= the number of elements in "first".
	//
	// EFFECTS: Returns a list comprising the first n elements of
	//          "first", followed by all elements of "second",
	//           followed by any remaining elements of "first".
	//
	//     For example: insert (( 1 2 3 ), ( 4 5 6 ), 2)
	//            gives ( 1 2 4 5 6 3 ).
	if (n == 0) return append(second, first);
	else return list_make(list_first(first), insert_list(list_rest(first), second, n - 1));
}

static list_t cut_firstNelements(list_t list, int n) { 
	// EFFECTS: Returns the rest of a list without the first n elements.
	if (n == 0) return list;
	else return cut_firstNelements(list_rest(list), n - 1);
}
list_t chop(list_t list, unsigned int n) {
	// REQUIRES: "list" has at least n elements.
	//
	// EFFECTS: Returns the list equal to "list" without its last n
	//          elements.
	return reverse(cut_firstNelements(reverse(list), n));
}

int tree_sum(tree_t tree) {
	// EFFECTS: Returns the sum of all elements in "tree". 
	//          Returns zero if "tree" is empty.
	if (tree_isEmpty(tree)) return 0;
	else return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
}

bool tree_search(tree_t tree, int key) {
	// EFFECTS: Returns true if there exists any element in "tree"
	//          whose value is "key". Otherwise, return "false".
	if (tree_isEmpty(tree)) return false;
	else
		if (key == tree_elt(tree)) return true;
		else
			return tree_search(tree_left(tree), key) || tree_search(tree_right(tree), key);
}

int depth(tree_t tree) {
	// EFFECTS: Returns the depth of "tree", which equals the number of
	//          layers of nodes in the tree.
	//          Returns zero is "tree" is empty.
	if (tree_isEmpty(tree)) return 0;
	else
		if (depth(tree_left(tree)) > depth(tree_right(tree)))
			return 1 + depth(tree_left(tree));
		else 
			return 1 + depth(tree_right(tree));
}

int tree_min(tree_t tree) {
	// REQUIRES: "tree" is non-empty.
	// EFFECTS: Returns the smallest element in "tree".
	if (tree_isEmpty(tree)) return 10000000;
	else if (depth(tree) == 1) return tree_elt(tree);
	else
		if (tree_elt(tree) < tree_min(tree_left(tree)) && tree_elt(tree) < tree_min(tree_right(tree)))
			return tree_elt(tree);
		else
			if (tree_min(tree_left(tree)) < tree_min(tree_right(tree)))
				return tree_min(tree_left(tree));
			else
				return tree_min(tree_right(tree));
}

list_t traversal(tree_t tree) {
	// EFFECTS: Returns the elements of "tree" in a list using an
	//          in-order traversal. An in-order traversal prints 
	//          the "left most" element first, then the second-left-most, 
	//          and so on, until the right-most element is printed.
	//
	//          For any node, all the elements of its left subtree
	//          are considered as on the left of that node and
	//          all the elements of its right subtree are considered as
	//          on the right of that node.
	if (tree_isEmpty(tree)) return list_make();
	else 
		return append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));
}

bool tree_hasPathSum(tree_t tree, int sum) {
	// EFFECTS: Returns true if and only if "tree" has at least one root-to-leaf
	//          path such that adding all elements along the path equals "sum".
	sum -= tree_elt(tree);
	if (tree_isEmpty(tree)) return false;
	else
		if (sum == 0)
			if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)))
				return true;
			else
				return false;
		else
			return tree_hasPathSum(tree_left(tree), sum) || tree_hasPathSum(tree_right(tree), sum);
}

bool covered_by(tree_t A, tree_t B) {
	// EFFECTS: Returns true if tree A is covered by tree B.
	if (tree_isEmpty(A)) return true;
	else if (tree_isEmpty(B)) return false;
	else
		if (tree_elt(A) == tree_elt(B) && 
			covered_by(tree_left(A), tree_left(B)) && 
			covered_by(tree_right(A), tree_right(B))) return true;
		else return false;
}

bool contained_by(tree_t A, tree_t B) {
	// EFFECTS: Returns true if tree A is covered by tree B
	//          or a subtree of B.
	if (tree_isEmpty(A)) return true;
	else if (tree_isEmpty(B)) return false;
	else
		if (covered_by(A, B) || contained_by(A, tree_left(B)) || contained_by(A, tree_right(B)))
			return true;
		else return false;
}

tree_t insert_tree(int elt, tree_t tree) {
	// REQUIRES: "tree" is a sorted binary tree.
	//
	// EFFECTS: Returns a new tree with elt inserted at a leaf such that 
	//          the resulting tree is also a sorted binary tree.
	if (tree_isEmpty(tree)) return tree_make(elt, tree_make(), tree_make());
	else
		if (elt < tree_elt(tree))
			return tree_make(tree_elt(tree), insert_tree(elt, tree_left(tree)), tree_right(tree));
		else
			return tree_make(tree_elt(tree), tree_left(tree), insert_tree(elt, tree_right(tree)));
}


#include <stdio.h>
#include <stdlib.h>

enum operator {
	OP_MULTIPLY,
	OP_DIVIDE,
	OP_ADD,
	OP_SUBTRACT,
	OP_IDENTITY /* marks leaves */
};

struct bnode {
	int value;
	enum operator operator;
	struct bnode *left;
	struct bnode *right;
};

char
op_lookup(enum operator op) {
	switch (op) {
		case OP_MULTIPLY: return '*';
		case OP_DIVIDE:   return '/';
		case OP_ADD:      return '+';
		case OP_SUBTRACT: return '-';
		default:
			/* FIXME return this, error out somehow else? */
			return '?';
	}
}

double
evaluate_op(double left, enum operator op, double right) {
	switch(op) {
		case OP_MULTIPLY: return left * right;
		case OP_DIVIDE:   return (double)left / right;
		case OP_ADD:      return left + right;
		case OP_SUBTRACT: return left - right;
		default:
			/* FIXME return nan */
			return -100000;
	}
}

double
evaluate(struct bnode* node) {
	if (node->operator == OP_IDENTITY)
		return node->value;

	/* FIXME could/should NULL-check children
	 * Non-identity node should have two childre, but I might manage to
	 * screw it up somehow eh */
	return evaluate_op(
		evaluate(node->left),
		node->operator,
		evaluate(node->right));
}

void
generate_tree_perms(int depth, int decision_depth, struct bnode *node) {
	if (depth == 0) {
		node->operator = OP_IDENTITY;
		node->value = rand()%20;
		return ;
	}
	/* Hmmm */
	struct bnode *children = NULL;
	children = malloc(2*sizeof(children[0]));
	children[0].left = NULL;
	children[0].right = NULL;
	children[1].left = NULL;
	children[1].right = NULL;
	node->left = &children[0];
	node->right = &children[1];
	node->operator = OP_ADD;
	node->right->operator = OP_IDENTITY;
	node->right->value = 999;

/*	if (depth == 0 || decision_depth == 0) {
		node->left->operator = OP_IDENTITY;
		node->left->value = rand()%20;
		node->right->operator = OP_IDENTITY;
		node->right->value = rand()%20;
		return;
	}*/

	if (depth == decision_depth)
		generate_tree_perms(0, 0, node->right);

	generate_tree_perms(depth-1, decision_depth, node->left);
}

void
dump_tree(struct bnode *node) {
	if (node->operator == OP_IDENTITY) {
		printf("%d", node->value);
		return;
	}

	printf("(");
	if (node->left != NULL)
		dump_tree(node->left);

	printf(" %c ", op_lookup(node->operator));

	if (node->right != NULL)
		dump_tree(node->right);
	printf(")");
}

int
main(int argc, char **argv) {
	struct bnode a,b,c,d,e, o1,o2,o3,o4;

/*	((1+2)/(3*(4-5))) */
	a.value = 1; a.operator = OP_IDENTITY; a.left = a.right = NULL;
	b.value = 2; b.operator = OP_IDENTITY; b.left = b.right = NULL;
	c.value = 3; c.operator = OP_IDENTITY; c.left = c.right = NULL;
	d.value = 4; d.operator = OP_IDENTITY; d.left = d.right = NULL;
	e.value = 5; e.operator = OP_IDENTITY; e.left = e.right = NULL;

	o1.left  = &a;
	o1.right = &b;
	o1.operator = OP_ADD;

	o2.left = &d;
	o2.right = &e;
	o2.operator = OP_SUBTRACT;

	o3.left = &c;
	o3.right = &o2;
	o3.operator = OP_MULTIPLY;

	o4.left = &o1;
	o4.right = &o3;
	o4.operator = OP_DIVIDE;

	dump_tree(&o4);
	printf("\n = %f\n", evaluate(&o4));



	struct bnode t;
	t.operator = OP_ADD;
	generate_tree_perms(3, 0, &t);
	dump_tree(&t);
}


enum e_ttype
{
	T_NULL = 0,
	T_WORD = 1,
	T_REDIR = 2,
	T_PIPE = 3,
	T_DOUBLE_QUOTES = 4,
	T_SINGLE_QUOTES = 5
};

typedef struct s_node{
	enum e_ttype	type;
	char			*str;
	t_node			*left;
	t_node			*right;
	t_node			*parent;
}	t_node;

typedef struct s_tree
{
	t_node	*top;
	int		node_count;
}	t_tree;

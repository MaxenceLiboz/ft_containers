#ifndef NODE_HPP
#define NODE_HPP

#define BLACK 0
#define RED 1

namespace ft
{
	template <class T>
	class Node 
	{
		public :
			typedef Node<T>*	struct_node_pointer;
			typedef T 			value_type;

			struct_node_pointer parent;
			struct_node_pointer left;
			struct_node_pointer right;
            value_type 			*value;
            value_type 			max_size;
			bool 				color;

			Node() :  parent(0), left(0), right(0), value(NULL), color(RED) {}
			Node(value_type *value, struct_node_pointer parent = 0, struct_node_pointer left = 0,
				struct_node_pointer right = 0, bool color = RED)
			:  parent(parent), left(left), right(right), value(value), color(color)
			{}
			~Node() {}
	};
}

#endif

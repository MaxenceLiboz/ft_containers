#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <limits>

#include "Node.hpp"
#include "../iterators/tree_iterator.hpp"
#include "../iterators/reverse_bidirectional_iterator.hpp"
#include "../includes/distance.hpp"
#include "../includes/pair.hpp"
#include "../includes/enable_if.hpp"
#include "../includes/is_integral.hpp"

#define LEAF NULL
#define LEFT 0
#define RIGHT 1

namespace ft {
	template<class T, class T_alloc, class Compare, class Node_alloc = std::allocator<Node<T> > >
	class tree {
	public:

		typedef				T													value_type;
		typedef				Node_alloc											node_alloc_type;
		typedef typename	T::first_type										key_type;
		typedef				T_alloc												value_type_alloc_type;
        typedef typename    Node_alloc::size_type                               Node_size_type;
		typedef typename	value_type_alloc_type::size_type					size_type;
		typedef typename	value_type_alloc_type::difference_type				difference_type;
		typedef typename	ft::Node<value_type>								node_struct;
		typedef				node_struct *										node_struct_pointer;
		typedef				Compare												compare;
		typedef				ft::tree_iterator<T>							    iterator;
		typedef		 		ft::const_tree_iterator<T>	 						const_iterator;
		typedef 			ft::reverse_bidirectional_iterator<iterator>		reverse_iterator;
		typedef 			ft::reverse_bidirectional_iterator<const_iterator>	const_reverse_iterator;

	private:
		node_struct_pointer			_tree_extrimities;
		node_alloc_type				_node_allocator;
		value_type_alloc_type		_value_type_allocator;
		compare						_comp;
		node_struct_pointer			_end_node;
		size_type					_size;

    public:
        /* ************************************************************************** */
        /* ----------------------- Constructors && Destructors ---------------------- */
        /* ************************************************************************** */
		tree(const compare &comp, const value_type_alloc_type &value_type_allocator, const node_alloc_type &node_alloc = node_alloc_type()) : _node_allocator(node_alloc) {
			_tree_extrimities = _node_allocator.allocate(1); // So that we can access the root in the insert even the first time.
			_end_node = _node_allocator.allocate(1);
            value_type  *new_value = _value_type_allocator.allocate(1);
            value_type  tmp;
            _value_type_allocator.construct(new_value, tmp);
			_node_allocator.construct(_tree_extrimities, Node<T>());
			_node_allocator.construct(_end_node, Node<T>(new_value));

			_comp = comp;
			_value_type_allocator = value_type_allocator;
			_size = 0;
            _tree_extrimities->right = _end_node;
            _tree_extrimities->left = _end_node;
            _tree_extrimities->parent = _end_node;
		}

		~tree() {
            while (_size > 0)
            {
                erase(*_tree_extrimities->left->value);
            }
            _free_node(_end_node);
            _node_allocator.destroy(_tree_extrimities);
            _node_allocator.deallocate(_tree_extrimities, 1);
        }

		/* ************************************************************************** */
		/* -------------------------------- Iterators ------------------------------- */
		/* ************************************************************************** */
		iterator begin() {
			return iterator(_size == 0 ? _end_node : _tree_extrimities->left);
		}

		const_iterator begin() const {
			return const_iterator(_size == 0 ? _end_node : _tree_extrimities->left);
		}

		reverse_iterator rbegin() {
			return reverse_iterator(_size == 0 ? _end_node : _tree_extrimities->right->right);
		}

		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(_size == 0 ? _end_node : _tree_extrimities->right->right);
		}

		iterator end() {
			return iterator(_size == 0 ? _end_node : _tree_extrimities->right->right);
		}

		const_iterator end() const {
			return const_iterator(_size == 0 ? _end_node : _tree_extrimities->right->right);
		}

		reverse_iterator rend() {
			return reverse_iterator(_size == 0 ? _end_node : _tree_extrimities->left);
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(_size == 0 ? _end_node : _tree_extrimities->left);
		}

		iterator lower_bound (const key_type &k) {
			node_struct_pointer	tmp = _tree_extrimities->parent;
			iterator it;

			_node_finding(tmp, k);
			return it = tmp;
		}

        const_iterator lower_bound (const key_type &k) const {
            node_struct_pointer	tmp = _tree_extrimities->parent;
            const_iterator it;

            _node_finding(tmp, k);
            return it = tmp;
        }

		iterator upper_bound(const key_type &k) {
			node_struct_pointer	tmp = _tree_extrimities->parent;
			iterator it;

            _node_finding(tmp, k);
            if (tmp == _end_node)
                return end();
            if (_comp(tmp->value->first, k) || k == tmp->value->first)
                tmp = _get_next_node(tmp);
            return it = tmp;
        }

        const_iterator upper_bound(const key_type &k) const {
            node_struct_pointer	tmp = _tree_extrimities->parent;
            const_iterator it;

            _node_finding(tmp, k);
            if (tmp == _end_node)
                return end();
            if (_comp(tmp->value->first, k) || k == tmp->value->first)
                tmp = _get_next_node(tmp);
            return it = tmp;
        }

		/* ************************************************************************** */
		/* -------------------------------- Operations ------------------------------ */
		/* ************************************************************************** */
		size_type count(const key_type k) const {
			node_struct_pointer	tmp = _tree_extrimities->parent;
			return !_node_finding(tmp, k);
		}

		void	swap(tree &x)
		{
			if (this->empty() && x.empty())
				return;
			node_struct_pointer	tmp = this->_tree_extrimities;
			this->_tree_extrimities = x._tree_extrimities;
			x._tree_extrimities = tmp;

			tmp = this->_end_node;
			this->_end_node = x._end_node;
			x._end_node = tmp;

			size_type size_tmp = this->_size;
			this->_size = x._size;
			x._size = size_tmp;

			node_alloc_type alloc_tmp = this->_node_allocator;
			this->_node_allocator = x._node_allocator;
			x._node_allocator = alloc_tmp;

			value_type_alloc_type v_alloc_tmp = this->_value_type_allocator;
			this->_value_type_allocator = x._value_type_allocator;
			x._value_type_allocator = v_alloc_tmp;

			compare cmp_tmp = this->_comp;
			this->_comp = x._comp;
			x._comp = cmp_tmp;
		}

		/* ************************************************************************** */
		/* -------------------------------- Capacity -------------------------------- */
		/* ************************************************************************** */
		bool empty() const { return (_tree_extrimities->parent == _end_node ? true : false); }

		size_type size() const { return _size; }

        size_type max_size() const {
            return std::numeric_limits<size_type>::max() / (sizeof(ft::Node<value_type>) - sizeof(value_type*));
        }



        /* ************************************************************************** */
		/* ----------------------- insert algorithm ------------------------------ */
		/* ************************************************************************** */

		ft::pair<iterator, bool> insert(iterator &position, const value_type &value) {
			(void)position;
			node_struct_pointer tmp = _tree_extrimities->parent;
			if (_size > 0)
				_tree_extrimities->right->right = LEAF;

			bool valid = _node_finding(tmp, value.first);
			if (valid == false)
            {
                _fix_extrimities_insert(_tree_extrimities->parent);
                return ft::make_pair(iterator(tmp), false);
            }

            node_struct_pointer new_node = _node_allocator.allocate(1);
            value_type  *new_value = _value_type_allocator.allocate(1);
            _value_type_allocator.construct(new_value, value);
            _node_allocator.construct(new_node, Node<value_type>(new_value, tmp == _end_node ? NULL : tmp, LEAF, LEAF, RED));

			if (_size == 0)
				tmp = new_node;
			else {
				if (_comp(value.first, tmp->value->first))
					tmp->left = new_node;
				else
					tmp->right = new_node;
			}
			_fix_tree_insert(new_node);
			_fix_extrimities_insert(new_node);
			_size += 1;
			return ft::make_pair(iterator(new_node), true);
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			iterator it;
			if (_tree_extrimities->right != NULL)
				_tree_extrimities->right->right = LEAF;
			for (; first != last; first++)
				insert(it, *first);
		}

		/* ************************************************************************** */
		/* ------------------------- Deletion algorithm ----------------------------- */
		/* ************************************************************************** */
		size_type erase(value_type n) {
            if (_size == 0)
				return 0;
			_tree_extrimities->right->right = LEAF;
			node_struct_pointer v = _tree_extrimities->parent;
			bool valid = !_node_finding(v, n.first);
			if (valid == false)
			{
                _fix_extrimities_erase();
                return 0;
			}
			_delete_node(v);
            _size--;
            _fix_extrimities_erase();
            if (_size == 1)
                _tree_extrimities->parent->color = BLACK;
            return 1;
        }

        void erase_range(iterator first, iterator last) {
            int size = ft::distance(first, last);
            int i = 0;
            node_struct_pointer tmp[size];
            for (; first != last; first++) {
                tmp[i] = _tree_extrimities->parent;
               _node_finding(tmp[i], first->first);
               i++;
            }
            while (i--) {
                erase(*tmp[i]->value);
            }
            return;
        }


	private:
		/* ************************************************************************** */
		/* ----------------------- Access operation --------------------------------- */
		/* ************************************************************************** */
		node_struct_pointer _parent(node_struct_pointer n) { return n->parent; }


		node_struct_pointer _grand_parent(node_struct_pointer n) {
			node_struct_pointer p = _parent(n);
			return p == NULL ? NULL : _parent(p);
		}

		node_struct_pointer _aunt(node_struct_pointer n) {
			node_struct_pointer p = _parent(n);
			return _siblings(p);
		}

		node_struct_pointer _siblings(node_struct_pointer n) {
			node_struct_pointer p = _parent(n);
			if (p == NULL)
				return NULL;
			return (n == p->left ? p->right : p->left);
		}

		node_struct_pointer _left(node_struct_pointer n) { return n->left; }

		node_struct_pointer _right(node_struct_pointer n) { return n->right; }

		bool hasRedChild(node_struct_pointer n) {
			return (n->left != NULL && n->left->color == RED) ||
				   (n->right != NULL && n->right->color == RED);
		}

		bool _is_one_left(node_struct_pointer v) { return v == v->parent->left; }

		void _is_root(node_struct_pointer n) {
			if (_parent(n) == NULL)
				n->color = BLACK;
		}

		node_struct_pointer _get_next_node(node_struct_pointer ptr) const {
			if (ptr->right != NULL) {
				ptr = ptr->right;
				while (ptr->left != NULL)
					ptr = ptr->left;
				return ptr;
			}
			while (ptr->parent && ptr->parent->right == ptr)
				ptr = ptr->parent;
			return ptr->parent;
		}

		node_struct_pointer _get_prev_node(node_struct_pointer ptr) {
			if (ptr->left != NULL) {
				ptr = ptr->left;
				while (ptr->right != NULL)
					ptr = ptr->right;
				return ptr;
			}
			while (ptr->parent && ptr->parent->left == ptr)
				ptr = ptr->parent;
			return ptr->parent;
		}

		/* ************************************************************************** */
		/* ----------------------- Rotate operation --------------------------------- */
		/* ************************************************************************** */
		void _left_rotate(node_struct_pointer x) {
			node_struct_pointer y = x->right;
			x->right = y->left;
			if (y->left != NULL) {
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == NULL) {
				_tree_extrimities->parent = y;
			} else if (x == x->parent->left) {
				x->parent->left = y;
			} else {
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}

		void _right_rotate(node_struct_pointer x) {
			node_struct_pointer y = x->left;
			x->left = y->right;
			if (y->right != NULL) {
				y->right->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == NULL) {
				_tree_extrimities->parent = y;
			} else if (x == x->parent->right) {
				x->parent->right = y;
			} else {
				x->parent->left = y;
			}
			y->right = x;
			x->parent = y;
		}

		/* ************************************************************************** */
		/* ----------------------- Utils insert algorithm ------------------------ */
		/* ************************************************************************** */
		bool _node_finding(node_struct_pointer &tmp, const key_type &value) const {
			if (_size > 0) {
				while ((_comp(value, tmp->value->first) && tmp->left != LEAF) ||
					   (_comp(tmp->value->first, value) && tmp->right != LEAF)) {
                    if (tmp->value->first == value)
                        return false;
					if (_comp(value, tmp->value->first))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				if (value == tmp->value->first)
					return false;
			}
			return true;
		}

		void _fix_tree_insert(node_struct_pointer n) {
			if (_parent(n) == NULL)
				return _is_root(n);
			else if (_parent(n)->color == BLACK)
				return;
			else if (_aunt(n) && _aunt(n)->color == RED)
				_change_color(n);
			else {
				if (n->parent == n->parent->parent->right)
					_right_side_rotation(n);
				else
					_left_side_rotation(n);
			}
		}

		void _change_color(node_struct_pointer n) {
			_parent(n)->color = BLACK;
			_aunt(n)->color = BLACK;

			if (_grand_parent(n)->parent != NULL)
				_grand_parent(n)->color = RED;
			_fix_tree_insert(_grand_parent(n));
		}

		void _right_side_rotation(node_struct_pointer n) {
			while (n->parent->color == 1) {
				node_struct_pointer uncle = n->parent->parent->left;
				if (uncle && uncle->color == 1) {
					uncle->color = 0;
					n->parent->color = 0;
					n->parent->parent->color = 1;
					n = n->parent->parent;
				} else {
					if (n == n->parent->left) {
						n = n->parent;
						_right_rotate(n);
					}
					n->parent->color = 0;
					n->parent->parent->color = 1;
					_left_rotate(n->parent->parent);
				}
				if (n == _tree_extrimities->parent) {
					break;
				}
			}
			_tree_extrimities->parent->color = 0;
		}

		void _left_side_rotation(node_struct_pointer n) {
			while (n->parent->color == 1) {
				node_struct_pointer uncle = n->parent->parent->right;
				if (uncle && uncle->color == 1) {
					uncle->color = 0;
					n->parent->color = 0;
					n->parent->parent->color = 1;
					n = n->parent->parent;
				} else {
					if (n == n->parent->right) {
						n = n->parent;
						_left_rotate(n);
					}
					n->parent->color = 0;
					n->parent->parent->color = 1;
					_right_rotate(n->parent->parent);
				}
				if (n == _tree_extrimities->parent)
					break;
			}
			_tree_extrimities->parent->color = 0;
		}

		void _fix_extrimities_insert(node_struct_pointer new_node) {
			if (_size > 0) {
				while (_parent(_tree_extrimities->parent) != NULL)
					_tree_extrimities->parent = _parent(_tree_extrimities->parent);
                _tree_extrimities->left = _tree_extrimities->parent;
                while (_tree_extrimities->left && _tree_extrimities->left->left != NULL)
					_tree_extrimities->left = _tree_extrimities->left->left;
                _tree_extrimities->right = _tree_extrimities->parent;
                while (_tree_extrimities->right && _tree_extrimities->right->right != NULL)
                    _tree_extrimities->right = _tree_extrimities->right->right;
			} else {
				_tree_extrimities->parent = new_node;
				_tree_extrimities->left = new_node;
				_tree_extrimities->right = new_node;
			}
            _tree_extrimities->right->right = _end_node;
            _end_node->parent = _tree_extrimities->right;
		}

		/* ************************************************************************** */
		/* ----------------------- Utils deletion algorithm ------------------------- */
		/* ************************************************************************** */
        void    _free_node(node_struct_pointer node)
        {
            _value_type_allocator.destroy(node->value);
            _value_type_allocator.deallocate(node->value, 1);
            node->value = NULL;
            node->parent = NULL;
            node->left = NULL;
            node->right = NULL;
            _node_allocator.destroy(node);
            _node_allocator.deallocate(node, 1);
            node = NULL;
        }

		node_struct_pointer _replacing_node(node_struct_pointer x) {
			if (x->left != NULL && x->right != NULL)
				return _successor(x->right);

			if (x->left == NULL && x->right == NULL)
				return NULL;

			if (x->left != NULL)
				return x->left;
			else
				return x->right;
		}

		void _swap_node_values(node_struct_pointer &u, node_struct_pointer &v) {
            ft::Node<T> tmp(v->value, v->parent, v->left, v->right, v->color);

            v->value = u->value;
            u->value = tmp.value;
		}

		void _delete_node(node_struct_pointer &v) {
			node_struct_pointer u = _replacing_node(v);

			bool uvBlack = ((u == NULL or u->color == BLACK) && (v->color == BLACK));
			node_struct_pointer parent = v->parent;

			if (u == NULL) {
				if (v == _tree_extrimities->parent) {
                    _free_node(v);
                    return;
				} else {
					if (uvBlack) {
						_fix_double_black(v);
					} else {
						if (_siblings(v) != NULL)
							_siblings(v)->color = RED;
					}

					if (_is_one_left(v)) {
						parent->left = NULL;
					} else {
						parent->right = NULL;
					}
				}
                _free_node(v);
				return;
			}

			if (v->left == NULL || v->right == NULL) {
				if (v == _tree_extrimities->parent){
                    u->parent = v->parent;
                    u->left = u->right = NULL;
                    _tree_extrimities->parent = u;
                    _free_node(v);
                } else {
					if (_is_one_left(v)) {
						parent->left = u;
					} else {
						parent->right = u;
					}
                    _free_node(v);
                    u->parent = parent;
					if (uvBlack) {
						_fix_double_black(u);
					} else {
						u->color = BLACK;
					}
				}
				return;
			}

			_swap_node_values(u, v);
			_delete_node(u);
		}

		void _fix_double_black(node_struct_pointer x) {
			if (x == _tree_extrimities->parent)
				return;

			node_struct_pointer brother = _siblings(x);
			node_struct_pointer parent = x->parent;
			if (brother == NULL) {
				_fix_double_black(parent);
			} else {
				if (brother->color == RED) {
					parent->color = RED;
					brother->color = BLACK;
					if (_is_one_left(brother)) {
						_right_rotate(parent);
					} else {
						_left_rotate(parent);
					}
					_fix_double_black(x);
				} else {
					if (hasRedChild(brother)) {
						if (brother->left != NULL && brother->left->color == RED) {
							if (_is_one_left(brother)) {
								brother->left->color = brother->color;
								brother->color = parent->color;
								_right_rotate(parent);
							} else {
								brother->left->color = parent->color;
								_right_rotate(brother);
								_left_rotate(parent);
							}
						} else {
							if (_is_one_left(brother)) {
								brother->right->color = parent->color;
								_left_rotate(brother);
								_right_rotate(parent);
							} else {
								brother->right->color = brother->color;
								brother->color = parent->color;
								_left_rotate(parent);
							}
						}
						parent->color = BLACK;
					} else {
						brother->color = RED;
						if (parent->color == BLACK)
							_fix_double_black(parent);
						else
							parent->color = BLACK;
					}
				}
			}
		}

		node_struct_pointer _successor(node_struct_pointer n){
			node_struct_pointer tmp = n;
			while (tmp && tmp->left != NULL)
				tmp = tmp->left;
			return tmp;
		}

		void _fix_extrimities_erase() {
            if (_size > 0)
            {
                node_struct_pointer tmp = _tree_extrimities->parent;
                while (tmp && tmp->left != NULL)
                    tmp = tmp->left;
                _tree_extrimities->left = tmp;
                tmp = _tree_extrimities->parent;
                while (tmp && tmp->right != NULL)
                    tmp = tmp->right;
                _tree_extrimities->right = tmp;
            }
            else
            {
                _tree_extrimities->right = _end_node;
                _tree_extrimities->parent = _end_node;
                _tree_extrimities->left = _end_node;
            }
            _tree_extrimities->right->right = _end_node;
            _end_node->parent = _tree_extrimities->right;
        }
	};
}

#endif

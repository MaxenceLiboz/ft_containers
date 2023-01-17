#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "../tree/Node.hpp"
#include "../tree/tree.hpp"
#include "../iterators/iterator.hpp"
#include "../iterators/iterator_traits.hpp"

namespace ft {

    template<class T>
    class tree_iterator;

    template<class T>
    class const_tree_iterator;


    template<class T>
    class tree_iterator : ft::iterator<std::bidirectional_iterator_tag, T> {
    public:
        typedef T value_type;

        /* The iterator category */
        typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;

        /* The value_type pointed by the iterator (BST)*/

        /* The difference type */
        typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::difference_type difference_type;

        /* The pointer to the value */
        typedef         value_type*                                                                 pointer;
        typedef         value_type&                                                                 reference;

        /* The reference to the value */

        typedef Node<T> *node_struct_pointer;

    private:

    public:
        node_struct_pointer _pointer;

        tree_iterator() : _pointer(0) {}

        tree_iterator(const tree_iterator<T> &it) {
            *this = it;
        }

        tree_iterator(const node_struct_pointer &src) {
            _pointer = src;
        }

        tree_iterator &operator=(const node_struct_pointer &src) {
            _pointer = src;
            return *this;
        }

        tree_iterator &operator=(const tree_iterator<T> &rhs) {
            if (*this != rhs)
                this->_pointer = rhs._pointer;
            return *this;
        }

        friend bool operator==(const tree_iterator<T> &lhs, const const_tree_iterator<T> &rhs) {
            return (lhs._pointer == rhs._pointer);
        }

        friend bool operator!=(const tree_iterator<T> &lhs, const const_tree_iterator<T> &rhs) {
            return !(lhs == rhs);
        }

        friend bool operator==(const tree_iterator<T> &lhs, const tree_iterator<T> &rhs) {
            return (lhs._pointer == rhs._pointer);
        }

        friend bool operator!=(const tree_iterator<T> &lhs, const tree_iterator<T> &rhs) {
            return !(lhs == rhs);
        }

        reference operator*() const { return *_pointer->value;}

        pointer operator->() const { return &operator*(); } // To change

        tree_iterator operator++(int) {
            tree_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        tree_iterator &operator++() {
            _pointer = _get_next_iter(_pointer);
            return *this;
        }

        tree_iterator operator--(int) {
            tree_iterator tmp(*this);
            --(*this);
            return tmp;
        }

        tree_iterator &operator--() {
            _pointer = _get_prev_iter(_pointer);
            return *this;
        }


    private:
        node_struct_pointer _get_next_iter(node_struct_pointer ptr) {
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

        node_struct_pointer _get_prev_iter(node_struct_pointer ptr) {
            if (ptr && ptr->left != NULL) {
                ptr = ptr->left;
                while (ptr->right != NULL)
                    ptr = ptr->right;
                return ptr;
            }
            while (ptr->parent && ptr->parent->left == ptr)
                ptr = ptr->parent;
            return ptr->parent;
        }

    };

    template<class T>
    class const_tree_iterator : ft::iterator<std::bidirectional_iterator_tag, T> {
    public:
        typedef T value_type;

        /* The iterator category */
        typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;

        /* The value_type pointed by the iterator (BST)*/

        /* The difference type */
        typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::difference_type difference_type;

        /* The pointer to the value */
        typedef         const value_type*                                                             pointer;
        typedef         const value_type&                                                             reference;

        /* The reference to the value */

        typedef Node<T> *node_struct_pointer;

    private:

    public:
        node_struct_pointer _pointer;

        const_tree_iterator() : _pointer(0) {}

        const_tree_iterator(const const_tree_iterator<T> &it) {
            *this = it;
        }

        const_tree_iterator(const tree_iterator<T> &it) {
            *this = it;
        }

        const_tree_iterator(const node_struct_pointer &src) {
            _pointer = src;
        }

        const_tree_iterator &operator=(const node_struct_pointer &src) {
            _pointer = src;
            return *this;
        }

        const_tree_iterator &operator=(const const_tree_iterator<T> &rhs) {
            if (*this != rhs)
                this->_pointer = rhs._pointer;
            return *this;
        }

        const_tree_iterator &operator=(const tree_iterator<T> &rhs) {
            if (*this != rhs)
                this->_pointer = rhs._pointer;
            return *this;
        }


        friend bool operator==(const const_tree_iterator<T> &lhs, const const_tree_iterator<T> &rhs) {
            return (lhs._pointer == rhs._pointer);
        }

        friend bool operator!=(const const_tree_iterator<T> &lhs, const const_tree_iterator<T> &rhs) {
            return !(lhs == rhs);
        }

        friend bool operator==(const const_tree_iterator<T> &lhs, const tree_iterator<T> &rhs) {
            return (lhs._pointer == rhs._pointer);
        }

        friend bool operator!=(const const_tree_iterator<T> &lhs, const tree_iterator<T> &rhs) {
            return !(lhs == rhs);
        }

        reference operator*() const { return *_pointer->value;}

        pointer operator->() const { return &operator*(); } // To change

        const_tree_iterator operator++(int) {
            const_tree_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        const_tree_iterator &operator++() {
            _pointer = _get_next_iter(_pointer);
            return *this;
        }

        const_tree_iterator operator--(int) {
            const_tree_iterator tmp(*this);
            --(*this);
            return tmp;
        }

        const_tree_iterator &operator--() {
            _pointer = _get_prev_iter(_pointer);
            return *this;
        }


    private:
        node_struct_pointer _get_next_iter(node_struct_pointer ptr) {
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

        node_struct_pointer _get_prev_iter(node_struct_pointer ptr) {
            if (ptr && ptr->left != NULL) {
                ptr = ptr->left;
                while (ptr->right != NULL)
                    ptr = ptr->right;
                return ptr;
            }
            while (ptr->parent && ptr->parent->left == ptr)
                ptr = ptr->parent;
            return ptr->parent;
        }

    };
}
#endif

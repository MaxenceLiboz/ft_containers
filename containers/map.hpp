#ifndef MAP_HPP
#define MAP_HPP

#include <memory>

#include "../includes/pair.hpp"
#include "../includes/equal.hpp"
#include "../includes/lexicographical_compare.hpp"
#include "../tree/tree.hpp"


namespace ft {
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type; 
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename ft::tree<value_type, allocator_type, key_compare>::iterator iterator;
        typedef typename ft::tree<value_type, allocator_type, key_compare>::reverse_iterator reverse_iterator;
        typedef typename ft::tree<value_type, allocator_type, key_compare>::const_iterator const_iterator;
        typedef typename ft::tree<value_type, allocator_type, key_compare>::const_reverse_iterator const_reverse_iterator;

        class value_compare {
            friend class map;

        protected:
            Compare comp;

            value_compare(Compare c) : comp(c) {}

        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;

            bool operator()(const value_type &x, const value_type &y) const {
                return comp(x.first, y.first);
            }
        };

    private:
        ft::tree<value_type, allocator_type, key_compare> _tree;
        allocator_type _allocator;
        key_compare _comp;
    public:

        /* ************************************************************************** */
        /* ----------------------- Constructors && Destructors ---------------------- */
        /* ************************************************************************** */
        explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(
                comp, alloc) {
        }

        template<class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type(),
            typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0): _tree(comp, alloc) {
            _tree.insert(first, last);
        }

        map(const map &x) : _tree(x._comp, x._allocator) {
            *this = x;
        }

        ~map() {}

        /* ************************************************************************** */
        /* ------------------------------- Operator '=' ----------------------------- */
        /* ************************************************************************** */
        map &operator=(const map &x) {
            if (this == &x)
                return *this;
            this->clear();
            this->insert(x.begin(), x.end());
            return *this;
        }

        /* ************************************************************************** */
        /* -------------------------------- Iterators ------------------------------- */
        /* ************************************************************************** */
        iterator begin() { return _tree.begin(); }

        const_iterator begin() const { return _tree.begin(); }

        reverse_iterator rbegin() { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

        iterator end() { return _tree.end(); }

        const_iterator end() const { return _tree.end(); }

        reverse_iterator rend() { return _tree.rend(); }

        const_reverse_iterator rend() const { return _tree.rend(); }

        iterator root() const { return _tree.root(); }
        /* ************************************************************************** */
        /* -------------------------------- Capacity -------------------------------- */
        /* ************************************************************************** */
        bool empty() const { return _tree.empty(); }

        size_type size() const { return _tree.size(); }

        size_type max_size() const { return _tree.max_size(); }

        /* ************************************************************************** */
        /* ----------------------------- Elements Access ---------------------------- */
        /* ************************************************************************** */
        mapped_type &operator[](const key_type &k) { return insert(ft::make_pair(k, T())).first->second; }

        /* ************************************************************************** */
        /* -------------------------------- Modifiers ------------------------------- */
        /* ************************************************************************** */
        ft::pair<iterator, bool> insert(const value_type &val) {
            iterator it;
            return _tree.insert(it, val);
        }

        iterator insert(iterator position, const value_type &val) { return _tree.insert(position, val).first; }

        template<class InputIterator>
        void insert(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
            _tree.insert(first, last);
        }

        void erase(iterator position) {
            _tree.erase(ft::make_pair(position->first, position->second));
            return;
        }

        size_type erase(const key_type &k) {
            mapped_type v;
            return _tree.erase(ft::make_pair(k, v));
        }

        void erase(iterator first, iterator last) {
            _tree.erase_range(first, last);
            return;
        }

        void swap(map &x) { _tree.swap(x._tree); }

        void clear() { this->erase(this->begin(), this->end()); }

        /* ************************************************************************** */
        /* -------------------------------- Observers ------------------------------- */
        /* ************************************************************************** */
        key_compare key_comp() const { return _comp; }

        value_compare value_comp() const {
            return value_compare(_comp);
        }

        /* ************************************************************************** */
        /* -------------------------------- Operations ------------------------------ */
        /* ************************************************************************** */
        iterator find(const key_type &k) {
            iterator it = _tree.lower_bound(k);
            return it->first == k ? it : this->end();
        }

        const_iterator find(const key_type &k) const {
            const_iterator it = _tree.lower_bound(k);
            return it->first == k ? it : this->end();
        }

        size_type count(const key_type &k) const {
            return _tree.count(k);
        }

        iterator lower_bound(const key_type &k) {
            iterator it = _tree.lower_bound(k);
            if (it->first < k && it != end())
                return ++it;
            return it;
        }

        const_iterator lower_bound(const key_type &k) const {
            const_iterator it = _tree.lower_bound(k);
            if (it->first < k && it != end())
                return ++it;
            return it;
        }


        iterator upper_bound(const key_type &k) {
            return _tree.upper_bound(k);
        }

        const_iterator upper_bound(const key_type &k) const {
            const_iterator it = _tree.upper_bound(k);
            return it;
        }

        pair<iterator, iterator> equal_range(const key_type &k) {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        /* ************************************************************************** */
        /* -------------------------------- Get allocator --------------------------- */
        /* ************************************************************************** */
        allocator_type get_allocator() const { return _allocator; }
        /* ************************************************************************** */
        /* -------------------------- Relationnal Operators ------------------------- */
        /* ************************************************************************** */
        friend bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
            if (lhs.size() != rhs.size())
                return false;
            return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
        }

        friend bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
            return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }

        friend bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
            return !(lhs == rhs);
        }

        friend bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
            return !(rhs < lhs);
        }

        friend bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
            return rhs < lhs;
        }

        friend bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
            return !(lhs < rhs);
        }

	};

	template< class Key, class T, class Compare, class Alloc>
	void swap( ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs ){
		lhs.swap(rhs);
	}

}
#endif

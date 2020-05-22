/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * \author Stefano Crotti
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "bst_private.h"
#include <stdio.h>
#include <stdlib.h>


/**** BEGIN of FUNDAMENTAL OPERATIONS ****/


upo_bst_t upo_bst_create(upo_bst_comparator_t key_cmp)
{
    upo_bst_t tree = malloc(sizeof(struct upo_bst_s));
    if (tree == NULL)
    {
        perror("Unable to create a binary search tree");
        abort();
    }

    tree->root = NULL;
    tree->key_cmp = key_cmp;

    return tree;
}

upo_bst_node_t *upo_bst_node_create(void *key,void *value) {
    upo_bst_node_t *node = malloc(sizeof(upo_bst_node_t *));

    if (node == NULL) {
        perror("Unable to create a node");
        abort();
    }

    node->value = value;
    node->key = key;

    return node;
}

void upo_bst_destroy(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear(tree, destroy_data);
        free(tree);
    }
}

void upo_bst_destroy_node(upo_bst_node_t *node, int destroy_data)
{
    if (node != NULL)
    {
        if (destroy_data)
        {
            free(node->key);
            free(node->value);
        }
        free(node);
    }
}

void upo_bst_clear_impl(upo_bst_node_t *node, int destroy_data)
{
    if (node != NULL)
    {
        upo_bst_clear_impl(node->left, destroy_data);
        upo_bst_clear_impl(node->right, destroy_data);

        if (destroy_data)
        {
            free(node->key);
            free(node->value);
        }

        free(node);
    }
}

void upo_bst_clear(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear_impl(tree->root, destroy_data);
        tree->root = NULL;
    }
}

void* upo_bst_put(upo_bst_t tree, void *key, void *value)
{
    if (tree == NULL)
        return NULL;

    void *old_value = NULL;

    tree->root = upo_bst_put_impl(tree->root, key, value, old_value, upo_bst_get_comparator(tree));

    return old_value;
}

upo_bst_node_t* upo_bst_put_impl(upo_bst_node_t* node, void* key, void* value, void* old_value, upo_bst_comparator_t key_cmp) {
    old_value = NULL;

    if (node == NULL)
        return upo_bst_node_create(key, value);

    else if(key_cmp(key, node->key) < 0)
        node->left = upo_bst_put_impl(node->left, key, value, old_value, key_cmp);

    else if(key_cmp(key, node->key) > 0)
        node->right = upo_bst_put_impl(node->right, key, value, old_value, key_cmp);

    else {
        old_value = node->value;
        node->value = value;
    }

    return node;
}

void upo_bst_insert(upo_bst_t tree, void *key, void *value)
{
    tree->root = upo_bst_insert_impl(tree->root, key, value, upo_bst_get_comparator(tree));
}

upo_bst_node_t *upo_bst_insert_impl(upo_bst_node_t *node, void *key, void *value, upo_bst_comparator_t key_cmp) {
    if (node == NULL)
        return upo_bst_node_create(key, value);

    else if(key_cmp(key, node->key) < 0)
        node->left = upo_bst_insert_impl(node->left, key, value, key_cmp);

    else if(key_cmp(key, node->key) > 0)
        node->right = upo_bst_insert_impl(node->right, key, value, key_cmp);

    return node;
}

void* upo_bst_get(const upo_bst_t tree, const void *key)
{
    upo_bst_node_t* node = upo_bst_get_impl(tree->root, key, upo_bst_get_comparator(tree));

    if (node != NULL)
        return node->value;

    else
        return NULL;
}

void *upo_bst_get_impl(upo_bst_node_t* node, const void* key, upo_bst_comparator_t key_cmp) {
    if (node == NULL)
        return NULL;

    if (key_cmp(key, node->key) < 0)
        return upo_bst_get_impl(node->left, key, key_cmp);

    else if(key_cmp(key, node->key) > 0)
        return upo_bst_get_impl(node->right, key, key_cmp);

    else
        return node;
}

int upo_bst_contains(const upo_bst_t tree, const void *key)
{
   if (upo_bst_get_impl(tree->root, key, upo_bst_get_comparator(tree)) != NULL)
       return 1;
   else
       return 0;
}

void upo_bst_delete(upo_bst_t tree, const void *key, int destroy_data)
{
    tree->root = upo_bst_delete_impl(tree->root, key, upo_bst_get_comparator(tree), destroy_data);
}

upo_bst_node_t *upo_bst_delete_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t key_cmp, int destroy_data) {
    if (node == NULL)
        return NULL;

    if (key_cmp(key, node->key) < 0)
        node->left = upo_bst_delete_impl(node->left, key, key_cmp, destroy_data);

    else if (key_cmp(key, node->key) > 0)
        node->right = upo_bst_delete_impl(node->right, key, key_cmp, destroy_data);

    else if (node->left != NULL && node->right != NULL)
        node = upo_bst_delete2C_impl(node, key_cmp, destroy_data);

    else
        node = upo_bst_delete1C_impl(node, destroy_data);

    return node;
}

upo_bst_node_t *upo_bst_delete1C_impl(upo_bst_node_t *node, int destroy_data) {
    upo_bst_node_t *tmp = node;

    if (node->left != NULL)
        node = node->left;

    else
        node = node->right;

    upo_bst_destroy_node(tmp, destroy_data);

    return node;
}

upo_bst_node_t *upo_bst_delete2C_impl(upo_bst_node_t *node, upo_bst_comparator_t key_cmp, int destroy_data) {
    upo_bst_node_t* max = upo_bst_delete_max_impl(node->left);

    node->key = max->key;

    node->value = max->value;

    node->left = upo_bst_delete_impl(node->left, max->key, key_cmp, destroy_data);

    return node;
}

upo_bst_node_t *upo_bst_delete_max_impl(upo_bst_node_t* node) {
    if (node == NULL)
        return NULL;

    else if (node->right != NULL)
        return upo_bst_delete_max_impl(node->right);

    else
        return node;
}

size_t upo_bst_size(const upo_bst_t tree)
{
    return upo_bst_size_impl(tree->root);
}

size_t upo_bst_size_impl(upo_bst_node_t* node) {
    if (node == NULL)
        return 0;

    return 1 + upo_bst_size_impl(node->left) + upo_bst_size_impl(node->right);
}

size_t upo_bst_height(const upo_bst_t tree)
{
    return upo_bst_height_impl(tree->root);
}

size_t upo_bst_height_impl(upo_bst_node_t* node) {
    if (node == NULL || upo_bst_is_leaf_impl(node))
        return 0;

    return 1 + upo_bst_height_max(upo_bst_height_impl(node->left), upo_bst_height_impl(node->right));
}

int upo_bst_is_leaf_impl(upo_bst_node_t *node) {

    return (node->left == NULL && node->right == NULL) ? 1 : 0;
}

size_t upo_bst_height_max(size_t a, size_t b) {
   return (a >= b) ? a : b;
}

void upo_bst_traverse_in_order(const upo_bst_t tree, upo_bst_visitor_t visit, void *visit_arg) {

    upo_bst_traverse_in_order_impl(tree->root, visit, visit_arg);
}

void upo_bst_traverse_in_order_impl(upo_bst_node_t *node, upo_bst_visitor_t visit, void *visit_arg) {

    if (node == NULL)
    {
        upo_bst_traverse_in_order_impl(node->left, visit, visit_arg);

        visit(node->key, node->value, visit_arg);

        upo_bst_traverse_in_order_impl(node->right, visit, visit_arg);
    }
}

int upo_bst_is_empty(const upo_bst_t tree)
{
    return (tree == NULL || tree->root == NULL) ? 1 : 0;
}


/**** END of FUNDAMENTAL OPERATIONS ****/


/**** BEGIN of EXTRA OPERATIONS ****/


void* upo_bst_min(const upo_bst_t tree)
{
    void *min = NULL;

    if (tree == NULL)
        return NULL;

    upo_bst_min_impl(tree->root, min);

    return min;
}

void upo_bst_min_impl(upo_bst_node_t *node, void *min) {

    if (node->right == NULL && node->left == NULL) {
        min = node->key;
        return;
    }

    else {
        if (min == NULL)
            min = node->key;

        if (node->left->key <= min)
            min = node->left->key;

        else if (node->right->key <= min)
            min = node->right->key;

        upo_bst_min_impl(node->left, min);
        upo_bst_min_impl(node->right, min);
    }
}

void* upo_bst_max(const upo_bst_t tree)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void upo_bst_delete_min(upo_bst_t tree, int destroy_data)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void upo_bst_delete_max(upo_bst_t tree, int destroy_data)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void* upo_bst_floor(const upo_bst_t tree, const void *key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void* upo_bst_ceiling(const upo_bst_t tree, const void *key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

upo_bst_key_list_t upo_bst_keys_range(const upo_bst_t tree, const void *low_key, const void *high_key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

upo_bst_key_list_t upo_bst_keys(const upo_bst_t tree)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

int upo_bst_is_bst(const upo_bst_t tree, const void *min_key, const void *max_key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}


/**** END of EXTRA OPERATIONS ****/


upo_bst_comparator_t upo_bst_get_comparator(const upo_bst_t tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    return tree->key_cmp;
}

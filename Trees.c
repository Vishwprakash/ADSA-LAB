#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define T 3
#define ORDER 3

// _________________ 1. AVL TREE ________________________
typedef struct AVLNode
{
    int val, ht;
    struct AVLNode *left, *right;
} AVLNode;

int H(AVLNode *n) { return n ? n->ht : 0; }
int B(AVLNode *n) { return n ? H(n->left) - H(n->right) : 0; }

AVLNode *new_avl(int v)
{
    AVLNode *n = calloc(1, sizeof(*n));
    n->val = v;
    n->ht = 1;
    return n;
}

AVLNode *rot(AVLNode *y, int dir)
{ // dir 0: Right, 1: Left
    AVLNode *x = dir ? y->right : y->left, *T2 = dir ? x->left : x->right;
    if (dir)
    {
        y->right = T2;
        x->left = y;
    }
    else
    {
        y->left = T2;
        x->right = y;
    }
    y->ht = 1 + MAX(H(y->left), H(y->right));
    x->ht = 1 + MAX(H(x->left), H(x->right));
    return x;
}

AVLNode *avl_ins(AVLNode *n, int v)
{
    if (!n)
        return new_avl(v);
    if (v < n->val)
        n->left = avl_ins(n->left, v);
    else if (v > n->val)
        n->right = avl_ins(n->right, v);
    else
        return n;

    n->ht = 1 + MAX(H(n->left), H(n->right));
    int b = B(n);
    if (b > 1 && v < n->left->val)
        return rot(n, 0);
    if (b < -1 && v > n->right->val)
        return rot(n, 1);
    if (b > 1 && v > n->left->val)
    {
        n->left = rot(n->left, 1);
        return rot(n, 0);
    }
    if (b < -1 && v < n->right->val)
    {
        n->right = rot(n->right, 0);
        return rot(n, 1);
    }
    return n;
}

AVLNode *avl_del(AVLNode *r, int v)
{
    if (!r)
        return NULL;
    if (v < r->val)
        r->left = avl_del(r->left, v);
    else if (v > r->val)
        r->right = avl_del(r->right, v);
    else
    {
        if (!r->left || !r->right)
        {
            AVLNode *tmp = r->left ? r->left : r->right;
            if (!tmp)
            {
                free(r);
                return NULL;
            }
            *r = *tmp;
            free(tmp);
        }
        else
        {
            AVLNode *m = r->right;
            while (m->left)
                m = m->left;
            r->val = m->val;
            r->right = avl_del(r->right, m->val);
        }
    }
    r->ht = 1 + MAX(H(r->left), H(r->right));
    int b = B(r);
    if (b > 1 && B(r->left) >= 0)
        return rot(r, 0);
    if (b > 1 && B(r->left) < 0)
    {
        r->left = rot(r->left, 1);
        return rot(r, 0);
    }
    if (b < -1 && B(r->right) <= 0)
        return rot(r, 1);
    if (b < -1 && B(r->right) > 0)
    {
        r->right = rot(r->right, 0);
        return rot(r, 1);
    }
    return r;
}

int avl_src(AVLNode *r, int v) { return !r ? 0 : r->val == v ? 1
                                                             : (v < r->val ? avl_src(r->left, v) : avl_src(r->right, v)); }
void avl_disp(AVLNode *r)
{
    if (r)
    {
        avl_disp(r->left);
        printf("%d ", r->val);
        avl_disp(r->right);
    }
}

// __________________________ 2. RED-BLACK TREE _______________________
enum Color
{
    RED,
    BLACK
};
typedef struct RBNode
{
    int val;
    enum Color color;
    struct RBNode *left, *right, *parent;
} RBNode;

RBNode *rb_root = NULL;

RBNode *new_rb(int v)
{
    RBNode *n = calloc(1, sizeof(*n));
    n->val = v;
    n->color = RED;
    return n;
}

void rb_rot(RBNode *x, int left)
{
    RBNode *y = left ? x->right : x->left;
    if (left)
    {
        x->right = y->left;
        if (y->left)
            y->left->parent = x;
    }
    else
    {
        x->left = y->right;
        if (y->right)
            y->right->parent = x;
    }
    y->parent = x->parent;
    if (!x->parent)
        rb_root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    if (left)
    {
        y->left = x;
        x->parent = y;
    }
    else
    {
        y->right = x;
        x->parent = y;
    }
}

void rb_ins_fix(RBNode *z)
{
    while (z->parent && z->parent->color == RED)
    {
        int is_left = (z->parent == z->parent->parent->left);
        RBNode *u = is_left ? z->parent->parent->right : z->parent->parent->left;
        if (u && u->color == RED)
        {
            z->parent->color = u->color = BLACK;
            z->parent->parent->color = RED;
            z = z->parent->parent;
        }
        else
        {
            if (z == (is_left ? z->parent->right : z->parent->left))
            {
                z = z->parent;
                rb_rot(z, is_left);
            }
            z->parent->color = BLACK;
            z->parent->parent->color = RED;
            rb_rot(z->parent->parent, !is_left);
        }
    }
    rb_root->color = BLACK;
}

void rb_ins(int v)
{
    RBNode *z = new_rb(v), *y = NULL, *x = rb_root;
    while (x)
    {
        y = x;
        x = (v < x->val) ? x->left : x->right;
    }
    z->parent = y;
    if (!y)
        rb_root = z;
    else if (v < y->val)
        y->left = z;
    else
        y->right = z;
    rb_ins_fix(z);
}

void rb_transplant(RBNode *u, RBNode *v)
{
    if (!u->parent)
        rb_root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v)
        v->parent = u->parent;
}

void rb_del_fix(RBNode *x, RBNode *xp)
{
    while (x != rb_root && (!x || x->color == BLACK))
    {
        int left = (x == (xp ? xp->left : NULL));
        RBNode *w = left ? xp->right : xp->left;
        if (w && w->color == RED)
        {
            w->color = BLACK;
            xp->color = RED;
            rb_rot(xp, left);
            w = left ? xp->right : xp->left;
        }
        if ((!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK))
        {
            if (w)
                w->color = RED;
            x = xp;
            xp = x ? x->parent : NULL;
        }
        else
        {
            if (left ? (!w->right || w->right->color == BLACK) : (!w->left || w->left->color == BLACK))
            {
                if (left ? w->left : w->right)
                    (left ? w->left : w->right)->color = BLACK;
                w->color = RED;
                rb_rot(w, !left);
                w = left ? xp->right : xp->left;
            }
            w->color = xp->color;
            xp->color = BLACK;
            if (left ? w->right : w->left)
                (left ? w->right : w->left)->color = BLACK;
            rb_rot(xp, left);
            x = rb_root;
        }
    }
    if (x)
        x->color = BLACK;
}

void rb_del(int val)
{
    RBNode *z = rb_root;
    while (z && z->val != val)
        z = (val < z->val) ? z->left : z->right;
    if (!z)
        return;
    RBNode *y = z, *x, *xp;
    enum Color y_orig = y->color;
    if (!z->left)
    {
        x = z->right;
        xp = z->parent;
        rb_transplant(z, z->right);
    }
    else if (!z->right)
    {
        x = z->left;
        xp = z->parent;
        rb_transplant(z, z->left);
    }
    else
    {
        y = z->right;
        while (y->left)
            y = y->left;
        y_orig = y->color;
        x = y->right;
        if (y->parent == z)
            xp = y;
        else
        {
            xp = y->parent;
            rb_transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rb_transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (y_orig == BLACK)
        rb_del_fix(x, xp);
}

int rb_src(RBNode *r, int v) { return !r ? 0 : r->val == v ? 1
                                                           : rb_src(v < r->val ? r->left : r->right, v); }
void rb_disp(RBNode *r)
{
    if (r)
    {
        rb_disp(r->left);
        printf("%d(%c) ", r->val, r->color == RED ? 'R' : 'B');
        rb_disp(r->right);
    }
}

// _______________________ 3. B-TREE __________________________
typedef struct BNode
{
    int keys[2 * T - 1], n, is_leaf;
    struct BNode *child[2 * T];
} BNode;

BNode *new_bt(int is_leaf)
{
    BNode *n = calloc(1, sizeof(*n));
    n->is_leaf = is_leaf;
    return n;
}
int bt_find(BNode *n, int k)
{
    int i = 0;
    while (i < n->n && n->keys[i] < k)
        i++;
    return i;
}

void bt_split(BNode *p, int i)
{
    BNode *c = p->child[i], *z = new_bt(c->is_leaf);
    z->n = T - 1;
    for (int j = 0; j < T - 1; j++)
        z->keys[j] = c->keys[j + T];
    if (!c->is_leaf)
        for (int j = 0; j < T; j++)
            z->child[j] = c->child[j + T];
    c->n = T - 1;
    for (int j = p->n; j >= i + 1; j--)
        p->child[j + 1] = p->child[j];
    p->child[i + 1] = z;
    for (int j = p->n - 1; j >= i; j--)
        p->keys[j + 1] = p->keys[j];
    p->keys[i] = c->keys[T - 1];
    p->n++;
}

void bt_ins_nf(BNode *n, int k)
{
    int i = n->n - 1;
    if (n->is_leaf)
    {
        while (i >= 0 && n->keys[i] > k)
        {
            n->keys[i + 1] = n->keys[i];
            i--;
        }
        n->keys[i + 1] = k;
        n->n++;
    }
    else
    {
        while (i >= 0 && n->keys[i] > k)
            i--;
        if (n->child[++i]->n == 2 * T - 1)
        {
            bt_split(n, i);
            if (n->keys[i] < k)
                i++;
        }
        bt_ins_nf(n->child[i], k);
    }
}

void bt_ins(BNode **root, int k)
{
    if (!*root)
    {
        *root = new_bt(1);
        (*root)->keys[0] = k;
        (*root)->n = 1;
        return;
    }
    BNode *r = *root;
    if (r->n == 2 * T - 1)
    {
        BNode *s = new_bt(0);
        s->child[0] = r;
        bt_split(s, 0);
        *root = s;
        bt_ins_nf(s, k);
    }
    else
        bt_ins_nf(r, k);
}

void bt_merge(BNode *n, int idx)
{
    BNode *c = n->child[idx], *s = n->child[idx + 1];
    c->keys[T - 1] = n->keys[idx];
    for (int i = 0; i < s->n; i++)
        c->keys[i + T] = s->keys[i];
    if (!c->is_leaf)
        for (int i = 0; i <= s->n; i++)
            c->child[i + T] = s->child[i];
    for (int i = idx + 1; i < n->n; i++)
        n->keys[i - 1] = n->keys[i];
    for (int i = idx + 2; i <= n->n; i++)
        n->child[i - 1] = n->child[i];
    c->n += s->n + 1;
    n->n--;
    free(s);
}

void bt_del_node(BNode *n, int k)
{
    int idx = bt_find(n, k);
    if (idx < n->n && n->keys[idx] == k)
    {
        if (n->is_leaf)
        {
            for (int i = idx + 1; i < n->n; i++)
                n->keys[i - 1] = n->keys[i];
            n->n--;
        }
        else
        {
            BNode *p = n->child[idx];
            if (p->n >= T)
            {
                while (!p->is_leaf)
                    p = p->child[p->n];
                int pk = p->keys[p->n - 1];
                n->keys[idx] = pk;
                bt_del_node(n->child[idx], pk);
            }
            else
                bt_merge(n, idx), bt_del_node(n->child[idx], k);
        }
    }
    else
    {
        if (n->is_leaf)
            return;
        int flag = (idx == n->n);
        if (n->child[idx]->n < T)
        {
            if (idx != 0 && n->child[idx - 1]->n >= T)
            {
                BNode *c = n->child[idx], *p = n->child[idx - 1];
                for (int i = c->n - 1; i >= 0; i--)
                    c->keys[i + 1] = c->keys[i];
                if (!c->is_leaf)
                    for (int i = c->n; i >= 0; i--)
                        c->child[i + 1] = c->child[i];
                c->keys[0] = n->keys[idx - 1];
                if (!c->is_leaf)
                    c->child[0] = p->child[p->n];
                n->keys[idx - 1] = p->keys[p->n - 1];
                c->n++;
                p->n--;
            }
            else if (idx != n->n && n->child[idx + 1]->n >= T)
            {
                BNode *c = n->child[idx], *s = n->child[idx + 1];
                c->keys[c->n] = n->keys[idx];
                if (!c->is_leaf)
                    c->child[c->n + 1] = s->child[0];
                n->keys[idx] = s->keys[0];
                for (int i = 1; i < s->n; i++)
                    s->keys[i - 1] = s->keys[i];
                if (!s->is_leaf)
                    for (int i = 1; i <= s->n; i++)
                        s->child[i - 1] = s->child[i];
                c->n++;
                s->n--;
            }
            else
                bt_merge(n, idx != n->n ? idx : idx - 1);
        }
        bt_del_node(n->child[flag && idx > n->n ? idx - 1 : idx], k);
    }
}

void bt_del(BNode **root, int k)
{
    if (!*root)
        return;
    bt_del_node(*root, k);
    if ((*root)->n == 0)
    {
        BNode *tmp = *root;
        *root = (*root)->is_leaf ? NULL : (*root)->child[0];
        free(tmp);
    }
}

int bt_src(BNode *r, int k)
{
    if (!r)
        return 0;
    int i = bt_find(r, k);
    return (i < r->n && r->keys[i] == k) ? 1 : (r->is_leaf ? 0 : bt_src(r->child[i], k));
}

void bt_disp(BNode *r)
{
    if (!r)
        return;
    for (int i = 0; i < r->n; i++)
    {
        if (!r->is_leaf)
            bt_disp(r->child[i]);
        printf("%d ", r->keys[i]);
    }
    if (!r->is_leaf)
        bt_disp(r->child[r->n]);
}

// ___________________ 4. B+ TREE ______________________
typedef struct BPNode
{
    int keys[ORDER], n, is_leaf;
    struct BPNode *child[ORDER + 1], *next;
} BPNode;

BPNode *new_bp(int is_leaf)
{
    BPNode *n = calloc(1, sizeof(*n));
    n->is_leaf = is_leaf;
    return n;
}

BPNode *bp_get_leaf(BPNode *r, int val)
{
    while (r && !r->is_leaf)
    {
        int i = 0;
        while (i < r->n && val >= r->keys[i])
            i++;
        r = r->child[i];
    }
    return r;
}

void bp_ins(BPNode **root, int val)
{
    if (!*root)
    {
        *root = new_bp(1);
        (*root)->keys[0] = val;
        (*root)->n = 1;
        return;
    }
    BPNode *leaf = bp_get_leaf(*root, val);
    int i = leaf->n - 1;
    while (i >= 0 && leaf->keys[i] > val)
    {
        leaf->keys[i + 1] = leaf->keys[i];
        i--;
    }
    leaf->keys[i + 1] = val;
    leaf->n++;
}

void bp_del(BPNode **root, int val)
{
    if (!*root)
        return;
    BPNode *leaf = bp_get_leaf(*root, val);
    for (int i = 0; i < leaf->n; i++)
    {
        if (leaf->keys[i] == val)
        {
            for (int j = i; j < leaf->n - 1; j++)
                leaf->keys[j] = leaf->keys[j + 1];
            leaf->n--;
            break;
        }
    }
}

int bp_src(BPNode *root, int val)
{
    BPNode *leaf = bp_get_leaf(root, val);
    for (int i = 0; leaf && i < leaf->n; i++)
        if (leaf->keys[i] == val)
            return 1;
    return 0;
}

void bp_disp(BPNode *root)
{
    BPNode *leaf = root;
    while (leaf && !leaf->is_leaf)
        leaf = leaf->child[0];
    while (leaf)
    {
        for (int i = 0; i < leaf->n; i++)
            printf("%d ", leaf->keys[i]);
        leaf = leaf->next;
    }
}

// ________________________ MAIN FUNCTION ____________________________
int main()
{
    int t, op, v;
    AVLNode *avl = NULL;
    BNode *bt = NULL;
    BPNode *bp = NULL;

    while (1)
    {
        printf("\n\n1.AVL 2.RB 3.B-Tree 4.B+ Tree 5.Exit\nChoice: ");
        if (scanf("%d", &t) != 1 || t == 5)
            break;

        while (1)
        {
            printf("\n1.Ins 2.Del 3.Src 4.Disp 5.Back\nChoice: ");
            if (scanf("%d", &op) != 1 || op == 5)
                break;

            if (op == 1)
            {
                printf("Val: ");
                scanf("%d", &v);
                if (t == 1)
                    avl = avl_ins(avl, v);
                else if (t == 2)
                    rb_ins(v);
                else if (t == 3)
                    bt_ins(&bt, v);
                else if (t == 4)
                    bp_ins(&bp, v);
            }
            else if (op == 2)
            {
                printf("Val: ");
                scanf("%d", &v);
                if (t == 1)
                    avl = avl_del(avl, v);
                else if (t == 2)
                    rb_del(v);
                else if (t == 3)
                    bt_del(&bt, v);
                else if (t == 4)
                    bp_del(&bp, v);
            }
            else if (op == 3)
            {
                printf("Val: ");
                scanf("%d", &v);
                int f = (t == 1) ? avl_src(avl, v) : (t == 2) ? rb_src(rb_root, v)
                                                 : (t == 3)   ? bt_src(bt, v)
                                                              : bp_src(bp, v);
                printf(f ? "Found %d\n" : "Not Found %d\n", v);
            }
            else if (op == 4)
            {
                printf("Tree: ");
                if (t == 1)
                    avl_disp(avl);
                else if (t == 2)
                    rb_disp(rb_root);
                else if (t == 3)
                    bt_disp(bt);
                else if (t == 4)
                    bp_disp(bp);
                printf("\n");
            }
        }
    }
    return 0;
}

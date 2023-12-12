package AVL;

import java.util.ArrayList;

public class AVL {
    Node root;
    int height(Node node){
        if(node==null) return 0;
        return node.height;
    }
    Node rotate_right(Node y){
        Node x=y.left;
        Node b=x.right;
        x.right=y;
        y.left=b;
        y.height=Math.max(height(y.left),height(y.right))+1;
        x.height=Math.max(height(x.left), height(x.right)) + 1;
        return x;
    }
    Node rotate_left(Node x){
        Node y=x.right;
        Node a = y.left;
        y.left = x;
        x.right = a;
        x.height = Math.max(height(x.left), height(x.right)) + 1;
        y.height = Math.max(height(y.left), height(y.right)) + 1;
        return y;
    }
    Node insert(Node node,int new_data){
        if(node==null) return new Node(new_data);
        if(new_data<node.data){
            node.left=insert(node.left,new_data);
        }
        else{
            node.right=insert(node.right,new_data);
        }
        node.height=Math.max(height(node.left),height(node.right))+1;
        int balance_factor=get_balance_factor(node);
        if (balance_factor > 1 && new_data < node.left.data) {
            return rotate_right(node);
        }
        if (balance_factor < -1 && new_data > node.right.data) {
            return rotate_left(node);
        }
        if (balance_factor > 1 && new_data > node.left.data) {
            node.left = rotate_left(node.left);
            return rotate_right(node);
        }
        if (balance_factor < -1 && new_data < node.right.data) {
            node.right = rotate_right(node.right);
            return rotate_left(node);
        }
        return node;
    }
    int get_balance_factor(Node node){
        if(node==null) return 0;
        return height(node.left)-height(node.right);
    }
    void print_tree(Node node){
        if(node==null) return;
        System.out.print(node.data);
        if(node.left!=null || node.right!=null){
            System.out.print("(");
            print_tree(node.left);
            System.out.print(",");
            print_tree(node.right);
            System.out.print(")");
        }
        return;
    }
    Node delete_help(Node node,int val){
        if(node==null) return node;
        if(val<node.data){
            node.left=delete_help(node.left,val);
        }
        else if(val>node.data){
            node.right=delete_help(node.right,val);
        }
        else{
            if(node.left==null || node.right==null){
                Node non_empty=node.left;
                if(non_empty==null) non_empty=node.right;
                if(non_empty==null){
                    node=null;
                }
                else{
                    node=non_empty;
                }
            }
            else{
                Node new_node=inorder(node.right);
                node.data=new_node.data;
                node.right=delete_help(node.right,node.data);
            }
        }
        if(node==null) return node;
        node.height=Math.max(height(node.left),height(node.right))+1;
        int balance_factor=get_balance_factor(node);
        if (balance_factor > 1 && get_balance_factor(node.left) >= 0)
            return rotate_right(node);
        if (balance_factor > 1 && get_balance_factor(node.left) < 0)
        {
            node.left = rotate_left(node.left);
            return rotate_right(node);
        }
        if (balance_factor < -1 && get_balance_factor(node.right) <= 0)
            return rotate_left(node);
        if (balance_factor < -1 && get_balance_factor(node.right) > 0)
        {
            node.right = rotate_right(node.right);
            return rotate_left(node);
        }
        return node;

    }

    Node inorder(Node node) {
        if(node.left==null) return node;
        return inorder(node.left);
    }
    Node find(Node node,int val){
        if(node==null) return node;
        if(node.data==val) return node;
        if(val<node.data) return find(node.left,val);
        return find(node.right,val);
    }
    ArrayList<Integer> print_in_order(Node node){
        ArrayList<Integer> nodes=new ArrayList<>();
        print_in_order_help(node,nodes);
        return nodes;
    }
    void print_in_order_help(Node node, ArrayList<Integer> nodes){
        if(node==null) return;
        print_in_order_help(node.left,nodes);
        if(node!=null) nodes.add(node.data);
        print_in_order_help(node.right,nodes);
    }
}

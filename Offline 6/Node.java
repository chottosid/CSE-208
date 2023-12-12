package BinHeap;

public class Node {
    int data, degree;
    Node parent, left_child, right_sibling;
    public Node(int data, Node parent, Node left_child, Node right_sibling) {
        this.data = data;
        this.parent = parent;
        this.left_child = left_child;
        this.right_sibling = right_sibling;
        this.degree = 0;
    }
    public Node(int data) {
        this(data, null, null, null);
    }
}

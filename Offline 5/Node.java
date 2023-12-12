package AVL;
public class Node {
    int data;
    int height;
    Node left,right;
    Node(int data){
        this.data=data;
        height=1;
        left=right=null;
    }
}

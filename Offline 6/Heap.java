package BinHeap;
public class Heap {
    private static final int INF = Integer.MAX_VALUE - 1; //Sentinel Value
    Node head;

    public Heap() {
        head = null;
    }

    Node find_min() {   //traverses root list, runs in log(n)
        Node y = null;
        Node x = head;
        int mn = INF;
        while (x != null) {
            if (x.data < mn) {
                mn = x.data;
                y = x;
            }
            x = x.right_sibling;
        }
        return y;
    }

    void bin_link(Node y, Node z) {     //makes y left child of z, basically turns B_k y,z into B_(k+1) z
        y.parent = z;
        y.right_sibling = z.left_child;
        z.left_child = y;
        z.degree = z.degree + 1;
    }

    Heap bin_union(Heap h1, Heap h2) {      //unions two given heap, log(n)
        Heap h = new Heap();
        h.head = bin_merge(h1, h2); //new heap with rootlist sorted in asc of degree with duplications

        if (h.head == null) {
            return h;
        }

        Node prev = null;
        Node x = h.head;
        Node next = x.right_sibling;
        while (next != null) {  //sorts out duplication in new heap's root list, log(n)
            if (x.degree != next.degree || (next.right_sibling != null && next.right_sibling.degree != x.degree)) {
                prev = x;
                x = next;
            } else {
                if (x.data < next.data) {
                    x.right_sibling = next.right_sibling;
                    bin_link(next, x);
                } else {
                    if (prev == null) {
                        h.head = next;
                    } else {
                        prev.right_sibling = next;
                    }
                    bin_link(x, next);
                    x = next;
                }
            }
            next = x.right_sibling;
        }
        return h;
    }

    Node bin_merge(Heap h1, Heap h2) {  //merge two heap's root list, log(n)
        Node temp1 = h1.head;
        Node temp2 = h2.head;
        Node head = null;
        Node tail = null;
        if (temp1 == null) {
            return temp2;
        }
        if (temp2 == null) {
            return temp1;
        }
        if (temp1.degree <= temp2.degree) {
            head = temp1;
            temp1 = temp1.right_sibling;
        } else {
            head = temp2;
            temp2 = temp2.right_sibling;
        }
        tail = head;
        while (temp1 != null && temp2 != null) {
            if (temp1.degree <= temp2.degree) {
                tail.right_sibling = temp1;
                temp1 = temp1.right_sibling;
            } else {
                tail.right_sibling = temp2;
                temp2 = temp2.right_sibling;
            }
            tail = tail.right_sibling;
        }

        if (temp1 != null) {
            tail.right_sibling = temp1;
        } else {
            tail.right_sibling = temp2;
        }

        return head;
    }

    void insert(int data) { //log(n)
        Node x = new Node(data);
        Heap h = new Heap();
        x.parent = null;
        x.right_sibling = null;
        x.left_child = null;
        x.degree = 0;
        h.head = x;
        this.head = bin_union(this, h).head;
    }



    int extract_min() {     //removes min node from root list, arrange min nodes childs in reverse order,
        Node temp = head;   // create new heap of them and merge heaps.
        Node prev = null;   // log(n)
        Node y = null;
        Node y_prev = null;
        int mn = INF;

        while (temp != null) {
            if (temp.data < mn) {
                y = temp;
                y_prev = prev;
                mn = y.data;
            }
            prev = temp;
            temp = temp.right_sibling;
        }

        if (y == null) {
            return INF;
        }

        if (y_prev == null) {
            head = y.right_sibling;
        } else {
            y_prev.right_sibling = y.right_sibling;
        }

        Heap h_new = new Heap();
        Node tempChild = y.left_child;
        Node prevChild = null;

        while (tempChild != null) {     //reverses child list
            Node nextChild = tempChild.right_sibling;
            tempChild.right_sibling = prevChild;
            prevChild = tempChild;
            tempChild = nextChild;
        }

        h_new.head = prevChild;
        Heap heap = bin_union(this, h_new);
        head = heap.head;

        return y.data;
    }

    public void print() {
        System.out.println("Printing Binomial Heap...");
        Node temp=head;
        while (temp!=null){
            print_help(temp);
            temp=temp.right_sibling;
        }
    }
    private void print_help(Node root){
        System.out.println("Binomial Tree, B"+root.degree);
        System.out.println("Level 0 : "+root.data);
        for(int level=1;level<=root.degree;level++){
            Node temp=root;
            System.out.print("Level "+level+" : ");
            for(int i=0;i<level;i++){
                temp=temp.left_child;
            }
            while (temp!=null){
                System.out.print(temp.data+" ");
                temp=temp.right_sibling;
            }
            System.out.println();
        }
    }
}

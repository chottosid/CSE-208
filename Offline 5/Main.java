package AVL;

import java.io.*;
import java.sql.Time;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) throws IOException {
        AVL tree = new AVL();
        double insert_time=0.0,delete_time=0.0,find_time=0.0,traverse_time=0.0;
        int insert_cnt=0,delete_cnt=0,find_cnt=0,traverse_cnt=0;
        long start,end;
        File file=new File("AVL/out_avl.txt");
        PrintStream s=new PrintStream(file);
        System.setOut(s);
        BufferedReader br=new BufferedReader(new FileReader("AVL/in.txt"));
        while (true){
            String line=br.readLine();
            if (line==null) break;
            String[] lines=line.split(" ");
            if(lines[0].equals("F")){
                int val=Integer.parseInt(lines[1]);
                start=System.nanoTime();
                Node node=tree.find(tree.root,val);
                end=System.nanoTime();
                find_time+=(end-start);
                find_cnt++;
                if(node==null) System.out.println("not found");
                else System.out.println("found");
            } else if (lines[0].equals("I")) {
                int val=Integer.parseInt(lines[1]);
                start=System.nanoTime();
                tree.root=tree.insert(tree.root,val);
                end=System.nanoTime();
                insert_time+=end-start;
                insert_cnt++;
                tree.print_tree(tree.root);
                System.out.println();
            } else if (lines[0].equals("D")) {
                int val=Integer.parseInt(lines[1]);
                start=System.nanoTime();
                tree.root=tree.delete_help(tree.root,val);
                end=System.nanoTime();
                delete_time+=end-start;
                delete_cnt++;
                tree.print_tree(tree.root);
                System.out.println();
            }
            else{
                start=System.nanoTime();
                ArrayList<Integer> nodes=tree.print_in_order(tree.root);
                for(Integer node:nodes){
                    System.out.print(node+" ");
                }
                System.out.println();
                end=System.nanoTime();
                traverse_time+=end-start;
                traverse_cnt++;
            }
        }
        br.close();
        BufferedWriter bw=new BufferedWriter(new FileWriter("AVL/report_avl.txt"));
        bw.write("operation time(ms)\n");
        bw.write("insert: "+insert_time*1000000/insert_cnt+"\n");
        bw.write("delete: "+delete_time*1000000/delete_cnt+"\n");
        bw.write("search: "+find_time*1000000/find_cnt+"\n");
        bw.write("trav: "+traverse_time*1000000/traverse_cnt+"\n");
        bw.write("total: "+(insert_time+delete_time+find_time+traverse_time)*1000000);
        bw.close();
    }
}

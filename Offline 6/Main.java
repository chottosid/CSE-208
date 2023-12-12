package BinHeap;

import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br=new BufferedReader(new FileReader("BinHeap/input.txt"));
        System.setOut(new PrintStream(new File("BinHeap/output.txt")));
        Heap heap=new Heap();
        while (true){
            String line=br.readLine();
            if(line==null) break;
            String[] words=line.split(" ");
            if(words[0].equals("I")){
                heap.insert(Integer.parseInt(words[1]));
            } else if (words[0].equals("P")) {
                heap.print();
            } else if (words[0].equals("F")) {
                if(heap.find_min()==null){
                    System.out.println("Heap Empty");
                }
                else System.out.println("Find-Min returned "+heap.find_min().data);
            }else if (words[0].equals("E")) {
                System.out.println("Extract-Min returned "+heap.extract_min());
            } else if (words[0].equals("U")) {
                Heap new_heap = new Heap();
                for (int i = 1; i < words.length; i++) {
                    new_heap.insert(Integer.parseInt(words[i]));
                }
                heap = heap.bin_union(heap, new_heap);
            }
        }
        br.close();
    }
}

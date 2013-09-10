public class Insertion {  
    public static void insertionSort(Comparable []data){  
        for(int index=1;index<data.length;index++){  
            Comparable key = data[index];  
            int position = index;  
            //shift larger values to the right  
            while(position>0&&data[position-1].compareTo(key)>0){  
                data[position] = data[position-1];  
                position--;  
            }  
            data[position]=key;  
        }     
    }  
    public static void main(String []args){  
        Comparable []c={4,9,23,1,45,27,5,2};  
        insertionSort(c);  
        for(int i=0;i<c.length;i++)  
            System.out.println("²åÈëÅÅÐò£º"+c[i]);  
    }  
}
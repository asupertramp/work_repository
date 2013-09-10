import java.util.*;
public class QuickSort{
	public static void main(String[] args){
		int[] arr={8,7,9,3,6,1,5,4,2,3};
		quickSort(arr,0,arr.length-1);
		print(arr);
	}
	private static void quickSort(int[] arr,int beg,int end){
		if(beg<end){
			//int q=partion(arr,beg,end);
			int q=randomPartion(arr,beg,end);
			quickSort(arr,beg,q-1);
			quickSort(arr,q+1,end);
		}
	}
	private  static int partion(int[] arr,int beg,int end){
		int part=arr[end],temp;
		int i=beg-1;
		for(int j=beg;j<end;j++){
			if(arr[j]<=part){
				i++;
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
		arr[end]=arr[i+1];
		arr[i+1]=part;
		return i+1;
	}
	private static int randomPartion(int[] arr,int beg,int end){
		Random rad=new Random();
		int i=beg+rad.nextInt(end-beg+1);
		int temp=arr[end];
		arr[end]=arr[i];
		arr[i]=temp;
		return partion(arr,beg,end);
	}
	private static void print(int[] arr){
		for(int i=0;i<arr.length;i++)
			System.out.print(arr[i]+",");
	}
}
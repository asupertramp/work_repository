import java.util.*;
public class StackTester{
	public static void main(String[] args) throws Exception{
		Stack s=new Stack();
		Scanner scan=new Scanner(System.in);
		while(true){
			System.out.println("����pop��ջ������push��ջ,����exit�˳�");
			String cmd=scan.next();
			if(cmd.equals("pop")){
				System.out.println(s.pop());
			}
			else if(cmd.equals("push")){
				while(scan.hasNextInt()){
					int val=scan.nextInt();
					if (s.push(val))
						System.out.printf("push %d successfully\n",val);
					else
						System.out.printf("push  %d failed\n",val);
				}
			}
			else if(cmd.equals("exit")) break;
		}
	}
}
class Stack{
	public Stack(){
		stackArray=new Object[STACKLENGTH];
		top=-1;
	}
	public Object pop() throws Exception{
		if(isEmpty())
			throw new Exception("ջ�ѿ�");
		else
			return stackArray[top--];
	}
	private boolean isEmpty(){
		return top==-1;
	}
	private boolean isFull(){
		return top==stackArray.length-1;
	}
	public boolean push(Object val){
		if(isFull()){
			return false;
		}
		else{
			stackArray[++top]=val;
			return true;
		}
	}
	private Object[] stackArray; 
	private int top;
	private final int STACKLENGTH=1024;
}
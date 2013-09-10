
public class Test{
	public static void main(String[] args){
		LinkedList<Integer> l=new LinkedList();
		l.insert(1);
		l.insert(45);
		l.insert(3);
		l.insert(67);
		l.insert(23);
		l.traverse();
		l.delete(3);
		l.traverse();
		System.out.println("the 4th:"+l.get(3));
	}
}


class LinkedList<E>{
	
	public LinkedList(){
		this.head=null;
		size=0;
	}
	public LinkedList(E e){
		Node<E> n=new Node<E>(e);
		this.head=n;
		size=1;
	}
	
	public void insert(E e){
		Node<E> n=new Node<E>(e);
		if(head==null)
			head=n;
		else{
			n.next=head;
			head.previous=n;
			head=n;
		}
		size++;
	}
	public boolean delete(E e){
		Node<E> n=search(e);
		if(n==null)
			return false;
		else{
			if(n.previous==null)
				head=n.next;
			else
				n.previous.next=n.next;
			if(n.next!=null)
				n.next.previous=n.previous;
			size--;
			return true;
		}
	}
	
	public void clear(){
		Node<E> t=head;
		while(t!=null){
			Node<E> e=t.next;
			t.previous=null;
			t.next=null;
			t=e;			
		}
		size=0;
	}
	public int indexOf(E e){
		int index=0;
		for(Node<E> n=head;n!=null;n=n.next){
			if(n.element.equals(e))
				return index;
			index++;
		}
		return -1;
	}
	
	public boolean contains(E e){
		return indexOf(e)!=-1;
	}
	
	public E get(int index){
		if(index<0||index>size){
			throw new IndexOutOfBoundsException("Index: "+index+
                                                ", Size: "+size);
		}
		int i;
		Node<E> n;
		for(n=head,i=0;i<index;n=n.next,i++)
			;
		return n.element;
		
	}
	
	public Node<E> search(E e){
		Node<E> t=head;
		while(t!=null){
			if(t.element==e){
				return t;
			}
			t=t.next;
		}
		return null;
	}
	public void traverse(){
		Node<E> t=head;
		while(t!=null){
			System.out.println(t.toString());
			t=t.next;
		}
	}
	public int getSize(){
		return this.size;
	}
	private Node<E> head;
	private int size;
	private static class Node<E>{
		E element;
		Node<E> previous;
		Node<E> next;
		Node(E e){
			this.element=e;
			this.previous=null;
			this.next=null;
		}
		Node(E e,Node<E> previous,Node<E> next){
			this.element=e;
			this.previous=previous;
			this.next=next;
		}
		public String toString(){
			return this.element+"";
		}
	}
}
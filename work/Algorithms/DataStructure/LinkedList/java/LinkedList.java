package LinkedList.java;
public class LinkedList<E>{
	
	public LinkedList<E>(){
		this.head=null;
	}
	public LinkedList<E>(E e){
		Node<E> n=new Node<E>(e);
		this.head=n;
	}
	
	public void insert(E e){
		Node<E> n=new Node<E>(e);
		if(head==null)
			head=n;
		else{
			n.next=head;
			head.privious=n;
			n=head;
		}
	}
	public boolean delete(E£å){
		Node<E> n=search(e);
		if(n==null)
			return false;
		else{
			n.previous.next=n.next;
			n.next.previous=n.previous;
		}
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
	public void tranverse(){
		Node<E> t=head;
		while(t!=null){
			System.out.println(t.toString());
			t=t.next;
		}
	}
	
	Node<E> head;
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
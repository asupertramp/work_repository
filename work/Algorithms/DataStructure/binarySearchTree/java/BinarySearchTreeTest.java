
public class BinarySearchTreeTest{
	public static void main(String[] args){
		BinaryTree<Integer> bt=new BinaryTree<Integer>();
		bt.insert(10);
		bt.insert(7);
		bt.insert(1);
		bt.insert(2);
		bt.insert(6);
		bt.insert(3);
		bt.inorderWalk(bt.root);
		//bt.search(bt.root,2);
		bt.delete(6);
		bt.delete(10);
		bt.inorderWalk(bt.root);
	}
}

class BinaryTree<E extends Comparable>{
	public BinaryTree(){
		root=null;
	}
	public Node<E> search(Node<E> node,E e){
		if(node==null||node.element==e){
			return node;
		}
		if(node.element.compareTo(e)>0)
			return search(node.left,e);
		else
			return search(node.right,e);
	}
	public void insert( E e){
		Node<E> node=new Node <E>(e);
		Node<E> y=null;
		Node<E> x=root;
		while(x!=null){
			y=x;
			if(x.element.compareTo(node.element)>0)
				x=x.left;
			else
				x=x.right;
		}
		node.parent=y;
		if(y==null){
			root=node;
		}
		else if(node.element.compareTo(y.element)>0)
			y.right=node;
		else
			y.left=node;
	}
	public void inorderWalk(Node<E> node){
		if(node!=null){
			inorderWalk(node.left);
			System.out.println(node.element);
			inorderWalk(node.right);
		}
	}
	
	public boolean delete(E e){
		Node<E> n=search(root,e);
		if(n==null){
			System.out.println("can't find the element");
			return false;
		}
		Node<E> x,y;
		if(n.left==null||n.right==null)
			y=n;
		else
			y=successor(n);
			
		if(y.left!=null)
			x=y.left;
		else
			x=y.right;
		if(x!=null)
			x.parent=y.parent;
		if(y.parent==null)
			root=x;
		else if(y==y.parent.left)
			y.parent.left=x;
		else
			y.parent.right=x;
		if(y!=n)
			n.element=y.element;
		return true;
		
	}
	public Node<E> successor(Node<E> node){
			if(node.right!=null)
				return minimum(node.right);
			else{
				Node<E> y=node.parent;
				while(y!=null&&y.right==node){
					node=y;
					y=y.parent;
				}
				return y;
			}
	}
	public Node<E> predecessor(Node<E> node){
		if(node.left!=null)
			return maximum(node.left);
		else{
			Node<E> y=node.parent;
			while(y!=null&&y.left==node){
				node=y;
				y=y.parent;
			}
			return y;
		}
	}
	
	public Node<E> maximum(Node<E> node){
		if(node.right==null)
			return node;
		return maximum(node.right);
	}
	
	public Node<E> minimum(Node<E> node){
		if(node.left==null)
			return node;
		return minimum(node.left);
	}
	
	private static class Node<E>{
		E element;
		Node parent;
		Node left;
		Node right;
		Node(E e){
			this.element=e;
			this.left=null;
			this.right=null;
			this.parent=null;
		}
		public String toString(){
			return  element+"";
		}
	}
	Node<E> root;
	
}
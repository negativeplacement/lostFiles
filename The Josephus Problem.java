import java.util.Iterator;
import java.util.Scanner;

/*
Problem : Implement a circular linked list with the provided code to represent the circle of soldiers and 
simulate the problem. Your program should use two parameters, n soldiers and k, where k is the 
number of counts. In other words, we successively remove the kth person from the list. 
 
The problem is considered solved when there are only two soldiers left.

In your main() method, prompt the user for the number of soldiers, n, and how many to count, k. 
After each round, print out which soldier was killed and the resulting circle of surviving soldiers. 
Consider the problem solved when only two soldiers remain: Josephus and his companion. At this 
point, print out a message indicating which two solders survived. 
 
The Iterator should be implemented to allow wrapping around the CircularLinkedList. Be 
sure to create the iterator by calling the appropriate CircularLinkedList method after you 
added all the nodes to the list.
*/
class CircularLinkedList<E> implements Iterable<E> 
{
	Node<E> head;
	Node<E> tail;
	int size;

	// Implement a constructor
	public CircularLinkedList()
	{
	    head = null;
		tail = null;
		size = 0;
	}

	// Return Node<E> found at the specified index
	// Be sure to check for out of bounds cases
	private Node<E> getNode(int index ) throws IndexOutOfBoundsException
	{
	    if(index < 0 || index > size)
	    {
	        throw new IndexOutOfBoundsException();
	    }
	    else
	    {
	        Node positionNode = head;
	        for(int i = 0; i < index; i++)
	        {
	            positionNode = positionNode.next;
	        }
	        return positionNode;
	    }
	}

	// Add a node to the end of the list
	// HINT: Use the overloaded add method as a helper method
	public boolean add(E item){
	    Node<E> newNode = new Node<>(item);
	    tail.next = newNode;
	    tail = newNode;
	    size++;
		return true;
	}

	public void add(int index, E item){
	    Node <E> newNode = new Node<E>(item);
	    if(index < 0 || index > size + 1)// Out of bounds
	    {
	        throw new IndexOutOfBoundsException();
	    }
	    else if(size == 0) // Adding an element to an empty list
	    {
	        newNode.next = newNode;
			head = newNode;
			tail = newNode;
	    }
	    else if(index == 0) // Adding an element to the front
	    {
	        newNode.next = head;
			tail.next = newNode;
	        head = newNode;
	    }
	    else if(index - 1 == size) // Adding an element to the end
	    {
	        tail.next = newNode;
			newNode.next = head;
	        tail = newNode;
	    }
	    else // Adding an element to the middle.
	    {
			Node<E> current = getNode(index);
	        Node<E> temp = current.next;
	        current.next = new Node <>(item);
	        (current.next).next = temp;
	    }
	    size++; 
	}
	
	public E remove(int index){
	    if(index < 0 || index > size + 1) // Out of bounds
	    {
	        throw new IndexOutOfBoundsException();
	    }
		else if(size == 1)
		{
			head = null;
			tail = null;
		}
	    else if(index == 0) // Removing the first element in the list
	    {
	        head = head.next;
			tail.next = head;
	    }
	    else if(index == size - 1) // Removing the last element in the list
	    {
			Node<E> current = getNode(index);
			tail = current;
			tail.next = head;
	    }
		else // Removing an element in the middle
		{
			Node<E> previous = getNode(index - 1);
			Node<E> current = getNode(index + 1);
			previous.next = current;
		}
		size--;
		return null;
	}

	public String toString(){
		Node<E> myNode = head;
		StringBuilder result = new StringBuilder();
		if(size == 0) // Empty List
		{
			return "";
		}
		if(size == 1) // Single Element List
		{
			return head.item.toString();
		}
		for (int i = 1; i <= size; i++) // while(myNode != tail) // Multi-Element List
		{
			result.append(myNode.item);
			result.append(" ==> ");
			myNode = myNode.next;
		}
		return result.toString();
	}
	
	public int size(){
	    return size;
	}
	
	public Iterator<E> iterator(){
		return new ListIterator<E>();
	}
	
	// This class is not static because it needs to reference its parent class
	private class ListIterator<E> implements Iterator<E>{
		Node<E> nextItem;
		Node<E> prev;
		int index;
		
		@SuppressWarnings("unchecked")
		// Creates a new iterator that starts at the head of the list
		public ListIterator(){
			nextItem = (Node<E>) head;
			index = 0;
		}

		// Returns true if there is a next node
		public boolean hasNext(){
			return (nextItem != null);
		}
		
		// Advances the iterator to the next item
		// Should wrap back around to the head
		public E next(){
			prev = nextItem;
			nextItem = nextItem.next;
			index = (index + 1) % size;
			return prev.item;
		}
		
		// Remove the last node visted by the .next() call
		// For example, if we had just created an iterator,
		// the following calls would remove the item at index 1 (the second person in the ring)
		// next() next() remove()
		// Use CircularLinkedList.this to reference the CircularLinkedList parent class
		public void remove(){
			int thisPosition = index;
			if(nextItem == head){
				thisPosition = size - 1;
			} else{
				if(index != 0){
					thisPosition = index - 1;
				}
				index--;
			}
			CircularLinkedList.this.remove(thisPosition);
		}
	}
	
	// The Node class
	private static class Node<E>{
		E item;
		Node<E> next;
		public Node(E item){
			this.item = item;
		}
		
	}
	public static void main(String[] args){
	    int n, k;
	    Scanner readinput = new Scanner(System.in);
		System.out.print("How many soliders do you have: ");
		n = readinput.nextInt();
		System.out.print("What is the count: ");
		k = readinput.nextInt();
		CircularLinkedList newList = new CircularLinkedList();
		for(int i = 1; i <= n; i++){
			newList.add(i, i);
		}
		System.out.println("\n");
		System.out.print(newList.toString());
		System.out.println("\n");

		Iterator<Integer> iterator = newList.iterator();
		while (iterator.hasNext() && newList.size > 2){
			for (int i = 0; i < k; i++){
				iterator.next();
			}
			iterator.remove();
			System.out.print(newList.toString());
			System.out.println("\n");
		}
	}
}

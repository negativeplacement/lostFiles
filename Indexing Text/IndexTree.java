package index;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;


// Your class. Notice how it has no generics.
// This is because we use generics when we have no idea what kind of data we are getting
// Here we know we are getting two pieces of data:  a string and a line number
public class IndexTree {

	// This is your root 
	// again, your root does not use generics because you know your nodes
	// hold strings, an int, and a list of integers
	private IndexNode root;
	
	// Make your constructor
	// It doesn't need to do anything
	IndexTree()
	{
		root = null;
	}
	// complete the methods below
	
	// this is your wrapper method
	// it takes in two pieces of data rather than one
	// call your recursive add method
	public void add(String word, int lineNumber)
	{
		root = add(root, word, lineNumber);
	}
	// your recursive method for add
	// Think about how this is slightly different the the regular add method
	// When you add the word to the index, if it already exists, 
	// you want to  add it to the IndexNode that already exists
	// otherwise make a new indexNode
	private IndexNode add(IndexNode root, String word, int lineNumber)
	{
		if(root == null)
		{
			root = new IndexNode(word, lineNumber);
			return root;
		}
		else if(word.compareTo(root.word) > 0)
		{
			root.right = add(root.right, word, lineNumber);
		}
		else if(word.compareTo(root.word) < 0)
		{
			root.left = add(root.left, word, lineNumber);
		}
		else if(word.compareTo(root.word) == 0)
		{
			root.trackOccurence(lineNumber);
		}
		return root;
	}
	
	// returns true if the word is in the index
	public boolean contains(String word)
	{
		if(root == null)
		{
			return false;
		}
		else if(word.compareTo(root.word) > 0)
		{
			return contains(root.right, word);
		}
		else if(word.compareTo(root.word) < 0)
		{
			return contains(root.left, word);
		}
		else if(word.compareTo(root.word) == 0)
		{
			return true;
		}
		return false;
	}
	
	// call your recursive method
	// use book as guide
	public void delete(String word)
	{
		root = delete(root, word);
	}
	
	// your recursive case
	// remove the word and all the entries for the word
	// This should be no different than the regular technique.
	private IndexNode delete(IndexNode root, String word)
	{
		if(root == null)
		{
			return null;
		}
		else if(word.compareTo(root.word) > 0)
		{
			root.right = delete(root.right, word);
		}
		else if(word.compareTo(root.word) < 0)
		{
			root.left = delete(root.left, word);
		}
		else if(word.compareTo(root.word) == 0)
		{
			if(root.left == null && root.right == null)
			{
				return null;
			}
			else if(root.left != null && root.right != null)
			{
				IndexNode thisNode = root.left;
				while(thisNode.right != null)
				{
					thisNode = thisNode.right;
				}
				root.word = thisNode.word;
				root.occurences = thisNode.occurences;
				root.list = thisNode.list;
				root.right = delete(root.left, root.word);
				return root;
			}
			else if(root.right == null)
			{
				return root.left;
			}
			else if(root.left == null)
			{
				return root.right;
			}
			return root;
		}
		return root;
	}
	
	// prints all the words in the index in inorder order
	// To successfully print it out
	// this should print out each word followed by the number of occurrences and the list of all occurrences
	// each word and its data gets its own line
	public void printIndex()
	{
		printIndex(root);
	}
	public void printIndex(IndexNode thisRoot)
	{
		if(thisRoot == null)
		{
			return;
		}
		else
		{
			System.out.println(thisRoot.toString());
		}
		printIndex(thisRoot.left);
		printIndex(thisRoot.right);
	}
	
	public static void main(String[] args)
	{
		IndexTree index = new IndexTree();
		
		// add all the words to the tree
		try
		{
			Scanner readFile = new Scanner(new File("shakespeare.txt"));
			int thisLine = 1;		
			while(readFile.hasNextLine())
			{
				String getLine = readFile.nextLine(); //Get a line
				String getWord[] = getLine.split("\\s+"); // Split each string in the line and add it to the array individually
				for(String thisWord : getWord)
				{
					thisWord = thisWord.replaceAll("[^a-zA-Z0-9]", ""); // Replcae a sepcial characters in the string
					index.add(thisWord, thisLine);
				}
				thisLine++;
			}
		}
		catch(FileNotFoundException thisException) // Use try catch because of unhandled exception type FileNotFoundException 
		{
			thisException.printStackTrace();
		}
		// print out the index
		index.printIndex();
		// test removing a word from the index
		index.delete("yourself");
		index.delete("zeal");
		index.printIndex();
	}
}

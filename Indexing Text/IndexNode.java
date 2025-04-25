package index;

import java.util.List;
import java.util.ArrayList;

public class IndexNode  {

	String word;
	int occurences;
	List<Integer> list;
	
	IndexNode left;
	IndexNode right;
	
	
	// Constructors
	// Constructor should take in a word and a line number
	// it should initialize the list and set occurrences to 1
	IndexNode(String thisWord, int thisLine)
	{
		this.word = thisWord;
		list = new ArrayList<>();
		list.add(thisLine); // Adding the first line
		occurences = 1;
	}

	// Complete This
	// return the word, the number of occurrences, and the lines it appears on.
	// string must be one line

	void trackOccurence(int thisLine)
	{
		occurences++;
		list.add(thisLine);
	}
	
	public String toString()
	{
		return word + " appears " + occurences + " time(s) in line(s) " + list;
	}
	
	
	
}

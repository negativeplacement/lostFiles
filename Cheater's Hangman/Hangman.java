import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;

public class Hangman 
{
    public static void main(String[] args)
    {
        HashMap<String, Integer> eachWord = new HashMap<>(); // Obtain each word from the dictionary txt
        Set<String> selectionSet = new HashSet<>(); // Contain set with the most possible words based on user input to select from
        String hiddenWord;
        try 
        {
            Scanner readFile = new Scanner(new File("dictionary.txt"));
            while(readFile.hasNextLine())
            {
                String getWord = readFile.nextLine();
                getWord.toLowerCase(); // To prevent any invalid user input
                eachWord.put(getWord, getWord.length()); // Each word is its own key identifier, with its length as the value
            }
        } 
        catch (FileNotFoundException thisException) 
        {
            thisException.printStackTrace();
        }
        Scanner getInput = new Scanner(System.in);
        while(true)
        {
            int getSize, getGuesses;
            while(true)
            {
                System.out.print("Enter the size of the word: ");
                getSize = getInput.nextInt();
                if(eachWord.containsValue(getSize)) 
                {
                    break;
                }
                else
                {
                    System.out.println("The dictionary doesnt contain a word of that length");
                }
            }
            Set<String> checkWord = new HashSet<>();
            for(Map.Entry<String, Integer> setWords : eachWord.entrySet())
            {
                if(setWords.getValue() == getSize)
                {
                    checkWord.add(setWords.getKey().toLowerCase());
                }
            }
            System.out.print("Enter the number of wrong guesses: ");
            getGuesses = getInput.nextInt();
            int remaningGuesses = getGuesses;
            Set<Character> guessedLetter = new HashSet<>();
            String yourGuess = "";
            for (int placeChar = 0; placeChar < getSize; placeChar++) 
            {
                yourGuess += "_";
            }
            char userGuess;
            System.out.println("Word : " + yourGuess);
            System.out.println("Guesses: " + guessedLetter);
            System.out.println("You have " + remaningGuesses + " remaining guesses");
            System.out.println("Guess a letter of the word: ");
            userGuess = getInput.next().charAt(0);
            if(guessedLetter.contains(userGuess))
            {
                System.out.println("You already guessed " + userGuess);
            }
            else if(!guessedLetter.contains(userGuess))
            {
                guessedLetter.add(userGuess);
            }
            Map<String, Set<String>> groupThisWord = new HashMap<>();
            for (String thisWord : checkWord)
            {
                String charAt = "";
                for(char thisChar : thisWord.toCharArray())
                {
                    if(thisChar == userGuess)
                    {
                        charAt += thisChar;
                    }
                    else 
                    {
                        charAt += "_";
                    }
                }
                if(!groupThisWord.containsKey(charAt))
                {
                    groupThisWord.put(charAt, new HashSet<>());
                }
                groupThisWord.get(charAt).add(thisWord);
            }
            //System.out.println(groupThisWord);
            String keyLargestSet = "";
            int compareSet = 0;
            for(String findSet : groupThisWord.keySet())
            {
                if(groupThisWord.get(findSet).size() > compareSet)
                {
                    compareSet = groupThisWord.get(findSet).size();
                    keyLargestSet = findSet;
                }
            }
            selectionSet = groupThisWord.get(keyLargestSet);
            Random getRand = new Random();
            int thisRand = getRand.nextInt(selectionSet.size());
            while(true)
            {
                hiddenWord = selectionSet.toArray()[thisRand].toString();
                StringBuilder string = new StringBuilder(yourGuess); 
                remaningGuesses--;
                if(yourGuess.equals(hiddenWord))
                {
                    int contiuePlay;
                    System.out.println("Enter 1 to play again");
                    contiuePlay = getInput.nextInt();
                    if(contiuePlay == 1)
                    {
                        remaningGuesses = getGuesses;
                        break;
                    }
                }
                else if( remaningGuesses == 0 && !(yourGuess.equals(hiddenWord)))
                {
                    System.out.println("Youv'e ran out of guesses");
                    System.out.println("The word was " + hiddenWord);
                    int contiuePlay;
                    System.out.println("Enter 1 to play again");
                    contiuePlay = getInput.nextInt();
                    if(contiuePlay == 1)
                    {
                        remaningGuesses = getGuesses;
                        break;
                    }    
                }
                //System.out.println(hiddenWord); User cant see the hidden word
                for(int j = 0; j < getSize; j++)
                {
                    if(hiddenWord.charAt(j) == userGuess)
                    {
                        string.setCharAt(j, userGuess);
                    }
                }
                yourGuess = string.toString();
                System.out.println("Word : " + string);
                System.out.println("Guesses: " + guessedLetter);
                System.out.println("You have " + remaningGuesses + " remaining guesses");
                System.out.println("Guess a letter of the word: ");
                userGuess = getInput.next().charAt(0);
                if(guessedLetter.contains(userGuess))
                {
                    System.out.println("You already guessed " + userGuess);
                }
                else if(!guessedLetter.contains(userGuess))
                {
                    guessedLetter.add(userGuess);
                }
            }
        }
    }
}



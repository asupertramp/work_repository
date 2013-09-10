import java.util.*;
public class Permutation
{
	static ArrayList<String> getPermutation(String s)
	{
		ArrayList<String> per=new ArrayList<String>();
		if(s==null)
			return null;
		if(s.length()==0)
		{
			per.add("");
			return per;
		}
		char first=s.charAt(0);
		ArrayList<String> subPer=getPermutation(s.substring(1));
		for(String word:subPer)
		{
			for(int i=0;i<=word.length();++i)
			{
				per.add(insertChar(word,first,i));
			}
		}
		return per;
	}
	static String insertChar(String word,char c,int index)
	{
		String start=word.substring(0,index);
		String end=word.substring(index);
		return start+c+end;
	}
	
	public static void main(String[] arg)
	{
		String s="abcd";
		ArrayList<String> p=getPermutation(s);
		for(String w:p)
			System.out.println(w);
	}
}
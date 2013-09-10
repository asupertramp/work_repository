import java.util.*;
public class Subsets
{
	static ArrayList<ArrayList<Integer>> getSubsets(ArrayList<Integer> set,int index)
	{
		ArrayList<ArrayList<Integer>> allsubsets;
		if(set.size()==index)
		{
			allsubsets=new ArrayList<ArrayList<Integer>>();
			allsubsets.add(new ArrayList<Integer>());
		}
		else
		{
			allsubsets=getSubsets(set,index+1);
			int item=set.get(index);
			ArrayList<ArrayList<Integer>> more=new ArrayList<ArrayList<Integer>>();
			for(ArrayList<Integer> subset:allsubsets)
			{
				ArrayList<Integer> newsub=new ArrayList<Integer>();
				newsub.addAll(subset);
				newsub.add(item);
				more.add(newsub);
			}
			allsubsets.addAll(more);
		}
		return allsubsets;
	}
	static ArrayList<ArrayList<Integer>> getSubsets2(ArrayList<Integer> set)
	{
		int count=1<<set.size();
		ArrayList<ArrayList<Integer>> allsubsets=new ArrayList<ArrayList<Integer>>();
		for(int i=0;i<count;++i)
		{
			int k=i;
			int index=0;
			ArrayList<Integer> subset=new ArrayList<Integer>();
			while(k>0)
			{
				if((k&1)>0)
					subset.add(set.get(index));
				k>>=1;
				index++;
			}
			allsubsets.add(subset);
		}
		return allsubsets;
	}
	public static void main(String[] args)
	{
		ArrayList<Integer> set=new ArrayList<Integer>();
		for(int i=0;i<5;++i)
			set.add(i);
		ArrayList<ArrayList<Integer>> allsubs=getSubsets2(set);
		for(ArrayList<Integer> sub:allsubs)
		{
			for(int i=0;i<sub.size();++i)
				System.out.print(sub.get(i));
			System.out.println("");
		}
	}
}
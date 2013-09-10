import java.util.*;
public class MakeChange
{
	static int makeChange(int n ,int deom)
	{
		if(n<0) return 0;
		int next_deom=0;
		switch(deom)
		{
			case 25:
				next_deom=10;
				break;
			case 10:
				next_deom=5;
				break;
			case 5:
				next_deom=1;
				break;
			case 1:
				return 1;
		}
		int ways=0;
		for(int i=0;n-i*deom>=0;++i)
			ways+=makeChange(n-i*deom,next_deom);
		return ways;
	}
	static ArrayList<ArrayList<Integer>> makeChange2(int n,int deom)
	{
		if(n<0) return null;
		ArrayList<ArrayList<Integer>> ways=new ArrayList<ArrayList<Integer>>();
		int next_deom=0;
		switch(deom)
		{
			case 25:
				next_deom=10;
				break;
			case 10:
				next_deom=5;
				break;
			case 5:
				next_deom=1;
				break;
			case 1:
				ArrayList<Integer> al=new ArrayList<Integer>();
				for(int i=0;i<n;++i)
					al.add(1);
				ways.add(al);
				return ways;
		}
		for(int i=0;i*deom<=n;++i)
		{
			ArrayList<ArrayList<Integer>> sub=makeChange2(n-i*deom,next_deom);
			for(ArrayList<Integer> s:sub)
			{
				for(int j=0;j<i;++j)
					s.add(deom);
			}
			ways.addAll(sub);
		}
		return ways;
	}
	
	public static void main(String[] arg)
	{
		ArrayList<ArrayList<Integer>> ways=makeChange2(100,25);
		for(ArrayList<Integer> way:ways)
		{
			for(int i=0;i<way.size();++i)
			{
				System.out.print(way.get(i)+",");
			}
			System.out.println("");
			
		}
		System.out.println("ways:"+ways.size());
		System.out.println("ways:"+makeChange(100,25));
		char[] cs="edcba".toCharArray();
		Arrays.sort(cs);
		System.out.println(cs);
	}
	
}
/* hr.c - writes horizontal bar to standard output
 * (c) Copyright 2019-2020 Bartosz Mierzynski
 */

package hr;
//import java.lang.*

public class Hr /* extends Object */ {
	
	public static int get_columns() {
		String columns = "";
		int    n       = 0;

		try {
			columns = System.getenv("COLUMNS");
			n = Integer.parseInt(columns.trim());
		} catch(Exception e) {
			//e.printStackTrace();
			if(columns == null || columns.isEmpty())
				n = 80;
		}

		return n;
	}

	public static void hr(int n) {
			while(n-- > 0)
				System.out.print('#');
			System.out.print('\n');
	}

	public static void hr(int n, String s) {
		char[] arr = s.toCharArray();
		
		for(int i = 0; i < n; ++i)
			System.out.print(arr[i % s.length()]);
		System.out.print('\n');
	}

	public static void main(String[] args) {
		int n = get_columns();
		
		if(args.length == 0)
			hr(n);
		else
			for(String arg : args)
				hr(n, arg);
		
		//System.exit(0);
	}

}

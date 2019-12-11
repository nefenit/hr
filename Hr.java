public class Hr /* extends Object */ {

	public static void main(String[] args) {
		char[] argarr;
		String columns = "";
		int    cols    = 0;
	
		try {
			columns = System.getenv("COLUMNS");
			cols = Integer.parseInt(columns.trim());
		} catch(Exception e) {
			//e.printStackTrace();
			if(columns == null || columns.isEmpty())
				cols = 80;
		}

		if(args.length == 0) {
			while(cols-- > 0)
				System.out.print('#');
			System.out.print('\n');
		} else {
			for(String arg : args) {
				argarr = arg.toCharArray();
				for(int i = 0; i < cols; ++i)
					System.out.print(argarr[i%arg.length()]);
				System.out.print('\n');
			}
		}
		
		System.exit(0); //might be omitted
	}

}

#!/usr/bin/env lua
--[[ 
 hr - writes horizontal bar on terminal
 (c) Copyright 2019 Bartosz Mierzynski
]]

local function main()
	cols = tonumber(os.getenv("COLUMNS"));
	if(cols == nil)
	then
		cols = 80
	end
	if(#arg == 0)
	then
		while(cols > 0)
		do
			io.write('#')
			cols = cols - 1
		end
		io.write('\n')
	else
		for j = 1,#arg, 1
		do
			for i = 0, cols-1, 1
			do
				io.write(arg[j]:sub(i%#arg[j]+1,i%#arg[j]+1))
			end
			io.write('\n')
		end
	end
	return 0
end

os.exit(main())


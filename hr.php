#!/usr/bin/env php
<?php
/* hr.c - writes horizontal bar to standard output
 * (c) Copyright 2019 Bartosz Mierzynski
 */

if(extension_loaded("ncurses")) {
	$ncurses_session = ncurses_init();
	ncurses_getmaxyx(STDSCR, $height, $width);
	$cols = $width ?: 80;
	ncurses_end();
} else {
	$cols = 80;
}

if($argc < 2) {
	while($cols--)
		echo '#';
	echo "\n";
} else {
	array_shift($argv);
	foreach($argv as $arg) {
		$len = strlen($arg);
		for($i = 0; $i < $cols; ++$i)
			echo $arg[$i % $len];
		echo "\n";
	}
}
?>

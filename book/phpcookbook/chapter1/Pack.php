<?php
$books = array (
		array (
				'Elmer Gantry',
				'Sinclair Lewis',
				1927 
		),
		array (
				'The Scarlatti Inheritance',
				'Robert Ludlum',
				1971 
		),
		array (
				'The Parsifal Mosaic',
				'William Styron',
				1979 
		) 
);

foreach ( $books as $book ) {
	print pack ( 'A25A15A3', $book [0], $book [1], $book [2] );
	echo PHP_EOL;
}

foreach ( $books as $book ) {
	// 如果大于固定长度则截断，小于用.填充
	$title = str_pad ( substr ( $book [0], 0, 25 ), 25, '.' );
	$author = str_pad ( substr ( $book [1], 0, 15 ), 15, '.' );
	$year = str_pad ( substr ( $book [2], 0, 4 ), 4, '.' );
	print "$title$author$year" . PHP_EOL;
}
function fixed_width_substr($fields, $data) {
	$r = array ();
	for($i = 0, $j = count ( $data ); $i < $j; $i ++) {
		$line_pos = 0;
		foreach ( $fields as $field_name => $field_length ) {
			$r [$i] [$field_name] = rtrim ( substr ( $data [$i], $line_pos, $field_length ) );
			$line_pos += $field_length;
		}
	}
	return $r;
}

$book_fields = array (
		'title' => 25,
		'author' => 15,
		'publication_year' => 4 
);
$book = array (
		'Elmer GantryElmer GantryE Gantry Sinclai 1927',
		'Elmer GantryElmer GantryE Gantry Sinclai 1937',
		'Elmer GantryElmer GantryE Gantry Sinclai 1947' 
);
print_r ( fixed_width_substr ( $book_fields, $book ) );
print PHP_EOL;

function fixed_width_unpack($format='A25title/A15author/A4publication_year', $data)
{
	$r=[];
	for ($i = 0,$j=count($data); $i < $j; $i++) {
		$r[$i]=unpack($format, $data[$i]);
	}
	return $r;
}
print_r(fixed_width_unpack('A25title/A15author/A4publication_year',$book));
echo PHP_EOL;

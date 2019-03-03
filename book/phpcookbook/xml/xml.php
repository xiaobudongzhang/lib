<?php
header('Content-type:text/xml');
print '<?xml version="1.0"?>';
print "<shows>";

$shows=[
[
'name'=>'byz',
'channel'=>'abc'
]
];

foreach($shows as $show){
	       print "      <show>";
	       foreach($show as $tag=>$name){
		print "      <$tag>".htmlspecialchars($name)."</$tag>";
		}
		print "    </show>";
}

print "</shows>";
<?php


print_r(Locale::getDefault());

$messages = array ();
$messages ['en_US'] = array (
		'CART' => "You have {0,spellout} {0, plural,  =1 {item} other {items} } in your shopping cart." 
);
$messages ['fr_FR'] = array (
		'CART' => "Vous {0, plural, " . " =0 {n'avez pas d'articles} " . " =1 {avez un article} " . " other {avez {0,spellout} articles}} " . "dans votre panier." 
);


$fmts=[];
foreach (array_keys($messages) as $locale){
	$fmts[$locale]=new MessageFormatter($locale, $messages[$locale]['CART']);
}
//print_r($fmts);

foreach ($fmts as $locale=>$obj)
{
	print $obj->format([1]);	
	echo PHP_EOL;
}
>>>>>>> ba9706672ae4246e32ea874be309e48288911881

<?php
$words = array('Малина', 'Клубника', 'Огурец');

$collator=new Collator('ru_RU');
print_r($words);

$collator->sort($words);

print_r($words);
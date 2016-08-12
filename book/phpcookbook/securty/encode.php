<?php

//echo MCRYPT_BLOWFISH;;die;
$salt='xyz';
$id=1337;
//var_dump(mcrypt_list_algorithms());
//var_export(mcrypt_list_modes());
//echo hash_hmac('sha1',$id,$salt);

 $d=mcrypt_module_open('blowfish-compat','', 'ofb', '');
$iv=mcrypt_create_iv(
mcrypt_enc_get_iv_size($d),
MCRYPT_DEV_URANDOM
);

$en_data=mcrypt_encrypt(MCRYPT_BLOWFISH,'testme','testdata',MCRYPT_MODE_CBC,$iv);
echo $en_data;echo PHP_EOL;
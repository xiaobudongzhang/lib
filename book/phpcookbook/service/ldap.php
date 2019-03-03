<?php
$ds = ldap_connect('ldap.baidu.com') or die('d');
$bind=ldap_bind($ds);
var_dump($bind);
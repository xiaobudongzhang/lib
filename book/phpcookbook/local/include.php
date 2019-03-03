<?php
print_r(ini_get('include_path'));
echo PHP_EOL;
ini_set('include_path', "E:/www");
print_r(ini_get('include_path'));
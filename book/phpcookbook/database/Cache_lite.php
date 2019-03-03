<?php
require_once 'Cache/Lite.php';
$opts=[
    'cacheDir'=>'/tmp',
    'lifeTime'=>600	
    ];

new Cache_Lite($opts);
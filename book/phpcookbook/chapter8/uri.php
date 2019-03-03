<?php
//$body=file_get_contents('php://input');
//var_dump($body);
//http_response_code(202);
//print_r($_SERVER);
echo <<<HTML
<html>
<body onload="return false;">
<form id='redirectForm' method='POST' action='/done.html'>
<input type='hidden' name='status' value='complete'/>
<input type='hidden' name='id' value='0u812'/>
<input type='submit' value='Please Click Here To Continue'/>
</form>
</body>
</html>
HTML;
//virtual('d');

//print_r(get_browser());
var_export(filter_list());
var_dump(filter_has_var(INPUT_GET,'test'));
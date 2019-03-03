<?php
$str = <<<EOD
<html>me</html><body>me</body>
EOD;
echo tidy_repair_string($str);